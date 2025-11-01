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
{
    QString text = ui->textEdit->toPlainText();
    QString command = "ffmpeg";
    QStringList arguments;
    //エンコード方式を選択
    if (encodetype == "AMD"){
        arguments << "-threads" << "0" << "-vaapi_device" << "/dev/dri/renderD128" << "-i" << file
                  << "-vf" << "format=nv12,hwupload"
                  << "-c:v" << "hevc_vaapi" << dir + "/" + text;
        qDebug() << encodetype;
    }else if (encodetype == "CPU"){
        arguments << "-threads" << "0" << "-i" << file << dir + "/" + text;
        qDebug() << encodetype;
    }else{
        arguments << "-threads" << "0" << "-i"  << file << dir + "/" + text;
        qDebug() << encodetype;
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
    connect(process,static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),this,[=](int exitCode, QProcess::ExitStatus) {
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

    // 「変換中」と表示
    ui->label_10->setText("変換中");
    ui->label_10->setStyleSheet("background-color: orange;");

    // QProcessを生成
    QProcess *process = new QProcess();

    // コマンド実行（非同期）
    process->start(command, arguments);

    // 終了時の処理
    //終了したときの返される値から判断
    connect(process,static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),this,[=](int exitCode, QProcess::ExitStatus) {
        if (exitCode == 0) {
            ui->label_11->setText("変換完了");
            ui->label_11->setStyleSheet("background-color: #339966;");
        } else{
            ui->label_11->setText("変換失敗");
            ui->label_11->setStyleSheet("background-color: #993333;");
        }
    });
}

//ファイルを選択
void MainWindow::on_action_triggered()
{
    file = QFileDialog::getOpenFileName();
    ui->label_5->setText(file);
    ui->label_6->setText(file);
}

//終了
void MainWindow::on_actionexit_triggered()
{
    this -> close();
}

//エンコードタイプAMD
void MainWindow::on_checkBox_toggled(bool checked)
{
    if (checked) {
        // QProcessを生成
        QProcess *process = new QProcess();
        QString command = "lspci";
        // コマンド実行（非同期）
        process->start(command);
        process->waitForFinished();
        QString output = process -> readAllStandardOutput();
        if(output.contains("AMD")){
            encodetype = "";
            ui -> checkBox_2 -> setChecked(false);
            encodetype = "AMD";
            qDebug() << "type:" << encodetype;
            }else{
            QMessageBox::critical(this, tr("GPUの確認"), tr("AMDのGPUが確認できません。"));
            encodetype = "";
            ui -> checkBox -> setChecked(false);
        }
    }
}

//エンコードタイプCPU
void MainWindow::on_checkBox_2_toggled(bool checked)
{
    if (checked) {
        encodetype = "";
        ui -> checkBox -> setChecked(false);
        encodetype = "CPU";
        qDebug() << "type:" << encodetype;
    }
}

