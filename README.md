# Flappy Bird Clone

A Qt-based C++ recreation of the classic Flappy Bird game, featuring smooth animations, collision detection, and score tracking.

## Features

* Smooth bird animations and wing flapping.
* Randomly generated moving obstacles.
* Score tracking with best score.
* Collision detection with game over handling.

## How to Play

* Click **Start Game** to begin.
* Press **Space** or **Left Click** to make the bird fly.
* Avoid pillars to score points.

## Build & Run

```bash
git clone https://github.com/maishanajalam/flappy-bird-clone.git
cd flappy-bird-clone/FlappyBird
qmake FlappyBird.pro
make
./FlappyBird
```

## Project Structure

```
FlappyBird/
├── main.cpp
├── widget.h/cpp
├── scene.h/cpp
├── bird.h/cpp
├── pillaritem.h/cpp
├── widget.ui
├── resource.qrc
└── FlappyBird.pro
```


