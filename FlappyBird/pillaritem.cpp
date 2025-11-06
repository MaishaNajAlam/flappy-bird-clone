#include "pillaritem.h"
#include "bird.h"
#include "scene.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsScene>

PillarItem::PillarItem(): pastBird(false)
{

    QPixmap topOriginal(":/images/bottomPipe.png");
    QPixmap bottomOriginal(":/images/topPipe.png");

    QPixmap topScaled = topOriginal.scaled(80, 500, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap bottomScaled = bottomOriginal.scaled(80, 500, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    topPillar = new QGraphicsPixmapItem(topScaled);
    bottomPillar = new QGraphicsPixmapItem(bottomScaled);

    // Set the gap between the two pipes
    int pipeGap = 150;

    topPillar->setPos(-topPillar->boundingRect().width() / 2, - (topPillar->boundingRect().height() + pipeGap/2));
    bottomPillar->setPos(-bottomPillar->boundingRect().width() / 2, pipeGap/2);

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos=QRandomGenerator::global()->bounded(150);
    int xRandomizer=QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0)+QPoint(260+xRandomizer,yPos));

    xAnimation=new QPropertyAnimation(this,"x",this);
    xAnimation->setStartValue(260 +xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);
    xAnimation->start();


    connect(xAnimation,&QPropertyAnimation::finished,[=](){
        qDebug()<<"Animation finished";
        scene()->removeItem(this);
        delete this;
    });

}

PillarItem::~PillarItem()
{
    qDebug()<<"Deleting pillars";
    delete topPillar;
    delete bottomPillar;
}

qreal PillarItem::x() const{
    return m_x;
}

void PillarItem::freezeInPlace()
{
    xAnimation->stop();
}

void PillarItem::setX(qreal x){
    //qDebug()<<"Pillar position:"<<x;
    m_x=x;

    if(x<0 && !pastBird){
        pastBird=true;
        QGraphicsScene* mScene=scene();
        Scene* myScene=dynamic_cast<Scene*>(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }
    if(collisionWithBird()){
        emit collideFail();
    }
    setPos(QPointF(0,0)+QPointF(x,yPos));
}

bool PillarItem::collisionWithBird()
{
    QList<QGraphicsItem*> collidingItems=topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());
    foreach (QGraphicsItem* item, collidingItems) {
        Bird* bird=dynamic_cast<Bird*>(item);
        if(bird){
            return true;
        }
    }
    return false;
}
