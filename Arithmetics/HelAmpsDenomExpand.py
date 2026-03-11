import os.path
import re

new_lines = []


denom_string = """
    const MG_ARITHM::Double<fptype> P{0}d[4] = {{ -cxreal( {1}{0}[0] ), -cxreal( {1}{0}[1] ), -cximag( {1}{0}[1] ), -cximag( {1}{0}[0] ) }};
    const MG_ARITHM::Double<fptype> Md{0} = M{0};
    const fptype_sv PmM2 = static_cast<fptype_sv>(( P{0}d[0] * P{0}d[0] ) - ( P{0}d[1] * P{0}d[1] ) - ( P{0}d[2] * P{0}d[2] ) - ( P{0}d[3] * P{0}d[3] ) - (Md{0} * Md{0}));
    const fptype_sv iMW = M{0} * W{0};
    const cxtype_sv denden = cxmake( PmM2, iMW );
    const cxtype_sv denom = Ccoeff * COUP / denden;
"""
if os.path.isfile("../HelAmps_sm_backup"):
    file = "../HelAmps_sm_backup"
else:
    file = "../HelAmps_sm.h" 

with open(file, "r") as f:
    lines = f.readlines()
    for idx, line in enumerate(lines):
        if '#include "mgOnGpuConfig.h"' in line:
            new_lines.append(line)
            new_lines.append('    #include "Arithmetics/Double.h"\n')

        if "cxtype_sv denom" in line and "//" not in line:
            if  "P" not in line:
                print("Fail there is no P in line")
                print(line)
            idxx = idx - 1
            wave = None

            while idxx >= 0:
                pline = lines[idxx]

                if "  {" == pline:
                    break

                if re.search(r'P\d\[4', pline):
                    m = re.search(r'-cxreal\(\s*([A-Z]\d)\[', pline)
                    if m:
                        wave = m.group(1)[0]
                    break

                idxx -= 1

            m = re.search(r'P(\d+)\[0\]', line)
            new_lines.append("//" + line)
            new_lines.append(denom_string.format(m.group(1),wave))

        else:
            new_lines.append(line)
with open("../HelAmps_sm_backup" , "w") as f:
    f.writelines(lines)
with open("../HelAmps_sm.h" , "w") as f:
    f.writelines(new_lines)
