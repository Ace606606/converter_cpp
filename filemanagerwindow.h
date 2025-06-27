#pragma once  // Директива препроцессора, чтобы гарантировать, что этот файл
              // будет включен только один раз.

#include <QComboBox>         // Выпадающий список для выбора кодировки.
#include <QDir>              // Для работы с директориями.
#include <QFile>             // Для работы с файлами.
#include <QFileDialog>       // Для диалогов открытия/сохранения файла.
#include <QFileInfo>         // Информация о файле.
#include <QFileSystemModel>  // Модель данных для доступа к файловой системе.
#include <QHBoxLayout>       // Для горизонтального расположения виджетов.
#include <QLabel>            // Для текстовых меток.
#include <QLineEdit>         // Однострочное поле для отображения текущего пути.
#include <QMainWindow>  // Базовый класс для создания главного окна приложения.
#include <QMessageBox>  // Для вывода информационных сообщений и ошибок.
#include <QPushButton>  // Кнопки для действий.
#include <QStandardPaths>  // Для получения стандартных путей (например, домашней директории).
#include <QTextCodec>  // Для преобразования текста между различными кодировками.
#include <QTextEdit>  // Виджет для отображения и редактирования многострочного текста (содержимое файла).
#include <QTextStream>  // Для чтения/записи текста с поддержкой кодировок.
#include <QTreeView>  // Виджет для отображения древовидной структуры (каталоги/файлы).
#include <QVBoxLayout>  // Для вертикального расположения виджетов.

// Объявляем класс FileManagerWindow, который наследуется от QMainWindow.
// Это будет наше основное окно приложения.
class FileManagerWindow : public QMainWindow {
   Q_OBJECT  // Макрос, необходимый для классов, использующих сигналы и слоты
             // Qt.

       public :
       // Конструктор класса. Родительский виджет (parent) обычно nullptr для
       // главного окна.
       explicit FileManagerWindow(QWidget *parent = nullptr);
    // Деструктор, очищает ресурсы (хотя Qt делает это автоматически для
    // дочерних виджетов).
    ~FileManagerWindow();

   private slots:
    // Слот для обработки выбора файла/папки в древовидном представлении.
    void on_treeView_clicked(const QModelIndex &index);
    // Слот для обработки двойного клика по файлу/папке.
    void on_treeView_doubleClicked(const QModelIndex &index);
    // Слот для обработки нажатия кнопки "Открыть файл".
    void on_openFile_clicked();
    // Слот для обработки нажатия кнопки "Сохранить как...".
    void on_saveFileAs_clicked();
    // Слот для обработки изменения выбранной кодировки в QComboBox.
    void on_encodingComboBox_currentIndexChanged(const QString &encodingName);

   private:
    // Приватные члены класса - это виджеты и модели, которые будут составлять
    // наш интерфейс.
    QFileSystemModel
        *_fileSystemModel;  // Модель, предоставляющая данные файловой системы.
    QTreeView *_treeView;   // Виджет для отображения древовидного представления
                            // файлов и каталогов.
    QLineEdit *_currentPathLineEdit;  // Поле для отображения текущего пути.
    QTextEdit *_fileContentTextEdit;  // Поле для отображения содержимого файла.
    QComboBox *_encodingComboBox;     // Выпадающий список для выбора кодировки.
    QPushButton *_openFileButton;     // Кнопка для открытия файла.
    QPushButton
        *_saveFileAsButton;  // Кнопка для сохранения файла с другой кодировкой.

    QString _currentFilePath;   // Текущий открытый файл (полный путь).
    QString _selectedEncoding;  // Текущая выбранная кодировка.

    // Приватные методы для выполнения основной логики.
    void setupUI();  // Метод для настройки пользовательского интерфейса.
    void loadSupportedEncodings();  // Загрузка списка поддерживаемых кодировок
                                    // в комбо-бокс.
    void readFileContent(const QString &filePath,
                         const QString &encoding);  // Чтение файла.
    void saveFileContent(const QString &filePath, const QString &content,
                         const QString &encoding);  // Сохранение файла.
};
