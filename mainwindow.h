#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_MainWindow.h>
#include <QDir>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT

private slots:
    void updateFolderView();
    void onListItemClicked(QListWidgetItem* item);
    void changeDirectory();     // Слот для кнопки "Смена каталога"
    void chooseFile();          // Слот для кнопки "Выбор файла"

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H