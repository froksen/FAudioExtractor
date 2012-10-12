#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "soundfile.h"
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>
#include <QtCore>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Makes sure the window is in the center of desktop
    QRect r = MainWindow::geometry();
    r.moveCenter(QApplication::desktop()->availableGeometry().center());
    MainWindow::setGeometry(r);

    //Creates the pointer for the SoundFile class
    mSoundFile = new SoundFile(this);

    //The types of formats that are supported
//    QStringListModel *supportedformatsmodel = new QStringListModel(this);
//    supportedformatsmodel->setStringList(mSoundFile->Supportedformats());
//    ui->comboBox_outputfile->setModel(supportedformatsmodel);
    QMap <QString,QString> supportedformatsmap = mSoundFile->Supportedformats();

    foreach(QString name, supportedformatsmap.keys()){
        ui->comboBox_outputfile->addItem(name,mSoundFile->Supportedformats().value(name));
    }


    //Fixes so no outputdir is shown as default
    ui->lineEdit_outputfile->clear();

    //Hides the outputTextfield
    on_checkBox_stateChanged(0);

    //Pusbuttons Connections
    mProcess = new process(this);

    //About dialog
    mAboutdialog = new AboutDialog();

    //Hides forcestop button
    ui->pushButton->setEnabled(0);
    ui->pushButton_2->hide();

    connect(this,SIGNAL(inputLineEdithasText(bool)),ui->pushButton,SLOT(setEnabled(bool)));

    //While working
    connect(mProcess,SIGNAL(stderrChanged(QString)),ui->pushButton,SLOT(hide()));
    connect(mProcess,SIGNAL(stderrChanged(QString)),ui->pushButton_2,SLOT(show()));
    connect(mProcess,SIGNAL(stdoutChanged(QString)),ui->pushButton,SLOT(hide()));
    connect(mProcess,SIGNAL(stdoutChanged(QString)),ui->pushButton_2,SLOT(show()));

    connect(mProcess,SIGNAL(stdoutChanged(QString)),ui->comboBox_outputfile,SLOT(hide()));
    connect(mProcess,SIGNAL(stderrChanged(QString)),ui->comboBox_outputfile,SLOT(show()));


    //When done
    connect(mProcess,SIGNAL(extractionDone(int)),ui->pushButton,SLOT(show()));
    connect(mProcess,SIGNAL(extractionDone(int)),ui->pushButton_2,SLOT(hide()));


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

        //emits signal
        emit inputLineEdithasText(1);

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
        //Emits signal
        emit outputLineEdithasText(1);

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
    mAboutdialog->exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox msgBox;    msgBox.setText(trUtf8("Force stop - sure?"));
    msgBox.setInformativeText(trUtf8("The process can NOT be resumed. The audio that have been extracted might not work."));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();



    switch (ret)  {
      case QMessageBox::Yes:
            mProcess->stopCommand();
          break;
      case QMessageBox::No:
          break;
    }

}
