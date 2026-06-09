import sys
import os
import subprocess

def main():
    if len(sys.argv) > 1:
        target_file = sys.argv[1]
    else:
        target_file = input("请输入 .cpp 文件的完整路径: ").strip()
    if not target_file:
        print("错误: 未提供有效路径。")
        sys.exit(1)
    target_file = os.path.abspath(target_file)
    if not os.path.isfile(target_file):
        print(f"错误: 文件不存在: {target_file}")
        sys.exit(1)
    parent_dir = os.path.dirname(target_file)                                     
    p_info_dir = os.path.join(parent_dir, "P_Info")                                      
    script_dir = os.path.dirname(os.path.abspath(__file__))
    scripts = [
        os.path.join(script_dir, "deepseek_run_trace_generation_driver.py"),
        os.path.join(script_dir, "extract_cpp_to_Pinfo.py"),
        os.path.join(script_dir, "gene_EMR_inv.py")
    ]
    args_list = [
        [target_file],                           
        [parent_dir],                        
        [p_info_dir]                            
    ]
    for script_path, args in zip(scripts, args_list):
        if not os.path.isfile(script_path):
            print(f"错误: 脚本不存在: {script_path}")
            sys.exit(1)
        cmd = [sys.executable, script_path] + args
        print(f"\n正在执行: {' '.join(cmd)}")
        result = subprocess.run(cmd, capture_output=False, text=True)        
        if result.returncode != 0:
            print(f"错误: 脚本 {os.path.basename(script_path)} 执行失败 (返回码 {result.returncode})")
            sys.exit(result.returncode)
        else:
            print(f"脚本 {os.path.basename(script_path)} 执行成功。")
    print("\n所有步骤已完成。")
if __name__ == "__main__":
    main()
