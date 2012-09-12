#ifndef SOUNDFILE_H
#define SOUNDFILE_H

#include <QObject>
#include <QDir>

class SoundFile : public QObject
{
    Q_OBJECT
public:
    explicit SoundFile(QObject *parent = 0);
    
    void setFilename(QString Filename="myaudiofile");
    QString Filename();
    void setFormat(QString Format="mp3");
    QString Format();
    void setOutputdirectory(QString outputdir = QDir::homePath());
    QString Outputdirectory();
    void setInputvideofile(QString inputdir);
    QString Inputvideofile();


private:
    QString filename;
    QString inputvideofile;
    QString format;
    QString directoryoutput;

signals:
    
public slots:
    
};

#endif // SOUNDFILE_H
