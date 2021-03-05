#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

    void setMaxMineLabel();//设置标签显示最大雷数

private slots:

    void on_btn_cancel_clicked();//取消按钮

    void on_btn_yes_clicked();//点击确定

    void on_spinBox_h_valueChanged(int arg1);

    void on_spinBox_w_valueChanged(const QString &arg1);


signals:
    void cancelSignal();
    void yesSignal(int w,int h,int m);



private:
    Ui::SettingWindow *ui;
    int height;
    int width;
    int mine;
};

#endif // SETTINGWINDOW_H
