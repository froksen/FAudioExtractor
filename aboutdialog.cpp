#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    updateAbouttab();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::updateAbouttab()
{
    ui->textEditAbout->append(QString("<b>%1:</b> %2").arg(trUtf8("Created by"),"Ole Hom Frandsen"));
    ui->textEditAbout->append(QString("<b>%1:<&b> %2").arg(trUtf8("Licensed under"),"GPLv2"));
}

void AboutDialog::on_pushButtonClose_clicked()
{
    AboutDialog::close();
}
