#!/bin/bash

#########################
# Wrapper script for running Process in background
# This ensures the process continues even if SSH disconnects
#########################

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SCRIPT_NAME="${SCRIPT_DIR}/${1}"

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log_info() {
    echo -e "${BLUE}[INFO]${NC} $*"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $*"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $*"
}

# Check if Process script exists
if [ ! -f "$SCRIPT_NAME" ]; then
    log_error "Process script not found: $SCRIPT_NAME"
    exit 1
fi

# Make sure it's executable
chmod +x "$SCRIPT_NAME"

# Set default log file
WORK_DIR="$(pwd)"
LOG_FILE="${WORK_DIR}/background_process_$(date +%Y%m%d_%H%M%S).log"
PID_FILE="${WORK_DIR}/background_process.pid"
STATUS_FILE="${WORK_DIR}/background_process.status"

# Check if already running
if [ -f "$PID_FILE" ]; then
    OLD_PID=$(cat "$PID_FILE")
    if ps -p "$OLD_PID" > /dev/null 2>&1; then
        log_error "Process already running with PID $OLD_PID"
        log_info "Check status: tail -f $LOG_FILE"
        log_info "To kill: kill $OLD_PID"
        tail -f $LOG_FILE
        exit 1
    else
        log_info "Removing stale PID file"
        rm -f "$PID_FILE"
    fi
fi

log_info "Starting Process in background..."
log_info "Working directory: $WORK_DIR"
log_info "Log file: $LOG_FILE"
log_info "PID file: $PID_FILE"

# Start the Process in background with nohup
# Redirect all output to log file
nohup "$SCRIPT_NAME" "$WORK_DIR" > "$LOG_FILE" 2>&1 &

ORCH_PID=$!

# Save PID
echo "$ORCH_PID" > "$PID_FILE"
echo "RUNNING" > "$STATUS_FILE"

log_success "Process started with PID: $ORCH_PID"
log_info ""
log_info "Monitor progress with:"
log_info "  tail -f $LOG_FILE"
log_info ""
log_info "Check if running:"
log_info "  ps -p $ORCH_PID"
log_info ""
log_info "Stop Process:"
log_info "  kill $ORCH_PID"
log_info ""
log_info "Check status:"
log_info "  ./check_background_process_status.sh $WORK_DIR"

# Create a quick status checker script
cat > "${WORK_DIR}/check_background_process_status.sh" << 'EOF'
#!/bin/bash

WORK_DIR="${1:-.}"
PID_FILE="${WORK_DIR}/background_process.pid"
LOG_FILE=$(ls -t ${WORK_DIR}/background_process_*.log 2>/dev/null | head -1)

if [ ! -f "$PID_FILE" ]; then
    echo "No Process PID file found"
    exit 1
fi

PID=$(cat "$PID_FILE")

if ps -p "$PID" > /dev/null 2>&1; then
    echo "Process is RUNNING (PID: $PID)"
    echo ""
    echo "Recent log output:"
    echo "===================="
    tail -20 "$LOG_FILE"
else
    echo "Process is NOT running (PID $PID is dead)"
    echo ""
    if [ -f "$LOG_FILE" ]; then
        echo "Last log lines:"
        echo "===================="
        tail -30 "$LOG_FILE"
        echo ""
        echo "Full log: $LOG_FILE"
    fi
    rm -f "$PID_FILE"
fi
EOF

chmod +x "${WORK_DIR}/check_background_process_status.sh"

log_success "You can now safely disconnect from SSH"
log_info "The Process will continue running in the background"
log_info "-------------------------------------------------"
log_info "Automatically starting the tail - exit with CTRL+C"
log_info "-------------------------------------------------"

tail -f $LOG_FILE
