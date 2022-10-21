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
    if (dynamic_cast<SpaceShip*>(unit2)) {
        xyOffset *= -1;
    }
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


    if (dynamic_cast<SpaceShip*>(unit2)) {
        Vxy1 *= -1;
        Vxy2 *= -1;
    }
    unit1->setVxy(Vxy1);
    unit2->setVxy(Vxy2);
}

void Collisions::update() {
    this->asteroidsCollisions();
    this->abilitiesCollisions();
}

void Collisions::asteroidsCollisions() {
    for (auto firstAsteroidIterator = this->objectManager->getAsteroids().begin(); firstAsteroidIterator != this->objectManager->getAsteroids().end(); ) {
        this->asteroidWithPlayerCollisions(*firstAsteroidIterator);
        this->asteroidWithReticleCollisions(*firstAsteroidIterator);

        for (auto secondAsteroidIterator = firstAsteroidIterator + 1; secondAsteroidIterator != this->objectManager->getAsteroids().end(); ++secondAsteroidIterator) {
            Vector2D vectorBetween = (*firstAsteroidIterator)->getXYrel() - (*secondAsteroidIterator)->getXYrel();
            double minDistance = (*firstAsteroidIterator)->getRadius() + (*secondAsteroidIterator)->getRadius();

            if ( vectorBetween.len() < minDistance ) {
                fixCoord((*firstAsteroidIterator), (*secondAsteroidIterator), vectorBetween);
                calcVelocity((*firstAsteroidIterator), (*secondAsteroidIterator), vectorBetween);
            }
        }

        this->asteroidWithBulletsCollisions(firstAsteroidIterator);

        if (firstAsteroidIterator != this->objectManager->getAsteroids().end()) {
            ++firstAsteroidIterator;
        }
    }
}

void Collisions::abilitiesCollisions() {
    for (auto abilityIter = this->objectManager->getBuffs().begin(); abilityIter < this->objectManager->getBuffs().end(); ++abilityIter) {
        double distance = (this->objectManager->getPlayer()->getXYrel() - (*abilityIter)->getXYrel()).len();
        double minDistance = this->objectManager->getPlayer()->getRadius() + (*abilityIter)->getRadius();
        if ( distance < minDistance ) {
            this->objectManager->getPlayer()->setAbility((*abilityIter)->getAbility());
            delete *abilityIter;
            abilityIter = this->objectManager->getBuffs().erase(abilityIter);
        }
    }
}

void Collisions::asteroidWithPlayerCollisions(Asteroid* asteroid) {
    Vector2D vectorBetween = this->objectManager->getPlayer()->getXYrel() - asteroid->getXYrel();
    double minDistance = this->objectManager->getPlayer()->getRadius() + asteroid->getRadius();

    if (this->objectManager->getPlayer()->getIsAutoShootOn()) {
        double minDistanceAutoShoot = this->objectManager->getPlayer()->getAutoShootRadius() + asteroid->getRadius();
        if (vectorBetween.len() < minDistanceAutoShoot) {
            this->objectManager->getPlayer()->autoShoot(asteroid);
        }
    }

    if ( vectorBetween.len() < minDistance ) {
        if (!this->objectManager->getPlayer()->getIsShieldOn()) {
            throw YouDied();
        }
        fixCoord(asteroid, this->objectManager->getPlayer(), vectorBetween);
        calcVelocity(asteroid, this->objectManager->getPlayer(), vectorBetween);
    }
}

void Collisions::asteroidWithReticleCollisions(Asteroid *asteroid) {
    if (this->objectManager->getPlayer()->getIsMissileOn()) {
        Vector2D vector = this->objectManager->getPlayer()->getReticle()->getXYrel() - asteroid->getXYrel();
        double minDistForDefinition = this->objectManager->getPlayer()->getReticle()->getRadius() + asteroid->getRadius();

        if (vector.len() < minDistForDefinition) {
            this->objectManager->getPlayer()->setTarget(asteroid);
        }
    }
}

void Collisions::asteroidWithBulletsCollisions(std::vector<Asteroid*>::iterator& asteroidIterator) {
    for (auto bulletIter = this->objectManager->getBullets().begin(); bulletIter != this->objectManager->getBullets().end(); ) {
        double distance = ((*bulletIter)->getXYrel() - (*asteroidIterator)->getXYrel()).len();
        double minDistance = (*bulletIter)->getRadius() + (*asteroidIterator)->getRadius();

        if ( distance < minDistance ) {
            int newAsteroidsAmount;
            auto bigAster = dynamic_cast<BigAsteroid *>(*asteroidIterator);
            if (bigAster) {
                bigAster->divide(this->objectManager->getAsteroids());
                newAsteroidsAmount = this->objectManager->getNumAsteroids() + 1;
                int newDestroyedBigAsteroidsAmount = this->objectManager->getDestroyedBigAsteroidsAmount() + 1;
                this->objectManager->setDestroyedBigAsteroidsAmount(newDestroyedBigAsteroidsAmount);
            } else {
                newAsteroidsAmount = this->objectManager->getNumAsteroids() - 1;
                int newDestroyedSmallAsteroidsAmount = this->objectManager->getDestroyedSmallAsteroidsAmount() + 1;
                this->objectManager->setDestroyedSmallAsteroidsAmount(newDestroyedSmallAsteroidsAmount);
            }

            (*asteroidIterator)->createAbility(this->objectManager->getBuffs());

            int newBulletsAmount = this->objectManager->getPlayer()->getNumBullets() - 1;
            this->objectManager->setNumAsteroids(newAsteroidsAmount);
            this->objectManager->getPlayer()->setNumBullets(newBulletsAmount);

            delete *asteroidIterator;
            delete *bulletIter;
            bulletIter = this->objectManager->getBullets().erase(bulletIter);
            asteroidIterator = this->objectManager->getAsteroids().erase(asteroidIterator);
            break;
        }
        ++bulletIter;
    }
}
