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
    QString filetypes ="3dostr 4xm aa aac aax ac3 ac4 ace acm act adf adp ads adx aea afc aiff aix alaw alias_pix alp amr amrnb amrwb anm apac apc ape apm apng aptx aptx_hd aqtitle argo_asf argo_brp argo_cvg asf asf_o ass ast au av1 avi avr avs avs2 avs3 bethsoftvid bfi bfstm bin bink binka bit bitpacked bmp_pipe bmv boa bonk brender_pix brstm c93 caf cavsvideo cdg cdxl cine codec2 codec2raw concat cri_pipe daud dcstr dds_pipe dfa dfpwm dhav dirac dnxhd dpx_pipe dsf dsicin dss dts dtshd dv dvbsub dvbtxt dxa ea ea_cdata eac3 epaf evc exr_pipe f32be f32le f64be f64le film_cpk filmstrip fits flac flic flv frm fsb fwse g722 g723_1 g726 g726le g729 gdv gem_pipe genh gif gif_pipe gsm gxf h261 h263 h264 hca hcom hdr_pipe hevc hnm ico idcin idf iec61883 iff ifv ilbc image2 image2pipe imf ingenient ipmovie ipu ircam iss iv8 ivf ivr j2k_pipe jack jacosub jpeg_pipe jpegls_pipe jpegxl_anim jpegxl_pipe jv kmsgrab kux kvag laf lavfi libcdio libdc1394 libgme libopenmpt live_flv lmlm4 loas lrc luodat lvf lxf m4v matroska matroska,webm mca mcc mgsts microdvd mjpeg mjpeg_2000 mlp mlv mm mmf mods moflex mov mov,mp4,m4a,3gp,3g2,mj2 mpc mpc8 mpeg mpegts mpegtsraw mpegvideo mpjpeg mpl2 mpsub msf msnwctcp msp mtaf mtv mulaw musx mv mvi mxf mxg nc nistsphere nsp nsv nut nuv obu ogg oma openal paf pam_pipe pbm_pipe pcx_pipe pdv pfm_pipe pgm_pipe pgmyuv_pipe pgx_pipe phm_pipe photocd_pipe pictor_pipe pjs pmp png_pipe pp_bnk ppm_pipe psd_pipe psxstr pva pvf qcp qdraw_pipe qoi_pipe r3d rawvideo realtext redspark rka rl2 rm roq rpl rsd rso rtp rtsp s16be s16le s24be s24le s32be s32le s8 sami sbc sbg scc scd sdns sdp sdr2 sds sdx ser sga sgi_pipe shn siff simbiosis_imx sln smjpeg smk smush sol sox spdif srt stl subviewer subviewer1 sunrast_pipe sup svag svg_pipe svs swf tak tedcaptions thp tiertexseq tiff_pipe tmv truehd tta tty txd ty u16be u16le u24be u24le u32be u32le u8 usm v210 v210x vag vbn_pipe vc1 vidc vividas vivo vmd vobsub voc vpk vplayer vqf vvc w64 wady wav wavarc wc3movie webp_pipe webvtt wsaud wsd wsvqa wv wve x11grab xa xbin xbm_pipe xmd xmv xpm_pipe xvag xwd_pipe xwma yop yuv4mpegpipe";
    QDir files(dir);
    QStringList fileList = files.entryList(QDir::Files);
    QString filetype = text.section('.', 1);
    //エラーを確認する
    if(file==""){
        QMessageBox::critical(this, tr("エラー"), tr("ファイルを選択してください。"));
    }else if(text==""){
        QMessageBox::critical(this, tr("エラー"), tr("ファイル名を記入してください。"));
    }else if(dir==""){
        QMessageBox::critical(this, tr("エラー"), tr("ディレクトリを選択してください。"));
    }else if(fileList.contains(text)){
        qDebug() << "ファイル一覧:" << fileList;
        QMessageBox::critical(this, tr("エラー"), tr("選択されたディレクトリ内に変換後の名前と同一のファイルがあります。"));
    }else if((filetypes.contains(filetype)==0)){
        QMessageBox::critical(this, tr("エラー"), tr("変換後の名前のファイル名は対応していません"));
    }else if((filetypes.contains(filetype)==0)){
        QMessageBox::critical(this, tr("エラー"), tr("変換後の名前のファイル名は対応していません"));
    }else{
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
}

//画像を出力する
void MainWindow::on_pushButton_11_clicked()
{
    //ファイル名を読み込む
    QString text = ui->textEdit_4->toPlainText();
    QString command = "convert";
    QStringList arguments;
    arguments << file << dir + "/" + text;
    QDir files(dir);
    QStringList fileList = files.entryList(QDir::Files);
    QString filetypes = "3FR, 3G2, 3GP, AAI, AI, APNG, ART, ARW, AVI, AVIF, AVS, BGR, BGRA, BGRO, BIE, BMP, BMP2, BMP3, BRF, CAL, CALS, CANVAS, CAPTION, CIN, CIP, CLIP, CMYK, CMYKA, CR2, CR3, CRW, CUR, CUT, DATA, DCM, DCR, DCX, DDS, DFONT, DJVU, DNG, DOT, DPX, DXT1, DXT5, EPDF, EPI, EPS, EPS2, EPS3, EPSF, EPSI, EPT, EPT2, EPT3, ERF, EXR, FAX, FILE, FITS, FLV, FRACTAL, FTP, FTS, G3, G4, GIF, GIF87, GRADIENT, GRAY, GRAYA, GROUP4, GV, H, HALD, HDR, HEIC, HEIF, HISTOGRAM, HRZ, HTM, HTML, HTTP, HTTPS, ICB, ICO, ICON, IIQ, INFO, INLINE, IPL, ISOBRL, ISOBRL6, J2C, J2K, JBG, JBIG, JNG, JNX, JP2, JPC, JPE, JPEG, JPG, JPM, JPS, JPT, JSON, K25, KDC, LABEL, M2V, M4V, MAC, MAGICK, MAP, MASK, MAT, MATTE, MEF, MIFF, MKV, MNG, MONO, MOV, MP4, MPC, MPEG, MPG, MRW, MSL, MSVG, MTV, MVG, NEF, NRW, NULL, ORF, OTB, OTF, PAL, PALM, PAM, PANGO, PATTERN, PBM, PCD, PCDS, PCL, PCT, PCX, PDB, PDF, PDFA, PEF, PES, PFA, PFB, PFM, PGM, PGX, PICON, PICT, PIX, PJPEG, PLASMA, PNG, PNG00, PNG24, PNG32, PNG48, PNG64, PNG8, PNM, POCKETMOD, PPM, PREVIEW, PS, PS2, PS3, PSB, PSD, PTIF, PWP, RADIAL-GRADIENT, RAF, RAS, RAW, RGB, RGBA, RGBO, RGF, RLA, RLE, RMF, RW2, SCR, SCT, SFW, SGI, SHTML, SIX, SIXEL, SPARSE-COLOR, SR2, SRF, STEGANO, SUN, SVG, SVGZ, TEXT, TGA, THUMBNAIL, TIFF, TIFF64, TILE, TIM, TTC, TTF, TXT, UBRL, UBRL6, UIL, UYVY, VDA, VICAR, VID, VIDEO, VIFF, VIPS, VST, WBMP, WEBM, WEBP, WMF, WMV, WMZ, WPG, X, X3F, XBM, XC, XCF, XPM, XPS, XV, XWD, YCbCr, YCbCrA, YUV";
    QString filetype = text.section('.', 1);

    //エラーを確認する
    if(file==""){
        QMessageBox::critical(this, tr("エラー"), tr("ファイルを選択してください。"));
    }else if(text==""){
        QMessageBox::critical(this, tr("エラー"), tr("ファイル名を記入してください。"));

    }else if(dir==""){
        QMessageBox::critical(this, tr("エラー"), tr("ディレクトリを選択してください。"));
    }
    else if(fileList.contains(text)){
        qDebug() << "ファイル一覧:" << fileList;
        QMessageBox::critical(this, tr("エラー"), tr("選択されたディレクトリ内に変換後の名前と同一のファイルがあります。"));
    }else if((filetypes.contains(filetype)==0)){
        QMessageBox::critical(this, tr("エラー"), tr("変換後の名前のファイル名は対応していません"));
    }else{

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
            QMessageBox::critical(this, tr("エラー"), tr("AMDのGPUが確認できません。"));
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

