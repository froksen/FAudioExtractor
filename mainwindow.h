#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "soundfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_inputfile_clicked();
    void on_pushButton_outputfile_clicked();
    void on_comboBox_outputfile_currentIndexChanged(const QString &arg1);
    void on_pushButton_clicked();

private slots:
    void doExtraction();

private:
    Ui::MainWindow *ui;

    SoundFile *mSoundFile;

};

#endif // MAINWINDOW_H
