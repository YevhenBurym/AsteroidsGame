#include "UnitManager.h"

UnitManager::UnitManager(Game* game) {
    srand(time(NULL));
    this->game = game;
    int wSprite, hSprite;
    this->game->getMap()->getUnitSprites().reticleSprite->getSize(wSprite, hSprite);
    this->isNeedDeAcc = false;

    CoordXY avatarCoord;
    avatarCoord.x = this->game->getMap()->getWMap()/2 - this->game->getMap()->getMapOffsetCoord().x;
    avatarCoord.y = this->game->getMap()->getHMap()/2 - this->game->getMap()->getMapOffsetCoord().y;
    this->avatar = new Avatar(avatarCoord, 0, 0, this->game->getMap()->getUnitSprites().spaceshipSprite, this->game->getMap());
}

UnitManager::~UnitManager() {
    for (auto it = this->game->getObjects().begin(); it != this->game->getObjects().end(); ) {
        delete (*it++);
    }
    this->game->getObjects().clear();
    this->game->getObjects().shrink_to_fit();
    this->avatar;
}

void UnitManager::createAsteroids() {
    CoordXY asteroidCoord = {0, 0};
    Velocity asteroidVelocity = {0, 0};
    int minVLimit = 100;
    int maxVLimit = 300;
    int angleRange = 180;
    if (this->game->getNumAsteroids() < this->game->getAsteroidslimit()) {
        int newAmountAsteroids = this->game->getNumAsteroids() + 1;
        this->game->setNumAsteroids(newAmountAsteroids);
        asteroidCoord = this->randomizeAppearCoord(this->game->getMap()->getWMap(), this->game->getMap()->getHMap());
        asteroidVelocity = this->randomizeVelocity(minVLimit, maxVLimit, angleRange);

        uint8_t randomAsteroid = RANDRANGE_0_1 * 100;

        if (randomAsteroid > 80) {
            this->game->getObjects().push_back(new BigAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta, this->game->getMap()->getUnitSprites().bigAsteroidSprite, this->game->getMap()));
        } else {
            this->game->getObjects().push_back(new SmallAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta, this->game->getMap()->getUnitSprites().smallAsteroidSprite, this->game->getMap()));
        }
    }
}

CoordXY UnitManager::randomizeAppearCoord(int wMap, int hMap) {
    CoordXY randomXY = {0, 0};
    uint8_t randomSide = RANDRANGE_0_1 * 3;
    int wSreen, hSreen;
    this->game->getWindow()->getSize(wSreen, hSreen);

    if (randomSide == 0) {
        randomXY.y = RANDRANGE_0_1 * hMap;
        randomXY.x = RANDRANGE_0_1 * (wMap - wSreen) / 2 - 0 + 0;
    }
    else if (randomSide == 1) {
        randomXY.x = RANDRANGE_0_1 * wMap;
        randomXY.y = RANDRANGE_0_1 * (hMap - hSreen) / 2 - 0 + 0;
    }
    else if (randomSide == 2) {
        randomXY.y = RANDRANGE_0_1 * hMap;
        randomXY.x = RANDRANGE_0_1 * (wMap - wSreen) + wSreen;
    }
    else if (randomSide == 3) {
        randomXY.x = RANDRANGE_0_1 * wMap;
        randomXY.y = RANDRANGE_0_1 * (hMap - hSreen) + hSreen;
    }
    return randomXY;
}

Velocity UnitManager::randomizeVelocity(int minVelocity, int maxVelocity, int angleRange) {

    Velocity randomV = {0, 0};

    randomV.v = RANDRANGE_0_1 * (maxVelocity - minVelocity) + minVelocity;
    randomV.theta = 2 * (RANDRANGE_0_1 - 0.5) * angleRange;

    return randomV;
}

void UnitManager::drawAsteroids() {
    for (auto it = this->game->getObjects().begin(); it != this->game->getObjects().end(); ++it) {
        (*it)->calcCoord((*it)->getVx(), (*it)->getVy(), 0.001);
        int x = (*it)->getXrel() - (*it)->getRadius();
        int y = (*it)->getYrel() - (*it)->getRadius();
        Sprite* currSprite = (*it)->getSprite();
        if (currSprite == this->game->getMap()->getUnitSprites().spaceshipSprite) {
            currSprite->draw(x,y,90- this->avatar->getAngle());
        } else {
            currSprite->draw(x,y);
        }
    }
}

//void UnitManager::divideBigAsteroid(BigAsteroid* asteroid) {
//    int x = 0, y = 0, r = 0;
//    Velocity v = { 0,0 };
//
//    x = asteroid->getXrel();
//    y = asteroid->getYrel();
//    v = asteroid->getV();
//    r = asteroid->getRadius();
//    CoordXY xy1;
//    CoordXY xy2;
//    xy1.x= x + r;
//    xy1.y= y + r;
//    xy2.x= x - r;
//    xy2.y= y - r;
//    this->game->getObjects().push_back(new SmallAsteroid(xy1, v.v, v.theta + 45, this->game->getMap()->getUnitSprites().smallAsteroidSprite, this->game->getMap()));
//    this->game->getObjects().push_back(new SmallAsteroid(xy2, v.v, v.theta - 45, this->game->getMap()->getUnitSprites().smallAsteroidSprite, this->game->getMap()));
//    this->numAsteroids += 1;
//    this->numBullets  -= 1;
//}


void UnitManager::calcOffset() {
    this->game->getMap()->calcCoord(this->game->getMap()->getVx(), this->game->getMap()->getVy(), 0.001);

    if (this->game->getMap()->getV().v) {
        for (auto it = this->game->getObjects().begin(); it != this->game->getObjects().end(); ++it) {
            (*it)->setXof(this->game->getMap()->getX());
            (*it)->setYof(this->game->getMap()->getY());
        }
    }
}

//------------------------------------------------------------------//
void UnitManager::createAvatar() {
    this->game->getObjects().push_back(this->avatar);
}

void UnitManager::makeShoot() {
    Bullet* bullet = this->getAvatar()->makeShoot();
    if (this->game->getNumBullets() < this->game->getAmmoLimit()) {
        int newAmountBullets = this->game->getNumBullets() + 1;
        this->game->setNumBullets(newAmountBullets);
        //this->numBullets += 1;
        this->game->getObjects().push_back(bullet);
    } else {
        for (auto it = this->game->getObjects().begin(); it != this->game->getObjects().end(); ++it) {
            if (dynamic_cast<Bullet*>(*it)) {
                delete (*it);
                this->game->getObjects().erase(it);
                this->game->getObjects().push_back(bullet);
                return;
            }
        }
    }
}

void UnitManager::deAcceleration() {
    double step = 0.001;
    double acc = 500;
    double vMap = this->game->getMap()->getV().v;
    double thetaMap = this->game->getMap()->getV().theta;
    if (isNeedDeAcc) {
        if (vMap > 0) {
            vMap -= acc * step;
        }
        else {
            isNeedDeAcc = false;
        }
        this->game->getMap()->setV(vMap, thetaMap);
    }
}

void UnitManager::setIsNeededDeacc(bool state) {
    this->isNeedDeAcc = true;
}

Avatar *UnitManager::getAvatar() const {
    return this->avatar;
}

