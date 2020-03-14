#include "inputrequest.h"
#include "ui_inputrequest.h"

InputRequest::InputRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputRequest)
{
    ui->setupUi(this);
}

InputRequest::~InputRequest()
{
    delete ui;
}

void InputRequest::setM(int m)
{
   ui->tableWidget->setColumnCount(m);
   ui->tableWidget->setRowHeight(0,20);
   for(int i=0;i<m;i++)
   {
       ui->tableWidget->setColumnWidth(i,20);
   }
}

void InputRequest::on_buttonBox_accepted()
{
    i=ui->lineEdit->text().toInt();
    for (int i=0;(int)i<ui->tableWidget->columnCount();i++)
    {
        re_list.push_back(ui->tableWidget->item(0,i)->text().toInt());
    }
}

vector<int> InputRequest::getRequestList()
{
    return re_list;
}

int InputRequest::getI()
{
    return i;
}
