#!/bin/bash

#LOC="/home/stloufra/git/madgraph4gpu/MG5aMC/mg5amcnlo/PROC_pp_ttxgg/SubProcesses/P1_gg_ttxgg"

LOC="/data/frstlouk/madgraph4gpu/MG5aMC/mg5amcnlo/PROC_pp_ttxgg/SubProcesses/P1_gg_ttxgg"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Create symlinks instead of copying files
ln -sf "$SCRIPT_DIR/Cadnize.sh" "$LOC/Cadnize.sh"
ln -sf "$SCRIPT_DIR/test.sh" "$LOC/test.sh"
ln -sf "$SCRIPT_DIR/histogram.py" "$LOC/histogram.py"
ln -s "$SCRIPT_DIR/srcpy" "$LOC/srcpy"

echo "Symlinks created successfully in $LOC"
