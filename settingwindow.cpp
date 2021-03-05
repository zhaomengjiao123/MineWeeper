#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
}

SettingWindow::~SettingWindow()
{
    delete ui;
}


//点击取消
void SettingWindow::on_btn_cancel_clicked()
{
    this->hide();
    emit cancelSignal();
}

//点击确定
void SettingWindow::on_btn_yes_clicked()
{
    this->hide();
    qDebug()<<"更改后的宽高为："<<ui->spinBox_w->value()<<","<<ui->spinBox_h->value()<<","<<ui->spinBox_m->value();
    emit yesSignal(ui->spinBox_w->value(),ui->spinBox_h->value(),ui->spinBox_m->value());
}

void SettingWindow::on_spinBox_h_valueChanged(int arg1)
{
    setMaxMineLabel();
}

void SettingWindow::on_spinBox_w_valueChanged(const QString &arg1)
{
    setMaxMineLabel();
}

void SettingWindow::setMaxMineLabel(){
    QString str="雷数(10~";
    str+=QString::number(ui->spinBox_w->value()*ui->spinBox_h->value()-1);
    str+=")(个):";
    this->ui->label_m->setText(str);
    this->ui->spinBox_m->setMaximum(ui->spinBox_w->value()*ui->spinBox_h->value()-1);
}
