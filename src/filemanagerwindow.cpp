// ./src/filemanagerwindow.cpp
#include "filemanagerwindow.h"

#include <QDebug>

#include "constant.hpp"

void FileManagerWindow::updateStatusBar() {
    QString status =
        QString(
            "Version: %1 | Кодировка: %2 | Расположение открытого файла: %3")
            .arg(AppConstants::APP_VERSION)
            .arg(_selectedEncoding)
            .arg(QDir::toNativeSeparators(_currentFilePath));

    _statusBar->showMessage(status);
}

FileManagerWindow::FileManagerWindow(QWidget *parent)
    : QMainWindow(parent),
      _fileSystemModel(new QFileSystemModel(this)),
      _treeView(new QTreeView(this)),
      _currentPathLineEdit(new QLineEdit(this)),
      _fileContentTextEdit(new QTextEdit(this)),
      _encodingComboBox(new QComboBox(this)),
      _openFileButton(new QPushButton("Открыть файл", this)),
      _saveFileAsButton(new QPushButton("Сохранить как...", this)),
      _selectedEncoding(AppConstants::DEFAULT_ENCODING_UTF8),
      _statusBar(new QStatusBar(this)) {
    setupUI();
    loadSupportedEncodings();

    _fileSystemModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    _fileSystemModel->setRootPath(QDir::homePath());
    _treeView->setModel(_fileSystemModel);
    _currentPathLineEdit->setText(QDir::homePath());

    for (int i = 1; i < _fileSystemModel->columnCount(); ++i) {
        _treeView->hideColumn(i);
    }

    connect(_treeView, &QTreeView::clicked, this,
            &FileManagerWindow::on_treeView_clicked);

    connect(_treeView, &QTreeView::doubleClicked, this,
            &FileManagerWindow::on_treeView_doubleClicked);

    connect(_openFileButton, &QPushButton::clicked, this,
            &FileManagerWindow::on_openFile_clicked);

    connect(_saveFileAsButton, &QPushButton::clicked, this,
            &FileManagerWindow::on_saveFileAs_clicked);

    connect(_encodingComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &FileManagerWindow::on_encodingComboBox_currentIndexChanged);

    _treeView->setRootIndex(_fileSystemModel->index(QDir::homePath()));
}

FileManagerWindow::~FileManagerWindow() {}

void FileManagerWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel(AppConstants::LABEL_FILESYSTEM));
    leftLayout->addWidget(_treeView);

    QVBoxLayout *rightLayout = new QVBoxLayout();

    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(new QLabel(AppConstants::LABEL_PATH));
    _currentPathLineEdit->setReadOnly(true);
    pathLayout->addWidget(_currentPathLineEdit);
    rightLayout->addLayout(pathLayout);

    QHBoxLayout *encodingLayout = new QHBoxLayout();
    encodingLayout->addWidget(new QLabel(AppConstants::LABEL_ENCODING));
    encodingLayout->addWidget(_encodingComboBox);
    rightLayout->addLayout(encodingLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(_openFileButton);
    buttonLayout->addWidget(_saveFileAsButton);
    rightLayout->addLayout(buttonLayout);

    rightLayout->addWidget(new QLabel(AppConstants::LABEL_CONTENT));
    _fileContentTextEdit->setReadOnly(false);
    rightLayout->addWidget(_fileContentTextEdit);

    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 2);

    setMinimumSize(AppConstants::WINDOW_WIDTH, AppConstants::WINDOW_HEIGHT);
    setWindowTitle(AppConstants::APP_NAME);

    setStatusBar(_statusBar);
    updateStatusBar();
}

void FileManagerWindow::loadSupportedEncodings() {
    QList<QByteArray> codecs = QTextCodec::availableCodecs();
    _encodingComboBox->addItem(
        AppConstants::DEFAULT_ENCODING_UTF8);  // add default UTF-8

    for (const auto &enc : AppConstants::SUPPORTED_ENCODINGS) {
        if (codecs.contains(enc))
            _encodingComboBox->addItem(enc);
        else {
            qDebug() << "Кодировка не доступна в системе:" << enc;
        }
    }

    QTextCodec *testCodec = QTextCodec::codecForName("UTF-16");
    qDebug() << "Is UTF-16BE codec available?" << (testCodec != nullptr);
    // добавить все кодировки поддерживаемые в Qt
    // for (auto &code : codecs) {
    //     _encodingComboBox->addItem(code);
    // }

    // UTF-8 default
    int index = _encodingComboBox->findText(
        AppConstants::DEFAULT_ENCODING_UTF8);  // return idx
    if (index != -1) {
        _encodingComboBox->setCurrentIndex(index);
    }
}

void FileManagerWindow::on_treeView_clicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    QFileInfo fileInfo = _fileSystemModel->fileInfo(index);

    if (fileInfo.isFile()) {
        _currentFilePath = fileInfo.absoluteFilePath();
        _currentPathLineEdit->setText(QFileInfo(fileInfo).absolutePath());
        //=======================================================
        QString detectedEnc = detectEncoding(_currentFilePath);
        int comboIndex = _encodingComboBox->findText(detectedEnc);
        if (comboIndex != -1) {
            _encodingComboBox->setCurrentIndex(
                comboIndex);  // Устанавливаем найденную кодировку
        } else {
            // Если найденная кодировка не в списке ComboBox, просто выбираем
            // дефолтную UTF-8
            _encodingComboBox->setCurrentIndex(_encodingComboBox->findText(
                AppConstants::DEFAULT_ENCODING_UTF8));
        }
        _selectedEncoding = _encodingComboBox->currentText();
        //=======================================================
        readFileContent(_currentFilePath, _selectedEncoding);
    }

    updateStatusBar();
}

void FileManagerWindow::on_treeView_doubleClicked(const QModelIndex &index) {
    on_treeView_clicked(index);
}

void FileManagerWindow::on_openFile_clicked() {
    QString filePath = QFileDialog::getOpenFileName(
        this, "Открыть файл", _currentPathLineEdit->text(),
        "Все файлы (*.*);;Текстовые файлы (*.txt);;C++ файлы (*.h *.cpp)");
    if (!filePath.isEmpty()) {
        _currentFilePath = filePath;
        _currentPathLineEdit->setText(QFileInfo(filePath).absolutePath());

        QString detectedEnc = detectEncoding(_currentFilePath);
        int comboIndex = _encodingComboBox->findText(detectedEnc);
        if (comboIndex != -1) {
            _encodingComboBox->setCurrentIndex(comboIndex);
        } else {
            _encodingComboBox->setCurrentIndex(_encodingComboBox->findText(
                AppConstants::DEFAULT_ENCODING_UTF8));
        }
        _selectedEncoding = _encodingComboBox->currentText();

        readFileContent(_currentFilePath, _selectedEncoding);
        updateStatusBar();
    }
}

void FileManagerWindow::on_saveFileAs_clicked() {
    if (_fileContentTextEdit->document()->isEmpty() &&
        _currentFilePath.isEmpty()) {
        QMessageBox::information(
            this, "Информация",
            "Нет содержимого для сохранения или выбранного файла.");
        return;
    }

    QString saveFilePath = QFileDialog::getSaveFileName(
        this, "Сохранить файл как...",
        QDir(_currentPathLineEdit->text()).filePath("копия_файла.txt"),
        "Все файлы (*.*);;Текстовые файлы (*.txt)");

    if (!saveFilePath.isEmpty()) {
        saveFileContent(saveFilePath, _fileContentTextEdit->toPlainText(),
                        _selectedEncoding);
        QMessageBox::information(this, "Сохранение", "Файл успешно сохранен.");
    }
}

void FileManagerWindow::on_encodingComboBox_currentIndexChanged(int index) {
    if (index >= 0) {
        _selectedEncoding = _encodingComboBox->itemText(index);
        if (!_currentFilePath.isEmpty()) {
            readFileContent(_currentFilePath, _selectedEncoding);
        }
        updateStatusBar();
    }
}

void FileManagerWindow::readFileContent(const QString &filePath,
                                        const QString &encoding) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка чтения файла",
                             "Не удалось открыть файл: " + file.errorString());
        _fileContentTextEdit->clear();
        return;
    }

    QTextStream in(&file);
    QTextCodec *codec = QTextCodec::codecForName(encoding.toUtf8());

    if (codec) {
        in.setCodec(codec);
    } else {
        QMessageBox::warning(this, "Ошибка кодировки",
                             "Неизвестная кодировка: " + encoding +
                                 ". Используется системная кодировка.");
        in.setCodec(QTextCodec::codecForLocale());
    }

    QString content = in.readAll();
    _fileContentTextEdit->setPlainText(content);

    file.close();
}

void FileManagerWindow::saveFileContent(const QString &filePath,
                                        const QString &content,
                                        const QString &encoding) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text |
                   QIODevice::Truncate)) {
        QMessageBox::warning(
            this, "Ошибка сохранения файла",
            "Не удалось сохранить файл: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    QTextCodec *codec = QTextCodec::codecForName(encoding.toUtf8());
    qDebug() << "Попытка сохранить в кодировке:" << encoding;
    if (codec) {
        out.setCodec(codec);
        if (encoding == "UTF-16" || encoding == "UTF-16LE" ||
            encoding == "UTF-16BE" || encoding == "UTF-32" ||
            encoding == "UTF-32LE" || encoding == "UTF-32BE") {
            out.setGenerateByteOrderMark(true);
        }
    } else {
        QMessageBox::warning(this, "Ошибка кодировки",
                             "Неизвестная кодировка: " + encoding +
                                 ". Используется системная кодировка.");
        out.setCodec(QTextCodec::codecForLocale());
        qDebug() << "Откат на системную кодировку:"
                 << QTextCodec::codecForLocale()->name();
    }

    out << content;
    file.close();
}

QString FileManagerWindow::detectEncoding(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Exit: !file.open(QIODevice::ReadOnly)";
        return AppConstants::DEFAULT_ENCODING_UTF8;
    }

    QByteArray rawData = file.read(1024);
    file.close();

    if (rawData.isEmpty()) {
        qDebug() << "Exit: rawData.isEmpty()";
        return AppConstants::DEFAULT_ENCODING_UTF8;
    }

    if (rawData.size() >= 4) {
        // UTF-32BE BOM: 00 00 FE FF
        if ((quint8)rawData[0] == 0x00 && (quint8)rawData[1] == 0x00 &&
            (quint8)rawData[2] == 0xFE && (quint8)rawData[3] == 0xFF) {
            qDebug() << "Определено по BOM: UTF-32BE";
            return "UTF-32BE";
        }
        // UTF-32LE BOM: FF FE 00 00
        else if ((quint8)rawData[0] == 0xFF && (quint8)rawData[1] == 0xFE &&
                 (quint8)rawData[2] == 0x00 && (quint8)rawData[3] == 0x00) {
            qDebug() << "Определено по BOM: UTF-32LE";
            return "UTF-32LE";
        }
    }

    if (rawData.size() >= 3) {
        // UTF-8 BOM: EF BB BF
        if ((quint8)rawData[0] == 0xEF && (quint8)rawData[1] == 0xBB &&
            (quint8)rawData[2] == 0xBF) {
            qDebug() << "Определено по BOM: UTF-8";
            return "UTF-8";
        }
    }

    if (rawData.size() >= 2) {
        // UTF-16BE BOM: FE FF
        if ((quint8)rawData[0] == 0xFE && (quint8)rawData[1] == 0xFF) {
            qDebug() << "Определено по BOM: UTF-16BE";
            return "UTF-16BE";
        }
        // UTF-16LE BOM: FF FE
        else if ((quint8)rawData[0] == 0xFF && (quint8)rawData[1] == 0xFE) {
            qDebug() << "Определено по BOM: UTF-16LE";
            return "UTF-16LE";
        }
    }

    QString bestEncoding = AppConstants::DEFAULT_ENCODING_UTF8;
    int maxRussianLowercaseCount = 0;

    for (const QByteArray &encodingName : AppConstants::ENCODING_RUS) {
        QTextCodec *codec = QTextCodec::codecForName(encodingName);
        if (!codec) {
            continue;
        }

        QTextCodec::ConverterState state;
        QString decodedText =
            codec->toUnicode(rawData.constData(), rawData.size(), &state);

        if (state.invalidChars > 0 && encodingName != "UTF-8") {
            continue;
        }

        int currentRussianLowercaseCount = 0;
        for (QChar c : decodedText) {
            if (c.unicode() >= 0x0430 && c.unicode() <= 0x044F) {
                currentRussianLowercaseCount++;
            }
        }

        if (currentRussianLowercaseCount > maxRussianLowercaseCount) {
            maxRussianLowercaseCount = currentRussianLowercaseCount;
            bestEncoding = encodingName;
        }
    }

    qDebug() << "Автоматически определенная кодировка (по содержимому):"
             << bestEncoding
             << "с кол-ом русских символов:" << maxRussianLowercaseCount;

    return bestEncoding;
}
