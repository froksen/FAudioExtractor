#include "soundfile.h"

SoundFile::SoundFile(QObject *parent) :
    QObject(parent)
{
}

void SoundFile::setFilename(QString Filename)
{
    filename = Filename;
}

QString SoundFile::Filename()
{
    return filename;
}

void SoundFile::setFormat(QString Format)
{
    format = Format;
}

QString SoundFile::Format()
{
    return format;
}

void SoundFile::setOutputdirectory(QString outputdir)
{
    directoryoutput = outputdir;
}

QString SoundFile::Outputdirectory()
{
    return directoryoutput;
}

void SoundFile::setInputvideofile(QString Inputvideofile)
{
    inputvideofile = Inputvideofile;
}

QString SoundFile::Inputvideofile()
{
    return inputvideofile;
}
