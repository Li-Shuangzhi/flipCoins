#ifndef MYPUSHBTN_H
#define MYPUSHBTN_H

#include <QPushButton>

class MyPushbtn : public QPushButton
{
    Q_OBJECT
public:
    MyPushbtn(QString normalImag ,QString pressImag = "" );
    void Zoom();

signals:

public slots:
private:
    QString normalImagPath;
    QString pressImagPath;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MYPUSHBTN_H
