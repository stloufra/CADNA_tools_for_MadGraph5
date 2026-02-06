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
            if (var_name.startswith('FT_') or "fptype" in  var_name) and var_name not in excluded_types:
            #if var_name.startswith('FT_VVV1P0_1') :
                ft_types[var_name] = type_name
            
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
        
    return ft_types

def check_usage_of_typedef(filepath, list_of_types):
    """
    Check the CPPProcess files for actuall usage of the type defs.

    Args:
        list_of_types: List of types to be checked
        filepath: Path to the header file
     
    Returns:
        dict: Dictionary mapping FT_ names to their actuall usage (e.g,. {FT_FFV1_1: True})
    """
    usage = {}
    try:
        with open(filepath, 'r') as f:
            lines = f.readlines()

        for t in list_of_types.keys():
            pattern = t.replace("FT_","")#+"<W_ACCESS"
            if "V" in pattern or "F" in pattern:
                pattern = " " + pattern
            usage[t] =  sum(pattern in line for line in lines)
#            usage[t] = 1

    except Exception as e:
        print(f"Error reading {filepath} to search for types: {e}")

    return usage


def find_and_scan_p_directories():
    """
    Find all P1* directories and scan their promiseTypes.h files.
    
    Returns:
        dict: Dictionary mapping directory names to their FT_ typedef information
    """
    curr = os.getcwd()
    p_dirs = [f for f in os.listdir() if "P1_" in f]
    #p_dirs = [".."]
    
    all_data = {}
    
    for p in p_dirs:
        promise_file = os.path.join(curr, p, "boiler_plate/output_promise_files/src/boilerplate/promiseTypes.h")
        cpprocess_file = os.path.join(curr, p, "boiler_plate/src/CPPProcess.cc")
        
        if os.path.exists(promise_file):
            print(f"Found: {p}")
            typedefs = parse_typedef_file(promise_file)
            if typedefs:
                used_typdefs = check_usage_of_typedef(cpprocess_file, typedefs)
                if used_typdefs:
                    all_data[p] = [typedefs, used_typdefs]
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
    #print(f"values {data_dict.values()}")
    #print(f"keys {data_dict.keys()}")

    all_ft_names = set()
    for typedefs, used_typdefs in data_dict.values():
        all_ft_names.update(typedefs.keys())
    
    all_ft_names = sorted(all_ft_names)
    dir_names = sorted(data_dict.keys())
    
    # Create figure
    fig, ax = plt.subplots(figsize=(max(12, len(dir_names) * 0.5), 
                                     max(8, len(all_ft_names) * 0.3)))
    
    # Create the grid
    for i, ft_name in enumerate(all_ft_names):
        for j, dir_name in enumerate(dir_names):
            # Check if this FT_ type exists in this directory
            if ft_name in data_dict[dir_name][0]:
                type_name = data_dict[dir_name][0][ft_name]
                usage = data_dict[dir_name][1][ft_name]
                
                # Color the cell if it's double
                if type_name == 'double':
                    color = '#4CAF50'  # Green for double
                    if usage:
                        ax.add_patch(mpatches.Rectangle((j, len(all_ft_names) - i - 1), 
                                                     1, 1, 
                                                     facecolor=color, 
                                                     edgecolor='black',
                                                     linewidth=0.5))
                    else:
                        ax.add_patch(mpatches.Rectangle((j, len(all_ft_names) - i - 1), 
                                                     1, 1, 
                                                     facecolor='red', 
                                                     edgecolor='black',
                                                     linewidth=0.5))
                else:  # float
                    if usage:
                        ax.add_patch(mpatches.Rectangle((j, len(all_ft_names) - i - 1), 
                                                     1, 1, 
                                                     facecolor='white', 
                                                     edgecolor='black',
                                                     linewidth=0.5))
                    else:
                        # Draw empty cell with gray color if type is not used
                        ax.add_patch(mpatches.Rectangle((j, len(all_ft_names) - i - 1), 
                                                 1, 1, 
                                                 facecolor='grey', 
                                                 edgecolor='black',
                                                 linewidth=0.5))
    

            else:
                ax.add_patch(mpatches.Rectangle((j, len(all_ft_names) - i - 1), 
                                                 1, 1, 
                                                 facecolor='red', 
                                                 edgecolor='lightgray',
                                                 linewidth=0.5))
            if "V" in ft_name:
                ax.text(
                    j + 0.5, len(all_ft_names) - i - 1 + 0.5,
                    str(usage),
                    ha='center',
                    va='center',
                    fontsize=8,
                    color='black'
                )
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
    missing_patch = mpatches.Patch(color='grey', label='not used')
    ax.legend(handles=[double_patch, float_patch, missing_patch], 
              loc='upper left', bbox_to_anchor=(1.02, 1))
    
    plt.tight_layout()
    plt.savefig("promiseResultGathered.png")
    plt.show()

# Example usage:
if __name__ == "__main__":
    # Method 1: Automatic scan for P1* directories with promiseTypes.h
    print("Scanning P1* directories...")
    typedef_data = find_and_scan_p_directories()

       # Print summary
    print(f"\nFound {len(typedef_data)} directories with typedef information:")
    for dir_name, (typedefs,used_typdefs) in typedef_data.items():
        print(f"  {dir_name}: {len(typedefs)} FT_ types")
    
    # Create the plot
    if typedef_data:
        print("\nGenerating plot...")
        plot_typedef_table(typedef_data)
    else:
        print("\nNo typedef data found in the specified directories.")
