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

//動画/音声ファイルを読み込む
void MainWindow::on_pushButton_clicked()
{
    file = QFileDialog::getOpenFileName();
    ui->label_6->setText(file);
}

//動画/音声を出力するフォルダを選択
void MainWindow::on_pushButton_5_clicked()
{
    dir = QFileDialog::getExistingDirectory();
    ui->label_7->setText(dir);
}

//画像ファイルを読み込む
void MainWindow::on_pushButton_9_clicked()
{
    file = QFileDialog::getOpenFileName();
    ui->label_5->setText(file);
}

//画像を出力するフォルダを選択
void MainWindow::on_pushButton_10_clicked()
{
    dir = QFileDialog::getExistingDirectory();
    ui->label_8->setText(dir);
}


void MainWindow::on_pushButton_2_clicked()
{
    //ファイル名を読み込む
    QString text = ui->textEdit->toPlainText();
    QString command = "ffmpeg";
    QStringList arguments;
    //コマンドを作成
    arguments << "-i" << file << dir + "/" + text;
    QProcess::execute(command, arguments);
    ui->label_10->setText("変換終了＆ただいま準備中…");

}


void MainWindow::on_pushButton_11_clicked()
{
    //ファイル名を読み込む
    QString text = ui->textEdit_4->toPlainText();
    QString command = "convert";
    QStringList arguments;
    //コマンドを作成
    arguments << file << dir + "/" + text;
    QProcess::execute(command, arguments);
    ui->label_11->setText("変換終了＆ただいま準備中…");
}

