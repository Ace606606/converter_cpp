#include "mainwindow.h"
#include "ui_MainWindow.h"  // Сгенерированный заголовок (автоматически из .ui)
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);  // Инициализация интерфейса

    connect(ui->folder_view, &QListWidget::itemClicked, this, &MainWindow::onListItemClicked);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::updateFolderView);
    connect(ui->change_catalog_btn, &QPushButton::clicked, this, &MainWindow::changeDirectory);
    connect(ui->choose_file_btn, &QPushButton::clicked, this, &MainWindow::chooseFile);


}
void MainWindow::updateFolderView()
{
    QString path = ui->textEdit->toPlainText(); // Получаем путь из QTextEdit
    QDir dir(path);

    if (!dir.exists()) {
        qDebug() << "Директория не существует!";
        return;
    }

    ui->folder_view->clear(); // Очищаем список перед обновлением

    QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    for (const QFileInfo &fileInfo : list) {
        QString itemText = fileInfo.fileName(); // Имя файла или папки
        QListWidgetItem *item = new QListWidgetItem(itemText);
        item->setData(Qt::UserRole, fileInfo.absoluteFilePath()); // Сохраняем полный путь как данные
        ui->folder_view->addItem(item);
    }
}
void MainWindow::onListItemClicked(QListWidgetItem* item)
{
    if (!item) return;

    QString filePath = item->data(Qt::UserRole).toString(); // Получаем полный путь из данных
    QFileInfo fileInfo(filePath);

    if (!fileInfo.isFile()) {
        // Если это папка — не загружаем текст
        ui->file_edit->setPlainText("");
        ui->encode_value_lbl->setText("—");
        ui->created_value_lbl->setText("—");
        ui->edited_value_lbl->setText("—");
        return;
    }

    // Отображаем имя файла как пример
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();

    // Выводим содержимое файла в редактор
    ui->file_edit->setPlainText(content);

    // Определяем кодировку
    QString encoding = "UTF-8"; // Упрощённо, можно улучшить с помощью библиотек вродеuchardet

    // Обновляем информацию о файле
    ui->encode_value_lbl->setText(encoding);
    ui->created_value_lbl->setText(fileInfo.birthTime().toString("dd.MM.yyyy hh:mm:ss"));
    ui->edited_value_lbl->setText(fileInfo.lastModified().toString("dd.MM.yyyy hh:mm:ss"));
}
void MainWindow::changeDirectory()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "Выберите папку");

    if (!dirPath.isEmpty()) {
        ui->textEdit->setPlainText(dirPath);   // Устанавливаем путь в QTextEdit
        updateFolderView();                    // Обновляем содержимое QListWidget
    }
}
void MainWindow::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл");

    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);

        // Устанавливаем путь к файлу в QTextEdit
        ui->textEdit->setPlainText(fileInfo.path());

        // Обновляем содержимое списка и выбираем нужный файл в QListWidget
        updateFolderView();

        // Выбираем файл в списке
        for (int i = 0; i < ui->folder_view->count(); ++i) {
            QListWidgetItem *item = ui->folder_view->item(i);
            QString path = item->data(Qt::UserRole).toString();
            if (path == filePath) {
                ui->folder_view->setCurrentItem(item);
                onListItemClicked(item);  // Обновляем информацию о файле
                break;
            }
        }
    }
}




MainWindow::~MainWindow() {
    delete ui;
}