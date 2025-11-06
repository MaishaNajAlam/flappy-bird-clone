#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include "bird.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene=new Scene(this);
    scene->setSceneRect(-250,-300,500,600);

    QPixmap backgroundPixmap(":/images/sky.png");
    backgroundPixmap = backgroundPixmap.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(backgroundPixmap);
    scene->addItem(pixItem);
    pixItem->setPos(-scene->width() / 2, -scene->height() / 2);

    scene->addLine(-400,0,400,0,QPen(Qt::blue));
    scene->addLine(0,-400,0,400,QPen(Qt::blue));

    // PillarItem *pillar=new PillarItem();
    // scene->addItem(pillar);

    // Bird* bird=new Bird(QPixmap(":/images/bird_up.png"));
    // scene->addItem(bird);

    ui->graphicsView->setScene(scene);

    scene->addBird();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startGameButton_clicked()
{
    scene->startGame();
}

