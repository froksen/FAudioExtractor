#include "soundfile.h"
#include <QDebug>

SoundFile::SoundFile(QObject *parent) :
    QObject(parent)
{
    //Creates the formatsmodel
    supportformatslist << "mp3" << "ogg" << "wav" << "wma" << "flac" << "aac";
}

void SoundFile::setFilename(QString Filename)
{
    filename = Filename;
    qDebug() << "Filename set to:" << filename;
}

QString SoundFile::Filename()
{
    return filename;
}

int SoundFile::setFormat(QString Format)
{
    format = Format;
    qDebug() << "Format set to:" << format;

    if(!supportformatslist.contains(format)){
        return -1;
    }

    return 0;

}

QString SoundFile::Format()
{
    return format;
}

void SoundFile::setOutputdirectory(QString outputdir)
{
    directoryoutput = outputdir;
    qDebug() << "Outputdirectory set to:" << directoryoutput;

}

QString SoundFile::Outputdirectory()
{
    return directoryoutput;
}

void SoundFile::setInputvideofile(QString Inputvideofile)
{
    inputvideofile = Inputvideofile;
    qDebug() << "Inputdirectory set to:" << inputvideofile;
}

QString SoundFile::Inputvideofile()
{
    return inputvideofile;
}

QString SoundFile::inputfileFilename()
{
    return QFileInfo(inputvideofile).baseName();
}

QStringList SoundFile::Supportedformats()
{
    return supportformatslist;
}
