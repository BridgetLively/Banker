#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <inputmat.h>
#include <inputnm.h>
#include <inputrequest.h>
#include <warning.h>
#include<error.h>
#include <banker.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    InputNM *input_nm;//输入n,m的类的对象
    InputRequest *input_re;//输入request数组的类的对象
    Banker *banker;//用于进行银行家算法的类的对象
    Warning *warn;//警告信息的类对象

    vector<vector<int>>v_max;//各进程所需资源数最大值
    vector<vector<int>>v_allocation;//系统当前已分配资源数
    vector<int>v_available;//系统当前可用资源数

    bool isLegal();//检测inputmat输入的数据合法性

    void appendTableRow();
    void dispNeed();
    void dispAvai();

private slots:
    void on_actionstart_triggered();

    void on_actionrequest_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
