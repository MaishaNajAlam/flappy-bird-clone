#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include<QGraphicsScene>
#include<QTimer>
#include "pillaritem.h"
#include<bird.h>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();
    void startGame();
    void setGameOn(bool value);
    bool getGameOn();
    void incrementScore();

signals:
public slots:

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillarItems();
    void  setUpPillarTimer();
    void  freezeBirdAndPillars();
    QTimer* pillarTimer;
    Bird* bird;
    bool gameOn;

    int score,bestScore;

    QGraphicsPixmapItem* gameOverPix;
    QGraphicsTextItem* scoreTextItem;
};

#endif // SCENE_H
