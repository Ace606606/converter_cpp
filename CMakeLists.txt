# Указываем минимально необходимую версию CMake.
# Рекомендуется использовать 3.16 или выше для хорошей поддержки Qt5.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Определяем имя проекта. Это также будет использоваться как имя исполняемого файла.
project(FileManagerApp LANGUAGES CXX)

# Устанавливаем требуемый стандарт C++.
# C++17 необходим для std::filesystem, а также это хороший современный стандарт.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Отключаем расширения компилятора, чтобы придерживаться стандарта

# Находим пакеты Qt5.
# COMPONENTS перечисляет необходимые модули Qt.
# Core, Gui, Widgets - это основные модули для GUI-приложения.
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Включаем автоматическую обработку MOC (Meta-Object Compiler),
# UIC (User Interface Compiler) и RCC (Resource Compiler) для Qt.
# Это позволяет CMake автоматически запускать moc на файлах с Q_OBJECT.
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON) # Очень важно для Qt сигналов/слотов

# Определяем исходные файлы для исполняемого файла.
# main.cpp и filemanagerwindow.cpp - это основные файлы реализации.
set(SOURCES
    main.cpp
    filemanagerwindow.cpp
)

# Определяем заголовочные файлы.
# filemanagerwindow.h - это заголовочный файл, который содержит объявление класса окна.
# HEADERS больше не передаются напрямую в add_executable, так как AUTOMOC их обработает.
set(HEADERS
    filemanagerwindow.h
)

# Создаем исполняемый файл.
# Это основная команда CMake для создания исполняемого файла.
# Она берет имя исполняемого файла (FileManagerApp) и список исходных файлов.
# Теперь передаем только SOURCE файлы. Заголовочные файлы обрабатываются AUTOMOC.
add_executable(${PROJECT_NAME} ${SOURCES})

# Добавляем заголовочные файлы в пути поиска компилятора.
# Это необходимо, чтобы компилятор мог найти filemanagerwindow.h, когда он включается в .cpp файлы.
# PRIVATE означает, что эти заголовочники используются только этим проектом,
# но не экспортируются для использования другими библиотеками, если бы они были.
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} # Путь к текущей директории с исходниками
)

# Привязываем найденные модули Qt к исполняемому файлу.
# Это гарантирует, что все необходимые библиотеки Qt будут связаны с нашим приложением.
# Qt5::Core, Qt5::Gui, Qt5::Widgets - это целевые имена, предоставляемые find_package(Qt5).
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# Дополнительные настройки для Qt, если нужны:
# Например, если бы у нас были файлы .ui (из Qt Designer) или .qrc (файлы ресурсов Qt),
# они бы добавлялись здесь примерно так:
# qt5_add_resources(${PROJECT_NAME} resources.qrc)
# qt5_add_uic(${PROJECT_NAME} forms/mainwindow.ui)