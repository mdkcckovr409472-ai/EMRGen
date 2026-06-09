import os
import re
from fractions import Fraction
TOLERANCE = 1e-9
MAX_DENOMINATOR = 100
MAGNITUDE_DISPARITY_THRESHOLD = 1e5           

def _parse_invariant(invariant_str: str) -> list[tuple[float, str]]:
    """[内部函数] 解析Daikon不变量字符串。"""
    if '==' in invariant_str:
        invariant_str = invariant_str.split('==')[0].strip()
    if not invariant_str:
        return []
    temp_str = re.sub(r'\s*([+-])\s*(?=[0-9\.])', r' \1 ', invariant_str)
    if temp_str.startswith('- '):
        temp_str = '-' + temp_str[2:]
    terms_str = re.split(r'\s+[+-]\s+', temp_str)
    operators = ['+'] + re.findall(r'\s+([+-])\s+', temp_str)
    parsed_terms = []
    for i, term_str in enumerate(terms_str):
        term_str = term_str.strip()
        sign = 1.0 if operators[i] == '+' else -1.0
        if i == 0 and term_str.startswith('-'):
            sign = -1.0
            term_str = term_str[1:].strip()
        parts = term_str.split('*')
        try:
            if len(parts) == 2:
                coeff = float(parts[0].strip())
                var = parts[1].strip()
                parsed_terms.append((sign * coeff, var))
            elif len(parts) == 1:
                coeff = float(parts[0].strip())
                var = '1'
                parsed_terms.append((sign * coeff, var))
        except (ValueError, IndexError):
            return []
    return parsed_terms

def _simplify_terms(terms: list[tuple[float, str]]) -> list[tuple[float, str]]:
    """[内部函数] 化简解析后的项列表。"""
    if not terms:
        return []
    non_zero_coeffs = [abs(c) for c, v in terms if abs(c) > TOLERANCE]
    if len(non_zero_coeffs) < 2:
        return terms
    min_c = min(non_zero_coeffs)
    max_c = max(non_zero_coeffs)
    base_divisor = min_c
    if (max_c / min_c > MAGNITUDE_DISPARITY_THRESHOLD) and (len(non_zero_coeffs) > 2):
        other_coeffs = [c for c in non_zero_coeffs if c != min_c]
        if other_coeffs:
            base_divisor = min(other_coeffs)
    simplified_terms = []
    for coeff, var in terms:
        if abs(coeff / base_divisor) < TOLERANCE:
            continue
        norm_coeff = coeff / base_divisor
        frac = Fraction(norm_coeff).limit_denominator(MAX_DENOMINATOR)
        if abs(float(frac) - norm_coeff) < TOLERANCE:
            simplified_terms.append((float(frac), var))
        else:
            return []
    return simplified_terms

def _format_simplified_invariant(simplified_terms: list[tuple[float, str]]) -> str:
    """[内部函数] 将化简后的项列表格式化为人类可读的字符串。"""
    if not simplified_terms:
        return ""
    simplified_terms.sort(key=lambda x: x[1] == '1')
    result_parts = []
    for i, (coeff, var) in enumerate(simplified_terms):
        sign = " + " if coeff > 0 else " - "
        abs_coeff = abs(coeff)
        if i == 0:
            sign = "" if coeff > 0 else "-"
        if abs_coeff == 1 and var != '1':
            coeff_str = ""
        elif abs_coeff == int(abs_coeff):
            coeff_str = str(int(abs_coeff))
        else:
            coeff_str = f"{abs_coeff:.4f}".rstrip('0').rstrip('.')
        if var == '1':
            part = f"{sign}{coeff_str}"
        else:
            part = f"{sign}{coeff_str} * {var}" if coeff_str else f"{sign}{var}"
        result_parts.append(part)
    return "".join(result_parts).strip() + " == 0"

def simplify_daikon_report(file_path: str, verbose: bool = True) -> bool:
    """
    读取指定的 Daikon 报告文件，就地简化其中复杂的浮点数不变量。
    Args:
        file_path (str): 要处理的文件的完整路径。
        verbose (bool): 是否在控制台打印详细的处理信息。默认为 True。
    Returns:
        bool: 如果文件被修改则返回 True，否则返回 False。
    """
    if not os.path.isfile(file_path):
        if verbose:
            print(f"错误: 文件不存在 -> {file_path}")
        return False
    complex_invariant_regex = re.compile(r"(\d\.\d+E[+-]?\d+.*){2,}")
    new_lines = []
    made_changes = False
    try:
        if verbose:
            print(f"正在处理文件: {file_path}")
        with open(file_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        for line in lines:
            original_line = line.strip()
            if "==" in original_line and complex_invariant_regex.search(original_line):
                parsed = _parse_invariant(original_line)
                if parsed:
                    simplified = _simplify_terms(parsed)
                    formatted_result = _format_simplified_invariant(simplified)
                    if formatted_result and formatted_result != original_line:
                        indentation = line[:len(line) - len(line.lstrip())]
                        new_lines.append(indentation + formatted_result + '\n')
                        if verbose:
                            print(f"  - 原始: {original_line}")
                            print(f"  + 简化: {formatted_result}")
                        made_changes = True
                    else:
                        new_lines.append(line)
                else:
                    new_lines.append(line)
            else:
                new_lines.append(line)
        if made_changes:
            with open(file_path, 'w', encoding='utf-8') as f:
                f.writelines(new_lines)
            if verbose:
                print(f"  文件已成功更新。")
        else:
            if verbose:
                print(f"  未发现可简化的不变量或无需修改。")
        return made_changes
    except Exception as e:
        if verbose:
            print(f"  处理文件时发生错误 {file_path}: {str(e)}")
        return False
if __name__ == "__main__":
    print("--- Daikon Simplifier 模块测试 ---")
    fake_report_content = """
==================================
:::ENTER
  9.06041561752535E14 * return.result1[] - 9.06041561752535E14 * return.result2[] - 9.06041561752536E14 == 0
  y one of {1, 2, 3}
  1.4790821599836004E16 * Os - 7.395410799918003E15 * Of + 256 == 0
==================================
"""
    test_file_path = "test_daikon_report.txt"
    with open(test_file_path, "w", encoding='utf-8') as f:
        f.write(fake_report_content)
    changes_were_made = simplify_daikon_report(test_file_path)
    print(f"\n函数返回: {changes_were_made}")
    print("\n--- 更新后的文件内容 ---")
    with open(test_file_path, "r", encoding='utf-8') as f:
        print(f.read())
    os.remove(test_file_path)
