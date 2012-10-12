#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString locale = QLocale::system().name();
    qDebug() << "-----  Localization setup  -----";
    qDebug() << "System default locale:" << locale;

    //Loads the translations
    QTranslator translator;
    translator.load(":/translations/"+locale);
    a.installTranslator(&translator);







    MainWindow w;
    w.show();
    
    return a.exec();
}
