#ifndef FIGUREMATE_H
#define FIGUREMATE_H
/*
 * 图元类
 * 主要是有关于地雷的状态与操作
 */
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QStyleOptionGraphicsItem>

class FigureMate : public QObject,public QGraphicsPixmapItem  //继承
{
    Q_OBJECT//宏定义，可以使用信号和槽机制
public:
    FigureMate();
    void setRowAndCol(int x,int y){row=x;col=y;} //设置行和列
    void setOpened(bool s){opened=s;updateMate();}//模拟点击,打开
    void setMine(bool m){mine=m;}
    void setNumOfMines(int n){numOfMines=n;}//设置地雷个数
    void setFlag(bool m){flag=m;updateMate();}//标记
    void setOpenMine(bool s){openMine=s;}//设置打开雷，即踩雷
    bool isOpened(){return opened;}//判断是否打开过
    bool isMine(){return mine;}//判断是不是雷
    bool isFlag(){return flag;}//判断是否已被标记
    int getNumOfMines(){return numOfMines;}//得到雷数
    void simulateLeftClick();//模拟左键点击
    void updateMate();//更新显示

protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
     void openOnMine(int r,int c);//挖到了雷
     void openOnNone(int r,int c);//挖到没有雷的地方
     void doubleClickSignal(int r,int c);//左右键双击有效
     void checkSignal();//每次点击后，发送信号给myscene检查游戏是否结束
     void flagChangedSignal();//标记改变信号,用来numScene改变剩余地雷数

private:

     int row;//行
     int col;//列
     bool opened=false;//是否已经打开，默认设置为未打开
     bool mine=false;//有地雷吗？默认设置为没有
     bool flag=false;//是否被旗帜标记了，默认设置为没有被标记
     bool openMine=false;//是否打开了雷
     int numOfMines=0;//周围地雷个数
};

#endif // FIGUREMATE_H
