#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sceneclass.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->sceneC=new SceneClass;
    this->lookScene=new QGraphicsScene;
    this->mineScene=new NumberScene;
    this->timeScene=new NumberScene;
    this->timer=new QTimer;

    //设置剩余时间和剩余地雷显示
    connect(this->sceneC,&SceneClass::reinitializeSignal,this,&MainWindow::startTimer);
    connect(this->timer,&QTimer::timeout,this,&MainWindow::updateTimeScene);
    this->ui->graphicsView_time->setScene(this->timeScene);
    this->ui->graphicsView_mines->setScene(this->mineScene);
    connect(this->sceneC,&SceneClass::flagChangedSignal,this,&MainWindow::updateMineScene);
    connect(this->sceneC,&SceneClass::reinitializeSignal,this,&MainWindow::updateMineScene);



    //设置表情
    LookMate *look=new LookMate;
    this->lookScene->addItem(look);
    this->ui->graphicsView_look->setScene(this->lookScene);
    connect(look,&LookMate::restart,this,&MainWindow::initializeGame);
    connect(this->sceneC,&SceneClass::victorySignal,look,&LookMate::setLook);
    connect(this->sceneC,&SceneClass::gameOverSignal,look,&LookMate::setLook);
    connect(this,&MainWindow::gameOverSignal,look,&LookMate::setLook);//倒计时结束变哭脸
    connect(this->sceneC,&SceneClass::reinitializeSignal,look,&LookMate::setLook);


    //自定义菜单
    this->settingW=new SettingWindow;
    this->settingW->hide();

    this->ui->graphicsView->setScene(this->sceneC);
    this->ui->graphicsView->setGeometry(0,30,100,100);//从屏幕上（0，30）位置开始，显示一个100*100的界面


    //初始大小为10*10,10
    on_actionPrimary_triggered();

    connect(this->settingW,&SettingWindow::cancelSignal,this,&MainWindow::show);
    connect(this->settingW,&SettingWindow::yesSignal,this,&MainWindow::customSet);


    //去掉滚动框
    this->ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView_time->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView_time->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()//新游戏
{
    this->sceneC->initialize();
}

void MainWindow::on_actionPrimary_triggered()//初级
{
    customSet(10,10,10);
}

void MainWindow::on_actionMid_triggered()//中级
{
    customSet(15,15,30);
}

void MainWindow::on_actionSenior_triggered()//高级
{
    customSet(30,15,99);
}

void MainWindow::on_actionExit_triggered()//退出
{
    this->close();
}

void MainWindow::on_actionCustom_triggered()//自定义
{
    this->hide();
    this->settingW->show();
}

void MainWindow::customSet(int w,int h,int m){
    this->show();

    //设置表情,剩余时间,剩余地雷
    updateMineScene();

    this->ui->graphicsView_mines->setGeometry(0,0,60,30);
    this->ui->graphicsView_time->setGeometry(20*w+5-62,0,60,30);
    this->ui->graphicsView_look->setGeometry((20*w+5)/2-15,0,30,30);

    //设置地图
    this->sceneC->setMap(w,h,m);
    this->sceneC->initialize();
    this->setFixedSize(20*w+5,20*h+5+55);

    this->ui->graphicsView->setFixedSize(20*w+5,20*h+5);
}

void MainWindow::on_actionAbout_triggered()//关于
{
    QMessageBox msg;
    msg.setText("扫雷游戏规则："
                "把所有非地雷的格子揭开即胜利；踩到地雷格子就算失败。"
                "开局的时候使用鼠标左键随机点击一个方格，方格即被打开并显示出方格中的数字；方格中数字则表示其周围的8个方格隐藏了几颗雷。"
                "鼠标右键是标记雷，同时按下左键和右键完成双击。当双击位置周围已标记雷数等于该位置数字时操作有效，相当于对该数字周围未打开的方块均进行一次左键单击操作。"
                "地雷未标记完全时使用双击无效。若数字周围有标错的地雷，则游戏结束，标错的地雷上会显示一个“×”。");
    msg.exec();
}


void MainWindow::updateTimeScene(){//倒计时
    this->timeScene->setNumber(restTime);

    if(restTime==0){
        emit gameOverSignal(1);
        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setText("很遗憾！倒计时结束！您输掉了游戏！");
        msg.setStandardButtons(QMessageBox::Yes);
        msg.exec();


        this->sceneC->initialize();
    }else
        restTime--;
}

void MainWindow::updateMineScene(){
    qDebug()<<"update mine!"<<this->sceneC->getRestMines();

    this->mineScene->setNumber(this->sceneC->getRestMines());
}
