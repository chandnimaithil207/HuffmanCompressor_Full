/*#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseButton_clicked();
    void on_compressButton_clicked();
    void on_decompressButton_clicked();

private:
    Ui::MainWindow *ui;
    void updateReport(const QString &filePath, bool compressed);
    void showWarning(const QString &message);
};
*/
// mainwindow.h
/*
#pragma once
#include <QMainWindow>
#include "huffman.h"    // <-- include your header

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_compressButton_clicked();   // <-- this slot
    void on_decompressButton_clicked(); // if you have a decompress button

private:
    Ui::MainWindow *ui;
};*/
#pragma once
#include <QMainWindow>
#include "huffman.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseButton_clicked();       // ✅ Add this
    void on_compressButton_clicked();     // Already correct
    void on_decompressButton_clicked();   // Already correct

private:
    Ui::MainWindow *ui;

    void updateReport(const QString &originalPath, const QString &newPath, bool compressed); // ✅ Needed
    void showWarning(const QString &message);                                                // ✅ Needed
};
