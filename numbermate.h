#ifndef NUMBERMATE_H
#define NUMBERMATE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

/*
 * 单个数字显示
 */


class NumberMate : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    NumberMate();
    void setNumber(int a);//设置数字

signals:

public slots:
};

#endif // NUMBERMATE_H
