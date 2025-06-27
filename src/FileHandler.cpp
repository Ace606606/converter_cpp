#include "FileHandler.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#else
#include <pwd.h>
#include <unistd.h>
#endif

namespace detail {
// return home-directory
std::string get_home_directory() {
#ifdef _WIN32
    const char* home = getenv("USERPROFILE");
    if (home == nullptr) {
        home = getenv("HOMEDRIVE");
        const char* path = getenv("HOMEPATH");
        if (home != nullptr && path != nullptr) {
            return std::string(home) + path;
        }
    }
    return home ? home : "C:\\";
#else
    const char* home = getenv("HOME");
    if (home == nullptr) {
        struct passwd* pw = getpwuid(getuid());
        if (pw != nullptr) {
            home = pw->pw_dir;
        }
    }
    return home ? home : "/";
#endif
}

}  // namespace detail

void FileHandler::change_directory_impl(const fs::path& path) {
    if (!fs::exists(path)) {
        throw std::runtime_error("Directory does not exist: " + path.string());
    }

    if (!fs::is_directory(path)) {
        throw std::runtime_error("Path is not a directory: " + path.string());
    }

    try {
        _current_dir = fs::canonical(path);
    } catch (const fs::filesystem_error& e) {
        throw std::runtime_error("Cannot access directory: " + path.string());
    }
}

std::string FileHandler::read_file_impl(const fs::path& filepath,
                                        const std::string& encoding) const {
    if (!fs::exists(filepath)) {
        throw std::runtime_error("File does not exist: " + filepath.string());
    }

    if (!fs::is_regular_file(filepath)) {
        throw std::runtime_error("Path is not a file: " + filepath.string());
    }

    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filepath.string());
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    if (encoding == "UTF-16") {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>
            converter;
        std::u16string utf16 = converter.from_bytes(content);
        return std::string(reinterpret_cast<const char*>(utf16.data()),
                           utf16.size() * sizeof(char16_t));
    } else if (encoding == "Windows-1251") {
        return content;
    } else if (encoding == "ASCII") {
        content.erase(
            std::remove_if(
                content.begin(), content.end(),
                [](char c) { return static_cast<unsigned char>(c) > 127; }),
            content.end());
        return content;
    }

    return content;
}

void FileHandler::save_file_impl(const fs::path& filepath,
                                 const std::string& content,
                                 const std::string& encoding) const {
    std::ofstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot create file: " + filepath.string());
    }

    if (encoding == "UTF-16") {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>
            converter;
        std::u16string utf16 = converter.from_bytes(content);
        file.write(reinterpret_cast<const char*>(utf16.data()),
                   utf16.size() * sizeof(char16_t));
    } else if (encoding == "Windows-1251" || encoding == "ASCII") {
        file << content;
    } else {
        file << content;
    }
}

FileHandler::FileHandler() : _current_dir(detail::get_home_directory()) {}

void FileHandler::change_directory(const std::string& path) {
    fs::path new_path = path;
    if (path.empty()) {
        new_path = detail::get_home_directory();
    } else if (path == "..") {
        if (_current_dir.has_parent_path()) {
            new_path = _current_dir.parent_path();
        }
    } else if (!path.empty() && path[0] != '/' && path[0] != '\\'
#ifdef _WIN32
               && path.find(':') == std::string::npos
#endif
    ) {
        new_path = _current_dir / path;
    }

    change_directory_impl(new_path);
}

void FileHandler::print_current_directory() const {
    std::cout << "Current directory: " << _current_dir.string() << std::endl;
}

void FileHandler::list_directory_contents() const {
    std::cout << "Contents of " << _current_dir.string() << ":\n";

    try {
        for (const auto& entry : fs::directory_iterator(_current_dir)) {
            std::cout << (entry.is_directory() ? "[D] " : "[F] ")
                      << entry.path().filename().string() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        throw std::runtime_error("Cannot list directory contents: " +
                                 std::string(e.what()));
    }
}

std::string FileHandler::read_file(const std::string& filename,
                                   const std::string& encoding) const {
    fs::path filepath = _current_dir / filename;
    return read_file_impl(filepath, encoding);
}

void FileHandler::save_file(const std::string& filename,
                            const std::string& content,
                            const std::string& encoding) const {
    fs::path filepath = _current_dir / filename;
    save_file_impl(filepath, content, encoding);
}

const std::vector<std::string>& FileHandler::get_supported_encodings() const {
    return _supported_encodings;
}

std::string FileHandler::get_current_directory() const {
    return _current_dir.string();
}