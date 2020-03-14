#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionrequest->setDisabled(true);
    banker=new Banker;

}

MainWindow::~MainWindow()
{
    delete ui;
}

//开始菜单触发事件
void MainWindow::on_actionstart_triggered()
{
    //输入n,m
    input_nm=new InputNM;
    input_nm->exec();

    v_max=input_nm->input_mat->getMax();
    v_allocation=input_nm->input_mat->getAlloc();
    v_available=input_nm->input_mat->getAvai();

    //检测inputmat输入数据合法性
    if(isLegal())
    {
        //初始化Banker所需要用的数组
        banker->n=input_nm->n.toInt();
        banker->m=input_nm->m.toInt();
        banker->max=v_max;
        banker->allocation=v_allocation;
        banker->available=v_available;
        banker->calculateNeed();



        //设置安全时刻表的列数
        ui->tableWidget->setColumnCount(input_nm->n.toInt()+1);
        ui->tableWidget->setColumnWidth(0,20);

        //设置need表格的行列数
        ui->tableWidget_2->setRowCount(input_nm->n.toInt());
        ui->tableWidget_2->setColumnCount(input_nm->m.toInt()+1);
        ui->tableWidget_2->setColumnWidth(0,20);

        //设置available的列数
        ui->tableWidget_3->setColumnCount(input_nm->m.toInt());

        //展示need，available在T0时刻的数据
        if(banker->securityTest())
        {

            ui->actionrequest->setDisabled(false);
            dispNeed();
            dispAvai();
            appendTableRow();
        }else
        {
            warn=new Warning;
            warn->setLabel1("分配资源出现错误！！！");
            warn->setLabel2("初始资源分配不合理，系统处于不安全状态！！！");
            warn->setLabel3("请结束进程并重新开始分配资源！！！");

            warn->exec();
        }

    }else
    {
        warn=new Warning;
        warn->setLabel1("资源初始化错误！！！");
        warn->setLabel2("初始资源输入不合法，程序无法运行下去！！！");
        warn->setLabel3("请结束进程并重新开始分配资源！！！");

        warn->exec();
    }


    ui->actionstart->setDisabled(true);
}

//请求资源菜单触发事件
void MainWindow::on_actionrequest_triggered()
{

    input_re=new InputRequest;
    input_re->setM(input_nm->m.toInt());
    input_re->exec();

    //初始化Banker所需用的数据
    banker->requestList=input_re->getRequestList();

    //请求资源成功，在主页面展示T(X)时刻available和need数据
    if(banker->request(input_re->getI()))
    {
        dispAvai();
        dispNeed();
        appendTableRow();
    }
    else //请求失败，生成警告信息
    {
        warn=new Warning;
        if(!(banker->compareRN(input_re->getI())))//请求资源大于所需资源
        {
            warn->setLabel1("进程P"+QString::number(input_re->getI())+"请求资源出现错误！！！");
            warn->setLabel2("为进程P"+QString::number(input_re->getI())+"所请求资源数大于它所需要的资源数");
        }
        else
        {
            warn->setLabel1("P"+QString::number(input_re->getI())+"请求资源失败！！！");
            if(!banker->compareRA())//系统可用资源小于请求资源
            {
                warn->setLabel2("当前可分配资源不足，无法为P"+QString::number(input_re->getI())+"分配足够资源");
                warn->setLabel3("请等其他进程结束后再为P"+QString::number(input_re->getI())+"分配资源");
            }
            else
            {
                warn->setLabel2("分配后系统处于不安全状态，故无法为P"+QString::number(input_re->getI())+"分配资源");
            }
        }

        warn->exec();
    }

}


//添加安全序列
void MainWindow::appendTableRow()
{

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("T"+QString::number(ui->tableWidget->rowCount()-1)));
    for (int i=1;i<ui->tableWidget->columnCount();i++)
    {
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,i,new QTableWidgetItem(QString::number(banker->securityList[i-1])));
    }
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

//展示need矩阵
void MainWindow::dispNeed()
{
    ui->label_2->setText("T("+QString::number(ui->tableWidget->rowCount()-1)+")时刻各进程所需资源数：");
    QFont ft;
    ft.setPointSize(14);
    ui->label_2->setFont(ft);
    for (int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget_2->columnCount();j++)
        {
            if(j==0)
                ui->tableWidget_2->setItem((int)i,0,new QTableWidgetItem("P"+QString::number(i)));
            else
                ui->tableWidget_2->setItem(i,j,new QTableWidgetItem(QString::number(banker->need[i][j-1])));


        }
    }

}

//真是available数组
void MainWindow::dispAvai()
{
    ui->label_3->setText("T("+QString::number(ui->tableWidget->rowCount()-1)+")时刻可用资源数：");
    QFont ft;
    ft.setPointSize(14);
    ui->label_3->setFont(ft);
    for(int i=0;i<ui->tableWidget_3->columnCount();i++)
    {
        ui->tableWidget_3->setItem(0,i,new QTableWidgetItem(QString::number(banker->available[i])));
    }
}

bool MainWindow::isLegal()
{
    bool legal=true;
    //检测max,allocation,available
    for (int i=0;i<input_nm->n.toInt();i++)
    {
        for (int j=0;j<input_nm->m.toInt();j++)
        {
            if(v_max[i][j]<0)
            {
                legal=false;
                break;
            }
            if(v_allocation[i][j]<0)
            {
                legal=false;
                break;
            }
            if(v_available[j]<0)
            {
                legal=false;
                break;
            }
        }
    }
    return legal;
}
