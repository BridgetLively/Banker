#ifndef INPUTNM_H
#define INPUTNM_H

#include <QDialog>
#include <inputmat.h>

namespace Ui {
class InputNM;
}

class InputNM : public QDialog
{
    Q_OBJECT

public:
    explicit InputNM(QWidget *parent = nullptr);
    ~InputNM();
    InputMat *input_mat;//声明类InputMat的对象
    QString m,n;//输入框输入的值m,n

private slots:
    void on_buttonBox_accepted();//按钮ok的响应事件


private:
    Ui::InputNM *ui;
};

#endif // INPUTNM_H
