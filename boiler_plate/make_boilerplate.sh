#! /bin/bash

# Directory to search
DIR="./src"

# Absolute path of this script
SELF="$(readlink -f "$0")"

find "$DIR" -maxdepth 1 -type f -print0 | while IFS= read -r -d '' file; do
    # Absolute path of the file being checked
    ABS="$(readlink -f "$file")"

    # Skip this script
    if [[ "$ABS" == "$SELF" ]]; then
        # Optional: echo "Skipping self: $file"
        continue
    fi

    # Patch only files containing the exact include
    if grep -q '^#include "mgOnGpuConfig.h"' "$file"; then
         echo "Patching: $file"
         sed -i 's|#include "mgOnGpuConfig.h"|#include "boilerplate/typeTraits.h"|' "$file"
    fi

    if grep -q '^#include "mgOnGpuVectors.h"' "$file"; then
         echo "Removing mgOnGpuVectors include from: $file"
         sed -i '/^#include "mgOnGpuVectors.h"/d' "$file"
    fi

    if grep -q '"MemoryAccess' "$file"; then
             echo "Redirecting memory access in: $file"
             sed -i 's|"MemoryAccess|"accesses/MemoryAccess|' "$file"
    fi

    if grep -q '#include "Parameters_sm.h"' "$file"; then
             echo "Redirecting Parameters_sm in: $file"
             sed -i 's|#include "Parameters_sm.h"|#include "boilerplate/Parameters_sm.h"|' "$file"
    fi

    if grep -q '^#include "GpuAbstraction.h"' "$file"; then
          echo "Removing GpuAbstraction include from: $file"
          sed -i '/^#include "GpuAbstraction.h"/d' "$file"
    fi

    if grep -q '^#include "GpuRuntime.h"' "$file"; then
          echo "Removing GpuRuntime include from: $file"
          sed -i '/^#include "GpuRuntime.h"/d' "$file"
    fi
done

BUILD_DIR1="./debug"
BUILD_DIR2="./profile"
BUILD_DIR3="./release"

