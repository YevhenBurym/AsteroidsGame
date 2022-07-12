#include "UnitManager.h"

void UnitManager::fixCoordAfterCollision(GameObject* unit1, GameObject* unit2, CoordXY vectorBetween) {
    double alpha = 0;
    CoordXY xyOffset = { 0, 0 };
    double currX1 = unit1->getX();
    double currY1 = unit1->getY();
    double currX2 = unit2->getX();
    double currY2 = unit2->getY();
    double newX1 = 0, newY1 = 0, newX2 = 0, newY2 = 0;
    int minDist = unit1->getRadius() + unit2->getRadius();
    double segmentDist = hypot(vectorBetween.x, vectorBetween.y) - minDist;

    if ((vectorBetween.x == 0) && (vectorBetween.y < 0)) {
        alpha = -PI / 2;
    }
    else if ((vectorBetween.x == 0) && (vectorBetween.y > 0)) {
        alpha = PI / 2;
    }
    else {
        alpha = PI - atan2(vectorBetween.y, vectorBetween.x);
    }
    xyOffset.x = std::abs(segmentDist * cos(alpha));
    xyOffset.y = std::abs(segmentDist * sin(alpha));

    if ((vectorBetween.x > 0) && (vectorBetween.y > 0)) {
        newX1 = currX1 + xyOffset.x;
        newY1 = currY1 + xyOffset.y;
        newX2 = currX2 - xyOffset.x;
        newY2 = currY2 - xyOffset.y;
    }
    else if ((vectorBetween.x < 0) && (vectorBetween.y > 0)) {
        newX1 = currX1 - xyOffset.x;
        newY1 = currY1 + xyOffset.y;
        newX2 = currX2 + xyOffset.x;
        newY2 = currY2 - xyOffset.y;
    }
    else if ((vectorBetween.x > 0) && (vectorBetween.y < 0)) {
        newX1 = currX1 + xyOffset.x;
        newY1 = currY1 - xyOffset.y;
        newX2 = currX2 - xyOffset.x;
        newY2 = currY2 + xyOffset.y;
    }
    else if ((vectorBetween.x < 0) && (vectorBetween.y < 0)) {
        newX1 = currX1 - xyOffset.x;
        newY1 = currY1 - xyOffset.y;
        newX2 = currX2 + xyOffset.x;
        newY2 = currY2 + xyOffset.y;
    }
    else if ((vectorBetween.x == 0) && (vectorBetween.y > 0)) {
        newX1 = currX1;
        newY1 = currY1 + xyOffset.y;
        newX2 = currX2;
        newY2 = currY2 - xyOffset.y;
    }
    else if ((vectorBetween.x == 0) && (vectorBetween.y < 0)) {
        newX1 = currX1;
        newY1 = currY1 + xyOffset.y;
        newX2 = currX2;
        newY2 = currY2 - xyOffset.y;
    }
    else if ((vectorBetween.x < 0) && (vectorBetween.y == 0)) {
        newX1 = currX1 - xyOffset.x;
        newY1 = currY1;
        newX2 = currX2 + xyOffset.x;
        newY2 = currY2;
    }
    else if ((vectorBetween.x > 0) && (vectorBetween.y == 0)) {
        newX1 = currX1 - xyOffset.x;
        newY1 = currY1;
        newX2 = currX2 + xyOffset.x;
        newY2 = currY2;
    }

    unit1->setX(newX1);
    unit1->setY(newY1);
    unit2->setX(newX2);
    unit2->setY(newY2);
}

void UnitManager::calcVelocityAfterCollision(GameObject* unit1, GameObject* unit2, CoordXY vectorBetween) {
    double alpha = 0;
    double phi1 = 0;
    double phi2 = 0;
    double Vcentr1, Vcentr2, newVcentr1, newVcentr2;
    double Vtang1, Vtang2;
    double V1, V2, Vx1, Vy1, Vx2, Vy2;
    double m1 = unit1->getMass();
    double m2 = unit2->getMass();

    if ((vectorBetween.x == 0) && (vectorBetween.y < 0)) {
        alpha = -PI / 2;
    }
    else if ((vectorBetween.x == 0) && (vectorBetween.y > 0)) {
        alpha = PI / 2;
    }
    else {
        alpha = PI - atan2(vectorBetween.y, vectorBetween.x);
    }

    Vcentr1 = unit1->getVx() * cos(alpha) - unit1->getVy() * sin(alpha);
    Vcentr2 = unit2->getVx() * cos(alpha) - unit2->getVy() * sin(alpha);

    newVcentr1 = (2 * m2 * Vcentr2 + (m1 - m2) * Vcentr1) / (m1 + m2);
    newVcentr2 = (2 * m1 * Vcentr1 + (m2 - m1) * Vcentr2) / (m1 + m2);

    Vtang1 = unit1->getVy() * cos(alpha) + unit1->getVx() * sin(alpha);
    Vtang2 = unit2->getVy() * cos(alpha) + unit2->getVx() * sin(alpha);

    V1 = sqrt(newVcentr1 * newVcentr1 + Vtang1 * Vtang1);
    V2 = sqrt(newVcentr2 * newVcentr2 + Vtang2 * Vtang2);

    if ((newVcentr1 == 0) && (Vtang1 < 0)) {
        phi1 = -PI / 2;
    }
    else if ((newVcentr1 == 0) && (Vtang1 > 0)) {
        phi1 = PI / 2;
    }
    else {
        phi1 = PI - atan2(Vtang1, newVcentr1);
    }

    if ((newVcentr2 == 0) && (Vtang2 < 0)) {
        phi2 = -PI / 2;
    }
    else if ((newVcentr2 == 0) && (Vtang2 > 0)) {
        phi2 = PI / 2;
    }
    else {
        phi2 = PI - atan2(Vtang2, newVcentr2);
    }

    Vx1 = V1 * sin(phi1) * sin(alpha) - V1 * cos(phi1) * cos(alpha);
    Vy1 = V1 * sin(phi1) * cos(alpha) + V1 * cos(phi1) * sin(alpha);
    Vx2 = V2 * sin(phi2) * sin(alpha) - V2 * cos(phi2) * cos(alpha);
    Vy2 = V2 * sin(phi2) * cos(alpha) + V2 * cos(phi2) * sin(alpha);

    unit1->setVx(Vx1);
    unit1->setVy(Vy1);
    unit2->setVx(Vx2);
    unit2->setVy(Vy2);
}

UnitManager::UnitManager(int asteroidsLimit, int bulletsLimit, int maxVelocity, Game* game) {
    srand(time(NULL));
    this->game = game;
    this->asteroidsLimit = asteroidsLimit;
    this->numAsteroids = 0;
    this->bulletsLimit = bulletsLimit;
    this->numBullets = 0;

    int wSprite, hSprite;
    this->game->getMap()->getUnitSprites().reticleSprite->getSize(wSprite, hSprite);
    this->isNeedDeAcc = false;

    CoordXY avatarCoord;
    avatarCoord.x = this->game->getMap()->getWMap()/2 - this->game->getMap()->getMapOffsetCoord().x;
    avatarCoord.y = this->game->getMap()->getHMap()/2 - this->game->getMap()->getMapOffsetCoord().y;
    this->avatar = new Avatar(avatarCoord, 0, 0, this->game->getMap()->getUnitSprites().spaceshipSprite, this->game->getMap());
}

UnitManager::~UnitManager() {
    for (auto it = this->asteroids.begin(); it != asteroids.end(); ) {
        delete (*it++);
    }
    this->asteroids.clear();
    this->asteroids.shrink_to_fit();
    this->avatar;
}

void UnitManager::createAsteroids() {
    CoordXY asteroidCoord = {0, 0};
    Velocity asteroidVelocity = {0, 0};
    int minVLimit = 100;
    int maxVLimit = 300;
    int angleRange = 180;
    if (this->numAsteroids < this->asteroidsLimit) {
        this->numAsteroids += 1;
        asteroidCoord = this->randomizeAppearCoord(this->game->getMap()->getWMap(), this->game->getMap()->getHMap());
        asteroidVelocity = this->randomizeVelocity(minVLimit, maxVLimit, angleRange);

        uint8_t randomAsteroid = RANDRANGE_0_1 * 100;

        if (randomAsteroid > 80) {
            this->asteroids.push_back(new BigAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta, this->game->getMap()->getUnitSprites().bigAsteroidSprite, this->game->getMap()));
        } else {
            this->asteroids.push_back(new SmallAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta, this->game->getMap()->getUnitSprites().smallAsteroidSprite, this->game->getMap()));
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
    for (auto it = this->asteroids.begin(); it != this->asteroids.end(); ++it) {
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

void UnitManager::divideBigAsteroid(BigAsteroid* asteroid) {
    int x = 0, y = 0, r = 0;
    Velocity v = { 0,0 };

    x = asteroid->getXrel();
    y = asteroid->getYrel();
    v = asteroid->getV();
    r = asteroid->getRadius();
    CoordXY xy1;
    CoordXY xy2;
    xy1.x= x + r;
    xy1.y= y + r;
    xy2.x= x - r;
    xy2.y= y - r;
    this->asteroids.push_back(new SmallAsteroid(xy1, v.v, v.theta + 45, this->game->getMap()->getUnitSprites().smallAsteroidSprite, this->game->getMap()));
    this->asteroids.push_back(new SmallAsteroid(xy2, v.v, v.theta - 45, this->game->getMap()->getUnitSprites().smallAsteroidSprite, this->game->getMap()));
    this->numAsteroids += 1;
    this->numBullets  -= 1;
}

void UnitManager::checkCollisions() {
    for (auto it1 = this->asteroids.begin(); it1 != this->asteroids.end(); ++it1) {
        for (auto it2 = it1 + 1; it2 != this->asteroids.end(); ++it2) {

            CoordXY xyCentr1 = { (*it1)->getXrel() + (*it1)->getRadius(),(*it1)->getYrel() + (*it1)->getRadius() };
            CoordXY xyCentr2 = { (*it2)->getXrel() + (*it2)->getRadius(),(*it2)->getYrel() + (*it2)->getRadius() };
            CoordXY xyCentrVector = { xyCentr1.x - xyCentr2.x, xyCentr1.y - xyCentr2.y };
            int minDist = (*it1)->getRadius() + (*it2)->getRadius();

            if (hypot(xyCentrVector.x, xyCentrVector.y) < minDist && hypot(xyCentrVector.x, xyCentrVector.y) > minDist / 2) {
                if (dynamic_cast<Avatar*>(*it1) && dynamic_cast<Bullet*>(*it2) ||
                    dynamic_cast<Bullet*>(*it1) && dynamic_cast<Bullet*>(*it2)) {
                    break;
                }
                else if (dynamic_cast<Avatar*>(*it1) && !dynamic_cast<Bullet*>(*it2)) {
                    this->game->restart();
                    return;
                }
                else if (dynamic_cast<Bullet*>(*it1) && dynamic_cast<SmallAsteroid*>(*it2) ||
                         dynamic_cast<Bullet*>(*it2) && dynamic_cast<SmallAsteroid*>(*it1)) {
                    GameObject* temp1 = (*it1);
                    GameObject* temp2 = (*it2);
                    it2 = this->asteroids.erase(it2);
                    it2--;
                    it1 = this->asteroids.erase(it1);
                    it1--;
                    delete temp1;
                    delete temp2;
                    this->numAsteroids -= 1;
                    this->numBullets -= 1;

                    break;
                }
                else if (dynamic_cast<Bullet*>(*it1) && dynamic_cast<BigAsteroid*>(*it2) ||
                         dynamic_cast<Bullet*>(*it2) && dynamic_cast<BigAsteroid*>(*it1)) {
                    BigAsteroid* bigAster = nullptr;

                    if (dynamic_cast<BigAsteroid*>(*it2)) {
                        bigAster = dynamic_cast<BigAsteroid*>(*it2);
                    }
                    else if (dynamic_cast<BigAsteroid*>(*it1)) {
                        bigAster = dynamic_cast<BigAsteroid*>(*it1);
                    }
                    GameObject* temp1 = (*it1);
                    GameObject* temp2 = (*it2);
                    it2 = this->asteroids.erase(it2);
                    it2--;
                    it1 = this->asteroids.erase(it1);
                    it1--;
                    this->divideBigAsteroid(bigAster);
                    delete temp1;
                    delete temp2;

                    break;
                }
                else {
                    fixCoordAfterCollision((*it1), (*it2), xyCentrVector);
                    calcVelocityAfterCollision((*it1), (*it2), xyCentrVector);
                }
            }
        }
    }
}

void UnitManager::calcOffset() {
    this->game->getMap()->calcCoord(this->game->getMap()->getVx(), this->game->getMap()->getVy(), 0.001);

    if (this->game->getMap()->getV().v) {
        for (auto it = this->asteroids.begin(); it != this->asteroids.end(); ++it) {
            (*it)->setXof(this->game->getMap()->getX());
            (*it)->setYof(this->game->getMap()->getY());
        }
    }
}

//------------------------------------------------------------------//
void UnitManager::createAvatar() {
    this->asteroids.push_back(this->avatar);
}

void UnitManager::makeShoot() {
    Bullet* bullet = this->getAvatar()->makeShoot();
    if (this->numBullets < this->bulletsLimit) {
        this->numBullets += 1;
        this->asteroids.push_back(bullet);
    } else {
        for (auto it = this->asteroids.begin(); it != this->asteroids.end(); ++it) {
            if (dynamic_cast<Bullet*>(*it)) {
                delete (*it);
                this->asteroids.erase(it);
                this->asteroids.push_back(bullet);
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

std::vector<GameObject *> &UnitManager::getAsteroidsVector() {
    return this->asteroids;
}
