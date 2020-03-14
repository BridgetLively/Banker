#include "warning.h"
#include "ui_warning.h"

Warning::Warning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Warning)
{
    ui->setupUi(this);

}

Warning::~Warning()
{
    delete ui;
}

void Warning::setLabel1(QString str)
{
    ui->label->setText(str);
    QFont ft;
    ft.setPointSize(12);
    ui->label->setFont(ft);
}

void Warning::setLabel2(QString str)
{
    ui->label_2->setText(str);
    QFont ft;
    ft.setPointSize(9);
    ui->label_2->setFont(ft);
}

void Warning::setLabel3(QString str)
{
    ui->label_3->setText(str);
}
