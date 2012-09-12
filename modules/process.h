#ifndef PROCESS_H
#define PROCESS_H
#include <QtGui>
#include <QtCore>


class process : public QObject
{
    Q_OBJECT

private:
    QString command;
    QStringList arguments;


public:
    explicit process(QObject *parent = 0);
    QProcess *mprocess;
    QByteArray stderrdata;
    QByteArray stdoutdata;

    void setCommand(QString newCommand);
    void setArguments(QStringList newArguments);
    bool startCommand();
    void stopCommand();

signals:
    void stderrChanged(QString mytext);
    void stdoutChanged(QString mytext);
    void extractionDone(int value);


public slots:

private slots:
    void readstderr();
    void readstdout();
    void onProcessFinished(int exitCode, QProcess::ExitStatus status);



};

#endif // PROCESS_H
