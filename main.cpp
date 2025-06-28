#include <QApplication>
#include "mainwindow.h"
#include <QStyleFactory>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Установить системный стиль (на Windows это будет "windows")
    QApplication::setStyle(QStyleFactory::create("fusion"));

    MainWindow window;
    window.show();
    return app.exec();
}