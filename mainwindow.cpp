#include "mainwindow.h"
#include "ui_MainWindow.h"  // Сгенерированный заголовок (автоматически из .ui)
#include <QFileDialog>
#include <QDir>
#include <QTreeWidget>
#include <QFileIconProvider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);  // Инициализация интерфейса

    // Подключение кнопки к слоту
    connect(choose_file_btn, &QPushButton::clicked, this, &MainWindow::onChooseFolder);
}

void MainWindow::onChooseFolder() {
    QString folderPath = QFileDialog::getExistingDirectory(this, "Выберите папку");
    if (!folderPath.isEmpty()) {
        // Отображение пути в textEdit
        textEdit->setText(folderPath);

        // Обновление содержимого scrollArea
        updateScrollArea(folderPath);
    }
}
void MainWindow::updateScrollArea(const QString &path) {
    QWidget *oldWidget = scrollArea->takeWidget();
    if (oldWidget) delete oldWidget;

    QTreeWidget *tree = new QTreeWidget();
    tree->setHeaderLabels({"Файл", "Тип"});
    tree->setColumnCount(2);

    QDir dir(path);
    QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    QFileIconProvider iconProvider;
    for (const QFileInfo &file : files) {
        QTreeWidgetItem *item = new QTreeWidgetItem(tree);
        item->setIcon(0, iconProvider.icon(file));
        item->setText(0, file.fileName());
        item->setText(1, file.isDir() ? "Папка" : "Файл");
    }

    scrollArea->setWidget(tree);
}

MainWindow::~MainWindow() {
    delete ui;
}