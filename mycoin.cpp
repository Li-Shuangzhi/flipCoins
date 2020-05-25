#include "mycoin.h"
#include <QPixmap>
#include <QDebug>

myCoin::myCoin(QString coinImag)
{
    QPixmap pix;
    pix.load(coinImag);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet( "QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    ifINanimation = false;

    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/new/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet( "QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min > this->max){
            timer1->stop();
            this->ifINanimation = false;
            this->min = 1;
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/new/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet( "QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max < this->min){
            timer2->stop();
            this->ifINanimation = false;
            this->max = 8;
        }
    });


}
void myCoin::changeFlag()
{
    if(flag){
        qDebug() << "At Coins change";
        ifINanimation = true;
        timer1->start(30);
        flag = false;
    }
    else {
        qDebug() << "At Coins change";
        ifINanimation = true;
        timer2->start(30);
        flag = true;
    }
}
void myCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->ifINanimation)
    {
        return ;
    }
    else {
        return QPushButton::mousePressEvent(e);
    }
}
