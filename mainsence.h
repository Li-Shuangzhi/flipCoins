#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include "choosescene.h"

namespace Ui {
class MainSence;
}

class MainSence : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainSence(QWidget *parent = nullptr);
    ~MainSence();

private slots:
    void on_actionquit_triggered();

private:
    Ui::MainSence *ui;

    chooseScene* scenechose;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MAINSENCE_H
