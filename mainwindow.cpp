#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

    QString file;
    QString dir;
    QString encodetype = "";

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

//動画/音声を出力する
void MainWindow::on_pushButton_2_clicked()
{/*
    //ファイル名を読み込む
    QString text = ui->textEdit->toPlainText();
    QString command = "ffmpeg";
    QStringList arguments;
    //コマンドを作成
    arguments << "-i" << file << dir + "/" + text;
    QProcess::execute(command, arguments);
    ui->label_10->setText("変換終了");
    ui->label_10->setStyleSheet("background-color: #993333;");
*/
    QString text = ui->textEdit->toPlainText();
    QString command = "ffmpeg";
    QStringList arguments;
    if (encodetype == "AMD"){
        arguments << "-vaapi_device" << "/dev/dri/renderD128" << "-i" << file
                  << "-vf" << "format=nv12,hwupload"
                  << "-c:v" << "h264_vaapi" << dir + "/" + text;
    }else if (encodetype == "CPU"){
        arguments << "-i"  << file << dir + "/" + text;
    }else{
        arguments << "-i"  << file << dir + "/" + text;
    }
    // 「変換中」と表示
    ui->label_10->setText("変換中");
    ui->label_10->setStyleSheet("background-color: orange;");

    // QProcessを生成
    QProcess *process = new QProcess();

    // コマンド実行（非同期）
    process->start(command, arguments);

    // 終了時の処理
    //終了したときの返される値から判断
    connect(process, &QProcess::finished, [=](int exitCode) {
        if (exitCode == 0) {
            ui->label_10->setText("変換完了");
            ui->label_10->setStyleSheet("background-color: #339966;");
        } else{
            ui->label_10->setText("変換失敗");
            ui->label_10->setStyleSheet("background-color: #993333;");
        }
    });
}

//画像を出力する
void MainWindow::on_pushButton_11_clicked()
{
    //ファイル名を読み込む
    QString text = ui->textEdit_4->toPlainText();
    QString command = "convert";
    QStringList arguments;
    arguments << file << dir + "/" + text;

    /*
    //コマンドを作成
    arguments << file << dir + "/" + text;
    QProcess::execute(command, arguments);
    ui->label_11->setText("変換終了");
    ui->label_11->setStyleSheet("background-color: #993333;"); */

    // 「変換中」と表示
    ui->label_10->setText("変換中");
    ui->label_10->setStyleSheet("background-color: orange;");

    // QProcessを生成
    QProcess *process = new QProcess();

    // コマンド実行（非同期）
    process->start(command, arguments);

    // 終了時の処理
    //終了したときの返される値から判断
    connect(process, &QProcess::finished, [=](int exitCode) {
        if (exitCode == 0) {
            ui->label_11->setText("変換完了");
            ui->label_11->setStyleSheet("background-color: #339966;");
        } else{
            ui->label_11->setText("変換失敗");
            ui->label_11->setStyleSheet("background-color: #993333;");
        }
    });
}


void MainWindow::on_action_triggered()
{
    file = QFileDialog::getOpenFileName();
    ui->label_5->setText(file);
    ui->label_6->setText(file);
}


void MainWindow::on_actionexit_triggered()
{
    this -> close();
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if (checked) {
        encodetype = "AMD";
    } else {
        encodetype = "";
    }
}


void MainWindow::on_checkBox_2_toggled(bool checked)
{
    if (checked) {
        encodetype = "CPU";
    } else {
        encodetype = "";
    }
}

