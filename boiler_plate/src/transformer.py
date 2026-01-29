#!/usr/bin/env python3
"""
Transform C++ functions by adding explicit type casts to arithmetic operations.
Preserves original formatting while enabling per-line floating-point precision optimization.
"""

import re
import sys
from typing import Set, Tuple

class TypeCastTransformer:
    def __init__(self):
        self.new_types: Set[str] = set()
        self.max_depth = 50  # Prevent infinite recursion

    def extract_variable_name(self, line: str) -> str:
        """Extract the variable being assigned (e.g., 'V1[2]', 'TMP10', 'denom')"""
        # Match array assignment: V1[2] =
        match = re.match(r'^\s*(\w+)\[(\d+)\]\s*=', line)
        if match:
            return f"{match.group(1)}_{match.group(2)}"

        # Match variable declaration with type
        match = re.match(r'^\s*(?:const\s+)?(?:cxsmpl<[^>]+>|FT_\w+|cxtype_sv)\s+(\w+)\s*=', line)
        if match:
            return match.group(1)

        # Match simple assignment
        match = re.match(r'^\s*(\w+)\s*=', line)
        if match:
            return match.group(1)

        return "VAR"

    def create_type_name(self, var_name: str) -> str:
        """Create FT_for_VARNAME type name"""
        type_name = f"FT_for_{var_name}"
        self.new_types.add(type_name)
        return type_name

    def has_arithmetic(self, expr: str) -> bool:
        """Check if expression contains arithmetic operations"""
        if not expr:
            return False
        # Check for arithmetic operators (excluding -> and ::)
        return bool(re.search(r'(?<![:\-])[\+\-\*/](?![>:])', expr))

    def is_complex_type(self, token: str) -> bool:
        """Determine if token involves complex types"""
        token = token.strip()
        # Check for complex variables/functions
        return bool(re.search(r'(V\d+\[|TMP\d+|COUP\b|cI\b|cxreal|cximag|cxmake)', token))

    def wrap_operand(self, operand: str, cast_type: str) -> str:
        """Wrap a simple operand with appropriate cast"""
        operand = operand.strip()

        if not operand:
            return operand

        # Don't double-cast
        if operand.startswith('static_cast<'):
            return operand

        # Don't cast simple numeric literals
        if re.match(r'^[0-9]+\.?[0-9]*[fF]?$', operand):
            return operand

        is_complex = self.is_complex_type(operand)

        if is_complex:
            return f"static_cast<cxsmpl<{cast_type}>>({operand})"
        else:
            return f"static_cast<{cast_type}>({operand})"

    def strip_outer_parens(self, expr: str) -> tuple[str, bool]:
        """
        Remove outer parentheses if they wrap the entire expression.
        Returns (stripped_expr, had_outer_parens)
        """
        expr = expr.strip()
        if not expr.startswith('('):
            return expr, False

        # Check if opening paren matches closing paren at end
        depth = 0
        for i, c in enumerate(expr):
            if c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
            if depth == 0:
                # Found matching close paren
                if i == len(expr) - 1:
                    # It's at the end, so these are outer parens
                    return expr[1:-1], True
                else:
                    # Close paren is not at end, so not outer parens
                    return expr, False

        return expr, False

    def transform_expression(self, expr: str, cast_type: str, depth: int = 0) -> str:
        """
        Transform expression by wrapping operands with casts.
        Non-recursive approach using iteration.
        """
        if depth > self.max_depth:
            print(f"Warning: Max recursion depth reached, returning expr as-is", file=sys.stderr)
            return expr

        expr = expr.strip()

        # Base case: no expression or no arithmetic
        if not expr or not self.has_arithmetic(expr):
            return expr

        # Already transformed
        if expr.startswith('static_cast<'):
            return expr

        # Strip and remember outer parentheses
        stripped, had_parens = self.strip_outer_parens(expr)
        if had_parens:
            # Process inner content and re-wrap
            inner = self.transform_expression(stripped, cast_type, depth + 1)
            return f"( {inner} )"

        # Now process operators at the top level
        result = []
        current = []
        paren_depth = 0
        i = 0

        while i < len(expr):
            c = expr[i]

            if c == '(':
                paren_depth += 1
                current.append(c)
            elif c == ')':
                paren_depth -= 1
                current.append(c)
            elif paren_depth == 0 and c in '+-*/':
                # Check it's not -> or part of ::
                if c == '-' and i + 1 < len(expr) and expr[i + 1] == '>':
                    current.append(c)
                elif c == '-' and i > 0 and expr[i - 1] == ':':
                    current.append(c)
                else:
                    # It's an operator at top level
                    operand = ''.join(current).strip()
                    if operand:
                        # Check if operand has parens (sub-expression)
                        if '(' in operand:
                            # Recursively process sub-expression
                            operand = self.transform_expression(operand, cast_type, depth + 1)
                        else:
                            # Simple operand, just wrap it
                            operand = self.wrap_operand(operand, cast_type)
                        result.append(operand)

                    result.append(f' {c} ')
                    current = []
            else:
                current.append(c)

            i += 1

        # Process last operand
        operand = ''.join(current).strip()
        if operand:
            if '(' in operand:
                operand = self.transform_expression(operand, cast_type, depth + 1)
            else:
                operand = self.wrap_operand(operand, cast_type)
            result.append(operand)

        return ''.join(result)

    def transform_line(self, line: str) -> str:
        """Transform a single line by adding type casts to arithmetic operations"""
        # Preserve lines without assignments
        if '=' not in line:
            return line

        # Split on first = to get LHS and RHS
        eq_pos = line.find('=')
        lhs = line[:eq_pos]
        rest = line[eq_pos + 1:]

        # Extract semicolon and trailing content
        if ';' in rest:
            semi_pos = rest.rfind(';')
            rhs = rest[:semi_pos]
            trailing = rest[semi_pos:]
        else:
            rhs = rest
            trailing = ''

        # Check if RHS has arithmetic
        if not self.has_arithmetic(rhs):
            return line

        # Get variable name for type naming
        var_name = self.extract_variable_name(lhs)
        cast_type = self.create_type_name(var_name)

        # Check for outer cast that should be preserved
        outer_cast_match = re.match(r'\s*static_cast<cxsmpl<FT_w>>\s*\(\s*(.*)\s*\)\s*$', rhs, re.DOTALL)

        if outer_cast_match:
            # Transform inner expression, preserve outer cast
            inner = outer_cast_match.group(1)
            transformed = self.transform_expression(inner, cast_type, depth=0)
            return f"{lhs}=static_cast<cxsmpl<FT_w>>( {transformed} ){trailing}"
        else:
            # Transform entire RHS
            transformed = self.transform_expression(rhs, cast_type, depth=0)
            return f"{lhs}={transformed}{trailing}"

    def transform_function(self, code: str) -> Tuple[str, Set[str]]:
        """Transform entire function, preserving structure"""
        lines = code.split('\n')
        transformed_lines = [self.transform_line(line) for line in lines]
        return '\n'.join(transformed_lines), self.new_types


def main():
    """Command-line interface"""
    if len(sys.argv) > 1:
        # Read from file
        with open(sys.argv[1], 'r') as f:
            code = f.read()
    else:
        # Read from stdin
        print("Reading from stdin (paste code, then Ctrl+D):", file=sys.stderr)
        code = sys.stdin.read()

    transformer = TypeCastTransformer()
    transformed, new_types = transformer.transform_function(code)

    print(transformed)
    print("\n// New floating-point types defined:")
    for t in sorted(new_types):
        print(f"// typedef <base_type> {t};")

if __name__ == "__main__":
    main()