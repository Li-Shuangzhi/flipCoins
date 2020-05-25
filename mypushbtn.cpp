#include "mypushbtn.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushbtn::MyPushbtn(QString normalImag ,QString pressImag )
{
    this->normalImagPath = normalImag;
    this->pressImagPath = pressImag;
    QPixmap pix;
    bool res = pix.load(normalImagPath);
    if(!res)
    {
        qDebug()<<"the picture load error" + normalImag;
        return;
    }
    //不规则形状按钮
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton {border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void MyPushbtn::Zoom()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()) );
    animation->setKeyValueAt(0.5,QRect(this->x(),this->y() + 10,this->width(),this->height()) );
    //animation->setEasingCurve(QEasingCurve::OutBounce);
    //animation->start();
    //animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()) );
    animation->setEndValue(QRect(this->x(),this->y(),this->width() - 10,this->height()) );
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushbtn::mousePressEvent(QMouseEvent *event)
{
    QPixmap pix;
    if(this->pressImagPath != ""){
        pix.load(this->pressImagPath);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton {border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

    }
    QPushButton::mousePressEvent(event);
}
void MyPushbtn::mouseReleaseEvent(QMouseEvent *event)
{
    QPixmap pix;
    if(this->pressImagPath != "")
    {
        pix.load(this->normalImagPath);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton {border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

    }
    QPushButton::mouseReleaseEvent(event);
}






