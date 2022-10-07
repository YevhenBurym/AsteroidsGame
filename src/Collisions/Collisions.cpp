//
// Created by Евгений on 12.07.2022.
//

#include "Collisions.h"

Collisions::Collisions(ObjectManager *asteroidsManager) {
    this->objectManager = asteroidsManager;
}

double Collisions::findVecAngleInRad(Vector2D vector) {
    double angle;
    if ((vector.getX() == 0) && (vector.getY() < 0)) {
        angle = -M_PI / 2;
    }
    else if ((vector.getX() == 0) && (vector.getY() > 0)) {
        angle = M_PI / 2;
    }
    else {
        angle = M_PI - atan2(vector.getY(), vector.getX());
    }
    return angle;
}

void Collisions::fixCoord(MovableGameObject* unit1, MovableGameObject* unit2, Vector2D vectorBetween) {
    Vector2D xyOffset = {0, 0 };
    Vector2D currXY1 = {unit1->getX(), unit1->getY()};
    Vector2D currXY2 = {unit2->getX(), unit2->getY()};
    Vector2D newXY1, newXY2;

    double alpha = this->findVecAngleInRad(vectorBetween);

    double minDist = unit1->getRadius() + unit2->getRadius();
    double segmentDist = vectorBetween.len() - minDist;

    xyOffset.setX(std::abs(segmentDist * cos(alpha)));
    xyOffset.setY(std::abs(segmentDist * sin(alpha)));

    if ((vectorBetween.getX() > 0) && (vectorBetween.getY() > 0)) {
        newXY1 = currXY1 + xyOffset;
        newXY2 = currXY2 - xyOffset;
    }
    else if ((vectorBetween.getX() < 0) && (vectorBetween.getY() > 0)) {
        newXY1.setX(currXY1.getX() - xyOffset.getX());
        newXY1.setY(currXY1.getY() + xyOffset.getY());
        newXY2.setX(currXY2.getX() + xyOffset.getX());
        newXY2.setY(currXY2.getY() - xyOffset.getY());
    }
    else if ((vectorBetween.getX() > 0) && (vectorBetween.getY() < 0)) {
        newXY1.setX(currXY1.getX() + xyOffset.getX());
        newXY1.setY(currXY1.getY() - xyOffset.getY());
        newXY2.setX(currXY2.getX() - xyOffset.getX());
        newXY2.setY(currXY2.getY() + xyOffset.getY());
    }
    else if ((vectorBetween.getX()  < 0) && (vectorBetween.getY() < 0)) {
        newXY1 = currXY1 - xyOffset;
        newXY2 = currXY2 + xyOffset;
    }
    else if ((vectorBetween.getX() == 0) && (vectorBetween.getY() > 0) ||
                (vectorBetween.getX() == 0) && (vectorBetween.getY() < 0)) {
        newXY1.setX(currXY1.getX());
        newXY1.setY(currXY1.getY() + xyOffset.getY());
        newXY2.setX(currXY2.getX());
        newXY2.setY(currXY2.getY() - xyOffset.getY());
    }
    else if ((vectorBetween.getX()  < 0) && (vectorBetween.getY() == 0) ||
                (vectorBetween.getX()  > 0) && (vectorBetween.getY() == 0)) {
        newXY1.setX(currXY1.getX() - xyOffset.getX());
        newXY1.setY(currXY1.getY());
        newXY2.setX(currXY2.getX() + xyOffset.getX());
        newXY2.setY(currXY2.getY());
    }
    unit1->setX(newXY1.getX());
    unit1->setY(newXY1.getY());
    unit2->setX(newXY2.getX());
    unit2->setY(newXY2.getY());
}

void Collisions::calcVelocity(MovableGameObject* unit1, MovableGameObject* unit2, Vector2D vectorBetween) {
    Vector2D Vxy1{0,0};
    Vector2D Vxy2{0,0};
    double m1 = unit1->getMass();
    double m2 = unit2->getMass();

    double alpha = this->findVecAngleInRad(vectorBetween);

    double Vcentr1 = unit1->getVxy().getX() * cos(alpha) - unit1->getVxy().getY() * sin(alpha);
    double Vcentr2 = unit2->getVxy().getX() * cos(alpha) - unit2->getVxy().getY() * sin(alpha);

    double newVcentr1 = (2 * m2 * Vcentr2 + (m1 - m2) * Vcentr1) / (m1 + m2);
    double newVcentr2 = (2 * m1 * Vcentr1 + (m2 - m1) * Vcentr2) / (m1 + m2);

    double Vtang1 = unit1->getVxy().getY() * cos(alpha) + unit1->getVxy().getX() * sin(alpha);
    double Vtang2 = unit2->getVxy().getY() * cos(alpha) + unit2->getVxy().getX() * sin(alpha);

    double V1 = sqrt(newVcentr1 * newVcentr1 + Vtang1 * Vtang1);
    double V2 = sqrt(newVcentr2 * newVcentr2 + Vtang2 * Vtang2);

    double phi1 = this->findVecAngleInRad({newVcentr1, Vtang1});
    double phi2 = this->findVecAngleInRad({newVcentr2, Vtang2});

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
            Vector2D xyCentrVector = xyCentr1 - xyCentr2;
            double minDist = (*it1)->getRadius() + (*it2)->getRadius();

            if (xyCentrVector.len() < minDist && xyCentrVector.len() > minDist / 2) {
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