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
    } else if ((vector.getX() == 0) && (vector.getY() > 0)) {
        angle = M_PI / 2;
    } else {
        angle = M_PI - atan2(vector.getY(), vector.getX());
    }
    return angle;
}

void Collisions::fixCoord(GameObject *unit1, GameObject *unit2, Vector2D vectorBetween) {
    Vector2D xyOffset = {0, 0};
    Vector2D newXY1, newXY2;

    double alpha = this->findVecAngleInRad(vectorBetween);

    double minDist = unit1->getRadius() + unit2->getRadius();
    double segmentDist = vectorBetween.len() - minDist;

    xyOffset.setX(std::abs(segmentDist * cos(alpha)));
    xyOffset.setY(std::abs(segmentDist * sin(alpha)));

    if ((vectorBetween.getX() > 0) && (vectorBetween.getY() > 0)) {
        newXY1 = unit1->getXY() + xyOffset;
        newXY2 = unit2->getXY() - xyOffset;
    } else if ((vectorBetween.getX() < 0) && (vectorBetween.getY() > 0)) {
        newXY1.setX(unit1->getXY().getX() - xyOffset.getX());
        newXY1.setY(unit1->getXY().getY() + xyOffset.getY());
        newXY2.setX(unit2->getXY().getX() + xyOffset.getX());
        newXY2.setY(unit2->getXY().getY() - xyOffset.getY());
    } else if ((vectorBetween.getX() > 0) && (vectorBetween.getY() < 0)) {
        newXY1.setX(unit1->getXY().getX() + xyOffset.getX());
        newXY1.setY(unit1->getXY().getY() - xyOffset.getY());
        newXY2.setX(unit2->getXY().getX() - xyOffset.getX());
        newXY2.setY(unit2->getXY().getY() + xyOffset.getY());
    } else if ((vectorBetween.getX() < 0) && (vectorBetween.getY() < 0)) {
        newXY1 = unit1->getXY() - xyOffset;
        newXY2 = unit2->getXY() + xyOffset;
    } else if ((vectorBetween.getX() == 0) && (vectorBetween.getY() > 0) ||
               (vectorBetween.getX() == 0) && (vectorBetween.getY() < 0)) {
        newXY1.setX(unit1->getXY().getX());
        newXY1.setY(unit1->getXY().getY() + xyOffset.getY());
        newXY2.setX(unit2->getXY().getX());
        newXY2.setY(unit2->getXY().getY() - xyOffset.getY());
    } else if ((vectorBetween.getX() < 0) && (vectorBetween.getY() == 0) ||
               (vectorBetween.getX() > 0) && (vectorBetween.getY() == 0)) {
        newXY1.setX(unit1->getXY().getX() - xyOffset.getX());
        newXY1.setY(unit1->getXY().getY());
        newXY2.setX(unit2->getXY().getX() + xyOffset.getX());
        newXY2.setY(unit2->getXY().getY());
    }
    unit1->setXY(newXY1);
    unit2->setXY(newXY2);
}

void Collisions::calcVelocity(GameObject *unit1, GameObject *unit2, Vector2D vectorBetween) {
    Vector2D Vxy1{0, 0};
    Vector2D Vxy2{0, 0};
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
    for (auto asterIter = this->objectManager->getAsteroids().begin(); asterIter != this->objectManager->getAsteroids().end(); ++asterIter) {
        double distance = (this->objectManager->getPlayer()->getXYrel() - (*asterIter)->getXYrel()).len();
        double minDistance = this->objectManager->getPlayer()->getRadius() + (*asterIter)->getRadius();

        if ( distance < minDistance ) {
            throw YouDied();
        }

        for (auto asterIter2 = asterIter + 1; asterIter2 != this->objectManager->getAsteroids().end(); ++asterIter2) {
            Vector2D vectorBetween = (*asterIter)->getXYrel() - (*asterIter2)->getXYrel();
            minDistance = (*asterIter)->getRadius() + (*asterIter2)->getRadius();

            if ( vectorBetween.len() < minDistance ) {
                fixCoord((*asterIter), (*asterIter2), vectorBetween);
                calcVelocity((*asterIter), (*asterIter2), vectorBetween);
            }
        }

        for (auto bulletIter = this->objectManager->getBullets().begin(); bulletIter != this->objectManager->getBullets().end(); ++bulletIter) {
            distance = ((*bulletIter)->getXYrel() - (*asterIter)->getXYrel()).len();
            minDistance = (*bulletIter)->getRadius() + (*asterIter)->getRadius();

            if ( distance < minDistance ) {
                auto bigAster = dynamic_cast<BigAsteroid *>(*asterIter);
                if (bigAster) {
                    GameObject *temp1 = (*bulletIter);
                    GameObject *temp2 = (*asterIter);
                    auto iter1 = bulletIter - 1;
                    auto iter2 = asterIter - 1;
                    asterIter = this->objectManager->getAsteroids().erase(asterIter);
                    bulletIter = this->objectManager->getBullets().erase(bulletIter);
                    bulletIter = iter1;
                    asterIter = iter2;

                    bigAster->divide(this->objectManager->getAsteroids());

                    delete temp1;
                    delete temp2;

                    int newAsteroidsAmount = this->objectManager->getNumAsteroids() + 1;
                    int newBulletsAmount = this->objectManager->getPlayer()->getNumBullets() - 1;
                    this->objectManager->setNumAsteroids(newAsteroidsAmount);
                    this->objectManager->getPlayer()->setNumBullets(newBulletsAmount);
                    break;
                }

                auto smallAster = dynamic_cast<SmallAsteroid *>(*asterIter);
                smallAster->createAbility(this->objectManager->getBuffs());

                GameObject *temp1 = (*bulletIter);
                GameObject *temp2 = (*asterIter);
                asterIter = this->objectManager->getAsteroids().erase(asterIter);
                asterIter--;
                bulletIter = this->objectManager->getBullets().erase(bulletIter);
                bulletIter--;
                delete temp1;
                delete temp2;
                int newAsteroidsAmount = this->objectManager->getNumAsteroids() - 1;
                int newBulletsAmount = this->objectManager->getPlayer()->getNumBullets() - 1;
                this->objectManager->setNumAsteroids(newAsteroidsAmount);
                this->objectManager->getPlayer()->setNumBullets(newBulletsAmount);
                break;
            }
        }
    }
}