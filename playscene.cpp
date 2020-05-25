#include "playscene.h"
#include <QDebug>
#include <QPainter>
#include <QMenuBar>
#include "mypushbtn.h"
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include "dataconfig.h"
#include <QSound>

playScene::playScene(int index)
{
    isWin = false;
    QSound *qs = new QSound(":/new/res/BackButtonSound.wav",this);
    QSound* co = new QSound(":/new/res/ConFlipSound.wav",this);
    QSound* su = new QSound(":/new/res/LevelWinSound.wav",this);
    su->setLoops(-1);
    levelIndex = index;
    qDebug()<<index;
    setFixedSize(320,588);
    setWindowTitle("gaming");
    setWindowIcon(QIcon(":/new/res/Coin0001.png"));

    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);
    QMenu* menu = bar->addMenu("开始");
    QAction* action = menu->addAction("退出");

    QLabel* winLabel = new QLabel(this);
    QPixmap pix;
    pix.load(":/new/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,pix.width(),pix.height() );
    winLabel->setPixmap(pix);
    winLabel->move((this->width() - pix.width())*0.5,-pix.height() );

    MyPushbtn*backBtn = new MyPushbtn(":/new/res/BackButton.png",":/new/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    QString str = QString("Level %1").arg(levelIndex);
    QLabel*label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("楷体");
    font.setPointSize(20);
    font.setBold(true);
    label->setFont(font);
    label->setGeometry(20,this->height() -50,120,50);
    label->setText(str);

    dataConfig data;
    for (int i = 0;i < 4; i ++) {
        for(int j = 0;j < 4;j ++){
            array[i][j] = data.mData[this->levelIndex][i][j];
        }
    }

    for(int i = 0;i < 4; i++){
        for(int j = 0;j < 4; j++){
            QLabel *bg = new QLabel(this);
            QPixmap pix;
            pix.load(":/new/res/BoardNode.png");
            bg->setFixedSize(pix.width(),pix.height());
            bg->setPixmap(pix);
            bg->move(57 + i * 50,200 + j*50);
            QString str;
            if(array[i][j] == 1){
                str =":/new/res/Coin0001.png";
            }
            else {
                str = ":/new/res/Coin0008.png";
            }
            myCoin *coin = new myCoin(str);
            coin->setParent(this);
            coin->move(59 + i * 50,204 + j*50);

            coin->posX = i;
            coin->posY = j;
            coin->flag = array[i][j];



            connect(coin,&MyPushbtn::clicked,[=](){
                co->play();
                for(int i = 0;i < 4; i++){
                    for(int j = 0;j < 4;j ++){
                        this->coinbtns[i][j]->ifINanimation = true;
                    }
                }

                if(!this->isWin){

                    coin->changeFlag();
                    array[i][j] = !array[i][j];

                    QTimer::singleShot(200,this,[=](){

                        if(coin->posX + 1 <= 3)
                        {
                            coinbtns[coin->posX + 1][coin->posY]->changeFlag();
                            array[coin->posX + 1][coin->posY] = !array[coin->posX + 1][coin->posY];

                        }
                        if(coin->posX + 1 >= 2)
                        {
                            coinbtns[coin->posX - 1][coin->posY]->changeFlag();
                            array[coin->posX - 1][coin->posY] = !array[coin->posX - 1][coin->posY];

                        }
                        if(coin->posY + 1 <= 3)
                        {
                            coinbtns[coin->posX][coin->posY + 1]->changeFlag();
                            array[coin->posX][coin->posY + 1] = !array[coin->posX][coin->posY + 1];
                        }
                        if(coin->posY + 1 >= 2)
                        {
                            coinbtns[coin->posX][coin->posY - 1]->changeFlag();
                            array[coin->posX][coin->posY - 1] = !array[coin->posX][coin->posY - 1] ;
                        }
                        isWin = true;
                        for(int i = 0;i < 4;i ++){
                            for (int j = 0; j < 4; j++) {
                                if(coinbtns[i][j]->flag == false){
                                    isWin = false;
                                    break;
                                }
                            }
                        }
                        if(isWin){
                            su->play();
                            QPropertyAnimation* animation = new QPropertyAnimation(winLabel,"geometry");
                            animation->setDuration(1000);
                            animation->setStartValue(winLabel->rect());
                            animation->setEndValue(QRect(winLabel->x(),winLabel->y()+ 114,winLabel->width(),winLabel->height()));
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            animation->start();
                        }
                    });
                }
                for(int i = 0;i < 4; i++){
                    for(int j = 0;j < 4;j ++){
                        this->coinbtns[i][j]->ifINanimation = false;
                    }
                }

            });
            coinbtns[i][j] = coin;

        }
    }

    connect(action,&QAction::triggered,[=](){
        this->close();
    });
    connect(backBtn,&MyPushbtn::clicked,[=](){
        qs->play();
        QTimer::singleShot(500,[=](){
            emit this->BackClick();
        });
    });

}
void playScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/new/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(25,40,pix);
}
