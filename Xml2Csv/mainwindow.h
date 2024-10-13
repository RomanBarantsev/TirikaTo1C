#pragma once

#include <QMainWindow>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    private slots:
        void onConvertClicked();
    void onBrowseClicked();

private:
    QLabel *fileLabel;
    QPushButton *browseButton;
    QPushButton *convertButton;
    QCheckBox *isDeletedCheckBox;
    QCheckBox *isReplicatedCheckBox;
    QCheckBox *isSizedCheckBox;
    QCheckBox *isDiscountedCheckBox;
    QCheckBox *isSetCheckBox;

    QString filePath;

    void setupUi();
    void convertFile();
};