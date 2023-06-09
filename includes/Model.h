#pragma once

#include "Hero.h"
#include "Bullet.h"
#include "Boss.h"
#include "Enemies.h"

class Model {
public:
    Hero *hero_;
    std::vector<Bullet *> heroBullet;
    Boss *boss_;
    Bullet *bossBullet;
    std::vector<Enemies *> enemies_;
    Bullet *firstEnemyBullet;
    Bullet *secondEnemyBullet;

    Model();

    void updateModel();

    void updateHeroBullet(int);
};
