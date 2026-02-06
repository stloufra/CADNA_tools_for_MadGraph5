# PROMISE Analysis Orchestration Scripts

## Summary

Automation scripts for running PROMISE numerical precision analysis on MadGraph5 processes. Designed for NGT clusters with CERN infrastructure integration. Some components require adjustment for general use.

## Components

### 1. orchestrate_process_evaluation.sh

Automated workflow for precision analysis of MadGraph processes:

**Workflow:**
1. Copies all P1_* directories to P1_*_float variants
2. Serially compiles double (FPTYPE=d) and float (FPTYPE=f) versions for each directory
3. Immediately launches check_cpp.exe in background after each compilation
4. Waits for all processes to complete
5. Compares double vs float outputs and save only accuracy <3 ME and corresponding momenta
6. Runs PROMISE analysis on results (boilerplate creation, file transformation, casting insertion and export of FP_types, promise run)

**Key Implementation Details:**
- Modified check_sa.cc to output in scientific format with correct precision
- Serial compilation required due to make distclean conflicts between directories
- check_cpp.exe launched immediately after compilation to prevent deletion by subsequent distclean
- Parallel execution configurable (default: 20 parallel processes)
- PID tracking for reliable process monitoring
- Output validation handles fast-completing processes
- Email notifications on completion/failure

**Configuration:**
- CADNA_TOOLBOX_PATH: Path to CADNA tools (this repo)
- OUTPUT_PATH: Results destination
- MAX_PARALLEL_CHECKS: Parallel execution limit
- EMAIL_ENABLED: Enable notifications

### 2. batch_orchestration.sh

Sequential batch processing of multiple MadGraph input files:

**Workflow:**
1. Searches all files in __ins/ directory
2. For each file:
   - Runs mg5_aMC with the input file
   - Enters generated PROC_*/SubProcesses directory
   - Links and executes orchestration script
   - Monitors execution with step completion logging
   - Waits for orchestration to complete
   - Deletes process directory
   - Continues to next file

**Features:**
- Separate logging for mg5_aMC and orchestration steps
- Progress monitoring without log spam (only logs step completions)
- Error handling with summary reporting

**Usage:**
```bash
mkdir __ins
cp in_file __ins/.
./batch_orchestration.sh
```

### 3.  run_in_background.sh

Wrapper scripts for SSH-safe execution:

**run_in_background.sh:**
- Uses nohup for background execution
- Creates PID and log files
- Generates status checker script
- Fire-and-forget operation

Both wrappers ensure orchestration continues if SSH connection drops.

## CERN-Specific Dependencies

The following require CERN infrastructure and need adjustment for general use:
- Kerberos validation for email notifications
- lxplus.cern.ch SSH for email relay
- PROMISE environment validation

## Technical Notes

**Why Serial Compilation:**
make distclean removes shared build artifacts. Parallel compilation would cause race conditions where one process's distclean deletes files needed by another.

**Why Immediate Execution:**
After compiling check_cpp.exe, the next directory's make distclean will delete it. Launching immediately ensures the process is loaded into memory before deletion.

**Process Monitoring:**
Uses explicit PID array tracking with ps polling instead.

## Requirements

- MadGraph5_aMC@NLO
- CADNA toolbox
- PROMISE framework
- Python 3
- Bash 4.0+
- mailx or sendmail (optional, for email)

## Configuration Example

```bash
export CADNA_TOOLBOX_PATH=/shared/git/CADNA_tools_for_MadGraph5
export OUTPUT_PATH=/scratch/results
export CADNA_PATH=/shared/cadna
export MG5_PATH=./bin/mg5_aMC
export MAX_PARALLEL_CHECKS=8
export ITERATIONS=10000000
```

## Usage

Single orchestration:
```bash
cd PROC_xxx/SubProcesses
./orchestrate_process_evaluation.sh
```

Batch processing:
```bash
mkdir __ins && cp *.txt __ins/
./batch_orchestration.sh
```

SSH-safe execution:
```bash
./run_in_background.sh  "script.sh"
```
