#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "huffman.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Set modern dark stylesheet with emoji support
    this->setStyleSheet(R"(
    QWidget {
        background-color: #1e1e2f;
        color: #e0e0e0;
        font-family: 'Segoe UI', sans-serif;
        font-size: 14px;
    }

    QPushButton {
        background-color: #3a86ff;
        color: white;
        border: none;
        padding: 8px 16px;
        border-radius: 6px;
    }

    QPushButton:hover {
        background-color: #0059ff;
    }

    QPushButton:pressed {
        background-color: #0041c4;
    }

    QLineEdit, QTextEdit {
        background-color: #2e2e3f;
        color: #e0e0e0;
        border: 1px solid #555;
        border-radius: 4px;
        padding: 4px;
    }

    QLabel {
        color: #e0e0e0;
    }

    QGroupBox {
        border: 1px solid #444;
        border-radius: 5px;
        margin-top: 10px;
    }

    QGroupBox::title {
        subcontrol-origin: margin;
        subcontrol-position: top left;
        padding: 0 3px;
    }

    QMessageBox {
        background-color: #2c2c3c;
        color: white;
    }
)");

    // Apply emoji labels
    ui->browseButton->setText("📂 Browse");
    ui->compressButton->setText("📦 Compress");
    ui->decompressButton->setText("📤 Decompress");

    ui->labelOriginalSize->setText("📁 Original Size:");
    ui->labelCompressedSize->setText("🧬 Compressed Size:");
    ui->labelSpaceSaved->setText("💡 Space Saved:");
    ui->labelWarning->setText("🔔 Status messages appear here.");

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_browseButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select File");
    if (!filePath.isEmpty()) {
        ui->filePathEdit->setText(filePath);
    }
}

/*void MainWindow::on_compressButton_clicked() {
    QString filePath = ui->filePathEdit->text();
    if (filePath.endsWith(".huff")) {
        showWarning("File is already compressed.");
        return;
    }
    if (Huffman::compressFile(filePath.toStdString())) {
        updateReport(filePath, true);
    } else {
        showWarning("Compression failed.");
    }
}
*/
/*
void MainWindow::on_compressButton_clicked() {
    QString inputPath = QFileDialog::getOpenFileName(this, "Select Input File");
    QString outputPath = QFileDialog::getSaveFileName(this, "Save Compressed File");
    QString codeMapPath = QFileDialog::getSaveFileName(this, "Save Code Map File");

    if (!inputPath.isEmpty() && !outputPath.isEmpty() && !codeMapPath.isEmpty()) {
        Huffman::compress(inputPath.toStdString(), outputPath.toStdString(), codeMapPath.toStdString());
        QMessageBox::information(this, "Success", "File compressed successfully!");
    }
}
    */
    void MainWindow::on_compressButton_clicked() {
    QString inputPath = ui->filePathEdit->text();
    if (inputPath.isEmpty()) {
        showWarning("Please select a file to compress.");
        return;
    }
    if (inputPath.endsWith(".huff")) {
        showWarning("File is already compressed.");
        return;
    }

    QString outputPath = QFileDialog::getSaveFileName(this, "Save Compressed File", inputPath + ".huff");
    if (outputPath.isEmpty()) return;

    QString codeMapPath = QFileDialog::getSaveFileName(this, "Save Code Map File", inputPath + ".map");
    if (codeMapPath.isEmpty()) return;

    Huffman::compress(inputPath.toStdString(), outputPath.toStdString(), codeMapPath.toStdString());
    updateReport(inputPath, outputPath, true);
    QMessageBox::information(this, "Success", "File compressed successfully!");
}


/*
void MainWindow::on_decompressButton_clicked() {
    QString filePath = ui->filePathEdit->text();
    if (!filePath.endsWith(".huff")) {
        showWarning("File is not a compressed .huff file.");
        return;
    }
    if (Huffman::decompressFile(filePath.toStdString())) {
        updateReport(filePath, false);
    } else {
        showWarning("Decompression failed.");
    }
}
*/
/*
void MainWindow::on_decompressButton_clicked() {
    QString compressedPath = QFileDialog::getOpenFileName(this, "Select Compressed File");
    QString codeMapPath = QFileDialog::getOpenFileName(this, "Select Code Map File");
    QString outputPath = QFileDialog::getSaveFileName(this, "Save Decompressed Output");

    if (!compressedPath.isEmpty() && !codeMapPath.isEmpty() && !outputPath.isEmpty()) {
        Huffman::decompress(compressedPath.toStdString(), codeMapPath.toStdString(), outputPath.toStdString());
        QMessageBox::information(this, "Success", "File decompressed successfully!");
    }
}

void MainWindow::on_decompressButton_clicked() {
    QString inputPath = ui->filePathEdit->text();
    if (inputPath.isEmpty()) {
        showWarning("Please select a file to decompress.");
        return;
    }
    if (!inputPath.endsWith(".huff")) {
        showWarning("Selected file is not a compressed .huff file.");
        return;
    }

    QString codeMapPath = QFileDialog::getOpenFileName(this, "Select Code Map File");
    if (codeMapPath.isEmpty()) return;

    QString outputPath = QFileDialog::getSaveFileName(this, "Save Decompressed Output", inputPath.replace(".huff", "_decompressed.txt"));
    if (outputPath.isEmpty()) return;

    Huffman::decompress(inputPath.toStdString(), codeMapPath.toStdString(), outputPath.toStdString());
    updateReport(inputPath, outputPath, false);
    QMessageBox::information(this, "Success", "File decompressed successfully!");
}
void MainWindow::on_decompressButton_clicked() {
    QString filePath = ui->filePathEdit->text();
    if (!filePath.endsWith(".huff")) {
        showWarning("File is not a compressed .huff file.");
        return;
    }

    QString outPath = filePath.left(filePath.length() - 5); // remove ".huff"
    if (Huffman::decompressFile(filePath.toStdString(), outPath.toStdString())) {
        updateReport(outPath, false); // pass decompressed path
        QMessageBox::information(this, "Success", "File decompressed to:\n" + outPath);
    } else {
        showWarning("Decompression failed.");
    }
}*/
void MainWindow::on_decompressButton_clicked() {
    QString filePath = ui->filePathEdit->text();
    if (!filePath.endsWith(".huff")) {
        showWarning("File is not a compressed .huff file.");
        return;
    }

    QString outPath = filePath.left(filePath.length() - 5); // remove ".huff"

    if (Huffman::decompressFile(filePath.toStdString(), outPath.toStdString())) {
        updateReport(filePath, outPath, false);
        QMessageBox::information(this, "Success", "File decompressed to:\n" + outPath);
    } else {
        showWarning("Decompression failed.");
    }
}


/*
void MainWindow::updateReport(const QString &filePath, bool compressed) {
    QFileInfo originalInfo(filePath);
    QString newPath = compressed ? filePath + ".huff" : filePath.left(filePath.length() - 5);
    QFileInfo newInfo(newPath);
    qint64 originalSize = originalInfo.size();
    qint64 newSize = newInfo.size();
    double savings = 100.0 * (1.0 - double(newSize) / originalSize);

    ui->labelOriginalSize->setText("📁 Original Size: " + QString::number(originalSize) + " bytes");

    if (compressed) {
        ui->labelCompressedSize->setText("🧬 Compressed Size: " + QString::number(newSize) + " bytes");
        ui->labelSpaceSaved->setText("💡 Space Saved: " + QString::number(savings, 'f', 2) + "%");
    } else {
        ui->labelCompressedSize->setText("📂 Decompressed Size: " + QString::number(newSize) + " bytes");
        ui->labelSpaceSaved->setText("🔁 Size Difference: " + QString::number(-savings, 'f', 2) + "%");
    }

    ui->labelWarning->setText(compressed ? "File compressed successfully." : "File decompressed successfully.");
}
*/
void MainWindow::updateReport(const QString &originalPath, const QString &newPath, bool compressed) {
    QFileInfo originalInfo(originalPath);
    QFileInfo newInfo(newPath);

    qint64 originalSize = originalInfo.size();
    qint64 newSize = newInfo.size();
    double savings = 100.0 * (1.0 - double(newSize) / originalSize);

    ui->labelOriginalSize->setText("📁 Original Size: " + QString::number(originalSize) + " bytes");

    if (compressed) {
        ui->labelCompressedSize->setText("🧬 Compressed Size: " + QString::number(newSize) + " bytes");
        ui->labelSpaceSaved->setText("💡 Space Saved: " + QString::number(savings, 'f', 2) + "%");
    } else {
        ui->labelCompressedSize->setText("📂 Decompressed Size: " + QString::number(newSize) + " bytes");
        ui->labelSpaceSaved->setText("🔁 Size Difference: " + QString::number(-savings, 'f', 2) + "%");
    }

    ui->labelWarning->setText(compressed ? "File compressed successfully." : "File decompressed successfully.");
}

void MainWindow::showWarning(const QString &message) {
    ui->labelWarning->setText(message);
    QMessageBox::warning(this, "Warning", message);
}
