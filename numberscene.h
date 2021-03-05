#ifndef NUMBERSCENE_H
#define NUMBERSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "numbermate.h"
/*
 * 数字显示场景类
 */

class NumberScene: public QGraphicsScene
{
    Q_OBJECT
public:
    explicit NumberScene(QObject *parent = nullptr);
    void setNumber(int num);//设置显示数字
};

#endif // NUMBERSCENE_H
