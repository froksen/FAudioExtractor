#ifndef SOUNDFILE_H
#define SOUNDFILE_H

#include <QObject>
#include <QDir>
#include <QStringListModel>

class SoundFile : public QObject
{
    Q_OBJECT
public:
    explicit SoundFile(QObject *parent = 0);
    
    void setFilename(QString Filename="myaudiofile");
    QString Filename();
    int setFormat(QString Format = "mp3");
    QString Format();
    void setOutputdirectory(QString outputdir = QDir::homePath());
    QString Outputdirectory();
    void setInputvideofile(QString inputdir);
    QString Inputvideofile();
    QString inputfileFilename();

    QStringList Supportedformats();


private:
    //Information about the file
    QString filename = "myaudiofile";
    QString inputvideofile;
    QString format = "mp3";
    QString directoryoutput = QDir::homePath();

    //Other
    QStringList supportformatslist;



signals:
    
public slots:
    
};

#endif // SOUNDFILE_H
