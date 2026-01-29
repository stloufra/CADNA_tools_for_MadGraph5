#!/usr/bin/env python3

import os
import subprocess
from pathlib import Path
from multiprocessing.pool import ThreadPool

# -----------------------------
# Configuration
# -----------------------------
SCRIPT_DIR = Path("/data/frstlouk/CADNA_tools_for_MadGraph5")
MAX_PARALLEL_TESTS = 10
MAKE_CMD = [
    "make", "-j12",
    'OPTFLAGS= -O3 -g',
    "AVX=none",
    "HASCURAND=hasNoCurand",
    "USEOPENMP=1",
    "GTESTLIBS=",
    "CUDA_HOME="
]

FAILED_DIRS_FILE = "test_fail.txt"

# -----------------------------
# Utilities
# -----------------------------


def run_cmd(cmd, cwd, logfile="cmd_output.txt"):
    """Run a shell command and write output to logfile in real time."""
    logfile = Path(logfile)

    with logfile.open("a", buffering=1) as f:  # line-buffered
        f.write(f"$ {' '.join(cmd)}\n")

        process = subprocess.Popen(
            cmd,
            cwd=cwd,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1,          # line-buffered
        )

        for line in process.stdout:
            f.write(line)      # written immediately
            f.flush()          # ensure it hits disk

        process.wait()

        f.write("\n" + "-" * 80 + "\n")

        if process.returncode != 0:
            print(f"[ERROR] Command failed in {cwd}: {' '.join(cmd)}")
            return False

        return True

def symlink(src, dst):
    """Create/update symlink."""
    if dst.exists() or dst.is_symlink():
        dst.unlink()
    dst.symlink_to(src)


# -----------------------------
# Step 1: Discover folders
# -----------------------------
base_dir = Path.cwd()
folders = sorted([p for p in base_dir.iterdir() if p.is_dir() and p.name.startswith("P1_")])

print(f"Found {len(folders)} P1_* folders")

failed_folders = []


# -----------------------------
# Step 2–4: Sequential preparation + Cadnize + make
# -----------------------------

print(f"\n=== Cleaning { folders[0] } ===")
run_cmd(["make", "distclean"], cwd=folders[0])
    
for loc in folders:
    print(f"\n=== Processing {loc} ===")

    try:
        # Step 2: Symlinks
        symlink(SCRIPT_DIR / "Cadnize.sh", loc / "Cadnize.sh")
        symlink(SCRIPT_DIR / "test.sh", loc / "test.sh")
        symlink(SCRIPT_DIR / "histogram.py", loc / "histogram.py")

        # srcpy is a directory → symbolic directory link
        srcpy_dst = loc / "srcpy"
        if srcpy_dst.exists() or srcpy_dst.is_symlink():
            srcpy_dst.unlink()
        srcpy_dst.symlink_to(SCRIPT_DIR / "srcpy", target_is_directory=True)

        symlink(
            SCRIPT_DIR / "script/runMultipleTest.sh",
            loc / "runMultipleTest.sh"
        )

        # Step 3: Run Cadnize.sh
        if not run_cmd(["./Cadnize.sh"], cwd=loc):
            failed_folders.append(loc)
            continue

        # Step 4: make / compile test
        if not run_cmd(MAKE_CMD, cwd=loc):
            failed_folders.append(loc)
            continue

    except Exception as e:
        print(f"[ERROR] Unexpected failure in {loc}: {e}")
        failed_folders.append(loc)


# -----------------------------
# Write failed directories
# -----------------------------
with open(FAILED_DIRS_FILE, "w") as f:
    for d in failed_folders:
        f.write(f"{d}\n")

print(f"\nCompilation failures: {len(failed_folders)}")
print(f"Written to {FAILED_DIRS_FILE}")


# -----------------------------
# Step 5: runMultipleTest.sh in parallel
# -----------------------------
valid_folders = [d for d in folders if d not in failed_folders]

print(f"\nRunning runMultipleTest.sh in {len(valid_folders)} folders (max {MAX_PARALLEL_TESTS} parallel)")


def run_tests(loc):
    print(f"[TEST] {loc}")
    return run_cmd(["./test.sh","float", "O3" ,"1"], cwd=loc)


pool = ThreadPool(processes=MAX_PARALLEL_TESTS)
pool.map(run_tests, valid_folders)
pool.close()
pool.join()

print("\nAll tests completed.")

