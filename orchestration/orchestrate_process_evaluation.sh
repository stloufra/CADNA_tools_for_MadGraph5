#!/bin/bash

#########################
# Process Evaluation Orchestration Script
#########################
#
# WORKFLOW:
# Step 1: Copy P1_* directories to create P1_*_float versions
# Step 2: Serial compilation + immediate execution launch
#         - Compile double version
#         - Launch check_cpp.exe immediately (before next distclean!)
#         - Compile float version
#         - Launch check_cpp.exe immediately
#         - Repeat for all directories
#         CRITICAL: check_cpp.exe must launch right after compilation
#                   because the next make distclean will delete it!
# Step 3: Wait for all check_cpp.exe processes to complete
# Step 4: Compare double vs float results (parallel)
# Step 5: Run PROMISE analysis (parallel)
#
#########################

set -euo pipefail

#########################
# Configuration
#########################

# Maximum number of parallel check_cpp.exe processes
MAX_PARALLEL_CHECKS=8

# Maximum number of parallel analysis processes
MAX_PARALLEL_ANALYSIS=12

# Number of ITERATIONS
ITERATIONS=10000000
#ITERATIONS=10000

# CADNA toolbox path (set this to your actual path or pass as environment variable)
CADNA_TOOLBOX_PATH="${CADNA_TOOLBOX_PATH:-/path/to/cadna/toolbox}"

# CUDA_HOME setting for compilation
CUDA_HOME_VAL="${CUDA_HOME_VAL:-}"

#########################
# Global variables for process tracking
#########################

# Array to store all check_cpp.exe PIDs
CHECK_CPP_PIDS=()

# Variable to pass last launched PID from run_check_cpp to caller
LAST_CHECK_PID=0

#########################
# Working directory setup
#########################

# Get the work directory from argument or use current directory
if [ $# -ge 1 ]; then
    WORK_DIR="$1"
else
    WORK_DIR="."
fi

# Convert to absolute path - this must happen before any cd commands
# Save current directory first
SCRIPT_START_DIR="$(pwd)"

# Convert WORK_DIR to absolute path
if [[ "$WORK_DIR" = /* ]]; then
    # Already absolute
    WORK_DIR="$WORK_DIR"
else
    # Relative path - convert to absolute
    WORK_DIR="$(cd "$WORK_DIR" 2>/dev/null && pwd)" || {
        echo "ERROR: Cannot access directory: $1"
        exit 1
    }
fi

# Return to starting directory
cd "$SCRIPT_START_DIR"

# Verify WORK_DIR exists and is a directory
if [ ! -d "$WORK_DIR" ]; then
    echo "ERROR: Work directory does not exist: $WORK_DIR"
    exit 1
fi

#########################
# Color output
#########################
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

log_info() {
    echo -e "${BLUE}[INFO]${NC} $*"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $*"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $*"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $*"
}

#########################
# Step 1: Find and copy P1_* directories
#########################

step1_copy_directories() {
    log_info "Step 1: Finding and copying P1_* directories..."
    
    cd "$WORK_DIR"
    
    # Find all P1_* directories EXCLUDING _float versions
    local p1_dirs=($(find . -maxdepth 1 -type d -name "P1_*" ! -name "*_float" | sed 's|^\./||' | sort))
    
    if [ ${#p1_dirs[@]} -eq 0 ]; then
        log_error "No P1_* directories found!"
        exit 1
    fi
    
    log_info "Found ${#p1_dirs[@]} P1_* directories (excluding existing _float copies)"
    
    # Copy each directory with _float suffix
    for dir in "${p1_dirs[@]}"; do
        local float_dir="${dir}_float"
        
        if [ -d "$float_dir" ]; then
            log_warn "Directory $float_dir already exists, skipping copy"
        else
            log_info "Copying $dir -> $float_dir"
            cp -r "$dir" "$float_dir"
        fi
    done
    
    log_success "Step 1 completed"
}

#########################
# Step 2: Compile directories serially
#########################

compile_directory() {
    local dir="$1"
    local fptype="$2"
    local dir_type="$3"  # "double" or "float"
    local compile_status=0 
    
    log_info "Compiling $dir with FPTYPE=$fptype ($dir_type)"
    
    # Change to the directory (using absolute path from WORK_DIR)
    cd "$WORK_DIR/$dir"
    
    # Clean first (suppress normal output, log everything, show errors on failure)
    sleep 1
    make distclean > "distclean_${dir_type}.log" 2>&1
    local distclean_status=$?
    
    if [ $distclean_status -ne 0 ]; then
        log_warn "make distclean had issues for $dir"
        # Show only the error lines from the log
        if [ -s "distclean_${dir_type}.log" ]; then
            echo "Errors from distclean:"
            grep -i "error\|fatal" "distclean_${dir_type}.log" || cat "distclean_${dir_type}.log" | tail -20
        fi
    fi

    #symlink native_check_sa.py
    ln -sf "$CADNA_TOOLBOX_PATH/srcpy/native_check_sa.py"

    if python3 native_check_sa.py check_sa.cc; then
	    log_success "check_sa.cc transform successful for $dir"
    else
	    log_error "check_sa.cc failed for $dir"
	    compile_status=1
    fi
    
    # Compile
    if make -j12 \
        OPTFLAGS="-O3" \
        -f cudacpp.mk \
        FPTYPE="$fptype" \
        CUDA_HOME="$CUDA_HOME_VAL" \
        AVX=none \
        HASCURAND=hasNoCurand \
        USEOPENMP=1 \
        GTESTLIBS= \
        > "compile_${dir_type}.log" 2>&1; then
        log_success "Compilation successful for $dir ($dir_type)"
    else
        log_error "Compilation failed for $dir ($dir_type)"
        log_error "Check compile_${dir_type}.log for details"
        compile_status=1
    fi
    
    # CRITICAL: Return to WORK_DIR before exiting function
    cd "$WORK_DIR"
    
    return $compile_status
}

step2_compile_all() {
    log_info "Step 2: Compiling all directories serially and launching check_cpp.exe..."
    log_info "Note: check_cpp.exe must launch immediately after compilation"
    log_info "      because next distclean will delete the executable"
    
    cd "$WORK_DIR"
    
    local p1_dirs=($(find . -maxdepth 1 -type d -name "P1_*" ! -name "*_float" | sed 's|^\./||' | sort))
    
    local failed_dirs=()
    
    # Array to track all check_cpp.exe PIDs
    CHECK_CPP_PIDS=()
    
    for dir in "${p1_dirs[@]}"; do
        local float_dir="${dir}_float"
        
        # Compile double version
        if ! compile_directory "$dir" "d" "double"; then
            failed_dirs+=("$dir (double)")
        else
            # Launch check_cpp.exe immediately after successful compilation
            log_info "Launching check_cpp.exe for $dir (double) immediately..."
            run_check_cpp "$dir" "double"
            # Store the PID (run_check_cpp sets LAST_CHECK_PID)
            CHECK_CPP_PIDS+=($LAST_CHECK_PID)
        fi
        
        # Compile float version
        if [ -d "$float_dir" ]; then
            if ! compile_directory "$float_dir" "f" "float"; then
                failed_dirs+=("$float_dir (float)")
            else
                # Launch check_cpp.exe immediately after successful compilation
                log_info "Launching check_cpp.exe for $float_dir (float) immediately..."
                run_check_cpp "$float_dir" "float"
                # Store the PID
                CHECK_CPP_PIDS+=($LAST_CHECK_PID)
            fi
        fi
        
        # Control parallel execution - wait if we hit the limit
        # Check how many check_cpp.exe processes are currently running
        while [ $(count_running_check_cpp) -ge "$MAX_PARALLEL_CHECKS" ]; do
            local running=$(count_running_check_cpp)
            log_info "Parallel limit reached ($running/$MAX_PARALLEL_CHECKS running), waiting..."
            sleep 5
        done
    done
    
    if [ ${#failed_dirs[@]} -gt 0 ]; then
        log_error "Compilation failed for the following directories:"
        printf '%s\n' "${failed_dirs[@]}"
        exit 1
    fi
    
    log_success "Step 2 completed - all compilations successful"
    log_info "All check_cpp.exe processes have been launched in background"
    log_info "Total processes launched: ${#CHECK_CPP_PIDS[@]}"
}

#########################
# Step 3: Run check_cpp.exe in parallel
#########################

run_check_cpp() {
    local dir="$1"
    local fptype_name="$2"  # "double" or "float"
    local dir_name="$(basename "$dir")"
    
    cd "$WORK_DIR/$dir"
    
    local output_file="${fptype_name}_${dir_name}.out"
    
    log_info "Running check_cpp.exe in $dir -> $output_file"
    
    # Use nohup instead of setsid for better portability and job control
    # Also redirect stdin from /dev/null and detach properly
    nohup ./check_cpp.exe -p -v ${ITERATIONS} 1 1 \
        > "$output_file" 2>&1 \
        < /dev/null &
    
    local pid=$!
    
    # Store PID in global variable for caller to track
    LAST_CHECK_PID=$pid
    
    echo "$pid" > "${output_file}.pid"
    
    log_info "Started check_cpp.exe for $dir (PID: $pid)"
    
    # Return to WORK_DIR
    cd "$WORK_DIR"
    
    return 0
}

wait_for_running_jobs() {
    local max_jobs="$1"
    
    while [ $(jobs -r | wc -l) -ge "$max_jobs" ]; do
        sleep 2
    done
}

# Alternative: Check specific PIDs from our tracking array
count_running_check_cpp() {
    local count=0
    for pid in "${CHECK_CPP_PIDS[@]}"; do
        if ps -p "$pid" > /dev/null 2>&1; then
            ((count++))
        fi
    done
    echo $count
}

step3_run_all_checks() {
    log_info "Step 3: Waiting for all check_cpp.exe processes to complete..."
    log_info "Note: All processes were already launched in Step 2"
    
    cd "$WORK_DIR"
    
    if [ ${#CHECK_CPP_PIDS[@]} -eq 0 ]; then
        log_error "No check_cpp.exe PIDs to wait for!"
        log_error "This shouldn't happen - check Step 2"
        exit 1
    fi
    
    log_info "Tracking ${#CHECK_CPP_PIDS[@]} check_cpp.exe processes"
    log_info "PIDs: ${CHECK_CPP_PIDS[*]}"
    
    # Give processes a moment to start up
    log_info "Waiting 2 seconds for processes to initialize..."
    sleep 2
    
    # Verify processes are actually running
    log_info "Verifying processes are running..."
    local initially_running=0
    for pid in "${CHECK_CPP_PIDS[@]}"; do
        if ps -p "$pid" > /dev/null 2>&1; then
            initially_running=$((initially_running + 1))
        else
            log_warn "PID $pid is not running (may have finished already or failed to start)"
        fi
    done
    
    if [ $initially_running -eq 0 ]; then
        log_error "None of the check_cpp.exe processes are running!"
        log_error "They may have all completed instantly (unlikely) or failed to start"
        log_error "Check the output files for errors:"
        ls -lh "$WORK_DIR"/P1_*/*.out 2>/dev/null | tail -20
        exit 1
    fi
    
    log_info "Initially running: $initially_running/${#CHECK_CPP_PIDS[@]} processes"
    
    # Poll until all processes complete
    local max_iterations=7200  # 10 hours max (at 5 second intervals)
    local iteration=0
    local last_count=-1
    
    while [ $iteration -lt $max_iterations ]; do
        local running_count=0
        local running_pids=()
        
        for pid in "${CHECK_CPP_PIDS[@]}"; do
            # Check if PID is running - use || true to prevent set -e from exiting
            if ps -p "$pid" > /dev/null 2>&1 || true; then
                if ps -p "$pid" > /dev/null 2>&1; then
                    running_pids+=($pid)
                    running_count=$((running_count + 1))
                fi
            fi
        done
        
        if [ $running_count -eq 0 ]; then
            log_success "All check_cpp.exe processes have completed!"
            break
        fi
        
        # Only log if count changed or every minute
        if [ $running_count -ne $last_count ] || [ $((iteration % 12)) -eq 0 ]; then
            local completed=$((${#CHECK_CPP_PIDS[@]} - running_count))
            log_info "Progress: $completed/${#CHECK_CPP_PIDS[@]} completed, $running_count still running"
            if [ $running_count -le 5 ]; then
                log_info "Remaining PIDs: ${running_pids[*]}"
            fi
            last_count=$running_count
        fi
        
        sleep 5
        iteration=$((iteration + 1))
    done
    
    # Final check
    local still_running=0
    for pid in "${CHECK_CPP_PIDS[@]}"; do
        if ps -p "$pid" > /dev/null 2>&1; then
            still_running=$((still_running + 1))
            log_error "PID $pid still running after timeout!"
        fi
    done
    
    if [ $still_running -gt 0 ]; then
        log_error "$still_running processes still running - may be stuck!"
        log_error "Check output files and consider killing stuck processes"
        exit 1
    fi
    
    log_success "Step 3 completed - all check_cpp.exe runs finished"
    log_success "Total processes completed: ${#CHECK_CPP_PIDS[@]}"
}

#########################
# Step 4: Compare double vs float results
#########################

compare_results() {
    local double_dir="$1"
    local dir_name="$(basename "$double_dir")"
    local float_dir="${double_dir}_float"
    
    log_info "Comparing results for $dir_name..."
    
    cd "$WORK_DIR/$double_dir"
    
    # Create symlink to postprocess script
    if [ ! -L "native_output_postprocess.py" ]; then
        ln -sf "$CADNA_TOOLBOX_PATH/native_output_postprocess.py" .
    fi
    
    local double_output="double_${dir_name}.out"
    local float_output="${WORK_DIR}/${float_dir}/float_${dir_name}_float.out"
    local comparison_output="gdb_run_output_float-O3_1.out"
    
    # Check if input files exist
    if [ ! -f "$double_output" ]; then
        log_error "Double output file not found: $double_output"
        return 1
    fi
    
    if [ ! -f "$float_output" ]; then
	#echo From $(pwd)
	#echo $dir_name
	#echo $float_dir
        log_error "Float output file not found: $float_output"
        return 1
    fi

    if [ -f "$comparison_output" ]; then
	log_warn "Deleting previous comparison output in: $dir"
	rm $comparison_output
    fi

    # Run comparison
    local comparison_status=0
    if python3 native_output_postprocess.py \
        "$float_output" \
        "$double_output" \
        "$comparison_output" \
        > "comparison_${dir_name}.log" 2>&1; then
        log_success "Comparison completed for $dir_name"
        comparison_status=0


    else
        log_error "Comparison failed for $dir_name"
	echo python3 native_output_postprocess.py "$float_output" "$double_output" "$comparison_output" 
        comparison_status=1
    fi
    
    # Return to WORK_DIR
    cd "$WORK_DIR"
    
    return $comparison_status
}

step4_compare_all() {
    log_info "Step 4: Comparing double vs float results (max $MAX_PARALLEL_ANALYSIS parallel)..."
    
    cd "$WORK_DIR"
    
    local p1_dirs=($(find . -maxdepth 1 -type d -name "P1_*" ! -name "*_float" | sed 's|^\./||' | sort))
    
    if [ ${#p1_dirs[@]} -eq 0 ]; then
        log_error "No P1_* directories found!"
        exit 1
    fi
    
    for dir in "${p1_dirs[@]}"; do
        wait_for_running_jobs "$MAX_PARALLEL_ANALYSIS"
        
        compare_results "$dir" &
    done
    
    log_info "Waiting for all comparisons to complete..."
    wait
    
    log_success "Step 4 completed - all comparisons finished"
}

#########################
# Step 5: Run PROMISE analysis
#########################

run_promise_analysis() {
    local double_dir="$1"
    local dir_name="$(basename "$double_dir")"
    
    log_info "Running PROMISE analysis for $dir_name..."
    
    cd "$WORK_DIR/$double_dir"
    
    # Create symlink to promiseAnalyse.py
    if [ ! -L "promiseAnalyse.py" ]; then
        ln -sf "$CADNA_TOOLBOX_PATH/boiler_plate/promiseAnalyse.py" .
    fi
    
    # Run analysis
    local analysis_status=0
    if python3 promiseAnalyse.py \
        > "promise_analysis_${dir_name}.log" 2>&1; then
        log_success "PROMISE analysis completed for $dir_name"
        analysis_status=0
    else
        log_error "PROMISE analysis failed for $dir_name"
        analysis_status=1
    fi
    
    # Return to WORK_DIR
    cd "$WORK_DIR"
    
    return $analysis_status
}

step5_promise_analysis() {
    log_info "Step 5: Running PROMISE analysis (max $MAX_PARALLEL_ANALYSIS parallel)..."
    
    cd "$WORK_DIR"
    
    local p1_dirs=($(find . -maxdepth 1 -type d -name "P1_*" ! -name "*_float" | sed 's|^\./||' | sort))
    
    if [ ${#p1_dirs[@]} -eq 0 ]; then
        log_error "No P1_* directories found!"
        exit 1
    fi
    
    for dir in "${p1_dirs[@]}"; do
        wait_for_running_jobs "$MAX_PARALLEL_ANALYSIS"
        
        run_promise_analysis "$dir" &
    done
    
    log_info "Waiting for all PROMISE analyses to complete..."
    wait
    
    log_success "Step 5 completed - all PROMISE analyses finished"
}

#########################
# Cleanup and signal handling
#########################

cleanup() {
    local exit_code=$?
    
    log_info "Cleanup initiated (exit code: $exit_code)"
    
    # Kill any remaining background jobs
    jobs -p | xargs -r kill 2>/dev/null || true
    
    # Update status file if it exists
    if [ -f "${WORK_DIR}/orchestration.status" ]; then
        if [ $exit_code -eq 0 ]; then
            echo "COMPLETED" > "${WORK_DIR}/orchestration.status"
        else
            echo "FAILED" > "${WORK_DIR}/orchestration.status"
        fi
    fi
    
    # Remove PID file
    [ -f "${WORK_DIR}/orchestration.pid" ] && rm -f "${WORK_DIR}/orchestration.pid"
    
    if [ $exit_code -eq 0 ]; then
        log_success "Cleanup complete"
    else
        log_error "Cleanup complete (script failed)"
    fi
}

trap cleanup EXIT

handle_interrupt() {
    log_warn "Received interrupt signal (SIGINT/SIGTERM)"
    log_warn "Cleaning up background processes..."
    exit 130
}

trap handle_interrupt SIGINT SIGTERM

#########################
# Main execution
#########################

main() {
    log_info "========================================="
    log_info "Process Evaluation Orchestration Started"
    log_info "========================================="
    log_info "Start time: $(date)"
    log_info "Working directory: $WORK_DIR"
    log_info "Max parallel checks: $MAX_PARALLEL_CHECKS"
    log_info "Max parallel analyses: $MAX_PARALLEL_ANALYSIS"
    log_info "CADNA toolbox path: $CADNA_TOOLBOX_PATH"
    log_info "PID: $$"
    
    # Verify CADNA_TOOLBOX_PATH exists
    if [ ! -d "$CADNA_TOOLBOX_PATH" ]; then
        log_error "CADNA_TOOLBOX_PATH does not exist: $CADNA_TOOLBOX_PATH"
        log_error "Please set the correct path via environment variable or edit the script"
        exit 1
    fi

    if grep "override FPTYPE" ../Source/make_opts > /dev/null ; then
	    log_warn "Removing override FPTYPE from make_opts"
	    sed '1{/^override FPTYPE/d;}' ../Source/make_opts > make_opts.tmp && mv make_opts.tmp ../Source/make_opts
    fi
    
    if ! promise > /dev/null ; then
	    log_error "PROMISE was not sourced please source"
	    exit 1
    fi
    # Verify P1_* directories exist in work directory
    log_info "Checking for P1_* directories in work directory..."
    cd "$WORK_DIR"
    
    local p1_check=($(find . -maxdepth 1 -type d -name "P1_*" ! -name "*_float" 2>/dev/null | sed 's|^\./||' | sort))
    
    if [ ${#p1_check[@]} -eq 0 ]; then
        log_error "========================================="
        log_error "No P1_* directories found!"
        log_error "========================================="
        log_error "Work directory: $WORK_DIR"
        log_error "Expected: Directories named P1_*"
        log_error ""
        log_error "Current directory contents:"
        ls -lah "$WORK_DIR" | head -30
        log_error ""
        log_error "Suggestions:"
        log_error "1. Check you're in the right directory"
        log_error "2. Ensure directories are named P1_* (case sensitive)"
        log_error "3. Try running with explicit path:"
        log_error "   ./orchestrate_process_evaluation.sh /full/path/to/work/dir"
        exit 1
    fi
    
    log_success "Found ${#p1_check[@]} P1_* directories to process"
    
    # Record start time
    local start_time=$(date +%s)
    
    # Execute all steps
    step1_copy_directories
    step2_compile_all
    step3_run_all_checks
    step4_compare_all
    step5_promise_analysis
    
    # Calculate duration
    local end_time=$(date +%s)
    local duration=$((end_time - start_time))
    local hours=$((duration / 3600))
    local minutes=$(((duration % 3600) / 60))
    local seconds=$((duration % 60))
    
    log_success "========================================="
    log_success "Process evaluation orchestration complete!"
    log_success "========================================="
    log_success "End time: $(date)"
    log_success "Total duration: ${hours}h ${minutes}m ${seconds}s"
}

# Run main function
main "$@"
