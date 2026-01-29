#!/usr/bin/env python3
import sys
from pathlib import Path

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <file.cpp>")
    sys.exit(1)

file_path = Path(sys.argv[1])
backup_path = file_path.with_suffix(file_path.suffix + ".bak")

# Backup original file
backup_path.write_text(file_path.read_text())

lines = file_path.read_text().splitlines()
new_lines = []

in_block = False
brace_level = 0
block_started = False

for line in lines:
    if not in_block and "for( int ipar = 0; ipar < CPPProcess::npar; ipar++ )" in line:
        in_block = True
        block_started = False  # To insert the replacement at the first {
        new_lines.append(line)
        continue

    if in_block:
        # Detect start of loop block (the '{')
        if not block_started and "{" in line:
            brace_level += line.count("{")
            brace_level -= line.count("}")
            block_started = True

            # Insert replacement lines here
            replacement_block = [
                "  {// NB: 'setw' affects only the next field (of any type)",
                "  const int ndigits = std::numeric_limits<double>::digits10;",
                "  std::cout << std::scientific << std::setprecision(ndigits) // fixed format: affects all floats",
                "            << std::setw( 4 ) << ipar + 1",
                "            << std::setw( ndigits +  14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 0, ipar )",
                "            << std::setw( ndigits +  14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 1, ipar )",
                "            << std::setw( ndigits +  14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 2, ipar )",
                "            << std::setw( ndigits +  14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 3, ipar )",
                "            << std::endl",
                "            << std::defaultfloat; // default format: affects all floats"
            ]
            new_lines.extend(replacement_block)
            continue  # skip the line with '{' itself

        # Track brace level inside the loop
        brace_level += line.count("{")
        brace_level -= line.count("}")

        # End of loop
        if brace_level <= 0:
            in_block = False
            new_lines.append(line)  # append the closing '}'
        # Skip all original lines inside the loop
        continue

    # Lines outside the block
    new_lines.append(line)

file_path.write_text("\n".join(new_lines) + "\n")
print(f"Replacement done in {file_path}. Backup saved as {backup_path}")

