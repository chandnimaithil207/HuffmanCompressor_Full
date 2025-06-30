/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *browseButton;
    QLineEdit *filePathEdit;
    QPushButton *compressButton;
    QPushButton *decompressButton;
    QLabel *labelOriginalSize;
    QLabel *labelCompressedSize;
    QLabel *labelSpaceSaved;
    QLabel *labelWarning;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(640, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        browseButton = new QPushButton(centralwidget);
        browseButton->setObjectName("browseButton");
        browseButton->setGeometry(QRect(510, 20, 100, 30));
        filePathEdit = new QLineEdit(centralwidget);
        filePathEdit->setObjectName("filePathEdit");
        filePathEdit->setGeometry(QRect(20, 20, 480, 30));
        compressButton = new QPushButton(centralwidget);
        compressButton->setObjectName("compressButton");
        compressButton->setGeometry(QRect(140, 70, 120, 40));
        decompressButton = new QPushButton(centralwidget);
        decompressButton->setObjectName("decompressButton");
        decompressButton->setGeometry(QRect(300, 70, 120, 40));
        labelOriginalSize = new QLabel(centralwidget);
        labelOriginalSize->setObjectName("labelOriginalSize");
        labelOriginalSize->setGeometry(QRect(20, 130, 300, 30));
        labelCompressedSize = new QLabel(centralwidget);
        labelCompressedSize->setObjectName("labelCompressedSize");
        labelCompressedSize->setGeometry(QRect(20, 170, 300, 30));
        labelSpaceSaved = new QLabel(centralwidget);
        labelSpaceSaved->setObjectName("labelSpaceSaved");
        labelSpaceSaved->setGeometry(QRect(20, 210, 300, 30));
        labelWarning = new QLabel(centralwidget);
        labelWarning->setObjectName("labelWarning");
        labelWarning->setGeometry(QRect(20, 260, 600, 30));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        browseButton->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        compressButton->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        decompressButton->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        labelOriginalSize->setText(QCoreApplication::translate("MainWindow", "Original Size:", nullptr));
        labelCompressedSize->setText(QCoreApplication::translate("MainWindow", "Compressed Size:", nullptr));
        labelSpaceSaved->setText(QCoreApplication::translate("MainWindow", "Space Saved:", nullptr));
        labelWarning->setText(QCoreApplication::translate("MainWindow", "Status messages appear here.", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
