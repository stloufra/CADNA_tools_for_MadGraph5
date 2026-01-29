#!/usr/bin/env python3
"""
Compare significant digits of Matrix element values across multiple files.
"""

import sys
import re
from math import log10
from pathlib import Path
import matplotlib.pyplot as plt
import os


def extract_matrix_elements(filepath):
    """
    Extract all Matrix element values from a file.

    Returns:
        list of floats
    """
    matrix_elements = []
    pattern = re.compile(r'Matrix element\s*=\s*([\d.eE+-]+)')

    with open(filepath, 'r') as f:
        for line in f:
            match = pattern.search(line)
            if match:
                value_str = match.group(1)
                value_float = float(value_str)
                matrix_elements.append(value_float)

    return matrix_elements


def compare_values(val1, val2):
    """
    Compare two values using log10 of absolute relative difference.

    Returns:
        float: -log10(abs(relative_difference))
    """
    if val1 == val2:
        return float('inf')  # Exact match

    if val1 == 0 or val2 == 0:
        return 0

    # Calculate relative difference
    rel_diff = abs((val1 - val2) / max(abs(val1), abs(val2)))

    if rel_diff == 0:
        return float('inf')

    # Number of matching significant digits: -log10(rel_diff)
    matching_digits = -log10(rel_diff)

    return matching_digits


def plotHis_MEP(file1, file2, matrixElementPrecision_fl, matrixElementPrecisionZeros):
    """Plot histogram of matrix element precision"""
    fig, ax = plt.subplots()
    plt.title(f"Matrix element precision: {Path(file1).name} vs {Path(file2).name}")
    plt.xlabel(f"Digits of precision.        Sum = {len(matrixElementPrecision_fl) + matrixElementPrecisionZeros}")

    # Create histogram
    counts, edges, bars = ax.hist(matrixElementPrecision_fl, histtype='barstacked',
                                  bins=range(0, int(max(matrixElementPrecision_fl)) + 2))
    plt.bar_label(bars)

    # Show the mean
    mean_val = sum(matrixElementPrecision_fl) / len(matrixElementPrecision_fl)
    plt.axvline(x=mean_val, color='c', linestyle='dashed', linewidth=1)
    min_ylim, max_ylim = plt.ylim()
    plt.text(mean_val, max_ylim * 0.1, f'Mean: {mean_val:.2f}', color='black')

    # Create directory for histograms if it doesn't exist
    dir_name = "histograms"
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    # Save histogram
    output_name = f"comparisonME.png"
    plt.savefig(output_name)
    print(f"\nHistogram saved as: {output_name}")
    plt.show()
    plt.close()


def main():
    if len(sys.argv) != 3:
        print("Usage: python compare_matrix_elements.py <file1.txt> <file2.txt>")
        sys.exit(1)

    file1, file2 = sys.argv[1], sys.argv[2]

    # Validate files exist
    for filepath in [file1, file2]:
        if not Path(filepath).exists():
            print(f"Error: File '{filepath}' not found.")
            sys.exit(1)

    # Extract matrix elements from both files
    elements1 = extract_matrix_elements(file1)
    elements2 = extract_matrix_elements(file2)

    print(f"{file1}: Found {len(elements1)} Matrix element lines")
    print(f"{file2}: Found {len(elements2)} Matrix element lines")

    if len(elements1) != len(elements2):
        print(f"\nWarning: Files have different numbers of Matrix elements!")
        print(f"Comparing only the first {min(len(elements1), len(elements2))} elements.")

    num_elements = min(len(elements1), len(elements2))

    # Compare matrix elements line by line
    print("\n" + "="*80)
    print("COMPARISON RESULTS")
    print("="*80)

    matching_digits_list = []
    exact_matches = 0

    for i in range(num_elements):
        val1 = elements1[i]
        val2 = elements2[i]
        matching = compare_values(val1, val2)

        if matching == float('inf'):
            print(f"Element {i+1}: EXACT MATCH")
            exact_matches += 1
            matching_digits_list.append(16)  # Use 16 for exact matches
        else:
            print(f"Element {i+1}: {val1:.6e} vs {val2:.6e} -> {matching:.2f} significant digits")
            matching_digits_list.append(matching)

    # Statistics
    print(f"\n{'='*80}")
    print(f"Total comparisons: {len(matching_digits_list)}")
    print(f"Exact matches (zeros): {exact_matches}")
    print(f"Mean matching digits: {sum(matching_digits_list)/len(matching_digits_list):.2f}")
    print(f"Min matching digits: {min(matching_digits_list):.2f}")
    print(f"Max matching digits: {max(matching_digits_list):.2f}")
    print(f"{'='*80}")

    # Create histogram plot
    if matching_digits_list:
        plotHis_MEP(file1, file2, matching_digits_list, exact_matches)


if __name__ == "__main__":
    main()