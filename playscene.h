#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
class playScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playScene(QWidget *parent = nullptr);
    playScene(int index);
signals:
    void BackClick();
public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
private:
    int levelIndex;
    int array[4][4];
    myCoin* coinbtns[4][4];
    bool isWin;
};

#endif // PLAYSCENE_H
