#ifndef INPUTREQUEST_H
#define INPUTREQUEST_H

#include <QDialog>
#include <vector>
using namespace std;

namespace Ui {
class InputRequest;
}

class InputRequest : public QDialog
{
    Q_OBJECT

public:
    explicit InputRequest(QWidget *parent = nullptr);
    ~InputRequest();

    void setM(int m);//设置资源类数m

    int i;//进程数
    int getI();

    vector<int>re_list;//request数组
    vector<int>getRequestList();//外界获取request数组的接口

private slots:
    void on_buttonBox_accepted();//按钮ok的响应事件

private:
    Ui::InputRequest *ui;
};

#endif // INPUTREQUEST_H
