#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "soundfile.h"
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>

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
                                                    QDir::homePath() + "/" + mSoundFile->inputfileFilename() + "." + mSoundFile->Format(),
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
    ui->lineEdit_outputfile->setText(QString("%1/%2.%3").arg(mSoundFile->Outputdirectory(), mSoundFile->Filename(),mSoundFile->Format()));
}
