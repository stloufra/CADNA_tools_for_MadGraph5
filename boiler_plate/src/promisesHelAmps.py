import re
from typing import List, Set, Tuple

def extract_function_signature(text: str, start_pos: int) -> Tuple[str, int, int]:
    """Extract function signature and body bounds."""
    # Find the opening brace
    brace_count = 0
    in_function = False
    func_start = start_pos
    func_end = start_pos

    for i in range(start_pos, len(text)):
        if text[i] == '{':
            if not in_function:
                in_function = True
                func_start = i
            brace_count += 1
        elif text[i] == '}':
            brace_count -= 1
            if in_function and brace_count == 0:
                func_end = i + 1
                break

    return text[start_pos:func_end], func_start, func_end

def extract_function_argumets(text: str, start_pos: int) -> Tuple[str, str]:
    """Extract function arguments from signature."""
    brace_count = 0
    in_args = False
    args_start = start_pos
    args_end = start_pos

    for i in range(start_pos, len(text)):
        if text[i] == '(':
            in_args = True
            args_start = i
        elif text[i] == ')':
            in_args = False
            args_end = i + 1
            break

    argumets_text = text[args_start:args_end]
    arg_const = []
    arg_non_const = []
    for line in argumets_text.split('\n'):
        if 'const' in line:
            line.strip()
            line = line.replace('const', '')
            line = line.replace('fptype','')
            line = line.replace('[]','')
            line = line.replace(',','')
            line = line.replace(' ','')
            line = line.replace(')','')
            line = line.replace('(','')
            arg_const.append(line)
        else:
            line.strip()
            line = line.replace('const', '')
            line = line.replace('fptype','')
            line = line.replace('all','')
            line = line.replace('[]','')
            line = line.replace(',','')
            line = line.replace(' ','')
            line = line.replace(')','')
            line = line.replace('(','')
            if "vertexes" in line:
                line = line.replace("vertexes","vertex")
            arg_non_const.append(line)

    assert len(arg_non_const) ==1, "More than one returning argument"
    return arg_const, arg_non_const

def get_function_name(signature: str) -> str:
    """Extract function name from signature."""
    # Look for pattern like FUNC_NAME( after __device__
    match = re.search(r'(\w+)\s*\(', signature)
    if match:
        return match.group(1)
    return ""

def should_transform_function(func_text: str, func_name: str) -> bool:
    """Determine if function should be transformed."""
    # Transform functions that:
    # 1. Have vertex or amplitude computation (contain vertex = or *vertex =)
    # 2. Are computation functions (end with _0 or similar pattern)
    # 3. Have cxtype_sv operations
    if "INLINE" in func_text:
        return False
    if re.search(r'\*?\s*vertex\s*\)', func_text) or 'allvertexes' in func_text:
        if re.search(r'cxtype_sv', func_text):
            return True
    if func_name.endswith('_0') or func_name.endswith('_1'):
        return True
    if func_name.startswith('V') or func_name.startswith('F'):
        return True
    return False

def wrap_cx_calls(line: str, ft_type: str) -> str:
    # Negative lookbehind to ensure we are not already inside static_cast<ft_type>(
    pattern = rf'(?<!static_cast<{re.escape(ft_type)}>\()([+\-]\s*(?:cxreal|cximag)\s*\([^()]*\))'
    return re.sub(
        pattern,
        lambda m: f"static_cast<{ft_type}>({m.group(1)})",
        line,
    )

def transform_function(func_text: str, func_name: str) -> Tuple[str, str, int]:
    """Transform a single function to use FT_ types, now including F arrays and casting outputs."""

    line_count_start = len(func_text.split('\n'))

    ft_type = f"FT_{func_name}"
    arg_const, arg_out = extract_function_argumets(func_text, func_text.find('('))
    body_begin = func_text.find('{')
    func_text = func_text.replace("\r\n", "\n")

    body = func_text[body_begin:]
    before = func_text[:body_begin]

    lines = body.split('\n')
    new_lines = []
    in_ACCESS = False
    find_end = False

    for line in lines:
        new_line = line
        if "ACCESS" in line:
            in_ACCESS = True
            for arg in arg_const:
                arg = arg.replace("all","")
                if arg in new_line and "ACCESS" in new_line:
                    new_line = new_line.replace(" " + arg, " " + arg + "_")
        if in_ACCESS and "ACCESS" not in new_line:
            in_ACCESS = False
            for arg in arg_const:
                if "all" in arg:
                    if "COUP" in arg:
                        new_lines.append("\t \t const cxsmpl<" + ft_type + "> COUP = static_cast<cxsmpl<" + ft_type + ">>(COUP_);")
                    else:
                        arg = arg.replace("all","")
                        new_lines.append("\t \t cxsmpl<" + ft_type + "> " + arg + "[6];")
                        #new_lines.append("\t \t cxsmpl<" + ft_type + "> " + arg  + "=static_cast<cxsmpl<" + ft_type + ">>(" + arg +");")
            new_lines.append("\t\tfor(int i = 0; i < 6; ++i)")

            new_lines.append("\t\t{")
            for arg in arg_const:
                if "all" in arg and "COUP" not in arg:
                    arg = arg.replace("all","")
                    new_lines.append("\t \t " + arg + "[i] = static_cast<cxsmpl<" + ft_type + ">>(" + arg + "_[i]);")
            new_lines.append("\t\t}")
        if not in_ACCESS:
            new_line = new_line.replace("fptype", ft_type).replace("_sv","")
            new_line = new_line.replace("cxtype", "cxsmpl<"+ft_type+">").replace("_sv","")
            new_line = new_line.replace("cxmake<fptype>", "cxmake<"+ft_type+">")
            for arg in arg_const:
                if "all" not in arg and arg in line:
                    new_line = new_line.replace(arg, "static_cast<"+ft_type+">("+arg+")")

            if arg_out[0] in line and "const" not in line:
                arg = arg_out[0]
                if ";" in new_line:
                    new_line = new_line[:new_line.find("=")+1] + "static_cast<cxsmpl<fptype>>(" +new_line[new_line.find("=")+1:].replace(";","")  + ");"
                else:
                    new_line = new_line[:new_line.find("=")+1] + "static_cast<cxsmpl<fptype>>(" +new_line[new_line.find("=")+1:]
                    find_end = True

            if arg_out[0] in line and "const" in line:
                arg = arg_out[0]
                new_line = wrap_cx_calls(new_line, ft_type)

            for arg in arg_const:
                if "all" in arg:
                    arg = arg.replace("all","")
                    if arg in new_line and "const" in new_line and "cxsmp" not in new_line:
                        new_line = wrap_cx_calls(new_line, ft_type)

            if find_end:
                if ";" in new_line:
                    new_line = new_line.replace(";",");")
                    find_end = False

        new_lines.append(new_line)

    # Reassemble
    func_text = before + "\n".join(new_lines)
    inserted_lines = len(func_text.split('\n')) - line_count_start

    return func_text, ft_type, inserted_lines

def process_file(input_text: str) -> Tuple[str, List[str]]:
    """Process entire file and return modified text and list of FT types."""

    input_text = input_text.replace("cxmake", "cxmake<fptype>")

    output_text = input_text
    ft_types: List[str] = []

    # Find all __device__ functions in the original text
    pattern = r'(template\s*<[^>]+>\s*)?__device__\s+(?:INLINE\s+)?void\s+(\w+)\s*\('
    matches = list(re.finditer(pattern, input_text))

    # Cumulative character offset between input_text positions and output_text
    offset = 0

    for match in matches:
        func_name = match.group(2)
        start_pos = match.start()

        # Extract full function from the original input_text
        func_text, _, func_end = extract_function_signature(input_text, start_pos)
        original_len = func_end - start_pos  # length in characters

        if should_transform_function(func_text, func_name):
            print(func_name)
            transformed, ft_type, more = transform_function(func_text, func_name)
            # If `more` is "additional lines", convert to characters instead or
            # better: let transform_function return the full transformed text
            transformed_len = len(transformed)

            # Compute positions in the current output_text
            out_start = start_pos + offset
            out_end = out_start + original_len

            # Replace in output_text
            output_text = output_text[:out_start] + transformed + output_text[out_end:]

            # Update offset by the character delta
            offset += transformed_len - original_len

            ft_types.append(ft_type)

    return output_text, sorted(set(ft_types))

# Read input file
with open('HelAmps_sm.h', 'r') as f:
    input_text = f.read()

# Process file
output_text, ft_types = process_file(input_text)
#import shutil
#shutil.copy('HelAmps_sm.h', 'HelAmps_sm_original.h')
# Write output file
with open('HelAmps_sm_transformed.h', 'w') as f:
    f.write(output_text)

# Print FT types
print("Generated FT types:")
print("=" * 50)
for ft_type in ft_types:
    print(f"typedef __PR_{ft_type.strip().replace("_","").replace("FT","")}__  {ft_type};")
print("=" * 50)
for ft_type in ft_types:
    print(f"typedef float {ft_type};")
print("=" * 50)
print(f"\nTotal: {len(ft_types)} types")
print(f"\nTransformed file written to: HelAmps_sm_transformed.h")

'''
 // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], V3[6]
    template <class W_ACCESS, class A_ACCESS, class C_ACCESS>
    __device__ void
    VVV1_0(const fptype allV1[],
           const fptype allV2[],
           const fptype allV3[],
           const fptype allCOUP[],
           const fptype Ccoeff,
           fptype allvertexes[])
    {
        mgDebug(0, __FUNCTION__);

        const cxtype_sv* V1_ = W_ACCESS::kernelAccessConst(allV1);
        const cxtype_sv* V2_ = W_ACCESS::kernelAccessConst(allV2);
        const cxtype_sv* V3_ = W_ACCESS::kernelAccessConst(allV3);
        const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst(allCOUP);

        cxsmpl<FT_VVV1_0> V1[6];
        cxsmpl<FT_VVV1_0> V2[6];
        cxsmpl<FT_VVV1_0> V3[6];

        cxsmpl<FT_VVV1_0> COUP = static_cast<cxsmpl<FT_VVV1_0>>(COUP_);
        for (int i = 0; i < 6; ++i)
        {
            V1[i] = static_cast<cxsmpl<FT_VVV1_0>>(V1_[i]);
            V2[i] = static_cast<cxsmpl<FT_VVV1_0>>(V2_[i]);
            V3[i] = static_cast<cxsmpl<FT_VVV1_0>>(V3_[i]);
        }

        cxsmpl<FT_VVV1_0>* vertex = A_ACCESS::kernelAccess(allvertexes);
        const cxsmpl<FT_VVV1_0> cI = cxmake(0., 1.);
        const FT_VVV1_0 P1[4] = {+cxreal(V1[0]), +cxreal(V1[1]), +cximag(V1[1]), +cximag(V1[0])};
        const FT_VVV1_0 P2[4] = {+cxreal(V2[0]), +cxreal(V2[1]), +cximag(V2[1]), +cximag(V2[0])};
        const FT_VVV1_0 P3[4] = {+cxreal(V3[0]), +cxreal(V3[1]), +cximag(V3[1]), +cximag(V3[0])};
        const cxsmpl<FT_VVV1_0> TMP0 = (V3[2] * P1[0] - V3[3] * P1[1] - V3[4] * P1[2] - V3[5] * P1[3]);
        const cxsmpl<FT_VVV1_0> TMP1 = (V2[2] * V1[2] - V2[3] * V1[3] - V2[4] * V1[4] - V2[5] * V1[5]);
        const cxsmpl<FT_VVV1_0> TMP2 = (V3[2] * P2[0] - V3[3] * P2[1] - V3[4] * P2[2] - V3[5] * P2[3]);
        const cxsmpl<FT_VVV1_0> TMP3 = (V3[2] * V1[2] - V3[3] * V1[3] - V3[4] * V1[4] - V3[5] * V1[5]);
        const cxsmpl<FT_VVV1_0> TMP4 = (P1[0] * V2[2] - P1[1] * V2[3] - P1[2] * V2[4] - P1[3] * V2[5]);
        const cxsmpl<FT_VVV1_0> TMP5 = (V2[2] * P3[0] - V2[3] * P3[1] - V2[4] * P3[2] - V2[5] * P3[3]);
        const cxsmpl<FT_VVV1_0> TMP6 = (V3[2] * V2[2] - V3[3] * V2[3] - V3[4] * V2[4] - V3[5] * V2[5]);
        const cxsmpl<FT_VVV1_0> TMP7 = (V1[2] * P2[0] - V1[3] * P2[1] - V1[4] * P2[2] - V1[5] * P2[3]);
        const cxsmpl<FT_VVV1_0> TMP8 = (V1[2] * P3[0] - V1[3] * P3[1] - V1[4] * P3[2] - V1[5] * P3[3]);
        (*vertex) = static_cast<cxsmpl<FT_VVV1_0>>( Ccoeff * COUP * (TMP1 * (-cI * TMP0 + cI * TMP2) + (TMP3 * (+cI * TMP4 - cI * TMP5) + TMP6 * (-cI *
            TMP7 + cI * TMP8))));
        mgDebug(1, __FUNCTION__);
        return;
    }
'''