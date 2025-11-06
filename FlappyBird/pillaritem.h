#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QObject>
#include<QGraphicsItemGroup>
#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>

class PillarItem :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX  FINAL)
public:
    explicit PillarItem();
    ~PillarItem();
    qreal x() const;
    void freezeInPlace();

signals:
    void collideFail();

public slots:

    void setX(qreal x);

private:

    bool collisionWithBird();
    QGraphicsPixmapItem* topPillar;
    QGraphicsPixmapItem* bottomPillar;
    QPropertyAnimation* xAnimation;
    qreal m_x;
    int yPos;

    bool pastBird;
};

#endif // PILLARITEM_H
