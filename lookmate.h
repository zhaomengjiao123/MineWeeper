#ifndef LOOKMATE_H
#define LOOKMATE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

/*
 * Qt图形视图框架图片图元QGraphicsPixmapItem
 * 本类主要用来设置中间的表情：代表了游戏状态：0：游戏中；1：输了；2：赢了
 */
class LookMate : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    LookMate();
    void setLook(int type=0);//设置玩游戏时的小表情type=0:happy,type=1:unhappy,type=2:victory  
    
protected:
    
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    
    
signals:
    void restart();

public slots:
};


#endif // LOOKMATE_H
