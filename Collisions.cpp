//
// Created by Евгений on 12.07.2022.
//

#include "Collisions.h"

void Collisions::fixCoord(GameObject* unit1, GameObject* unit2, CoordXY vectorBetween) {
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
        alpha = -M_PI / 2;
    }
    else if ((vectorBetween.x == 0) && (vectorBetween.y > 0)) {
        alpha = M_PI / 2;
    }
    else {
        alpha = M_PI - atan2(vectorBetween.y, vectorBetween.x);
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

void Collisions::calcVelocity(GameObject* unit1, GameObject* unit2, CoordXY vectorBetween) {
    double alpha = 0;
    double phi1 = 0;
    double phi2 = 0;
    double Vcentr1, Vcentr2, newVcentr1, newVcentr2;
    double Vtang1, Vtang2;
    double V1, V2, Vx1, Vy1, Vx2, Vy2;
    double m1 = unit1->getMass();
    double m2 = unit2->getMass();

    if ((vectorBetween.x == 0) && (vectorBetween.y < 0)) {
        alpha = -M_PI / 2;
    }
    else if ((vectorBetween.x == 0) && (vectorBetween.y > 0)) {
        alpha = M_PI / 2;
    }
    else {
        alpha = M_PI - atan2(vectorBetween.y, vectorBetween.x);
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

    Vx1 = V1 * sin(phi1) * sin(alpha) - V1 * cos(phi1) * cos(alpha);
    Vy1 = V1 * sin(phi1) * cos(alpha) + V1 * cos(phi1) * sin(alpha);
    Vx2 = V2 * sin(phi2) * sin(alpha) - V2 * cos(phi2) * cos(alpha);
    Vy2 = V2 * sin(phi2) * cos(alpha) + V2 * cos(phi2) * sin(alpha);

    unit1->setVx(Vx1);
    unit1->setVy(Vy1);
    unit2->setVx(Vx2);
    unit2->setVy(Vy2);
}

void Collisions::check() {
    for (auto it1 = this->game->getObjects().begin(); it1 != this->game->getObjects().end(); ++it1) {
        for (auto it2 = it1 + 1; it2 != this->game->getObjects().end(); ++it2) {

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
                    it2 = this->game->getObjects().erase(it2);
                    it2--;
                    it1 = this->game->getObjects().erase(it1);
                    it1--;
                    delete temp1;
                    delete temp2;
                    int newAsteroidsAmount = this->game->getAsterManager()->getNumAsteroids() - 1;
                    int newBulletsAmount = this->game->getAvatar()->getNumBullets() - 1;
                    this->game->getAsterManager()->setNumAsteroids(newAsteroidsAmount);
                    this->game->getAvatar()->setNumBullets(newBulletsAmount);

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
                    auto iter1 = it1-1;
                    auto iter2 = it2-1;
                    it2 = this->game->getObjects().erase(it2);
                    it1 = this->game->getObjects().erase(it1);
                    it1 = iter1;
                    it2 = iter2;

                    bigAster->divide(this->game->getObjects());

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

Collisions::Collisions(Game *game) {
    this->game = game;
}
