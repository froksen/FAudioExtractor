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
    void setInputdirectory(QString inputdir);
    QString Inputdirectory();


private:
    QString filename;
    QString format;
    QString directoryoutput;
    QString directoryinput;

signals:
    
public slots:
    
};

#endif // SOUNDFILE_H
