#include "filemanagerwindow.h"  // Включаем заголовочный файл нашего класса

#include <QDebug>  // Для вывода отладочных сообщений в консоль (можно удалить в релизе)

// Конструктор FileManagerWindow
FileManagerWindow::FileManagerWindow(QWidget *parent)
    : QMainWindow(parent),  // Вызываем конструктор базового класса QMainWindow
      _fileSystemModel(new QFileSystemModel(
          this)),  // Инициализируем модель файловой системы
      // Инициализируем виджеты
      _treeView(new QTreeView(this)),
      _currentPathLineEdit(new QLineEdit(this)),
      _fileContentTextEdit(new QTextEdit(this)),
      _encodingComboBox(new QComboBox(this)),
      _openFileButton(new QPushButton("Открыть файл", this)),
      _saveFileAsButton(new QPushButton("Сохранить как...", this)),
      _selectedEncoding("UTF-8")  // Устанавливаем кодировку по умолчанию
{
    // Настраиваем пользовательский интерфейс
    setupUI();
    // Загружаем список поддерживаемых кодировок в QComboBox
    loadSupportedEncodings();

    // Настраиваем модель файловой системы
    _fileSystemModel->setFilter(
        QDir::AllDirs | QDir::Files |
        QDir::NoDotAndDotDot);  // Показываем папки, файлы, скрываем '.' и '..'
    _fileSystemModel->setRootPath(
        QDir::homePath());  // Устанавливаем корневой путь модели в домашнюю
                            // директорию

    // Связываем модель с древовидным представлением
    _treeView->setModel(_fileSystemModel);

    // Устанавливаем корневой индекс для QTreeView, чтобы отобразить домашнюю
    // директорию QModelIndex index = _fileSystemModel->index(QDir::homePath());
    // _treeView->setRootIndex(index);
    // _treeView->scrollTo(index); // Прокручиваем до корневого элемента
    // _treeView->expand(index); // Разворачиваем корневой элемент

    // Устанавливаем текущую директорию в поле ввода пути
    _currentPathLineEdit->setText(QDir::homePath());

    // Скрываем ненужные столбцы в QTreeView (размер, тип, дата)
    for (int i = 1; i < _fileSystemModel->columnCount(); ++i) {
        _treeView->hideColumn(i);
    }

    // Соединяем сигналы со слотами:
    // Когда пользователь кликает по элементу в дереве, вызывается
    // on_treeView_clicked
    connect(_treeView, &QTreeView::clicked, this,
            &FileManagerWindow::on_treeView_clicked);
    // Когда пользователь делает двойной клик по элементу в дереве, вызывается
    // on_treeView_doubleClicked
    connect(_treeView, &QTreeView::doubleClicked, this,
            &FileManagerWindow::on_treeView_doubleClicked);
    // Когда пользователь нажимает кнопку "Открыть файл", вызывается
    // on_openFile_clicked
    connect(_openFileButton, &QPushButton::clicked, this,
            &FileManagerWindow::on_openFile_clicked);
    // Когда пользователь нажимает кнопку "Сохранить как...", вызывается
    // on_saveFileAs_clicked
    connect(_saveFileAsButton, &QPushButton::clicked, this,
            &FileManagerWindow::on_saveFileAs_clicked);
    // Когда пользователь меняет выбор в комбо-боксе кодировок, вызывается
    // on_encodingComboBox_currentIndexChanged
    connect(_encodingComboBox,
            QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this, &FileManagerWindow::on_encodingComboBox_currentIndexChanged);

    // Устанавливаем текущий каталог, чтобы QTreeView отображал его содержимое.
    // Это важно для начального отображения файловой системы.
    _treeView->setRootIndex(_fileSystemModel->index(QDir::homePath()));
}

// Деструктор
FileManagerWindow::~FileManagerWindow() {
    // Деструкторы QObject-ов, у которых есть родитель (this), вызываются
    // автоматически Qt. Поэтому явное удаление new-созданных объектов не
    // требуется, если они являются дочерними.
}

// Метод для настройки пользовательского интерфейса
void FileManagerWindow::setupUI() {
    // Создаем центральный виджет
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Устанавливаем его как центральный
                                      // виджет главного окна

    // Создаем основной горизонтальный компоновщик (для дерева файлов и
    // остальной части)
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // --- Левая часть: Древовидное представление файлов ---
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel("Файловая система:"));
    leftLayout->addWidget(_treeView);  // Добавляем древовидное представление

    // --- Правая часть: Управление файлами и содержимое ---
    QVBoxLayout *rightLayout = new QVBoxLayout();

    // Строка для текущего пути
    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(new QLabel("Текущий путь:"));
    _currentPathLineEdit->setReadOnly(true);  // Только для чтения
    pathLayout->addWidget(_currentPathLineEdit);
    rightLayout->addLayout(pathLayout);

    // Строка для выбора кодировки
    QHBoxLayout *encodingLayout = new QHBoxLayout();
    encodingLayout->addWidget(new QLabel("Кодировка:"));
    encodingLayout->addWidget(_encodingComboBox);
    rightLayout->addLayout(encodingLayout);

    // Кнопки действий
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(_openFileButton);
    buttonLayout->addWidget(_saveFileAsButton);
    rightLayout->addLayout(buttonLayout);

    rightLayout->addWidget(new QLabel("Содержимое файла:"));
    _fileContentTextEdit->setReadOnly(true);  // Только для чтения по умолчанию
    rightLayout->addWidget(
        _fileContentTextEdit);  // Добавляем поле для содержимого файла

    // Добавляем обе части в основной компоновщик
    mainLayout->addLayout(leftLayout,
                          1);  // Левая часть занимает 1 долю (растягивается)
    mainLayout->addLayout(
        rightLayout, 2);  // Правая часть занимает 2 доли (растягивается больше)

    // Устанавливаем минимальный размер окна
    setMinimumSize(800, 600);
    setWindowTitle("Менеджер файлов на Qt");  // Устанавливаем заголовок окна
}

// Загружает список поддерживаемых кодировок в QComboBox
void FileManagerWindow::loadSupportedEncodings() {
    // Получаем список всех доступных кодеков Qt
    QList<QByteArray> codecs = QTextCodec::availableCodecs();
    _encodingComboBox->addItem("UTF-8");  // Добавляем UTF-8 по умолчанию
    // Добавляем другие часто используемые кодировки (если они доступны)
    if (codecs.contains("UTF-16")) _encodingComboBox->addItem("UTF-16");
    if (codecs.contains("Windows-1251"))
        _encodingComboBox->addItem("Windows-1251");
    if (codecs.contains("ASCII")) _encodingComboBox->addItem("ASCII");
    // Можете добавить другие кодировки по мере необходимости, например:
    // if (codecs.contains("UTF-32")) _encodingComboBox->addItem("UTF-32");
    // if (codecs.contains("ISO-8859-1"))
    // _encodingComboBox->addItem("ISO-8859-1");

    // Устанавливаем UTF-8 как выбранную по умолчанию
    int index = _encodingComboBox->findText("UTF-8");
    if (index != -1) {
        _encodingComboBox->setCurrentIndex(index);
    }
}

// Слот для обработки одиночного клика в древовидном представлении
void FileManagerWindow::on_treeView_clicked(const QModelIndex &index) {
    if (!index.isValid()) return;  // Проверяем валидность индекса

    QFileInfo fileInfo =
        _fileSystemModel->fileInfo(index);  // Получаем информацию о файле/папке

    if (fileInfo.isDir()) {
        // Если это директория, обновляем текущий путь
        _currentPathLineEdit->setText(fileInfo.absoluteFilePath());
        _treeView->setRootIndex(
            index);  // Меняем корневой индекс дерева на выбранную папку
        _treeView->expand(index);       // Разворачиваем выбранную папку
        _fileContentTextEdit->clear();  // Очищаем поле содержимого файла
        _currentFilePath.clear();       // Сбрасываем текущий путь файла
    } else if (fileInfo.isFile()) {
        // Если это файл, обновляем текущий путь файла
        _currentFilePath = fileInfo.absoluteFilePath();
        // Пытаемся прочитать содержимое файла с текущей выбранной кодировкой
        readFileContent(_currentFilePath, _selectedEncoding);
    }
}

// Слот для обработки двойного клика в древовидном представлении
void FileManagerWindow::on_treeView_doubleClicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    QFileInfo fileInfo = _fileSystemModel->fileInfo(index);

    if (fileInfo.isDir()) {
        // Если это директория, переходим в нее (обновляем корневой индекс и
        // поле пути)
        _currentPathLineEdit->setText(fileInfo.absoluteFilePath());
        _treeView->setRootIndex(index);
        _treeView->expand(index);
        _fileContentTextEdit->clear();
        _currentFilePath.clear();
    } else if (fileInfo.isFile()) {
        // Если это файл, просто обновляем его содержимое, как при одиночном
        // клике
        _currentFilePath = fileInfo.absoluteFilePath();
        readFileContent(_currentFilePath, _selectedEncoding);
    }
}

// Слот для кнопки "Открыть файл"
void FileManagerWindow::on_openFile_clicked() {
    // Открываем диалог выбора файла
    QString filePath = QFileDialog::getOpenFileName(
        this, "Открыть файл",
        _currentPathLineEdit->text(),  // Начинаем с текущего пути
        "Все файлы (*.*);;Текстовые файлы (*.txt);;C++ файлы (*.h *.cpp)");
    if (!filePath.isEmpty()) {
        _currentFilePath = filePath;  // Сохраняем выбранный путь
        // Читаем содержимое выбранного файла с текущей кодировкой
        readFileContent(_currentFilePath, _selectedEncoding);
        // Обновляем отображаемый путь, чтобы он соответствовал выбранному файлу
        _currentPathLineEdit->setText(QFileInfo(filePath).absolutePath());
        // Устанавливаем корневой индекс дерева на путь выбранного файла, чтобы
        // дерево обновилось
        _treeView->setRootIndex(
            _fileSystemModel->index(QFileInfo(filePath).absolutePath()));
    }
}

// Слот для кнопки "Сохранить как..."
void FileManagerWindow::on_saveFileAs_clicked() {
    if (_fileContentTextEdit->document()->isEmpty() &&
        _currentFilePath.isEmpty()) {
        QMessageBox::information(
            this, "Информация",
            "Нет содержимого для сохранения или выбранного файла.");
        return;
    }

    // Открываем диалог сохранения файла
    QString saveFilePath = QFileDialog::getSaveFileName(
        this, "Сохранить файл как...",
        QDir(_currentPathLineEdit->text())
            .filePath("копия_файла.txt"),  // Предлагаем имя файла
        "Все файлы (*.*);;Текстовые файлы (*.txt)");

    if (!saveFilePath.isEmpty()) {
        // Сохраняем текущее содержимое QTextEdit с выбранной кодировкой
        saveFileContent(saveFilePath, _fileContentTextEdit->toPlainText(),
                        _selectedEncoding);
        QMessageBox::information(this, "Сохранение", "Файл успешно сохранен.");
    }
}

// Слот для изменения выбранной кодировки
void FileManagerWindow::on_encodingComboBox_currentIndexChanged(
    const QString &encodingName) {
    _selectedEncoding = encodingName;  // Обновляем выбранную кодировку
    // Если есть открытый файл, перечитываем его с новой кодировкой
    if (!_currentFilePath.isEmpty()) {
        readFileContent(_currentFilePath, _selectedEncoding);
    }
}

// Чтение содержимого файла с заданной кодировкой
void FileManagerWindow::readFileContent(const QString &filePath,
                                        const QString &encoding) {
    QFile file(filePath);  // Создаем объект QFile для работы с файлом
    if (!file.open(
            QIODevice::ReadOnly |
            QIODevice::Text)) {  // Пытаемся открыть файл для чтения как текст
        // Если не удалось открыть, показываем сообщение об ошибке
        QMessageBox::warning(this, "Ошибка чтения файла",
                             "Не удалось открыть файл: " + file.errorString());
        _fileContentTextEdit->clear();  // Очищаем поле содержимого
        return;
    }

    QTextStream in(&file);  // Создаем QTextStream для чтения из файла
    QTextCodec *codec = QTextCodec::codecForName(
        encoding.toUtf8());  // Получаем кодек для указанной кодировки

    if (codec) {
        in.setCodec(codec);  // Устанавливаем кодек для потока
    } else {
        // Если кодек не найден, используем кодек по умолчанию (системный) и
        // предупреждаем
        QMessageBox::warning(this, "Ошибка кодировки",
                             "Неизвестная кодировка: " + encoding +
                                 ". Используется системная кодировка.");
        // in.setCodec(QTextCodec::codecForLocale()); // Можно установить
        // системную локаль
    }

    // Читаем весь текст из файла
    QString content = in.readAll();
    _fileContentTextEdit->setPlainText(
        content);  // Отображаем текст в QTextEdit

    file.close();  // Закрываем файл
}

// Сохранение содержимого файла с заданной кодировкой
void FileManagerWindow::saveFileContent(const QString &filePath,
                                        const QString &content,
                                        const QString &encoding) {
    QFile file(filePath);  // Создаем объект QFile для работы с файлом
    // Пытаемся открыть файл для записи как текст.
    // QIODevice::Truncate очищает файл, если он существует.
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text |
                   QIODevice::Truncate)) {
        // Если не удалось открыть/создать, показываем сообщение об ошибке
        QMessageBox::warning(
            this, "Ошибка сохранения файла",
            "Не удалось сохранить файл: " + file.errorString());
        return;
    }

    QTextStream out(&file);  // Создаем QTextStream для записи в файл
    QTextCodec *codec = QTextCodec::codecForName(
        encoding.toUtf8());  // Получаем кодек для указанной кодировки

    if (codec) {
        out.setCodec(codec);  // Устанавливаем кодек для потока
    } else {
        // Если кодек не найден, используем кодек по умолчанию (системный) и
        // предупреждаем
        QMessageBox::warning(this, "Ошибка кодировки",
                             "Неизвестная кодировка: " + encoding +
                                 ". Используется системная кодировка.");
        // out.setCodec(QTextCodec::codecForLocale()); // Можно установить
        // системную локаль
    }

    out << content;  // Записываем текст
    file.close();    // Закрываем файл
}