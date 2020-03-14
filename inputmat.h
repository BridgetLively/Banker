#ifndef INPUTMAT_H
#define INPUTMAT_H

#include <vector>
using namespace std;

#include <QDialog>
namespace Ui {
class InputMat;
}

class InputMat : public QDialog
{
    Q_OBJECT

public:
    explicit InputMat(QWidget *parent = nullptr);
    ~InputMat();

    void setNM(int n,int m);//将n,m的值传入类InputMat
    vector<vector<int>>v_max;//max矩阵
    vector<vector<int>>getMax();//外界获取max矩阵的接口

    vector<vector<int>>v_alloc;//allocation矩阵
    vector<vector<int>>getAlloc();//外界获取allocation矩阵的接口

    vector<int>v_avai;//available矩阵
    vector<int>getAvai();//外界获取available数组的接口

private slots:
    void on_next_clicked();//点击按钮next对应的事件

    void on_pre_clicked();//点击按钮pre对应的事件

    void on_buttonBox_accepted();//点击按钮ok对应的事件

private:
    Ui::InputMat *ui;
};

#endif // INPUTMAT_H
