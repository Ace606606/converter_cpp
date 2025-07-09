// ./include/filemanagerwindow.h
#pragma once

#include <QComboBox>         // Выпадающий список для выбора кодировки
#include <QDir>              // Для работы с директориями
#include <QFile>             // Для работы с файлами
#include <QFileDialog>       // Для диалогов открытия/сохранения файла
#include <QFileInfo>         // Информация о файле
#include <QFileSystemModel>  // Модель данных для доступа к файловой системе
#include <QHBoxLayout>       // Для горизонтального расположения виджетов
#include <QLabel>            // Для текстовых меток
#include <QLineEdit>         // Однострочное поле для отображения текущего пути
#include <QMainWindow>  // Базовый класс для создания главного окна приложения
#include <QMessageBox>  // Для вывода информационных сообщений и ошибок.
#include <QPushButton>  // Кнопки для действий.
#include <QStandardPaths>  // Для получения стандартных путей
#include <QStatusBar>
#include <QTextCodec>  // Для преобразования текста между различными кодировками
#include <QTextEdit>   // Виджет для отображения и редактирования текста
#include <QTextStream>  // Для чтения/записи текста с поддержкой кодировок
#include <QTreeView>    // Виджет для отображения структуры-дерево
#include <QVBoxLayout>  // Для вертикального расположения виджетов.

class FileManagerWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit FileManagerWindow(QWidget *parent = nullptr);
    ~FileManagerWindow();

   private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_treeView_doubleClicked(const QModelIndex &index);
    void on_openFile_clicked();
    void on_saveFileAs_clicked();
    void on_encodingComboBox_currentIndexChanged(int index);

   private:
    QFileSystemModel *_fileSystemModel;
    QTreeView *_treeView;
    QLineEdit *_currentPathLineEdit;
    QTextEdit *_fileContentTextEdit;
    QComboBox *_encodingComboBox;
    QPushButton *_openFileButton;
    QPushButton *_saveFileAsButton;
    QStatusBar *_statusBar;

    QString _currentFilePath;
    QString _selectedEncoding;

    void setupUI();
    void loadSupportedEncodings();
    void readFileContent(const QString &filePath, const QString &encoding);
    void saveFileContent(const QString &filePath, const QString &content,
                         const QString &encoding);
    void updateStatusBar();
    QString detectEncoding(const QString &filePath);
};
