#include "UnitManager.h"

void UnitManager::createSprites() {
    //this->sprites.smallAsteroidSprite = createSprite("data\\small_asteroid.png");
    //this->sprites.bigAsteroidSprite = createSprite("data\\big_asteroid.png");
    //this->sprites.spaceshipSprite = createSprite("data\\spaceship.png");

    this->sprites.spaceshipSprite = createTexture("data\\ship.png");
    this->sprites.smallAsteroidSprite = createTexture("data\\small.png");
    this->sprites.bigAsteroidSprite = createTexture("data\\big.png");
    this->sprites.reticleSprite = createTexture("data\\circle.tga");
    this->sprites.bulletSprite = createTexture("data\\bullet.png");
}

void UnitManager::destroySprites() {
    destroyTexture(sprites.bigAsteroidSprite);
    destroyTexture(sprites.smallAsteroidSprite);
    destroyTexture(sprites.spaceshipSprite);
    destroyTexture(sprites.reticleSprite);
    destroyTexture(sprites.bulletSprite);
}

void UnitManager::fixCoordAfterCollision(MoveableUnit1* unit1, MoveableUnit1* unit2, CoordXY vectorBetween) {
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

void UnitManager::calcVelocityAfterCollision(MoveableUnit1* unit1, MoveableUnit1* unit2, CoordXY vectorBetween) {
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

UnitManager::UnitManager(int asteroidsLimit, int bulletsLimit, int maxVelocity, AsteroidsGame* game) {
    srand(time(NULL));
    this->createSprites();
    this->asteroidsLimit = asteroidsLimit;
    this->numAsteroids = 0;
    this->bulletsLimit = bulletsLimit;
    this->numBullets = 0;
    this->game = game;

    int wSprite, hSprite;
    getTextureSize(this->sprites.reticleSprite, wSprite, hSprite);
    this->reticleOffset.x = wSprite / 2;
    this->reticleOffset.y = hSprite / 2;

    this->reticle.x = 0;
    this->reticle.y = 0;

    this->isNeedDeAcc = false;
    this->angleShip = 0;
}

UnitManager::~UnitManager() {
    for (auto it = this->asteroids.begin(); it != asteroids.end(); ) {
        delete (*it++);
    }
    this->asteroids.clear();
    this->asteroids.shrink_to_fit();
    this->destroySprites();
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
            this->asteroids.push_back(new BigAsteroid1(asteroidCoord.x, asteroidCoord.y, asteroidVelocity.v, asteroidVelocity.theta, this->sprites.bigAsteroidSprite, this->game->getMap()));
        } else {
            this->asteroids.push_back(new SmallAsteroid1(asteroidCoord.x, asteroidCoord.y, asteroidVelocity.v, asteroidVelocity.theta, this->sprites.smallAsteroidSprite, this->game->getMap()));
        }
    }
    drawAsteroids();
}

void UnitManager::createAvatar() {
    int hScreen, wScreen;
    getWindowSize(wScreen, hScreen);
    int xAvatar = this->game->getMap()->getWMap()/2 - this->game->getMap()->getMapOffsetCoord().x;
    int yAvatar = this->game->getMap()->getHMap()/2 - this->game->getMap()->getMapOffsetCoord().y;
    this->asteroids.push_back(new Avatar1(xAvatar, yAvatar, 0, 0, this->sprites.spaceshipSprite, this->game->getMap()));
}

std::vector<MoveableUnit1*>& UnitManager::getAsteroidsVector() {
    return this->asteroids;
}

CoordXY UnitManager::randomizeAppearCoord(int wMap, int hMap) {
    CoordXY randomXY = {0, 0};
    uint8_t randomSide = RANDRANGE_0_1 * 3;
    int wSreen, hSreen;
    getWindowSize(wSreen, hSreen);

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
        SDL_Texture* currTexture = (*it)->getSprite();
        if (currTexture == this->sprites.spaceshipSprite) {
            drawTexture(currTexture, x, y, 90 - this->angleShip);
        } else {
            drawTexture(currTexture, x, y);
        }
        //drawTexture((*it)->getSprite(), x, y);
    }
}

void UnitManager::drawReticle() {

    int x = this->reticle.x - this->reticleOffset.x;
    int y = this->reticle.y - this->reticleOffset.y;

    drawTexture(this->sprites.reticleSprite, x, y);
}

void UnitManager::shipHeadAngle() {
    int xAvatar = this->asteroids[0]->getXrel();
    int yAvatar = this->asteroids[0]->getYrel();
    double xRet = this->reticle.x;
    double yRet = this->reticle.y;
    if (this->game->getMap()->getV().v > 0) {
        xAvatar -= this->game->getMap()->getX();
        yAvatar -= this->game->getMap()->getY();
        xRet -= this->game->getMap()->getX();
        yRet -= this->game->getMap()->getY();
    }
    double alpha = 0;
    CoordXY xyDirVector = { xAvatar - xRet, yAvatar - yRet };
    double dist = hypot(xyDirVector.x, xyDirVector.y) ;

    if ((xyDirVector.x == 0) && (xyDirVector.y < 0)) {
        alpha = -PI / 2;
    } else if ((xyDirVector.x == 0) && (xyDirVector.y > 0)) {
        alpha = PI / 2;
    } else {
        alpha = PI - atan2(xyDirVector.y, xyDirVector.x);
    }
    alpha = alpha * 180 / PI;
    this->angleShip = alpha; // для розрахунку направлення корабля
}

void UnitManager::makeShoot() {
    int xAvatar = this->asteroids[0]->getXrel();
    int yAvatar = this->asteroids[0]->getYrel();
    this->shipHeadAngle();
    if (this->game->getMap()->getV().v > 0) {
        xAvatar -= this->game->getMap()->getX();
        yAvatar -= this->game->getMap()->getY();
    }
    if (this->numBullets < this->bulletsLimit) {
        this->numBullets += 1;
        this->asteroids.push_back(new Bullet1(xAvatar, yAvatar, 800, this->angleShip, this->sprites.bulletSprite, this->game->getMap()));
    } else {
        for (auto it = this->asteroids.begin(); it != this->asteroids.end(); ++it) {
            if (dynamic_cast<Bullet1*>(*it)) {
                delete (*it);
                this->asteroids.erase(it);
                this->asteroids.push_back(new Bullet1(xAvatar, yAvatar, 800, this->angleShip, this->sprites.bulletSprite, this->game->getMap()));
                return;
            }
        }
    }
}

void UnitManager::divideBigAsteroid(BigAsteroid1* asteroid) {
    int x = 0, y = 0, r = 0;
    Velocity v = { 0,0 };

    x = asteroid->getXrel();
    y = asteroid->getYrel();
    v = asteroid->getV();
    r = asteroid->getRadius();

    this->asteroids.push_back(new SmallAsteroid1(x + r, y + r, v.v, v.theta + 45, this->sprites.smallAsteroidSprite, this->game->getMap()));
    this->asteroids.push_back(new SmallAsteroid1(x - r, y - r, v.v, v.theta - 45, this->sprites.smallAsteroidSprite, this->game->getMap()));
    this->numAsteroids += 1;
    this->numBullets  -= 1;
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

void UnitManager::checkCollisions() {
    for (auto it1 = this->asteroids.begin(); it1 != this->asteroids.end(); ++it1) {
        for (auto it2 = it1 + 1; it2 != this->asteroids.end(); ++it2) {

            CoordXY xyCentr1 = { (*it1)->getXrel() + (*it1)->getRadius(),(*it1)->getYrel() + (*it1)->getRadius() };
            CoordXY xyCentr2 = { (*it2)->getXrel() + (*it2)->getRadius(),(*it2)->getYrel() + (*it2)->getRadius() };
            CoordXY xyCentrVector = { xyCentr1.x - xyCentr2.x, xyCentr1.y - xyCentr2.y };
            int minDist = (*it1)->getRadius() + (*it2)->getRadius();

            if (hypot(xyCentrVector.x, xyCentrVector.y) < minDist && hypot(xyCentrVector.x, xyCentrVector.y) > minDist / 2) {
                if (dynamic_cast<Avatar1*>(*it1) && dynamic_cast<Bullet1*>(*it2) ||
                    dynamic_cast<Bullet1*>(*it1) && dynamic_cast<Bullet1*>(*it2)) {
                    break;
                }
                else if (dynamic_cast<Avatar1*>(*it1) && !dynamic_cast<Bullet1*>(*it2)) {
                    this->game->restart();
                    return;
                }
                else if (dynamic_cast<Bullet1*>(*it1) && dynamic_cast<SmallAsteroid1*>(*it2) ||
                         dynamic_cast<Bullet1*>(*it2) && dynamic_cast<SmallAsteroid1*>(*it1)) {
                    MoveableUnit1* temp1 = (*it1);
                    MoveableUnit1* temp2 = (*it2);
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
                else if (dynamic_cast<Bullet1*>(*it1) && dynamic_cast<BigAsteroid1*>(*it2) ||
                         dynamic_cast<Bullet1*>(*it2) && dynamic_cast<BigAsteroid1*>(*it1)) {
                    BigAsteroid1* bigAster = nullptr;

                    if (dynamic_cast<BigAsteroid1*>(*it2)) {
                        bigAster = dynamic_cast<BigAsteroid1*>(*it2);
                    }
                    else if (dynamic_cast<BigAsteroid1*>(*it1)) {
                        bigAster = dynamic_cast<BigAsteroid1*>(*it1);
                    }
                    MoveableUnit1* temp1 = (*it1);
                    MoveableUnit1* temp2 = (*it2);
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

int UnitManager::getNumAsteroids() const {
    return this->numAsteroids;
}

int UnitManager::getNumBullets() const {
    return  this->numBullets;
}

void UnitManager::setNumAsteroids(int num) {
    this->numAsteroids = num;
}

void UnitManager::setNumBullets(int num) {
    this->numBullets = num;
}

void UnitManager::setXReticle(int x) {
    this->reticle.x = x;
}

void UnitManager::setYReticle(int y) {
    this->reticle.y = y;
}

void UnitManager::setIsNeededDeacc(bool state) {
    this->isNeedDeAcc = true;
}
