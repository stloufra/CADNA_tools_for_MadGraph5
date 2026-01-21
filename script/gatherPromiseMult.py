import os
import re
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from pathlib import Path

def parse_typedef_file(filepath):
    """
    Parse a header file and extract FT_ typedefs with their types.
    
    Args:
        filepath: Path to the header file
        
    Returns:
        dict: Dictionary mapping FT_ names to their types (e.g., {'FT_FFV1_1': 'double'})
    """
    # Types to exclude from the analysis
    excluded_types = {
        'fptype', 'fptype2',
        'FT_amp', 'FT_jamp', 'FT_w',
        'FT_imzxxx', 'FT_ipzxxx', 'FT_ixxxxx', 'FT_ixzxxx',
        'FT_omzxxx', 'FT_opzxxx', 'FT_oxxxxx', 'FT_oxzxxx',
        'FT_sxxxxx', 'FT_vxxxxx'
    }
    
    ft_types = {}
    
    try:
        with open(filepath, 'r') as f:
            content = f.read()
            
        # Pattern to match typedef lines
        pattern = r'typedef\s+(double|float)\s+(\w+);'
        matches = re.findall(pattern, content)
        
        for type_name, var_name in matches:
            # Only add FT_ types that are not in excluded list
            if var_name.startswith('FT_') and var_name not in excluded_types:
                ft_types[var_name] = type_name
            
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
        
    return ft_types

def scan_directories(base_dirs):
    """
    Scan multiple directories for header files and extract typedef information.
    
    Args:
        base_dirs: List of directory paths to scan
        
    Returns:
        dict: Dictionary mapping directory names to their FT_ typedef information
    """
    all_data = {}
    
    for base_dir in base_dirs:
        dir_path = Path(base_dir)
        if not dir_path.exists():
            print(f"Directory not found: {base_dir}")
            continue
            
        dir_name = dir_path.name
        
        # Find all header files (you can adjust the pattern)
        header_files = list(dir_path.glob('**/*.h')) + list(dir_path.glob('**/*.hpp'))
        
        dir_typedefs = {}
        for header_file in header_files:
            file_typedefs = parse_typedef_file(header_file)
            dir_typedefs.update(file_typedefs)
        
        if dir_typedefs:
            all_data[dir_name] = dir_typedefs
    
    return all_data

def find_and_scan_p_directories():
    """
    Find all P1* directories and scan their promiseTypes.h files.
    
    Returns:
        dict: Dictionary mapping directory names to their FT_ typedef information
    """
    curr = os.getcwd()
    p_dirs = [f for f in os.listdir() if "P1" in f]
    
    all_data = {}
    
    for p in p_dirs:
        promise_file = os.path.join(curr, p, "boiler_plate/output_promise_files/src/boilerplate/promiseTypes.h")
        
        if os.path.exists(promise_file):
            print(f"Found: {p}")
            typedefs = parse_typedef_file(promise_file)
            if typedefs:
                all_data[p] = typedefs
        else:
            print(f"Skipped: {p} (promiseTypes.h not found)")
    
    return all_data

def plot_typedef_table(data_dict):
    """
    Create a table-like plot showing typedef information across directories.
    Cells are colored for 'double' types and uncolored for 'float' types.
    
    Args:
        data_dict: Dictionary mapping directory names to their FT_ typedef information
    """
    if not data_dict:
        print("No data to plot")
        return
    
    # Get all unique FT_ names across all directories
    all_ft_names = set()
    for dir_data in data_dict.values():
        all_ft_names.update(dir_data.keys())
    
    all_ft_names = sorted(all_ft_names)
    dir_names = sorted(data_dict.keys())
    
    # Create figure
    fig, ax = plt.subplots(figsize=(max(12, len(dir_names) * 0.5), 
                                     max(8, len(all_ft_names) * 0.3)))
    
    # Create the grid
    for i, ft_name in enumerate(all_ft_names):
        for j, dir_name in enumerate(dir_names):
            # Check if this FT_ type exists in this directory
            if ft_name in data_dict[dir_name]:
                type_name = data_dict[dir_name][ft_name]
                
                # Color the cell if it's double
                if type_name == 'double':
                    color = '#4CAF50'  # Green for double
                    ax.add_patch(mpatches.Rectangle((j, len(all_ft_names) - i - 1), 
                                                     1, 1, 
                                                     facecolor=color, 
                                                     edgecolor='black',
                                                     linewidth=0.5))
                else:  # float
                    ax.add_patch(mpatches.Rectangle((j, len(all_ft_names) - i - 1), 
                                                     1, 1, 
                                                     facecolor='white', 
                                                     edgecolor='black',
                                                     linewidth=0.5))
            else:
                # Draw empty cell with gray color if type doesn't exist
                ax.add_patch(mpatches.Rectangle((j, len(all_ft_names) - i - 1), 
                                                 1, 1, 
                                                 facecolor='#f0f0f0', 
                                                 edgecolor='lightgray',
                                                 linewidth=0.5))
    
    # Set axis limits
    ax.set_xlim(0, len(dir_names))
    ax.set_ylim(0, len(all_ft_names))
    
    # Set ticks and labels
    ax.set_xticks([i + 0.1 for i in range(len(dir_names))])
    ax.set_xticklabels(dir_names, rotation=45, ha='right')
    
    ax.set_yticks([i + 0.1 for i in range(len(all_ft_names))])
    ax.set_yticklabels(all_ft_names[::-1])
    
    # Labels and title
    ax.set_xlabel('Directories', fontsize=12, fontweight='bold')
    ax.set_ylabel('FT_ Types', fontsize=12, fontweight='bold')
    ax.set_title('Typedef Distribution: double (colored) vs float (white)', 
                 fontsize=14, fontweight='bold', pad=20)
    
    # Add legend
    double_patch = mpatches.Patch(color='#4CAF50', label='double')
    float_patch = mpatches.Patch(color='white', edgecolor='black', label='float')
    missing_patch = mpatches.Patch(color='#f0f0f0', label='not defined')
    ax.legend(handles=[double_patch, float_patch, missing_patch], 
              loc='upper left', bbox_to_anchor=(1.02, 1))
    
    plt.tight_layout()
    #plt.show()
    plt.savefig("promiseResultGathered.png")

# Example usage:
if __name__ == "__main__":
    # Method 1: Automatic scan for P1* directories with promiseTypes.h
    print("Scanning P1* directories...")
    typedef_data = find_and_scan_p_directories()
    
    # Method 2: Manual directory list (alternative)
    # directories = ["./dir1", "./dir2", "./dir3"]
    # typedef_data = scan_directories(directories)
    
    # Print summary
    print(f"\nFound {len(typedef_data)} directories with typedef information:")
    for dir_name, typedefs in typedef_data.items():
        print(f"  {dir_name}: {len(typedefs)} FT_ types")
    
    # Create the plot
    if typedef_data:
        print("\nGenerating plot...")
        plot_typedef_table(typedef_data)
    else:
        print("\nNo typedef data found in the specified directories.")
