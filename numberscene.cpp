#include "numberscene.h"

NumberScene::NumberScene(QObject *parent) : QGraphicsScene(parent)
{

}


void NumberScene::setNumber(int num){

    if(num>=0){
        this->clear();

        int hundred,ten,one;//得到百位,十位,个位
        hundred=num/100;
        ten=(num%100)/10;
        one=num%10;

        NumberMate *hunItem,*tenItem,*oneItem;
        hunItem=new NumberMate;
        tenItem=new NumberMate;
        oneItem=new NumberMate;

        hunItem->setPos(1,0);
        tenItem->setPos(20,0);
        oneItem->setPos(39,0);

        hunItem->setNumber(hundred);
        tenItem->setNumber(ten);
        oneItem->setNumber(one);

        this->addItem(hunItem);
        this->addItem(tenItem);
        this->addItem(oneItem);
    }
}
