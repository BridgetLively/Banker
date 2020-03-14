#include "inputmat.h"
#include "ui_inputmat.h"

InputMat::InputMat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputMat)
{
    ui->setupUi(this);

    ui->buttonBox->setVisible(false);
    ui->label->setText("请输入max矩阵：");
    ui->stackedWidget->setCurrentIndex(0);
}

InputMat::~InputMat()
{
    delete ui;
}

void InputMat::on_next_clicked()
{
    switch (ui->stackedWidget->currentIndex())
    {
    case 0:
        ui->buttonBox->setVisible(false);
        ui->stackedWidget->setCurrentIndex(1);
        ui->label->setText("请输入allocation矩阵：");
        break;
    case 1:
        ui->buttonBox->setVisible(true);
        ui->stackedWidget->setCurrentIndex(2);
        ui->label->setText("请输入available数组：");
        break;
    }
}

void InputMat::on_pre_clicked()
{
    switch (ui->stackedWidget->currentIndex())
    {
    case 1:
        ui->buttonBox->setVisible(false);
        ui->stackedWidget->setCurrentIndex(0);
        ui->label->setText("请输入max矩阵：");
        break;
    case 2:
        ui->buttonBox->setVisible(false);
        ui->stackedWidget->setCurrentIndex(1);
        ui->label->setText("请输入allocation矩阵：");
        break;
    }
}

void InputMat::setNM(int n,int m)
{
    ui->input_max->setRowCount(n);
    ui->input_max->setColumnCount(m);
    ui->input_allocation->setRowCount(n);
    ui->input_allocation->setColumnCount(m);
    ui->input_available->setRowCount(1);
    ui->input_available->setColumnCount(m);
    for(int i=0;i<m;i++)
    {
        ui->input_max->setColumnWidth(i,20);
        ui->input_allocation->setColumnWidth(i,20);
        ui->input_available->setColumnWidth(i,20);
    }
    ui->input_available->setRowHeight(0,20);
    for(int i=0;i<n;i++)
    {
        ui->input_max->setRowHeight(i,20);
        ui->input_allocation->setRowHeight(i,20);
    }
}

void InputMat::on_buttonBox_accepted()
{
    for (unsigned long long i=0;(int)i<ui->input_max->rowCount();i++)
    {
        vector<int>tmp;
        vector<int>tmp1;
        for (unsigned long long j=0;(int)j<ui->input_max->columnCount();j++)
        {
            tmp.push_back(ui->input_max->item((int)i,(int)j)->text().toInt());
            tmp1.push_back(ui->input_allocation->item((int)i,(int)j)->text().toInt());
        }
        v_max.push_back(tmp);
        v_alloc.push_back(tmp1);
    }
    for (unsigned long long j=0;(int)j<ui->input_max->columnCount();j++)
    {
        v_avai.push_back(ui->input_available->item(0,(int)j)->text().toInt());
    }
}

vector<vector<int>> InputMat::getMax()
{
    return v_max;
}
vector<vector<int>> InputMat::getAlloc()
{
    return v_alloc;
}
vector<int> InputMat::getAvai()
{
    return v_avai;
}
