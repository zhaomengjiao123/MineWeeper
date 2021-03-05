#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsItem>
#include <QTimer>
#include <sceneclass.h>
#include "settingwindow.h"
#include "lookmate.h"
#include "numberscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actionPrimary_triggered();
    void on_actionNew_triggered();
    void on_actionMid_triggered();
    void on_actionSenior_triggered();
    void on_actionExit_triggered();
    void on_actionCustom_triggered();
    void customSet(int w,int h,int m);//自定义
    void on_actionAbout_triggered();
signals:
    void gameOverSignal(int looktype);//失败信号


public slots:
    void initializeGame(){sceneC->initialize();}
    void startTimer(){restTime=999;timer->start(100);updateTimeScene();}
    void updateTimeScene();//更新剩余时间
    void updateMineScene();


private:
    Ui::MainWindow *ui;
    SettingWindow *settingW;
    SceneClass *sceneC;
    QGraphicsScene *lookScene;//表情
    NumberScene *timeScene;//剩余时间(从999秒倒计时)
    NumberScene *mineScene;//剩余地雷数(全部地雷数-已标记数)
    QTimer *timer;//计时器
    int restTime=99;//剩余秒数
};
#endif // MAINWINDOW_H
