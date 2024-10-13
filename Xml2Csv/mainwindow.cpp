#include "mainwindow.h"
#include "main.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setAcceptDrops(true);
}

void MainWindow::setupUi()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    fileLabel = new QLabel("Перетащите файл сюда или ткните для обзора", this);
    fileLabel->setAlignment(Qt::AlignCenter);
    fileLabel->setMinimumHeight(100);
    fileLabel->setStyleSheet("QLabel { border: 2px dashed #aaa; border-radius: 5px; }");

    browseButton = new QPushButton("Обзор", this);
    convertButton = new QPushButton("Конвертировать", this);
    convertButton->setEnabled(false);

    isDeletedCheckBox = new QCheckBox("Deleted", this);
    isReplicatedCheckBox = new QCheckBox("Replicated", this);
    isSizedCheckBox = new QCheckBox("Sized", this);
    isDiscountedCheckBox = new QCheckBox("Discounted", this);
    isSetCheckBox = new QCheckBox("Set", this);

    layout->addWidget(fileLabel);
    layout->addWidget(browseButton);
    layout->addWidget(isDeletedCheckBox);
    layout->addWidget(isReplicatedCheckBox);
    layout->addWidget(isSizedCheckBox);
    layout->addWidget(isDiscountedCheckBox);
    layout->addWidget(isSetCheckBox);
    layout->addWidget(convertButton);

    setCentralWidget(centralWidget);

    connect(browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseClicked);
    connect(convertButton, &QPushButton::clicked, this, &MainWindow::onConvertClicked);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls() && event->mimeData()->urls().count() == 1)
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QUrl url = event->mimeData()->urls().first();
    if (url.isLocalFile())
    {
        filePath = url.toLocalFile();
        fileLabel->setText(QFileInfo(filePath).fileName());
        convertButton->setEnabled(true);
    }
}

void MainWindow::onBrowseClicked()
{
    QString defaultDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    filePath = QFileDialog::getOpenFileName(this, "Выберите XML-файл", defaultDir, "XML-файлы (*.xml)");

    if (!filePath.isEmpty())
    {
        fileLabel->setText(QFileInfo(filePath).fileName());
        convertButton->setEnabled(true);
    }
}

void MainWindow::onConvertClicked()
{
    convertFile();
}

void MainWindow::convertFile()
{
    if (!filePath.isEmpty()) {
        // Convert the XML to CSV
        convertXmlToCsv(filePath.toStdString());

        // Get the output CSV file path
        QString csvFilePath = QFileInfo(filePath).absolutePath() + "/" + QFileInfo(filePath).completeBaseName() + ".csv";

        // Create a custom message box with "Open" and "Open Folder" buttons
        QMessageBox msgBox;
        msgBox.setText("Файл успешно конвертирован!");
        msgBox.setInformativeText("Вы хотите открыть файл или папку?");

        QPushButton *openButton = msgBox.addButton(tr("Открыть"), QMessageBox::AcceptRole);
        QPushButton *openFolderButton = msgBox.addButton(tr("Открыть папку"), QMessageBox::AcceptRole);
        QPushButton *closeButton = msgBox.addButton(QMessageBox::Close);

        msgBox.exec();

        if (msgBox.clickedButton() == openButton) {
            QDesktopServices::openUrl(QUrl::fromLocalFile(csvFilePath));
        } else if (msgBox.clickedButton() == openFolderButton) {
            QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(csvFilePath).absolutePath()));
        }

    } else {
        QMessageBox::warning(this, "Ошибка", "Не выбран файл для конвертации.");
    }
}
