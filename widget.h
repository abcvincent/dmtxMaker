#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    QImage globalImg;//存储图片用
    QString globastr;//保存str信息

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
