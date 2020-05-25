#include "mainsence.h"
#include "ui_mainsence.h"
#include "mypushbtn.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QSound>

MainSence::MainSence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSence)
{
    ui->setupUi(this);
    setFixedSize(320,588);
    setWindowTitle("Flip COINS");
    setWindowIcon(QIcon(":/new/res/Coin0001.png"));
    MyPushbtn *btn = new MyPushbtn(":/new/res/MenuSceneStartButton.png");
    btn->setParent(this);
    btn->move(width()*0.5 - btn->width()*0.5,height()*0.7);
    scenechose = new chooseScene;

    QSound* sound = new QSound(":/new/res/TapButtonSound.wav",this);
    QSound *qs = new QSound(":/new/res/BackButtonSound.wav",this);

    connect(btn,&MyPushbtn::clicked,[=](){
            sound->play();
            btn->Zoom();
            QTimer::singleShot(500,this,[=](){
                this->hide();
                scenechose->setGeometry(this->geometry());
                scenechose->show();
            });
        }
    );
    connect(scenechose,&chooseScene::BackClicked,[=]{
        qs->play();
        this->setGeometry(scenechose->geometry());
        this->show();
        scenechose->hide();
    });
}

MainSence::~MainSence()
{
    delete ui;
}

void MainSence::on_actionquit_triggered()
{
    this->close();
}
void MainSence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pic;
    pic.load(":/new/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pic);

    pic.load(":/new/res/Title.png");
    painter.drawPixmap(20,25,pic);
}
