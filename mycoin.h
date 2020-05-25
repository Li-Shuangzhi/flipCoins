#ifndef MYCOIN_H
#define MYCOIN_H
#include <QTimer>
#include <QPushButton>

class myCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit myCoin(QWidget *parent = nullptr);
    myCoin(QString coinImag);
    int posX;
    int posY;
    bool flag;
    void changeFlag();
    QTimer* timer1;
    QTimer* timer2;
    int max = 8;
    int min = 1;
    bool ifINanimation;
signals:

public slots:

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MYCOIN_H
