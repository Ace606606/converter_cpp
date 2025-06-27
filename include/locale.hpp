// ./include/locale.hpp
#pragma once
#include <locale>
#include "logging.hpp"
#include <iostream>

namespace locale {

// update locale
void imbue_locale(const std::locale& locale) {
    std::wcout.imbue(locale);
    std::wcin.imbue(locale);
    std::wcerr.imbue(locale);

    std::cout.imbue(locale);
    std::cin.imbue(locale);
    std::cerr.imbue(locale);
}

int setup_streams_locale(const char* name_locale = "") {
    try {
        std::locale locale = std::locale(name_locale);
        locale::imbue_locale(locale);
        std::cout << LOGINFO << "Installed local: " << locale.name()
                  << std::endl;
        return 0;
    } catch (std::runtime_error& e) {
        std::locale locale = std::locale("C");
        locale::imbue_locale(locale);
        std::cerr << LOGERROR << "[name_locale:" << name_locale << "] "
                  << e.what() << std::endl;
        std::cerr << LOGERROR << "Use locale 'C'" << std::endl;
        return 1;
    }
}

}