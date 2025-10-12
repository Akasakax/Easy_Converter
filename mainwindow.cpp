#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

    QString file;
    QString dir;

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
    file = QFileDialog::getOpenFileName();
    ui->label_6->setText(file);
}


void MainWindow::on_pushButton_5_clicked()
{
    dir = QFileDialog::getExistingDirectory();
    ui->label_7->setText(dir);
}


void MainWindow::on_pushButton_9_clicked()
{
    file = QFileDialog::getOpenFileName();
    ui->label_5->setText(file);
}


void MainWindow::on_pushButton_10_clicked()
{
    dir = QFileDialog::getExistingDirectory();
    ui->label_8->setText(dir);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString text = ui->textEdit->toPlainText();
    QString command = "ffmpeg";
    QStringList arguments;
    arguments << "-i" << file << dir + "/" + text;
    QProcess::execute(command, arguments);
    ui->label_10->setText("変換終了＆ただいま準備中…");

}


void MainWindow::on_pushButton_11_clicked()
{
    QString text = ui->textEdit_4->toPlainText();
    QString command = "convert";
    QStringList arguments;
    arguments << file << dir + "/" + text;
    qDebug() << "file path:" << arguments;
    QProcess::execute(command, arguments);
    ui->label_11->setText("変換終了＆ただいま準備中…");
}

