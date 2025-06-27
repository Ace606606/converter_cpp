// ./include/FileHandler.hpp

#pragma once

#include <vector>
#include "config.hpp"

#include <filesystem>
namespace fs = std::filesystem;

class FileHandler {
   private:
    // текущая директория
    fs::path _current_dir;
    // поддерживаемые кодировки
    std::vector<std::string> _supported_encodings = {"UTF-8", "UTF-16",
                                                     "Windows-1251", "ASCII"};
    // внутрення логика                                          
    void change_directory_impl(const fs::path& path);
    std::string read_file_impl(const fs::path& filepath,
                               const std::string& encoding) const;
    
    void save_file_impl(const fs::path& filepath, const std::string& content,
                        const std::string& encoding) const;

   public:
    FileHandler();
    // изменить текущую директорию 
    void change_directory(const std::string& path);
    // отображение текущей директории
    void print_current_directory() const;
    // отобразить содержимое текущей директории
    void list_directory_contents() const;
    // чтение файла в текущей директории
    std::string read_file(const std::string& filename,
                          const std::string& encoding = "UTF-8") const;
    // сохранить файл
    void save_file(const std::string& filename, const std::string& content,
                   const std::string& encoding = "UTF-8") const;
    // вывести поддерживаемые кодировки
    const std::vector<std::string>& get_supported_encodings() const;
    // вывести текущую директорию
    std::string get_current_directory() const;
};