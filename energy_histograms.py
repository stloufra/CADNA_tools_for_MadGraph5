#!/usr/bin/env python3
"""
Enhanced Matrix Element Accuracy Histogram Generator

Groups all energy variants of the same process on a single plot.
Each energy gets its own color, with dashed lines for double and solid for float.

Usage:
    python generate_histograms_multi.py [--workdir /path/to/SubProcesses]
"""

import sys
import os
import re
import argparse
from pathlib import Path
from collections import defaultdict
import numpy as np
import matplotlib.pyplot as plt
import srcpy.momnetumParser as mpr
import matplotlib

matplotlib.use('Agg')

def parse_output_file(filepath):
    """Parse output file to extract matrix element accuracy."""
    matrix_element = []
    matrixElementAccuracy = []
    momentum = []
    momentaAccuracy = []
    matrixZeros = 0 
    
    print(f"      Parsing: {os.path.basename(filepath)}")
    
    with open(filepath, 'r') as f:
        matrixZeros =  mpr.parse_file(f, momentum, momentaAccuracy, matrix_element, matrixElementAccuracy, matrixZeros)
        print(f"        Found {len(matrixElementAccuracy)} accuracies via mpr with zeros = {matrixZeros}")
    return np.array(matrixElementAccuracy)


def parse_directory_name(dirname):
    """
    Parse directory name to extract process, energy, and precision.
    
    Expected formats:
      P1_process_energy_precision (e.g., P1_epem_mupmum_13TeV_double)
      P1_process_precision (e.g., P1_epem_mupmum_double)
    """
    match = re.match(r'P1_(.+)_(double|float)$', dirname)
    
    if match:
        process_energy = match.group(1)
        precision = match.group(2)
        
        # Try to extract energy
        energy_match = re.search(r'(\d+(?:\.\d+)?[TGM]eV)', process_energy)
        if energy_match:
            energy = energy_match.group(1)
            process = process_energy[:energy_match.start()].rstrip('_')
        else:
            process = process_energy
            energy = "default"
        
        return process, energy, precision
    
    return None


def find_output_files(directory):
    """Find all output files in a directory."""
    output_files = []
    
    for filename in os.listdir(directory):
        if filename.endswith('.out'):
            if filename.startswith('double_') or filename.startswith('float_'):
                output_files.append(os.path.join(directory, filename))
    
    return output_files


def group_directories(workdir):
    """
    Group P1_* directories by process, then by energy and precision.
    
    Returns:
        dict: {process: {energy: {'double': path, 'float': path}}}
    """
    groups = defaultdict(lambda: defaultdict(lambda: {'double': None, 'float': None}))
    
    for item in os.listdir(workdir):
        item_path = os.path.join(workdir, item)
        
        if not os.path.isdir(item_path):
            continue
        
        if not item.startswith('P1_'):
            continue
        
        parsed = parse_directory_name(item)
        if parsed is None:
            continue
        
        process, energy, precision = parsed
        groups[process][energy][precision] = item_path
    
    return groups


    
def create_multi_energy_histogram(process_data, process, output_path):
    """
    Create histogram with multiple energies on the same plot.
    Uses step function (stairs) and only plots bins with non-zero counts.
    
    Args:
        process_data: {energy: {'double': array, 'float': array}}
        process: Process name
        output_path: Where to save the plot
    """
    # Create figure with 2 subplots: main histogram and mean vs energy
    fig = plt.figure(figsize=(12, 10))
    gs = fig.add_gridspec(2, 1, height_ratios=[3, 1], hspace=0.3)
    ax_main = fig.add_subplot(gs[0])
    ax_mean = fig.add_subplot(gs[1])
    
    # Color palette for different energies
    colors = ['blue', 'red', 'green', 'orange', 'purple', 'brown', 'cyan', 'magenta', 'pink', 'gray']
    
    # Sort energies for consistent ordering
    def extract_energy_value(energy_str):
        """Extract numerical value from energy string for sorting"""
        match = re.search(r'(\d+(?:\.\d+)?)', energy_str)
        if match:
            return float(match.group(1))
        return 0
    
    sorted_energies = sorted(process_data.keys(), key=extract_energy_value)
    
    # Collect all data for bin calculation
    all_data = []
    for energy in sorted_energies:
        data_dict = process_data[energy]
        if 'double' in data_dict and data_dict['double'] is not None:
            all_data.extend(data_dict['double'])
        if 'float' in data_dict and data_dict['float'] is not None:
            all_data.extend(data_dict['float'])
    
    if len(all_data) == 0:
        print(f"Warning: No data for {process}")
        return
    
    # Create bins
    bins = 18
    bin_range = (0,17) 
    
    # For mean accuracy plot
    energy_values = []
    mean_double = []
    mean_float = []
    fraction_low = []
    total_count = 0
    
    # Plot each energy on main plot
    for idx, energy in enumerate(sorted_energies):
        color = colors[idx % len(colors)]
        data_dict = process_data[energy]
        
        energy_val = extract_energy_value(energy)
        
        # Plot double precision (dashed line)
        if 'double' in data_dict and data_dict['double'] is not None and len(data_dict['double']) > 0:
            counts, bin_edges = np.histogram(data_dict['double'], bins=bins, range=bin_range)
            
            # Normalize to get density
            counts_normalized = counts / (np.sum(counts) * (bin_edges[1] - bin_edges[0]))
            
            # Filter out zero bins
            ax_main.hist(data_dict['double'], bins=bins, range=bin_range,
                        histtype='stepfilled',
                        edgecolor=None,
                        facecolor=color,
                        alpha=0.1,
                        density=False)
            ax_main.hist(data_dict['double'],
                        bins=bins,
                        linestyle='--',
                        range=bin_range,
                        histtype='step',
                        color=color,
                        linewidth=1.5,
                        alpha=1.0,
                        label=f'{energy} double',
                        density=False)
            # Store mean for subplot
            energy_values.append(energy_val)
            mean_double.append(np.mean(data_dict['double']))
        
        # Plot float precision (solid line)
        if 'float' in data_dict and data_dict['float'] is not None and len(data_dict['float']) > 0:
            counts, bin_edges = np.histogram(data_dict['float'], bins=bins, range=bin_range)
            
            # Normalize to get density
            counts_normalized = counts / (np.sum(counts) * (bin_edges[1] - bin_edges[0]))
            
            # Filter out zero bins
            # Create step histogram using only non-zero bins
            ax_main.hist(data_dict['float'], bins=bins, range=bin_range,
                       histtype='stepfilled',
                       linestyle='-',
                       edgecolor=None,
                       facecolor=color,
                       alpha=0.1,
                       density=False)
            ax_main.hist(data_dict['float'],
                       bins=bins,
                       range=bin_range,
                       histtype='step',
                       color=color,
                       linewidth=1.5,
                       linestyle='-',
                       alpha=1.0,
                       label=f'{energy} float',
                       density=False)
            # Total number of float samples
            total_count = len(data_dict['float'])
            
            # Count how many have 0, 1, or 2 significant digits
            low_sig_count = np.sum(np.isin(data_dict['float'], [0, 1, 2]))
            
            # Fraction
            fraction_low.append( low_sig_count / total_count if total_count > 0 else 0.0)
            
                     # Store mean for subplot
            if len(energy_values) == len(mean_double):
                mean_float.append(np.mean(data_dict['float']))
    

    # Configure main plot
    ax_main.set_xlabel('Matrix Element sig. digits                      Total count: '+str(total_count), fontsize=12)
    ax_main.set_ylabel('Count', fontsize=12)
    ax_main.set_title(f'Matrix Element Accuracy Distribution: {process}', 
                      fontsize=14, fontweight='bold')
    ax_main.set_xlim(0,17)
    ax_main.legend(loc='best', fontsize=9, ncol=2)
    ax_main.grid(True, alpha=0.3)

    # Build text block for all energies (float only)
    text_lines = []
    
    for e, frac in zip(sorted_energies, fraction_low):
        text_lines.append(f'{e} TeV: {frac*100:.3f}% ≤ 2 digits')
    
    text_string = "Float precision\n" + "\n".join(text_lines)
    
    # Place one single annotation box in axis coordinates
    ax_main.text(
        0.78, 0.98,                     # top-left corner (axes coords)
        text_string,
        transform=ax_main.transAxes,
        fontsize=10,
        verticalalignment='top',
        bbox=dict(
            facecolor='white',
            alpha=0.8,
            edgecolor='black',
            boxstyle='round'
        )
    )
    
    # Use log scale if appropriate
    data_range = max(all_data) - min(all_data)
    if data_range > 100:
        ax_main.set_xscale('log')
    # Create mean accuracy vs energy subplot
    if energy_values and mean_double:
    
        # Sort by energy for proper line plot
        sorted_indices = np.argsort(energy_values)
        energy_values_sorted = np.array(energy_values)[sorted_indices]
        mean_double_sorted = np.array(mean_double)[sorted_indices]
    
        if mean_float and len(mean_float) == len(mean_double):
            mean_float_sorted = np.array(mean_float)[sorted_indices]
        else:
            mean_float_sorted = None
    
        # Create right y-axis for double precision
        ax_mean_right = ax_mean.twinx()
    
        # ---- Plot FLOAT (left axis) ----
        if mean_float_sorted is not None:
            ax_mean.plot(
                energy_values_sorted,
                mean_float_sorted,
                'o-',
                linewidth=2,
                markersize=8,
                color='red',
                label='Float mean sig. dig.',
                alpha=0.8
            )
    
        # ---- Plot DOUBLE (right axis) ----
        ax_mean_right.plot(
            energy_values_sorted,
            mean_double_sorted,
            'o--',
            linewidth=2,
            markersize=8,
            color='blue',
            label='Double mean sig. dig.',
            alpha=0.8
        )
    
        # ---- Axis labels ----
        ax_mean.set_xlabel('Energy [TeV]', fontsize=11)
    
        ax_mean.set_ylabel('Mean Accuracy (Float)', fontsize=11)
        ax_mean_right.set_ylabel('Mean Accuracy (Double)', fontsize=11)
    
    
        ax_mean.set_title('Mean Accuracy vs Energy', fontsize=12)
    
        # ---- X-axis ticks ----
        ax_mean.set_xticks(energy_values_sorted)
        ax_mean.set_xticklabels([f'{e:.0f}' for e in energy_values_sorted])
    
        # ---- Grid (apply to main axis only) ----
        ax_mean.grid(True, alpha=0.3)
    
        # ---- Combine legends from both axes ----
        lines_left, labels_left = ax_mean.get_legend_handles_labels()
        lines_right, labels_right = ax_mean_right.get_legend_handles_labels()
    
        ax_mean.legend(
            lines_left + lines_right,
            labels_left + labels_right,
            loc='best',
            fontsize=10
        )
    
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    plt.close()
    
    print(f"Saved histogram: {output_path}")

def main():
    parser = argparse.ArgumentParser(
        description='Generate matrix element accuracy histograms (multi-energy)'
    )
    parser.add_argument(
        '--workdir',
        default='.',
        help='SubProcesses directory (default: current directory)'
    )
    parser.add_argument(
        '--separate',
        action='store_true',
        help='Create separate plots for each energy instead of combined'
    )
    
    args = parser.parse_args()
    
    workdir = os.path.abspath(args.workdir)
    
    if not os.path.isdir(workdir):
        print(f"Error: Directory not found: {workdir}")
        sys.exit(1)
    
    print(f"Working directory: {workdir}")
    
    # Create output directory
    hist_dir = os.path.join(workdir, 'histograms')
    os.makedirs(hist_dir, exist_ok=True)
    print(f"Output directory: {hist_dir}")
    
    # Group directories by process, then energy
    groups = group_directories(workdir)
    
    if not groups:
        print("Error: No P1_* directories found matching pattern")
        sys.exit(1)
    
    print(f"\nFound {len(groups)} processes")
    
    # Process each group
    for process, energy_data in sorted(groups.items()):
        print(f"\nProcessing: {process}")
        print(f"  Energies: {', '.join(sorted(energy_data.keys()))}")
        
        process_data = {}
        
        for energy, paths in sorted(energy_data.items()):
            print(f"\n  Energy: {energy}")
            data_dict = {}
            
            # Load double precision
            if paths['double'] is not None:
                print(f"    Loading double: {os.path.basename(paths['double'])}")
                output_files = find_output_files(paths['double'])
                
                if output_files:
                    all_accuracies = []
                    for outfile in output_files:
                        try:
                            accuracies = parse_output_file(outfile)
                            if len(accuracies) > 0:
                                all_accuracies.extend(accuracies)
                        except Exception as e:
                            print(f"      Warning: Failed to parse {outfile}: {e}")
                    
                    if all_accuracies:
                        data_dict['double'] = np.array(all_accuracies)
                        print(f"      Loaded {len(all_accuracies)} matrix elements")
            
            # Load float precision
            if paths['float'] is not None:
                print(f"    Loading float: {os.path.basename(paths['float'])}")
                output_files = find_output_files(paths['float'])
                
                if output_files:
                    all_accuracies = []
                    for outfile in output_files:
                        try:
                            accuracies = parse_output_file(outfile)
                            if len(accuracies) > 0:
                                all_accuracies.extend(accuracies)
                        except Exception as e:
                            print(f"      Warning: Failed to parse {outfile}: {e}")
                    
                    if all_accuracies:
                        data_dict['float'] = np.array(all_accuracies)
                        print(f"      Loaded {len(all_accuracies)} matrix elements")
            
            if data_dict:
                process_data[energy] = data_dict
        
        # Create histogram(s)
        if process_data:
            if args.separate:
                # Create separate plots for each energy
                for energy, data_dict in process_data.items():
                    output_filename = f"{process}_{energy}_accuracy_hist.png"
                    output_path = os.path.join(hist_dir, output_filename)
                    create_multi_energy_histogram({energy: data_dict}, process, output_path)
            else:
                # Create combined plot with all energies
                output_filename = f"{process}_accuracy_hist.png"
                output_path = os.path.join(hist_dir, output_filename)
                create_multi_energy_histogram(process_data, process, output_path)
        else:
            print(f"  Skipping: No data available")
    
    print(f"\n{'='*60}")
    print(f"Complete! Histograms saved to: {hist_dir}")
    print(f"{'='*60}")

if __name__ == '__main__':
    main()
