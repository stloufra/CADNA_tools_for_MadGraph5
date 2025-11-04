#!/bin/bash

#LOC="/home/stloufra/git/madgraph4gpu/MG5aMC/mg5amcnlo/PROC_pp_ttxgg/SubProcesses/P1_gg_ttxgg"

LOC="/data/frstlouk/madgraph4gpu/MG5aMC/mg5amcnlo/PROC_pp_ttxgg/SubProcesses/P1_gg_ttxgg"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Create symlinks instead of copying files
ln -sf "$SCRIPT_DIR/srcpy/cadnize_bridge.py" "$LOC/cadnize_bridge.py"
ln -sf "$SCRIPT_DIR/srcpy/cadnize_check_sa.py" "$LOC/cadnize_check_sa.py"
ln -sf "$SCRIPT_DIR/srcpy/cadnize_constexpr_replace.py" "$LOC/cadnize_constexpr_replace.py"
ln -sf "$SCRIPT_DIR/srcpy/cadnize_CPPProcess_cout_amp_fp.py" "$LOC/cadnize_CPPProcess_cout_amp_fp.py"
ln -sf "$SCRIPT_DIR/srcpy/cadnize_exact_momenta.py" "$LOC/cadnize_exact_momenta.py"
ln -sf "$SCRIPT_DIR/srcpy/cadnize_exact_momenta_to_load_momenta.py" "$LOC/cadnize_exact_momenta_to_load_momenta.py"
ln -sf "$SCRIPT_DIR/srcpy/cadnize_expand_equations.py" "$LOC/cadnize_expand_equations.py"
ln -sf "$SCRIPT_DIR/srcpy/cadnize_libflags.py" "$LOC/cadnize_libflags.py"
ln -sf "$SCRIPT_DIR/srcpy/cadnize_seed_change.py" "$LOC/cadnize_seed_change.py"
ln -sf "$SCRIPT_DIR/srcpy/cadnize_std_replace.py" "$LOC/cadnize_std_replace.py"
ln -sf "$SCRIPT_DIR/Cadnize.sh" "$LOC/Cadnize.sh"
ln -sf "$SCRIPT_DIR/test.sh" "$LOC/test.sh"

echo "Symlinks created successfully in $LOC"
