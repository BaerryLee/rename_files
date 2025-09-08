#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string directory_path;
    std::string old_extension;
    std::string new_extension;

    std::cout << "请输入要修改文件的目录路径: ";
    std::getline(std::cin, directory_path);

    std::cout << "请输入旧的文件后缀名 (例如: .txt): ";
    std::getline(std::cin, old_extension);

    std::cout << "请输入新的文件后缀名 (例如: .log): ";
    std::getline(std::cin, new_extension);

    // 检查目录路径是否存在且有效
    if (!fs::exists(directory_path) || !fs::is_directory(directory_path)) {
        std::cerr << "错误：指定的目录路径无效或不存在。" << std::endl;
        return 1;
    }

    int files_renamed = 0;
    
    // 遍历指定目录下的所有文件
    for (const auto& entry : fs::directory_iterator(directory_path)) {
        // 检查当前 entry 是否为文件，而不是目录
        if (fs::is_regular_file(entry.status())) {
            // 获取文件的完整路径
            fs::path file_path = entry.path();
            
            // 检查文件是否有后缀名，并且后缀名是否与旧的后缀名匹配
            if (file_path.has_extension() && file_path.extension() == old_extension) {
                try {
                    // 构建新的文件路径，用新的后缀名替换旧的后缀名
                    fs::path new_file_path = file_path.parent_path() / (file_path.stem().string() + new_extension);

                    // 重命名文件
                    fs::rename(file_path, new_file_path);
                    std::cout << "已重命名: " << file_path.string() << " -> " << new_file_path.string() << std::endl;
                    files_renamed++;
                } catch (const fs::filesystem_error& e) {
                    std::cerr << "错误：无法重命名文件 " << file_path.string() << " - " << e.what() << std::endl;
                }
            }
        }
    }

    std::cout << "\n完成！总共修改了 " << files_renamed << " 个文件。" << std::endl;

    return 0;
}
