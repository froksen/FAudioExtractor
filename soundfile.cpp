#include "soundfile.h"
#include <QDebug>

SoundFile::SoundFile(QObject *parent) :
    QObject(parent)
{
    filename = "myaudiofile";
    format = "mp3";
    directoryoutput = QDir::homePath();

    //Creates the formatsmodel
    supportformatslist << "mp3" << "ogg" << "wav" << "wma" << "flac" << "aac";

    supportedformatsMap.insert("MPEG-1 Audio Layer 3 (MP3)","mp3");
    supportedformatsMap.insert("Ogg Vorbis (OGG)","ogg");
    supportedformatsMap.insert("Waveform Audio File Format (WAV)","wav");
    supportedformatsMap.insert("Windows Media Audio (WMA)","wma");
    supportedformatsMap.insert("Free Lossless Audio Codec (FLAC)","flac");
    //supportedformatsMap.insert("Advanced Audio Coding (AAC)","aac");
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
    format = supportedformatsMap.value(Format);
    qDebug() << "Format name:" << Format;
    qDebug() << "Format ext:" << format;

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

QMap<QString,QString> SoundFile::Supportedformats()
{
    return supportedformatsMap;
}
