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

    ui->textEditAbout->append("\n");
    ui->textEditAbout->append(QString("<h2>%1:</h2>").arg(trUtf8("Translations")));

    ui->textEditAbout->append(QString("<h3>%1:</h3>").arg(trUtf8("Danish")));
    ui->textEditAbout->append(QString("Ole 'Froksen' Holm Frandsen"));

    ui->textEditAbout->append(QString("<h3>%1:</h3>").arg(trUtf8("Czech")));
    ui->textEditAbout->append(QString("Pavel 'fri' Fric"));

    ui->textEditAbout->append(QString("<h3>%1:</h3>").arg(trUtf8("German")));
    ui->textEditAbout->append(QString("Schiwi"));
}

void AboutDialog::on_pushButtonClose_clicked()
{
    AboutDialog::close();
}
