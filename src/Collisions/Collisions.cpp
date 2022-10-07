//
// Created by Евгений on 12.07.2022.
//

#include "Collisions.h"

Collisions::Collisions(ObjectManager *asteroidsManager) {
    this->objectManager = asteroidsManager;
}

void Collisions::fixCoord(MovableGameObject* unit1, MovableGameObject* unit2, Vector2D vectorBetween) {
    double alpha = 0;
    Vector2D xyOffset = {0, 0 };
    double currX1 = unit1->getX();
    double currY1 = unit1->getY();
    double currX2 = unit2->getX();
    double currY2 = unit2->getY();
    double newX1 = 0, newY1 = 0, newX2 = 0, newY2 = 0;
    int minDist = unit1->getRadius() + unit2->getRadius();
    double segmentDist = hypot(vectorBetween.getX(), vectorBetween.getY()) - minDist;

    if ((vectorBetween.getX() == 0) && (vectorBetween.getY() < 0)) {
        alpha = -M_PI / 2;
    }
    else if ((vectorBetween.getX() == 0) && (vectorBetween.getY() > 0)) {
        alpha = M_PI / 2;
    }
    else {
        alpha = M_PI - atan2(vectorBetween.getY(), vectorBetween.getX());
    }
    xyOffset.setX(std::abs(segmentDist * cos(alpha)));
    xyOffset.setY(std::abs(segmentDist * sin(alpha)));

    if ((vectorBetween.getX() > 0) && (vectorBetween.getY() > 0)) {
        newX1 = currX1 + xyOffset.getX();
        newY1 = currY1 + xyOffset.getY();
        newX2 = currX2 - xyOffset.getX();
        newY2 = currY2 - xyOffset.getY();
    }
    else if ((vectorBetween.getX() < 0) && (vectorBetween.getY() > 0)) {
        newX1 = currX1 - xyOffset.getX();
        newY1 = currY1 + xyOffset.getY();
        newX2 = currX2 + xyOffset.getX();
        newY2 = currY2 - xyOffset.getY();
    }
    else if ((vectorBetween.getX() > 0) && (vectorBetween.getY() < 0)) {
        newX1 = currX1 + xyOffset.getX();
        newY1 = currY1 - xyOffset.getY();
        newX2 = currX2 - xyOffset.getX();
        newY2 = currY2 + xyOffset.getY();
    }
    else if ((vectorBetween.getX()  < 0) && (vectorBetween.getY() < 0)) {
        newX1 = currX1 - xyOffset.getX();
        newY1 = currY1 - xyOffset.getY();
        newX2 = currX2 + xyOffset.getX();
        newY2 = currY2 + xyOffset.getY();
    }
    else if ((vectorBetween.getX()  == 0) && (vectorBetween.getY() > 0)) {
        newX1 = currX1;
        newY1 = currY1 + xyOffset.getY();
        newX2 = currX2;
        newY2 = currY2 - xyOffset.getY();
    }
    else if ((vectorBetween.getX()  == 0) && (vectorBetween.getY() < 0)) {
        newX1 = currX1;
        newY1 = currY1 + xyOffset.getY();
        newX2 = currX2;
        newY2 = currY2 - xyOffset.getY();
    }
    else if ((vectorBetween.getX()  < 0) && (vectorBetween.getY() == 0)) {
        newX1 = currX1 - xyOffset.getX();
        newY1 = currY1;
        newX2 = currX2 + xyOffset.getX();
        newY2 = currY2;
    }
    else if ((vectorBetween.getX()  > 0) && (vectorBetween.getY() == 0)) {
        newX1 = currX1 - xyOffset.getX();
        newY1 = currY1;
        newX2 = currX2 + xyOffset.getX();
        newY2 = currY2;
    }

    unit1->setX(newX1);
    unit1->setY(newY1);
    unit2->setX(newX2);
    unit2->setY(newY2);
}

void Collisions::calcVelocity(MovableGameObject* unit1, MovableGameObject* unit2, Vector2D vectorBetween) {
    double alpha = 0;
    double phi1 = 0;
    double phi2 = 0;
    double Vcentr1, Vcentr2, newVcentr1, newVcentr2;
    double Vtang1, Vtang2;
    double V1, V2;
    Vector2D Vxy1{0,0};
    Vector2D Vxy2{0,0};
    double m1 = unit1->getMass();
    double m2 = unit2->getMass();

    if ((vectorBetween.getX() == 0) && (vectorBetween.getY() < 0)) {
        alpha = -M_PI / 2;
    }
    else if ((vectorBetween.getX() == 0) && (vectorBetween.getY() > 0)) {
        alpha = M_PI / 2;
    }
    else {
        alpha = M_PI - atan2(vectorBetween.getY(), vectorBetween.getX());
    }

    Vcentr1 = unit1->getVxy().getX() * cos(alpha) - unit1->getVxy().getY() * sin(alpha);
    Vcentr2 = unit2->getVxy().getX() * cos(alpha) - unit2->getVxy().getY() * sin(alpha);

    newVcentr1 = (2 * m2 * Vcentr2 + (m1 - m2) * Vcentr1) / (m1 + m2);
    newVcentr2 = (2 * m1 * Vcentr1 + (m2 - m1) * Vcentr2) / (m1 + m2);

    Vtang1 = unit1->getVxy().getY() * cos(alpha) + unit1->getVxy().getX() * sin(alpha);
    Vtang2 = unit2->getVxy().getY() * cos(alpha) + unit2->getVxy().getX() * sin(alpha);

    V1 = sqrt(newVcentr1 * newVcentr1 + Vtang1 * Vtang1);
    V2 = sqrt(newVcentr2 * newVcentr2 + Vtang2 * Vtang2);

    if ((newVcentr1 == 0) && (Vtang1 < 0)) {
        phi1 = -M_PI / 2;
    }
    else if ((newVcentr1 == 0) && (Vtang1 > 0)) {
        phi1 = M_PI / 2;
    }
    else {
        phi1 = M_PI - atan2(Vtang1, newVcentr1);
    }

    if ((newVcentr2 == 0) && (Vtang2 < 0)) {
        phi2 = -M_PI / 2;
    }
    else if ((newVcentr2 == 0) && (Vtang2 > 0)) {
        phi2 = M_PI / 2;
    }
    else {
        phi2 = M_PI - atan2(Vtang2, newVcentr2);
    }

    Vxy1.setX(V1 * sin(phi1) * sin(alpha) - V1 * cos(phi1) * cos(alpha));
    Vxy1.setY(V1 * sin(phi1) * cos(alpha) + V1 * cos(phi1) * sin(alpha));
    Vxy2.setX(V2 * sin(phi2) * sin(alpha) - V2 * cos(phi2) * cos(alpha));
    Vxy2.setY(V2 * sin(phi2) * cos(alpha) + V2 * cos(phi2) * sin(alpha));

    unit1->setVxy(Vxy1);
    unit2->setVxy(Vxy2);
}

void Collisions::update() {
    for (auto it1 = this->objectManager->getObjects().begin(); it1 != this->objectManager->getObjects().end(); ++it1) {
        auto player = dynamic_cast<SpaceShip*>(this->objectManager->getObjects().front());

        for (auto it2 = it1 + 1; it2 != this->objectManager->getObjects().end(); ++it2) {

            Vector2D xyCentr1 = {(*it1)->getXrel(), (*it1)->getYrel()};
            Vector2D xyCentr2 = {(*it2)->getXrel(), (*it2)->getYrel()};
            Vector2D xyCentrVector = {xyCentr1.getX() - xyCentr2.getX(), xyCentr1.getY() - xyCentr2.getY() };
            int minDist = (*it1)->getRadius() + (*it2)->getRadius();

            if (hypot(xyCentrVector.getX(), xyCentrVector.getY()) < minDist && hypot(xyCentrVector.getX(), xyCentrVector.getY()) > minDist / 2) {
                if (dynamic_cast<SpaceShip*>(*it1) && dynamic_cast<Bullet*>(*it2) ||
                    dynamic_cast<Bullet*>(*it1) && dynamic_cast<Bullet*>(*it2)) {
                    break;
                }
                else if (dynamic_cast<SpaceShip*>(*it1) && !dynamic_cast<Bullet*>(*it2)) {
                    throw YouDied();
                }
                else if (dynamic_cast<Bullet*>(*it1) && dynamic_cast<SmallAsteroid*>(*it2) ||
                         dynamic_cast<Bullet*>(*it2) && dynamic_cast<SmallAsteroid*>(*it1)) {
                    MovableGameObject* temp1 = (*it1);
                    MovableGameObject* temp2 = (*it2);
                    it2 = this->objectManager->getObjects().erase(it2);
                    it2--;
                    it1 = this->objectManager->getObjects().erase(it1);
                    it1--;
                    delete temp1;
                    delete temp2;
                    int newAsteroidsAmount = this->objectManager->getNumAsteroids() - 1;
                    int newBulletsAmount = player->getNumBullets() - 1;
                    this->objectManager->setNumAsteroids(newAsteroidsAmount);
                    player->setNumBullets(newBulletsAmount);

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
                    MovableGameObject* temp1 = (*it1);
                    MovableGameObject* temp2 = (*it2);
                    auto iter1 = it1 - 1;
                    auto iter2 = it2 - 1;
                    it2 = this->objectManager->getObjects().erase(it2);
                    it1 = this->objectManager->getObjects().erase(it1);
                    it1 = iter1;
                    it2 = iter2;

                    bigAster->divide(this->objectManager->getObjects());

                    int newAsteroidsAmount = this->objectManager->getNumAsteroids() + 1;
                    int newBulletsAmount = player->getNumBullets() - 1;
                    this->objectManager->setNumAsteroids(newAsteroidsAmount);
                    player->setNumBullets(newBulletsAmount);

                    delete temp1;
                    delete temp2;

                    break;
                }
                else {
                    fixCoord((*it1), (*it2), xyCentrVector);
                    calcVelocity((*it1), (*it2), xyCentrVector);
                }
            }
        }
    }
}