#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "soundfile.h"
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>
#include <modules/process.h>

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
    ui->lineEdit_outputfile->setText(QString("%1/%2.%3").arg(mSoundFile->Outputdirectory(), mSoundFile->Filename(),mSoundFile->Format()));
}

void MainWindow::on_pushButton_clicked()
{
    doExtraction();
}

void MainWindow::doExtraction()
{
    process *mProcess = new process(this);

    //Sets the arguments
    QStringList arguments;
    arguments << "-dumpaudio";
    arguments << mSoundFile->Inputvideofile();
    arguments << "-dumpfile";
    arguments << mSoundFile->Outputdirectory() + "/" + mSoundFile->Filename() + "." + mSoundFile->Format();

    //Sets the program
    mProcess->setCommand("mplayer");

    //Puts it all together
    mProcess->setArguments(arguments);
    mProcess->startCommand();

}
