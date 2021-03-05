#include "lookmate.h"

LookMate::LookMate()
{
    setLook();

}

void LookMate::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setLook();
    emit restart();
}

//设置表情
void LookMate::setLook(int type){

    if(type==0)//开心
        this->setPixmap(QPixmap(":/look/pic/happy.png"));
    else if(type==1)//不开心
        this->setPixmap(QPixmap(":/look/pic/unhappy.png"));
    else if(type==2)//胜利
        this->setPixmap(QPixmap(":/look/pic/victory.png"));
}
