#!/usr/bin/env python3
"""
visualize.py
---------------

This script reads sorting performance data from ``results.csv`` and
produces simple line plots comparing merge sort, quick sort and heap
sort on different input distributions.  The results file is expected
to have columns ``algorithm``, ``n``, ``distribution`` and
``time_ms``.  For each distribution (random, ascending, descending)
the script generates a separate PNG image showing running time
versus input size for the three algorithms.

Usage:
    python visualize.py [path/to/results.csv]

If no argument is provided the script looks for ``results.csv`` in
the current working directory.  Output images are saved in the same
directory as the input file.
"""

import csv
import os
import sys
from collections import defaultdict
import matplotlib.pyplot as plt


def load_results(csv_path):
    """Load results from a CSV file into a nested dictionary.

    Returns a mapping of distribution -> algorithm -> list of (n, time_ms).
    """
    data = defaultdict(lambda: defaultdict(list))
    with open(csv_path, newline='', encoding='utf-8') as f:
        reader = csv.DictReader(f)
        for row in reader:
            alg = row['algorithm']
            n = int(row['n'])
            dist = row['distribution']
            time_ms = float(row['time_ms'])
            data[dist][alg].append((n, time_ms))
    # Sort each list by n to ensure lines connect in order
    for dist in data:
        for alg in data[dist]:
            data[dist][alg].sort(key=lambda x: x[0])
    return data


def plot_distributions(data, output_dir):
    """Plot running times for each distribution and save PNG files."""
    for dist, alg_data in data.items():
        plt.figure()
        for alg, points in alg_data.items():
            ns = [p[0] for p in points]
            times = [p[1] for p in points]
            plt.plot(ns, times, marker='o', label=alg)
        plt.xlabel('Array size (n)')
        plt.ylabel('Time (ms)')
        plt.title(f'Sorting performance on {dist} data')
        plt.legend()
        plt.grid(True)
        # Save using distribution name
        filename = f'plot_{dist}.png'.replace(' ', '_')
        plt.savefig(os.path.join(output_dir, filename))
        plt.close()
        print(f'Plot saved to {filename}')


def main():
    if len(sys.argv) > 2:
        print("Usage: python visualize.py [results.csv]")
        sys.exit(1)
    csv_path = sys.argv[1] if len(sys.argv) == 2 else 'results.csv'
    if not os.path.isfile(csv_path):
        print(f'Error: {csv_path} does not exist')
        sys.exit(1)
    data = load_results(csv_path)
    output_dir = os.path.dirname(os.path.abspath(csv_path))
    plot_distributions(data, output_dir)


if __name__ == '__main__':
    main()