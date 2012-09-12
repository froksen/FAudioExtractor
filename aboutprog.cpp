#include "aboutprog.h"
#include "ui_aboutprog.h"
#include <QDesktopWidget>

AboutProg::AboutProg(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AboutProg)
{
    ui->setupUi(this);

//    QRect r = AboutProg::geometry();
//    r.moveCenter(QApplication::desktop()->availableGeometry().center());

    //Append texts
    appendTranslators();
    appendSpecialThanks();
}

AboutProg::~AboutProg()
{
    delete ui;
}

//This method makes it eaiser to add new translators, without having to retranste the entire textedit.
void AboutProg::appendTranslators()
{
    ui->textEdit_2->append(trUtf8("Danish - Ole 'Froksen' Holm Frandsen"));

}

void AboutProg::appendSpecialThanks()
{

}
