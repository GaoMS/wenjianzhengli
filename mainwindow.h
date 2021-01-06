#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    struct fileInfo {
        QStringList fileName;
        QStringList absolutePath;
        QStringList suffix;
        QStringList allFileKind;
    };

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString originalPath = "./";
    fileInfo files;
    void recursion_files(QString path, fileInfo &files);
    void move_files(fileInfo files);
};
#endif // MAINWINDOW_H
