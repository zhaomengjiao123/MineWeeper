#ifndef SCENECLASS_H
#define SCENECLASS_H

#include <QObject>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QMessageBox>
#include <figuremate.h>

/*
 * 游戏场景中操作
 */
class SceneClass : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneClass(QObject *parent = nullptr);
    
    void setMap(int w,int h,int m){width=w;height=h;mine=m;}//设置地图大小和地雷数
    
    void initialize();//游戏初始化
    
    int getRestMines();//得到剩余的地雷数

signals:
       void victorySignal(int looktype);//胜利信号
       void gameOverSignal(int looktype);//失败信号
       void reinitializeSignal(int looktype);//重新开始
       void flagChangedSignal();//标记改变

public slots:
       
       void gameOver(int row,int col);//游戏结束
       void findNoMines(int row,int col);//递归寻找无雷区
       void doubleClick(int row,int col);//某处双击
       void checkGame();//检查游戏是否结束
       void flagChange(){

           qDebug()<<" 标记信号！";
           emit flagChangedSignal();}//标记改变,改变剩余地雷数
       
    
private:
    

    static const int MAX_HEIGHT=24;
    static const int MAX_WIDTH=30;


    FigureMate *mates[MAX_WIDTH][MAX_HEIGHT];//figureMate类对象指针的二维数组。

    int mine=10;//地雷数
    int height=10;//地图宽高
    int width=10;//初级10*10  10个雷
};

#endif // SCENECLASS_H
