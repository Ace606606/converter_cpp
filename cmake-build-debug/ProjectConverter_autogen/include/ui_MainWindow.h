/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *menu_label;
    QGroupBox *groupBox;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *encode_lbl;
    QLabel *encode_value_lbl;
    QLabel *created_lbl;
    QLabel *created_value_lbl;
    QLabel *edited_lbl;
    QLabel *edited_value_lbl;
    QFrame *line;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QPushButton *change_catalog_btn;
    QPushButton *choose_file_btn;
    QPushButton *sel_encode_btn;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_3;
    QListWidget *folder_view;
    QPlainTextEdit *file_edit;
    QPushButton *save_btn;
    QWidget *widget3;
    QGridLayout *gridLayout;
    QLabel *path_label;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1000, 700);
        MainWindow->setMinimumSize(QSize(1000, 700));
        MainWindow->setMaximumSize(QSize(1000, 700));
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        menu_label = new QLabel(centralwidget);
        menu_label->setObjectName("menu_label");
        menu_label->setGeometry(QRect(10, 150, 211, 16));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 569, 460, 121));
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 30, 421, 77));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        encode_lbl = new QLabel(widget);
        encode_lbl->setObjectName("encode_lbl");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, encode_lbl);

        encode_value_lbl = new QLabel(widget);
        encode_value_lbl->setObjectName("encode_value_lbl");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, encode_value_lbl);

        created_lbl = new QLabel(widget);
        created_lbl->setObjectName("created_lbl");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, created_lbl);

        created_value_lbl = new QLabel(widget);
        created_value_lbl->setObjectName("created_value_lbl");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, created_value_lbl);

        edited_lbl = new QLabel(widget);
        edited_lbl->setObjectName("edited_lbl");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, edited_lbl);

        edited_value_lbl = new QLabel(widget);
        edited_value_lbl->setObjectName("edited_value_lbl");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, edited_value_lbl);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(480, 0, 3, 710));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(10, 170, 211, 171));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        change_catalog_btn = new QPushButton(widget1);
        change_catalog_btn->setObjectName("change_catalog_btn");

        verticalLayout->addWidget(change_catalog_btn);

        choose_file_btn = new QPushButton(widget1);
        choose_file_btn->setObjectName("choose_file_btn");

        verticalLayout->addWidget(choose_file_btn);

        sel_encode_btn = new QPushButton(widget1);
        sel_encode_btn->setObjectName("sel_encode_btn");

        verticalLayout->addWidget(sel_encode_btn);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(490, 10, 501, 681));
        verticalLayout_3 = new QVBoxLayout(widget2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        folder_view = new QListWidget(widget2);
        folder_view->setObjectName("folder_view");

        verticalLayout_3->addWidget(folder_view);

        file_edit = new QPlainTextEdit(widget2);
        file_edit->setObjectName("file_edit");

        verticalLayout_3->addWidget(file_edit);

        save_btn = new QPushButton(widget2);
        save_btn->setObjectName("save_btn");

        verticalLayout_3->addWidget(save_btn);

        widget3 = new QWidget(centralwidget);
        widget3->setObjectName("widget3");
        widget3->setGeometry(QRect(2, 12, 471, 69));
        gridLayout = new QGridLayout(widget3);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        path_label = new QLabel(widget3);
        path_label->setObjectName("path_label");

        gridLayout->addWidget(path_label, 0, 0, 1, 1);

        textEdit = new QTextEdit(widget3);
        textEdit->setObjectName("textEdit");
        textEdit->setMinimumSize(QSize(0, 40));
        textEdit->setMaximumSize(QSize(16777215, 40));

        gridLayout->addWidget(textEdit, 1, 0, 1, 1);

        pushButton = new QPushButton(widget3);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(40, 40));
        pushButton->setMaximumSize(QSize(40, 40));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("go-up")));
        pushButton->setIcon(icon);

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ConverterAPP", nullptr));
        menu_label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\320\265", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        encode_lbl->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\264\320\270\321\200\320\276\320\262\320\272\320\260", nullptr));
        encode_value_lbl->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        created_lbl->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217", nullptr));
        created_value_lbl->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        edited_lbl->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", nullptr));
        edited_value_lbl->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        change_catalog_btn->setText(QCoreApplication::translate("MainWindow", "\320\241\320\274\320\265\320\275\320\260 \320\272\320\260\321\202\320\260\320\273\320\276\320\263\320\260", nullptr));
        choose_file_btn->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200 \321\204\320\260\320\271\320\273\320\260", nullptr));
        sel_encode_btn->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\272\321\203", nullptr));
        save_btn->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        path_label->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \320\277\321\203\321\202\321\214", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
