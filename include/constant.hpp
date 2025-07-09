// ./include/constant.hpp
#pragma once
#include <QByteArray>
#include <QString>

namespace AppConstants {

inline const QString APP_NAME = "Конвертер файлов на Qt";
inline const QString APP_VERSION = "1.0.0";
inline const int WINDOW_WIDTH = 800;
inline const int WINDOW_HEIGHT = 600;
inline const QString LABEL_FILESYSTEM = "Файловая система:";
inline const QString LABEL_ENCODING = "Кодировка:";
inline const QString LABEL_PATH = "Текущий путь:";
inline const QString LABEL_CONTENT = "Содержимое файла:";

inline const QString DEFAULT_ENCODING_UTF8 = "UTF-8";

inline const std::vector<QByteArray> SUPPORTED_ENCODINGS = {
    //"UTF-8",  // Unicode 8-bit
    "UTF-16",       // Unicode 16-bit
    "UTF-16LE",     // Unicode 16-bit Little Endian
    "UTF-16BE",     // Unicode 16-bit Big Endian
    "UTF-32",       // Unicode 32-bit
    "UTF-32LE",     // Unicode 32-bit Little Endian
    "UTF-32BE",     // Unicode 32-bit Big Endian
    "cp1251",       // Кириллица (cp1251)
    "ISO-8859-1",   // Latin-1 (Западноевропейская)
    "ISO-8859-2",   // Latin-2 (Центральноевропейская)
    "ISO-8859-3",   // Latin-3 (Южноевропейская)
    "ISO-8859-4",   // Latin-4 (Североевропейская)
    "ISO-8859-5",   // Кириллица
    "ISO-8859-6",   // Арабская
    "ISO-8859-7",   // Греческая
    "ISO-8859-8",   // Иврит
    "ISO-8859-9",   // Турецкая
    "ISO-8859-10",  // Latin-6 (Североевропейская)
    "ISO-8859-13",  // Latin-7 (Балтийская)
    "ISO-8859-14",  // Latin-8 (Кельтская)
    "ISO-8859-15",  // Latin-9 (Западноевропейская с евро)
    "KOI8-R",       // Русская (кодировка KOI8)
    "KOI8-U",       // Украинская (кодировка KOI8)
    "Shift_JIS",    // Японская
    "EUC-JP",       // Японская
    "GB18030",      // Китайская
    "Big5",         // Традиционная китайская
    "TIS-620",      // Тайская
    "ASCII",        // Базовый ASCII
    "cp437"         // Английская DOS
};

inline const std::vector<QByteArray> ENCODING_RUS = {
    "UTF-8",       // Unicode 8-bit
    "cp1251",      // Кириллица (cp1251)
    "KOI8-R",      // Русская (кодировка KOI8)
    "ISO-8859-5",  // Кириллица
};

}  // namespace AppConstants