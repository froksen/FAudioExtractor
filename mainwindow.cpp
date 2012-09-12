#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "soundfile.h"
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>
#include <modules/process.h>
#include <QtCore>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Creates the pointer for the SoundFile class
    mSoundFile = new SoundFile(this);

    //The types of formats that are supported
    QStringListModel *supportedformatsmodel = new QStringListModel(this);
    supportedformatsmodel->setStringList(mSoundFile->Supportedformats());
    ui->comboBox_outputfile->setModel(supportedformatsmodel);

    //Fixes so no outputdir is shown as default
    ui->lineEdit_outputfile->clear();

    //Hides the outputTextfield
    on_checkBox_stateChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_inputfile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"),
                                QDir::homePath(),
                                tr("Movies (*.3g2 *.3gp *.asf *.asx *.flv *.mov *.mp4 *.mpg *.rm  *.swf *.vob *.wmv *.mkv *.avi *.mpeq *.ogg)"));


    if(!fileName.isEmpty()){

        //Sets the new INFO
        ui->lineEdit_inputfile->setText(fileName);
        mSoundFile->setInputvideofile(fileName);

        //Updates the outputfile
        QFileInfo mOutfile (fileName);
        mSoundFile->setFilename(mOutfile.baseName());
        mSoundFile->setOutputdirectory(mOutfile.absolutePath());

        ui->lineEdit_outputfile->setText(QString("%1/%2.%3").arg(mSoundFile->Outputdirectory(), mSoundFile->Filename(),mSoundFile->Format()));

    }
}

void MainWindow::on_pushButton_outputfile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"),
                                                    mSoundFile->Outputdirectory() + "/" + mSoundFile->inputfileFilename() + "." + mSoundFile->Format(),
                               "Soundfiles (*.mp3 *.ogg *.wav *.wma *.flac *.aac)");

    if(!fileName.isEmpty()){

        //Sets the new INFO
        QFileInfo mOutfile (fileName);
        mSoundFile->setFilename(mOutfile.baseName());
        mSoundFile->setOutputdirectory(mOutfile.absolutePath());

        //Updates GUI
        ui->lineEdit_outputfile->setText(fileName);

    }
}

void MainWindow::on_comboBox_outputfile_currentIndexChanged(const QString &arg1)
{
    mSoundFile->setFormat(arg1);
    if(ui->lineEdit_inputfile->text().isEmpty()) {
        return;
    }
    ui->lineEdit_outputfile->setText(QString("%1/%2.%3").arg(mSoundFile->Outputdirectory(), mSoundFile->Filename(),mSoundFile->Format()));
}

void MainWindow::on_pushButton_clicked()
{
    doExtraction();
}

void MainWindow::handleTerminaloutput(QString text)
{
//    QRegExp rx("(\\d+)");
//    QStringList list;


//    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!";
//    int pos = 0;

//    while ((pos = rx.indexIn(text, pos)) != -1) {
//        list << rx.cap(1);
//        pos += rx.matchedLength();
//    }
//    qDebug() << list;
//    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!";

    if(text.left(4) == "dump")
    {
        ui->progressBar->setValue(text.right(9).remove(0,2).remove(4,100).toFloat());
    }

}

void MainWindow::doExtraction()
{
    process *mProcess = new process(this);
    ui->progressBar->setValue(0);

    //Sets the arguments
    QStringList arguments;
    arguments << "-dumpaudio";
    arguments << mSoundFile->Inputvideofile();
    arguments << "-dumpfile";
    arguments << mSoundFile->Outputdirectory() + "/" + mSoundFile->Filename() + "." + mSoundFile->Format();

    //Sets the program
    mProcess->setCommand("mplayer");

    connect(mProcess,SIGNAL(stderrChanged(QString)),ui->textEdit,SLOT(append(QString)));
    connect(mProcess,SIGNAL(stdoutChanged(QString)),ui->textEdit,SLOT(append(QString)));
    connect(mProcess,SIGNAL(stdoutChanged(QString)),this,SLOT(handleTerminaloutput(QString)));
    connect(mProcess,SIGNAL(extractionDone(int)),ui->progressBar,SLOT(setValue(int)));
    connect(mProcess,SIGNAL(extractionDone(QString)),mProcess,SLOT(deleteLater()));


    //Puts it all together
    mProcess->setArguments(arguments);
    mProcess->startCommand();

    ui->progressBar->setValue(10);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0) {
        ui->textEdit->hide();
    }
    else {
        ui->textEdit->show();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox mssg;
    mssg.setStandardButtons(QMessageBox::Ok);
    mssg.setText("Created by Ole 'Froksen' Holm Frandsen <br> Released under the GPLv2 license");
    mssg.exec();
}
