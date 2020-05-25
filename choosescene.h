#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QMainWindow>
#include "playscene.h"

class chooseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseScene(QWidget *parent = nullptr);

signals:
    void BackClicked();
public slots:
protected:
    void paintEvent(QPaintEvent *event);
private:
    playScene*_playScene;
};

#endif // CHOOSESCENE_H
