#include "sceneclass.h"
/*场景类
 *
 *场景初始化
 *
 * 每次初始化时，调用this->clear()之后需要重新给items指针数组分配空间，因为clear()会自动delete掉原来的空间！！！！！
*/

SceneClass::SceneClass(QObject *parent) : QGraphicsScene(parent)
{
    this->initialize();

}

//初始化实现
void SceneClass::initialize(){
    this->clear();

    //状态初始化
    for(int i=0;i<MAX_WIDTH;++i){
        for(int j=0;j<MAX_HEIGHT;++j){

            this->mates[i][j] = new FigureMate();//每一个数组指针都new一个对象
            this->mates[i][j]->setPos(i*20,j*20);//setPos的坐标是父类坐标系的坐标，一般对于item位于scene中的应用场景。
            this->mates[i][j]->setPos(i*20,j*20);
            this->mates[i][j]->setRowAndCol(i,j);//为图元设置行和列


            //信号


            connect(this->mates[i][j],&FigureMate::openOnMine,this,&SceneClass::gameOver);//打开雷信号
            connect(this->mates[i][j],&FigureMate::openOnNone,this,&SceneClass::findNoMines);//打开空，发送寻找空区信号
            connect(this->mates[i][j],&FigureMate::doubleClickSignal,this,&SceneClass::doubleClick);
            connect(this->mates[i][j],&FigureMate::checkSignal,this,&SceneClass::checkGame);//检查游戏是否结束
            connect(this->mates[i][j],&FigureMate::flagChangedSignal,this,&SceneClass::flagChange);//标记改变


            this->mates[i][j]->setMine(false);//无雷
            this->mates[i][j]->setOpened(false);//未被打开
            this->mates[i][j]->setNumOfMines(0);//初始设置地雷数为0
            this->mates[i][j]->setFlag(false);//未被标记
            this->mates[i][j]->setOpenMine(false);//格子未被打开


        }

    }


   //显示大小
    for(int i=0;i<width;++i){

            for(int j=0;j<height;++j){
                this->addItem(this->mates[i][j]);
            }
        }


    int mineNumber=0;
    while(mineNumber<this->mine){//设置地雷位置
            int x=QRandomGenerator::global()->bounded(width);
            int y=QRandomGenerator::global()->bounded(height);

            //如果生成的地址已经有地雷了，则改变这个图元对象的状态，避免重复布雷！！！
            if(!this->mates[x][y]->isMine()){
                this->mates[x][y]->setMine(true);
                mineNumber++;
            }
        }

    int nx,ny,numOfMines;//周围的八个点  坐标
    int dx[8]={-1,-1,-1,0,0,1,1,1};
    int dy[8]={-1,0,1,-1,1,-1,0,1};
    //设置周围砖块数
    for(int i=0;i<width;++i){
        for(int j=0;j<height;++j){
            numOfMines = 0;

            for(int k=0;k<8;++k){//遍历它周围的八个格子
                nx=i+dx[k];
                ny=j+dy[k];
            if(0<=nx&&nx<width&&0<=ny&&ny<height){//判断是在第一象限，在范围内，防止四周的格子判断失误
                if(this->mates[nx][ny]->isMine()){
                    //这八个格子中如果有雷
                    numOfMines++;
                    }
            }
            }
            this->mates[i][j]->setNumOfMines(numOfMines);//设置雷数

        }
    }

    for(int i=0;i<width;++i)
            for(int j=0;j<height;++j)
                mates[i][j]->updateMate();

        emit reinitializeSignal(0);

}

void SceneClass::gameOver(int row,int col){

    qDebug()<<"游戏结束！";
    emit gameOverSignal(1);

    for(int i=0;i<width;++i){//显示其余的地雷
        for(int j=0;j<height;++j){
            if(mates[i][j]->isMine()&&!(i==row&&j==col)){
                mates[i][j]->setOpened(true);//全部打开
                mates[i][j]->updateMate();
            }
        }
    }


       QMessageBox msg;
       msg.setIcon(QMessageBox::Critical);
       msg.setText("很遗憾，您输掉了游戏：（");
       msg.setStandardButtons(QMessageBox::Yes);
       msg.exec();

       qDebug()<<"重新初始化";

       initialize();
   }


//无雷时，自动打开实现
void SceneClass::findNoMines(int row,int col){

    mates[row][col]->setOpened(true);//模拟点击

    if(mates[row][col]->getNumOfMines()!=0)
        return;//有数字的方块就不展开了

    int nx,ny;
    int dx[8]={-1,-1,-1,0,0,1,1,1};
    int dy[8]={-1,0,1,-1,1,-1,0,1};
    for(int i=0;i<8;++i){
        nx=row+dx[i];
        ny=col+dy[i];
        if(0<=nx&&nx<width&&0<=ny&&ny<height&&!mates[nx][ny]->isOpened()){
            findNoMines(nx,ny);
        }
    }
}

//双击事件
void SceneClass::doubleClick(int row,int col){
    int flags=0,mines=0;
    int nx,ny;
    int dx[8]={-1,-1,-1,0,0,1,1,1};
    int dy[8]={-1,0,1,-1,1,-1,0,1};
    for(int i=0;i<8;++i){
        nx=row+dx[i];
        ny=col+dy[i];
        if(0<=nx&&nx<width&&0<=ny&&ny<height&&!mates[nx][ny]->isOpened()){
            if(mates[nx][ny]->isMine())
                mines++;
            if(mates[nx][ny]->isFlag())
                flags++;

        }
    }
    if(flags==mines){
        for(int i=0;i<8;++i){
            nx=row+dx[i];
            ny=col+dy[i];
            if(0<=nx&&nx<width&&0<=ny&&ny<height&&!mates[nx][ny]->isOpened()&&!mates[nx][ny]->isFlag()){
                  mates[nx][ny]->simulateLeftClick();
            }
        }
    }
}

//检查游戏是否结束
void SceneClass::checkGame(){
    int block=0;
    for(int i=0;i<width;++i){
        for(int j=0;j<height;++j){
            if(mates[i][j]->isOpened()&&!mates[i][j]->isMine()){//打开了并且不是雷
                block++;
            }
        }
    }

    if(block==(height*width-mine)){//所有的格子数-雷数=被打开的格子数  胜利！！
        emit victorySignal(2);

        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setText("恭喜你赢了！！");
        msg.setStandardButtons(QMessageBox::Yes);
        msg.exec();

        initialize();
    }
}

//得到剩余雷数
int SceneClass::getRestMines(){//总的雷数-已经被标记的雷数=剩下的雷数

    int flags=0;//标记数设为0

    for(int i=0;i<width;++i){
        for(int j=0;j<height;++j){
            if(!mates[i][j]->isOpened()&&mates[i][j]->isFlag())//没有打开并且被标记标记
                flags++;
        }
    }
    return mine-flags;
}
