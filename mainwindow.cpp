#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    originalPath = QFileDialog::getExistingDirectory(this, "选择目录", originalPath, QFileDialog::ShowDirsOnly);
//    fileInfo files;
    recursion_files(originalPath, files);
    qDebug() << files.allFileKind;

    QStandardItemModel *model = new QStandardItemModel;

    model->setColumnCount(2);
    model->setHeaderData(0, Qt::Horizontal, "文件名");
    model->setHeaderData(1, Qt::Horizontal, "绝对路径");
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    for (int i = 0; i < files.fileName.length(); i++) {
        model->setItem(i, 0, new QStandardItem(files.fileName[i]));
        model->setItem(i, 1, new QStandardItem(files.absolutePath[i]));
    }
}

void MainWindow::recursion_files(QString path, fileInfo & files)
{
    QDir dir(path);

    for (QFileInfo fulldir : dir.entryInfoList()) {
        if (fulldir.fileName() == "." || fulldir.fileName() == "..")
            continue;
        if (fulldir.isDir()) {
            recursion_files(fulldir.absoluteFilePath(), files);
        }
        else {
            files.fileName.append(fulldir.fileName());
            files.absolutePath.append(fulldir.absoluteFilePath());
            files.suffix.append(fulldir.suffix());
            if (!files.allFileKind.contains(fulldir.suffix()))
                files.allFileKind.append(fulldir.suffix());
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString dstPath = QFileDialog::getExistingDirectory(this, "选择目录", originalPath, QFileDialog::ShowDirsOnly);
    ui->lineEdit->setText(dstPath);
}

void MainWindow::on_pushButton_3_clicked()
{
    move_files(files);
}

void MainWindow::move_files(fileInfo files)
{
    QString dstPath = ui->lineEdit->text() + "/";

    if (ui->checkBox->isChecked()) {
        for (QString su : files.allFileKind) {
            QString dstFolder = dstPath + su;
            QDir dir(dstFolder);
            if (!dir.exists()) {
                dir.mkdir(dstFolder);
            }
        }
        for (int i = 0; i < files.absolutePath.length(); i++) {
            QString dst = dstPath + files.suffix[i] + "/" + files.fileName[i];
            QFile::copy(files.absolutePath[i], dst);
        }
    }
    else {
        for (int i = 0; i < files.absolutePath.length(); i++) {
            QString dst = dstPath + files.fileName[i];
            QFile::copy(files.absolutePath[i], dst);
        }
    }

}
