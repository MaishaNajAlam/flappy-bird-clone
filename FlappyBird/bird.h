#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>

class Bird : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Bird(QPixmap pixmap);

    qreal y() const;
    void setY(qreal newY);

    qreal rotation() const;
    void setRotation(qreal newRotation);

    void shootUp();
    void startFlying();
    void freezeInPlace();


signals:

public slots:

    void fallToGroundIfNecesssary();
    void rotateTo(const qreal &end,const int& duration,const QEasingCurve& curve);
private:
    enum wingPosition{Up,Middle,Down};
    void updatePixmap();

    wingPosition wingpos;
    bool wingDirection;

    qreal m_y;
    qreal m_rotation;
    QPropertyAnimation* yAnimation;
    QPropertyAnimation* rotationAnimation;
    qreal groundpos;
};

#endif // BIRD_H
