#ifndef WARNING_H
#define WARNING_H

#include <QDialog>

namespace Ui {
class Warning;
}

class Warning : public QDialog
{
    Q_OBJECT

public:
    explicit Warning(QWidget *parent = nullptr);
    ~Warning();

    //显示标签
    void setLabel1(QString str);
    void setLabel2(QString str);
    void setLabel3(QString str);

private:
    Ui::Warning *ui;
};

#endif // WARNING_H
