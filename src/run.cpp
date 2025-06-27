#include "logging.hpp"
#include "FileHandler.hpp"
#include "locale.hpp"
#include <iostream>

void display_menu() {
    std::cout << "\nFile Manager Menu:\n";
    std::cout << "1. List directory contents\n";
    std::cout << "2. Change directory\n";
    std::cout << "3. Read file\n";
    std::cout << "4. Save file with different encoding\n";
    std::cout << "5. Print current directory\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);  // UTF-8 in Windows console
#endif

    locale::setup_streams_locale("C");

    try {
        FileHandler fm;
        std::cout << "Starting in home directory: "
                  << fm.get_current_directory() << std::endl;

        int choice = 0;
        do {
            display_menu();
            std::cin >> choice;
            std::cin.ignore();  // Clear newline

            try {
                switch (choice) {
                    case 1: {
                        fm.list_directory_contents();
                        break;
                    }
                    case 2: {
                        std::cout
                            << "Enter directory path (or .. for parent): ";
                        std::string path;
                        std::getline(std::cin, path);
                        fm.change_directory(path);
                        std::cout
                            << "Changed to: " << fm.get_current_directory()
                            << std::endl;
                        break;
                    }
                    case 3: {
                        std::cout << "Enter filename: ";
                        std::string filename;
                        std::getline(std::cin, filename);

                        std::cout << "Supported encodings:\n";
                        const auto& encodings = fm.get_supported_encodings();
                        for (size_t i = 0; i < encodings.size(); ++i) {
                            std::cout << i + 1 << ". " << encodings[i] << "\n";
                        }
                        std::cout << "Choose encoding (default 1 - UTF-8): ";

                        std::string enc_choice;
                        std::getline(std::cin, enc_choice);
                        std::string encoding = "UTF-8";
                        if (!enc_choice.empty()) {
                            size_t idx = std::stoul(enc_choice) - 1;
                            if (idx < encodings.size()) {
                                encoding = encodings[idx];
                            }
                        }

                        std::string content = fm.read_file(filename, encoding);
                        std::cout << "\nFile content (" << encoding << "):\n";
                        std::cout << content << std::endl;
                        break;
                    }
                    case 4: {
                        std::cout << "Enter source filename: ";
                        std::string src_filename;
                        std::getline(std::cin, src_filename);

                        std::cout << "Enter target filename: ";
                        std::string target_filename;
                        std::getline(std::cin, target_filename);

                        std::cout << "Supported encodings:\n";
                        const auto& encodings = fm.get_supported_encodings();
                        for (size_t i = 0; i < encodings.size(); ++i) {
                            std::cout << i + 1 << ". " << encodings[i] << "\n";
                        }
                        std::cout << "Choose target encoding: ";

                        std::string enc_choice;
                        std::getline(std::cin, enc_choice);
                        if (enc_choice.empty()) {
                            throw std::runtime_error(
                                "Encoding selection required");
                        }
                        size_t idx = std::stoul(enc_choice) - 1;
                        if (idx >= encodings.size()) {
                            throw std::runtime_error(
                                "Invalid encoding selection");
                        }
                        std::string encoding = encodings[idx];

                        // Read with current encoding (UTF-8)
                        std::string content = fm.read_file(src_filename);
                        // Save with new encoding
                        fm.save_file(target_filename, content, encoding);
                        std::cout << "File saved as " << target_filename
                                  << " with encoding " << encoding << std::endl;
                        break;
                    }
                    case 5: {
                        fm.print_current_directory();
                        break;
                    }
                    case 0: {
                        std::cout << "Exiting...\n";
                        break;
                    }
                    default: {
                        std::cout << "Invalid choice. Try again.\n";
                        break;
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } while (choice != 0);

    } catch (const std::exception& e) {
        std::cerr << LOGERROR << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}