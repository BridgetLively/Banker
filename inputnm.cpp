#include "inputnm.h"
#include "ui_inputnm.h"

InputNM::InputNM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputNM)
{
    ui->setupUi(this);
}

InputNM::~InputNM()
{
    delete ui;
}

void InputNM::on_buttonBox_accepted()
{
    m=ui->input_m->text();
    n=ui->input_n->text();
    input_mat=new InputMat();
    input_mat->setNM(n.toInt(),m.toInt());
    input_mat->exec();
}
