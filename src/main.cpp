#include <QApplication>

#include "filemanagerwindow.h"

int main(int argc, char *argv[]) {
    qputenv("QT_QPA_PLATFORM", "xcb");
    QApplication a(argc, argv);

    FileManagerWindow w;

    w.show();

    return a.exec();
}
