#!/usr/bin/env python3
"""
Enhanced Matrix Element Accuracy Histogram Generator

Groups all energy variants of the same process on a single plot.
Each energy gets its own color, with dashed lines for double and solid for float.
Applies phase space cuts per subprocess and produces convergence and grand summary plots.

Usage:
    python energy_histograms.py [--workdir /path/to/SubProcesses]
"""

import sys
import os
import re
import argparse
from pathlib import Path
from collections import defaultdict
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import srcpy.momnetumParser as mpr

matplotlib.use('Agg')


# ---------------------------------------------------------------------------
# Parsing
# ---------------------------------------------------------------------------

def parse_output_file(filepath):
    """
    Parse output file to extract matrix element accuracy and momenta.

    Returns
    -------
    accuracies : np.ndarray, shape (n_events,)
    momenta    : np.ndarray, shape (n_events, n_particles, 4)
    """
    matrix_element        = []
    matrixElementAccuracy = []
    momentum              = []
    momentaAccuracy       = []
    matrixZeros           = 0

    print(f"      Parsing: {os.path.basename(filepath)}")

    with open(filepath, 'r') as f:
        matrixZeros = mpr.parse_file(f, momentum, momentaAccuracy,
                                     matrix_element, matrixElementAccuracy,
                                     matrixZeros)
        print(f"        Found {len(matrixElementAccuracy)} accuracies, zeros = {matrixZeros}")

    return np.array(matrixElementAccuracy), np.array(momentum)


def parse_directory_name(dirname):
    """
    Parse P1_* directory name.

    Returns (process, energy, precision) or None.
    """
    match = re.match(r'P1_(.+)_(double|float)$', dirname)
    if not match:
        return None

    process_energy = match.group(1)
    precision      = match.group(2)

    energy_match = re.search(r'(\d+(?:\.\d+)?[TGM]eV)', process_energy)
    if energy_match:
        energy  = energy_match.group(1)
        process = process_energy[:energy_match.start()].rstrip('_')
    else:
        process = process_energy
        energy  = "default"

    return process, energy, precision


def find_output_files(directory):
    return [
        os.path.join(directory, f)
        for f in os.listdir(directory)
        if f.endswith('.out') and (f.startswith('double_') or f.startswith('float_'))
    ]


def group_directories(workdir):
    """
    Returns
    -------
    dict : {process: {energy: {'double': path, 'float': path}}}
    """
    groups = defaultdict(lambda: defaultdict(lambda: {'double': None, 'float': None}))

    for item in os.listdir(workdir):
        item_path = os.path.join(workdir, item)
        if not os.path.isdir(item_path) or not item.startswith('P1_'):
            continue
        parsed = parse_directory_name(item)
        if parsed is None:
            continue
        process, energy, precision = parsed
        groups[process][energy][precision] = item_path

    return groups


# ---------------------------------------------------------------------------
# Cut evaluation
# ---------------------------------------------------------------------------

def compute_cuts(accuracies, momenta, cuts_config):
    """
    Evaluate VBF/non-VBF phase space cuts for each event.

    Parameters
    ----------
    accuracies   : np.ndarray (n_events,)
    momenta      : np.ndarray (n_events, n_particles, 4)
    cuts_config  : mpr.CutConfig

    Returns
    -------
    cuts : list of str, one per event: 'none' | 'pt' | 'eta' | 'mjj'
    """
    cuts      = []
    jets      = cuts_config.jets
    mjj_thr   = cuts_config.mjj

    for ev in range(len(accuracies)):
        result = 'none'

        for i in range(len(jets)):
            p = momenta[ev][jets[i]]
            if mpr.pt(p) <= cuts_config.pt:
                result = 'pt'
                break
            if abs(mpr.eta(p)) >= cuts_config.eta:
                result = 'eta'
                break

        if result == 'none':
            for i in range(len(jets)):
                for j in range(i + 1, len(jets)):
                    m = mpr.mjj(momenta[ev][jets[i]], momenta[ev][jets[j]])
                    threshold = mjj_thr
                    if m <= threshold:
                        result = 'mjj'
                        break
                if result == 'mjj':
                    break

        cuts.append(result)

    return cuts


# ---------------------------------------------------------------------------
# Per-subprocess plots
# ---------------------------------------------------------------------------

def create_multi_energy_histogram(process_data, process, output_path):
    """
    Histogram of sig. digits across energies, showing only passing events.
    process_data : {energy: {'double': (acc, cuts), 'float': (acc, cuts)}}
    """
    fig = plt.figure(figsize=(12, 10))
    gs  = fig.add_gridspec(2, 1, height_ratios=[3, 1], hspace=0.3)
    ax_main = fig.add_subplot(gs[0])
    ax_mean = fig.add_subplot(gs[1])

    colors = ['blue', 'red', 'green', 'orange', 'purple',
              'brown', 'cyan', 'magenta', 'pink', 'gray']

    def extract_energy_value(s):
        m = re.search(r'(\d+(?:\.\d+)?)', s)
        return float(m.group(1)) if m else 0.0

    sorted_energies = sorted(process_data.keys(), key=extract_energy_value)

    bins      = 18
    bin_range = (0, 17)

    energy_values = []
    mean_double   = []
    mean_float    = []
    fraction_low  = []
    total_count   = 0

    for idx, energy in enumerate(sorted_energies):
        color     = colors[idx % len(colors)]
        data_dict = process_data[energy]

        energy_val = extract_energy_value(energy)

        for precision, linestyle in (('double', '--'), ('float', '-')):
            entry = data_dict.get(precision)
            if entry is None:
                continue
            acc, cuts, cuts_config = entry
            passing   = acc[[c == 'none' for c in cuts]]
            if len(passing) == 0:
                continue

            ax_main.hist(passing, bins=bins, range=bin_range,
                         histtype='stepfilled', edgecolor=None,
                         facecolor=color, alpha=0.1, density=False)
            ax_main.hist(passing, bins=bins, range=bin_range,
                         histtype='step', color=color, linewidth=1.5,
                         linestyle=linestyle, alpha=1.0,
                         label=f'{energy} {precision}', density=False)

            if precision == 'double':
                energy_values.append(energy_val)
                mean_double.append(np.mean(passing))

            if precision == 'float':
                total_count = len(passing)
                low_count   = np.sum(passing < 3)
                fraction_low.append(low_count / len(passing) if len(passing) > 0 else 0.0)
                if len(energy_values) == len(mean_double):
                    mean_float.append(np.mean(passing))

    ax_main.set_xlabel(f'Matrix Element sig. digits    Total passing count: {total_count}', fontsize=12)
    ax_main.set_ylabel('Count', fontsize=12)
    ax_main.set_title(f'Matrix Element Accuracy Distribution (after cuts): {process}',
                      fontsize=14, fontweight='bold')
    ax_main.set_xlim(0, 17)
    ax_main.legend(loc='best', fontsize=9, ncol=2)
    ax_main.grid(True, alpha=0.3)

    text_lines  = [f'{e}: {frac*100:.3f}% < 3 digits' for e, frac in zip(sorted_energies, fraction_low)]
    text_string = "Float precision (passing)\n" + "\n".join(text_lines)
    ax_main.text(0.78, 0.98, text_string, transform=ax_main.transAxes,
                 fontsize=10, verticalalignment='top',
                 bbox=dict(facecolor='white', alpha=0.8, edgecolor='black', boxstyle='round,pad=0.5'))

    # cut criteria box — use config from first available energy
    cfg = None
    for energy in sorted_energies:
        for prec in ('float', 'double'):
            entry = process_data[energy].get(prec)
            if entry is not None:
                cfg = entry[2]
                break
        if cfg is not None:
            break
    if cfg is not None:
        info = (
            f"jets: {cfg.jets}\n"
            f"$p_T$ > {cfg.pt} GeV\n"
            f"$|\\eta|$ < {cfg.eta}\n"
            f"$m_{{jj}}$ > {cfg.mjj} GeV"
        )
        ax_main.text(0.02, 0.98, info, transform=ax_main.transAxes, ha='left', va='top',
                     fontsize=8, family='monospace',
                     bbox=dict(boxstyle='round,pad=0.5', facecolor='white', alpha=0.8))

    if energy_values and mean_double:
        sorted_idx           = np.argsort(energy_values)
        energy_values_sorted = np.array(energy_values)[sorted_idx]
        mean_double_sorted   = np.array(mean_double)[sorted_idx]
        mean_float_sorted    = np.array(mean_float)[sorted_idx] if len(mean_float) == len(mean_double) else None

        ax_mean_right = ax_mean.twinx()

        if mean_float_sorted is not None:
            ax_mean.plot(energy_values_sorted, mean_float_sorted, 'o-',
                         linewidth=2, markersize=8, color='red',
                         label='Float mean sig. dig.', alpha=0.8)

        ax_mean_right.plot(energy_values_sorted, mean_double_sorted, 'o--',
                           linewidth=2, markersize=8, color='blue',
                           label='Double mean sig. dig.', alpha=0.8)

        ax_mean.set_xlabel('Energy [TeV]', fontsize=11)
        ax_mean.set_ylabel('Mean Accuracy (Float)', fontsize=11)
        ax_mean_right.set_ylabel('Mean Accuracy (Double)', fontsize=11)
        ax_mean.set_title('Mean Accuracy vs Energy (passing events)', fontsize=12)
        ax_mean.set_xticks(energy_values_sorted)
        ax_mean.set_xticklabels([f'{e:.0f}' for e in energy_values_sorted])
        ax_mean.grid(True, alpha=0.3)

        lines_l, labels_l = ax_mean.get_legend_handles_labels()
        lines_r, labels_r = ax_mean_right.get_legend_handles_labels()
        ax_mean.legend(lines_l + lines_r, labels_l + labels_r, loc='best', fontsize=10)

    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Saved: {output_path}")


def _convergence_info_box(ax, cfg):
    if cfg is None:
        return
    info = (
        f"jets: {cfg.jets}\n"
        f"$p_T$ > {cfg.pt} GeV\n"
        f"$|\\eta|$ < {cfg.eta}\n"
        f"$m_{{jj}}$ > {cfg.mjj} GeV"
    )
    ax.text(0.02, 0.98, info, transform=ax.transAxes, ha='left', va='top',
            fontsize=8, family='monospace',
            bbox=dict(boxstyle='round,pad=0.5', facecolor='white', alpha=0.8))


def _convergence_data(process_data, step=100):
    """
    Returns per-energy computed convergence series, float only.
    Yields (energy, color_idx, all_series, pass_series, cuts_config)
    where *_series = (indices, frac_below3, mean_acc) or None if too few events.
    """
    from collections import namedtuple
    Series = namedtuple('Series', ['indices', 'frac_below3', 'mean_acc'])

    def compute(vals):
        indices     = list(range(step, len(vals) + 1, step))
        frac_below3 = [sum(v < 3 for v in vals[:n]) / n * 100 for n in indices]
        mean_acc    = [sum(vals[:n]) / n                        for n in indices]
        return Series(indices, frac_below3, mean_acc)

    def extract_energy_value(s):
        m = re.search(r'(\d+(?:\.\d+)?)', s)
        return float(m.group(1)) if m else 0.0

    colors          = ['blue', 'red', 'green', 'orange', 'purple',
                       'brown', 'cyan', 'magenta', 'pink', 'gray']
    sorted_energies = sorted(process_data.keys(), key=extract_energy_value)

    for idx, energy in enumerate(sorted_energies):
        color = colors[idx % len(colors)]
        entry = process_data[energy].get('float')
        if entry is None:
            continue
        acc, cuts, cfg = entry
        if len(acc) == 0:
            continue

        passing = [v for v, c in zip(acc, cuts) if c == 'none']
        all_    = list(acc)

        all_series  = compute(all_)    if len(all_)    >= step else None
        pass_series = compute(passing) if len(passing) >= step else None

        yield energy, color, all_series, pass_series, cfg


def create_convergence_plot(process_data, process, output_path):
    """
    Two separate figures:
      1. Convergence of % < 3 sig. digits (float only)
      2. Convergence of mean sig. digits   (float only)
    Faint = all events, solid = passing events.
    output_path is used as base; _frac and _mean suffixes are appended before extension.
    """
    from matplotlib.lines import Line2D

    base, ext = os.path.splitext(output_path)

    legend_extra = [
        Line2D([0], [0], color='gray', linewidth=1,   alpha=0.35, label='all events'),
        Line2D([0], [0], color='gray', linewidth=1.8,              label='passing events'),
    ]

    cfg_first = None

    for title, ylabel, attr, threshold, out_suffix in (
        ('Convergence % < 3 sig. dig. (float)',  'Below 3 sig. dig. [%]', 'frac_below3', 0.1,  '_frac'),
        ('Convergence mean sig. dig. (float)',    'Mean sig. digits [1]',  'mean_acc',    None,  '_mean'),
    ):
        fig, ax = plt.subplots(figsize=(12, 6))

        for energy, color, all_s, pass_s, cfg in _convergence_data(process_data):
            if cfg_first is None:
                cfg_first = cfg
            if all_s is not None:
                ax.plot(all_s.indices, getattr(all_s, attr),
                        color=color, linewidth=1, alpha=0.35, linestyle='-')
            if pass_s is not None:
                ax.plot(pass_s.indices, getattr(pass_s, attr),
                        color=color, linewidth=1.8, linestyle='-', label=energy)

        if threshold is not None:
            ax.axhline(y=threshold, color='black', linewidth=1.2, linestyle='--',
                       label=f'{threshold}% criterion')

        handles, labels_ = ax.get_legend_handles_labels()
        ax.legend(handles + legend_extra, labels_ + [h.get_label() for h in legend_extra],
                  fontsize=8, loc='best')

        ax.set_xlabel('Events [1]', fontsize=11)
        ax.set_ylabel(ylabel, fontsize=11)
        ax.set_title(f'{title}: {process}', fontsize=13, fontweight='bold')
        ax.grid(True, alpha=0.3)

        _convergence_info_box(ax, cfg_first)

        fig.tight_layout()
        out = base + out_suffix + ext
        plt.savefig(out, dpi=150, bbox_inches='tight')
        plt.close()
        print(f"Saved: {out}")


# ---------------------------------------------------------------------------
# Grand summary plots
# ---------------------------------------------------------------------------

def create_grand_summary(all_process_data, hist_dir):
    """
    One grand bar plot with grouped bars: before cuts (steelblue) and after cuts (tomato),
    one group per subprocess+energy+precision combo.
    all_process_data : {process: {energy: {precision: (acc, cuts)}}}
    """
    labels      = []
    frac_before = []
    frac_after  = []

    def extract_energy_value(s):
        m = re.search(r'(\d+(?:\.\d+)?)', s)
        return float(m.group(1)) if m else 0.0

    for process in sorted(all_process_data.keys()):
        energy_data = all_process_data[process]
        for energy in sorted(energy_data.keys(), key=extract_energy_value):
            entry = energy_data[energy].get('float')
            if entry is None:
                continue
            acc, cuts, _ = entry
            if len(acc) == 0:
                continue

            passing = acc[[c == 'none' for c in cuts]]
            labels.append(f'{process}\n{energy}')
            frac_before.append(np.sum(acc < 3)     / len(acc)     * 100)
            frac_after.append( np.sum(passing < 3) / len(passing) * 100
                               if len(passing) > 0 else 0.0)

    if not labels:
        return

    x     = np.arange(len(labels))
    width = 0.35

    fig, ax = plt.subplots(figsize=(max(10, len(labels) * 1.6), 6))

    bars_before = ax.bar(x - width / 2, frac_before, width=width,
                         color='steelblue', edgecolor='white', label='before cuts')
    bars_after  = ax.bar(x + width / 2, frac_after,  width=width,
                         color='tomato',    edgecolor='white', label='after cuts')

    ax.bar_label(bars_before, labels=[f'{v:.3f}%' for v in frac_before],
                 padding=3, fontsize=7, color='steelblue', rotation=90)
    ax.bar_label(bars_after,  labels=[f'{v:.3f}%' for v in frac_after],
                 padding=3, fontsize=7, color='tomato',    rotation=90)

    ax.axhline(y=0.1, color='black', linewidth=1.2, linestyle='--', label='0.1% criterion')

    ax.set_xticks(x)
    ax.set_xticklabels(labels, fontsize=8)
    ax.set_ylabel('% events < 3 sig. digits', fontsize=11)
    ax.set_title('% below 3 sig. digits — before vs after cuts', fontsize=13, fontweight='bold')
    all_fracs = frac_before + frac_after
    ax.set_ylim(0, max(all_fracs) * 1.35 if max(all_fracs) > 0 else 1)
    ax.grid(True, alpha=0.3, axis='y')
    _convergence_info_box(ax, None)
    ax.legend(fontsize=10, loc='upper right')

    fig.tight_layout()
    out = os.path.join(hist_dir, 'grand_summary.png')
    plt.savefig(out, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Saved: {out}")


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description='Generate matrix element accuracy histograms (multi-energy)'
    )
    parser.add_argument('--workdir', default='.',
                        help='SubProcesses directory (default: current directory)')
    parser.add_argument('--separate', action='store_true',
                        help='Create separate plots for each energy instead of combined')
    args    = parser.parse_args()
    workdir = os.path.abspath(args.workdir)

    if not os.path.isdir(workdir):
        print(f"Error: Directory not found: {workdir}")
        sys.exit(1)

    print(f"Working directory: {workdir}")

    hist_dir = os.path.join(workdir, 'histograms')
    os.makedirs(hist_dir, exist_ok=True)
    print(f"Output directory: {hist_dir}")

    groups = group_directories(workdir)
    if not groups:
        print("Error: No P1_* directories found matching pattern")
        sys.exit(1)

    print(f"\nFound {len(groups)} processes")

    all_process_data = {}  # {process: {energy: {precision: (acc, cuts)}}}

    for process, energy_data in sorted(groups.items()):
        print(f"\nProcessing: {process}")
        print(f"  Energies: {', '.join(sorted(energy_data.keys()))}")

        process_data = {}

        for energy, paths in sorted(energy_data.items()):
            print(f"\n  Energy: {energy}")
            data_dict = {}

            for precision in ('double', 'float'):
                if paths[precision] is None:
                    continue
                print(f"    Loading {precision}: {os.path.basename(paths[precision])}")

                # load cuts config from the precision folder
                cuts_config  = mpr.read_cuts(os.listdir(".")[0],
                                             'cuts.toml')
                output_files = find_output_files(paths[precision])

                if not output_files:
                    continue

                all_acc  = []
                all_mom  = []
                for outfile in output_files:
                    try:
                        acc, mom = parse_output_file(outfile)
                        if len(acc) > 0:
                            all_acc.append(acc)
                            all_mom.append(mom)
                    except Exception as e:
                        print(f"      Warning: {outfile}: {e}")

                if not all_acc:
                    continue

                acc_arr = np.concatenate(all_acc)
                mom_arr = np.concatenate(all_mom)
                cuts    = compute_cuts(acc_arr, mom_arr, cuts_config)

                data_dict[precision] = (acc_arr, cuts, cuts_config)
                print(f"      Loaded {len(acc_arr)} events, "
                      f"{sum(c == 'none' for c in cuts)} passing cuts")

            if data_dict:
                process_data[energy] = data_dict

        if not process_data:
            print(f"  Skipping: no data")
            continue

        all_process_data[process] = process_data

        if args.separate:
            for energy, data_dict in process_data.items():
                out = os.path.join(hist_dir, f"{process}_{energy}_accuracy_hist_cuts.png")
                create_multi_energy_histogram({energy: data_dict}, process, out)
                out = os.path.join(hist_dir, f"{process}_{energy}_convergence_cuts.png")
                create_convergence_plot({energy: data_dict}, process, out)
        else:
            out = os.path.join(hist_dir, f"{process}_accuracy_hist_cuts.png")
            create_multi_energy_histogram(process_data, process, out)
            out = os.path.join(hist_dir, f"{process}_convergence_cuts.png")
            create_convergence_plot(process_data, process, out)

    create_grand_summary(all_process_data, hist_dir)

    print(f"\n{'='*60}")
    print(f"Complete. Histograms saved to: {hist_dir}")
    print(f"{'='*60}")


if __name__ == '__main__':
    main()
