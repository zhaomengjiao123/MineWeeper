#include "figuremate.h"

FigureMate::FigureMate()
{

        this->setFlag(QGraphicsItem::ItemIsSelectable);
        this->setAcceptedMouseButtons(Qt::AllButtons);

        updateMate();
}
void FigureMate::simulateLeftClick(){

    if(!opened&&!flag){//如果没有被标记并且打开了格子
        setOpened(true);//将这个格子设置为已打开
        if(mine){//如果有雷
            openMine=true;//设置为打开了雷
            updateMate();
            emit openOnMine(row,col);//发送打开了雷信号
        }
        else if(numOfMines==0)//如果打开的为空，发送信号
            emit openOnNone(row,col);
    }

}

void FigureMate::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug()<<"检测到按下！"<<row<<","<<col;
    qDebug()<<event->button();
    qDebug()<<event->buttons();

    if(event->buttons()==(Qt::LeftButton|Qt::RightButton)){
        qDebug()<<"左右键同时按下";
        if((opened&&numOfMines!=0)||(!opened&&flag)){//已经打开了，并且是有数字的，或者是没有被打开但是有旗帜标记的
            emit doubleClickSignal(row,col);
        }

    }else if(event->button()==Qt::LeftButton){//左击
        qDebug()<<"左键按下";
        simulateLeftClick();
    }else if(event->button()==Qt::RightButton){//右击
        qDebug()<<"右键按下";
        if(!opened){//如果右击时格子没有被打开，则标记为旗帜，并发送标记改变信号以此来改变显示的剩余地雷数
            setFlag(!flag);

            qDebug()<<"标记改变！";
            emit flagChangedSignal();

        }
    }
    emit checkSignal();//发送信号给scene检查游戏是否结束
}

void FigureMate::updateMate(){//更新
    if(openMine)
        this->setPixmap(QPixmap(":/mine/pic/mine_step.jpg"));
    else if(!opened){//未被打开
        if(!flag)
            this->setPixmap(QPixmap(":/mine/pic/notSweep.jpg"));//加密状态
        else
            this->setPixmap(QPixmap(":/mine/pic/flag.jpg"));//被标记
    }
    else if(mine){//有雷
        this->setPixmap(QPixmap(":/mine/pic/mine.jpg"));
    }else{

         if(numOfMines==0)
             this->setPixmap(QPixmap(":/mine/pic/mine0.jpg"));
         else if(numOfMines==1)
             this->setPixmap(QPixmap(":/mine/pic/mine1.jpg"));
         else if(numOfMines==2)
             this->setPixmap(QPixmap(":/mine/pic/mine2.jpg"));
         else if(numOfMines==3)
             this->setPixmap(QPixmap(":/mine/pic/mine3.jpg"));
         else if(numOfMines==4)
             this->setPixmap(QPixmap(":/mine/pic/mine4.jpg"));
         else if(numOfMines==5)
             this->setPixmap(QPixmap(":/mine/pic/mine5.jpg"));
         else if(numOfMines==6)
             this->setPixmap(QPixmap(":/mine/pic/mine6.jpg"));
         else if(numOfMines==7)
             this->setPixmap(QPixmap(":/mine/pic/mine7.jpg"));
         else if(numOfMines==8)
             this->setPixmap(QPixmap(":/mine/pic/mine8.jpg"));
    }
}


void FigureMate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)

/*painter : 此参数用于绘图;
option : 提供了item的风格，比如item的状态，曝光度以及详细的信息；
widget : 想画到哪个widget上，如果要画在缓存区上，这个参数一般填0；
*/

{
    QStyleOptionGraphicsItem op;
    op.initFrom(widget);
    op.state = QStyle::State_None;

    return QGraphicsPixmapItem::paint(painter, &op, widget);
}
