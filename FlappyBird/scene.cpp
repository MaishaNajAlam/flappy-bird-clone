#include "scene.h"
#include<QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include<QKeyEvent>
#include<QDebug>

Scene::Scene(QObject *parent): QGraphicsScene{parent},gameOn(false)
    ,score(0),bestScore(0),gameOverPix(nullptr),scoreTextItem(nullptr)
{
    setUpPillarTimer();

}

void Scene::addBird()
{
    bird=new Bird(QPixmap(":/images/bird_up.png"));
    addItem(bird);


}

void Scene::startGame()
{
    //start animation for Bird and also pillars


    bird->startFlying();
    score=0;
    if(!pillarTimer->isActive()){
        cleanPillarItems();
        setGameOn(true);
        hideGameOverGraphics();
        pillarTimer->start(1000);
    }

    if (!views().isEmpty()) {
        views().first()->setFocus();
    }

}


void Scene::setGameOn(bool value)
{
    gameOn=value;
}

bool Scene::getGameOn()
{
    return gameOn;
}

void Scene::incrementScore()
{
    score++;
    if(score>bestScore){
        bestScore=score;
    }
    qDebug()<<"Score:"<<score<<"Best Score:"<<bestScore;
}

void Scene::setUpPillarTimer()
{
    pillarTimer=new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){
        PillarItem* pillarItem= new PillarItem();
        connect(pillarItem,&PillarItem::collideFail,[=](){
            pillarTimer->stop();
            freezeBirdAndPillars();
            setGameOn(false);
            showGameOverGraphics();

        });
        addItem(pillarItem);
    });

    //pillarTimer->start(1000);
}

void Scene::freezeBirdAndPillars()
{
    bird->freezeInPlace();

    QList<QGraphicsItem*> sceneItems=items();
    foreach(QGraphicsItem* item,sceneItems){
        PillarItem* pillars=dynamic_cast<PillarItem*>(item);
        if(pillars){
            pillars->freezeInPlace();
        }
    }

}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        if(gameOn){
            bird->shootUp();}
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}


void Scene::showGameOverGraphics()
{
    hideGameOverGraphics();
    gameOverPix=new QGraphicsPixmapItem(QPixmap(":/images/gameOver.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0)-QPoint(gameOverPix->boundingRect().width()/2,gameOverPix->boundingRect().height()/2));

    scoreTextItem=new QGraphicsTextItem();
    QString htmlString="<p> Score : "+QString::number(score)+"</p>"
                         +"<p> Best Score : "+QString::number(bestScore)+"</p>";


    QFont mfont("Consolas",30,QFont::Bold);
    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mfont);
    scoreTextItem->setDefaultTextColor(Qt::yellow);
    addItem(scoreTextItem);
    scoreTextItem->setPos(QPointF(0,0)-QPointF(scoreTextItem->boundingRect().width()/2,-gameOverPix->boundingRect().height()/2));

}


void Scene::hideGameOverGraphics()
{
    if (gameOverPix != nullptr) {
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }

    if (scoreTextItem != nullptr) {
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }

    qDebug() << "hideGameOverGraphics() finished safely";
}




void Scene::cleanPillarItems()
{
    QList<QGraphicsItem*> sceneItems=items();
    foreach(QGraphicsItem* item,sceneItems){
        PillarItem* pillars=dynamic_cast<PillarItem*>(item);
        if(pillars){
            removeItem(pillars);
            delete pillars;
        }
    }
}
