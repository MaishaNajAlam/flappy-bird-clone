#include "bird.h"
#include<QTimer>
#include<QPoint>
#include<QGraphicsScene>
Bird::Bird(QPixmap pixmap):
    wingpos(wingPosition::Up),wingDirection(0)
{
    QPixmap scaledPixmap = pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);
    QTimer* birdWingsTimer=new QTimer(this);
    connect(birdWingsTimer,&QTimer::timeout,[=](){
        updatePixmap();
    });

    birdWingsTimer->start(80);

    groundpos=scenePos().y()+290;

    yAnimation=new QPropertyAnimation(this,"y",this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundpos);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

    connect(yAnimation,&QPropertyAnimation::finished,[=](){
        fallToGroundIfNecesssary();
    });

    //yAnimation->start();

    rotationAnimation=new QPropertyAnimation(this,"rotation",this);
    //rotateTo(90,1200,QEasingCurve::InQuad);

}

// void Bird::updatePixmap(){
//     if(wingpos==wingPosition::Middle){
//         if(wingDirection){
//             //UP
//             setPixmap(QPixmap(":/images/bird_up.png"));
//             wingpos=wingPosition::Up;
//             wingDirection=0;
//         }
//         else{
//             setPixmap(QPixmap(":/images/bird_down.png"));
//             wingpos=wingPosition::Down;
//             wingDirection=1;
//         }
//     }
//     else {
//         setPixmap(QPixmap(":/images/bird_middle.png"));
//         wingpos=wingPosition::Middle;
//     }

// }
void Bird::updatePixmap() {
    int birdWidth = 50;
    int birdHeight = 50;

    if (wingpos == wingPosition::Middle) {
        if (wingDirection) {
            // UP
            setPixmap(QPixmap(":/images/bird_up.png").scaled(birdWidth, birdHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            wingpos = wingPosition::Up;
            wingDirection = 0;
        } else {
            setPixmap(QPixmap(":/images/bird_down.png").scaled(birdWidth, birdHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            wingpos = wingPosition::Down;
            wingDirection = 1;
        }
    } else {
        setPixmap(QPixmap(":/images/bird_middle.png").scaled(birdWidth, birdHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        wingpos = wingPosition::Middle;
    }
}


qreal Bird::y() const
{
    return m_y;
}

void Bird::setY(qreal newY)
{
    moveBy(0,newY-m_y);
    m_y = newY;
}

qreal Bird::rotation() const
{
    return m_rotation;
}

void Bird::setRotation(qreal newRotation)
{
    m_rotation = newRotation;
    QPointF c=boundingRect().center();
    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(newRotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);

}

void Bird::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();
    qreal curPosY=y();
    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height() / 8);

    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);
    yAnimation->start();

    rotateTo(-20,200,QEasingCurve::OutCubic);
}

void Bird::startFlying()
{
    yAnimation->start();
    rotateTo(90,1200,QEasingCurve::InQuad);
}

void Bird::freezeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void Bird::fallToGroundIfNecesssary()
{
    if(y()<groundpos){
        rotationAnimation->stop();
        //yAnimation->stop();
        yAnimation->setStartValue(y());
        yAnimation->setEndValue(groundpos);
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setDuration(1200);
        yAnimation->start();

        rotateTo(90,1100,QEasingCurve::InCubic);
    }
}

void Bird::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}
