import os

def batch_rename_extension(directory_path, old_extension, new_extension):
    """
    批量修改指定目录下文件的后缀名。

    Args:
        directory_path (str): 要修改文件的目录路径。
        old_extension (str): 旧的文件后缀名，例如 '.txt'。
        new_extension (str): 新的文件后缀名，例如 '.log'。
    """
    # 检查目录是否存在
    if not os.path.isdir(directory_path):
        print(f"错误：指定的目录路径 '{directory_path}' 无效或不存在。")
        return

    # 确保后缀名以 '.' 开头
    if not old_extension.startswith('.'):
        old_extension = '.' + old_extension
    if not new_extension.startswith('.'):
        new_extension = '.' + new_extension

    files_renamed = 0
    
    # 遍历目录中的所有文件
    for filename in os.listdir(directory_path):
        # 组合完整的文件路径
        file_path = os.path.join(directory_path, filename)
        
        # 检查是否为文件，并且文件名以旧的后缀名结尾
        if os.path.isfile(file_path) and filename.endswith(old_extension):
            try:
                # 构建新的文件名
                new_filename = filename[:-len(old_extension)] + new_extension
                new_file_path = os.path.join(directory_path, new_filename)
                
                # 重命名文件
                os.rename(file_path, new_file_path)
                print(f"已重命名: {filename} -> {new_filename}")
                files_renamed += 1
            except OSError as e:
                print(f"错误：无法重命名文件 '{filename}' - {e}")
    
    print(f"\n完成！总共修改了 {files_renamed} 个文件。")

# --- 程序入口 ---
if __name__ == "__main__":
    dir_path = input("请输入要修改文件的目录路径: ")
    old_ext = input("请输入旧的文件后缀名 (例如: .txt): ")
    new_ext = input("请输入新的文件后缀名 (例如: .log): ")

    batch_rename_extension(dir_path, old_ext, new_ext)
