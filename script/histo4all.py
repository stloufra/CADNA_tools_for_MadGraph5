import os 
import subprocess

FILES = [f for f in os.listdir('.') if "gdb_run_output" in f] 

for file in FILES:
    print(f"running histogram on {file}")
    result = subprocess.run(
        ["python3", "histogram.py", file],
        text=True,
        capture_output=True
    )
    print(result.stdout)  # program output
    print(result.stderr)
