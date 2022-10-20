//
// Created by Евгений on 16.07.2022.
//

#include "SpaceShip.h"

void SpaceShip::limitateXY() {

    double x = this->xy.getX() + this->map->getXY().getX();
    double y = this->xy.getY() + this->map->getXY().getY();
    if (x >= this->map->getMaxCoord().getX()) {
        this->map->setX(this->map->getMinCoord().getX() - this->map->getXY().getX());
    } else if (x < this->map->getMinCoord().getX()) {
        this->map->setX(this->map->getMaxCoord().getX() + this->map->getXY().getX());
    }

    if (y >= this->map->getMaxCoord().getY()) {
        this->map->setY(this->map->getMinCoord().getY() - this->map->getXY().getY());
    } else if (y < this->map->getMinCoord().getY()) {
        this->map->setY(this->map->getMaxCoord().getY() + this->map->getXY().getY());
    }
}

SpaceShip::SpaceShip(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager,
                     int ammoLimit, Map *map, InputHandler *inputHandler, std::vector<GameObject *> *bullets)
        : GameObject(coord, Vxy, textureID, textureManager) {
    this->bulletsVelocity = 5;
    this->mass = 3;
    this->map = map;
    this->reticle = new Reticle("reticle", this->textureManager);
    this->angleShip = 0;
    this->ammoLimit = ammoLimit;
    this->numBullets = 0;
    this->inputHandler = inputHandler;
    this->bullets = bullets;
    this->buttonLeftPress = false;
    this->buttonRightPress = false;

    this->ability = NONE;

    this->isShieldON = false;
    this->isAutoShootON = false;
    this->isMissileON = false;
    this->abilityDuration = 10;
    this->target = nullptr;
    this->textureManager->getTextureSize("shield",this->widthShield, this->heightShield);
    this->widthShield *= 1.2;
    this->heightShield *= 1.2;
    if (this->widthShield % this->heightShield == this->widthShield) {
        this->shieldRadius = (this->heightShield - (this->heightShield % this->widthShield) / 2) / 2;
    } else {
        this->shieldRadius = (this->widthShield - (this->widthShield % this->heightShield) / 2) / 2;
    }
    this->autoShootRadius = this->radius * 5;
}

SpaceShip::~SpaceShip() {
    delete this->reticle;
}

Vector2D SpaceShip::getXYrel() const {
    return this->xy;
}

double SpaceShip::angleOnTarget(GameObject* inTarget) {
    double toDegrees = 180 / M_PI;
    double angle;
    Vector2D avatarXY = this->xy - this->map->getXY();
    Vector2D targetXY;
    if (dynamic_cast<Reticle*>(inTarget)) {
        targetXY = this->reticle->getXY() - this->map->getXY();
    } else {
        targetXY = inTarget->getXY();
    }
    Vector2D dirVector = avatarXY - targetXY;

    if ((dirVector.getX() == 0) && (dirVector.getY() < 0)) {
        angle = -M_PI / 2;
    } else if ((dirVector.getX() == 0) && (dirVector.getY() > 0)) {
        angle = M_PI / 2;
    } else {
        angle = M_PI - atan2(dirVector.getY(), dirVector.getX());
    }
    angle *= toDegrees;

    return angle;
}

void SpaceShip::makeShoot() {
    Vector2D avatarXY = this->xy - this->map->getXY();

    if (!this->target || !this->isMissileON) {
        if (this->numBullets < this->ammoLimit) {
            this->numBullets += 1;
            this->bullets->push_back(new Bullet(avatarXY, { this->bulletsVelocity * cos(this->angleShip * M_PI/ 180),-this->bulletsVelocity * sin(this->angleShip * M_PI/ 180)}, "bullet", this->textureManager, this->map));
        } else {
            delete *this->bullets->begin();
            this->bullets->erase(this->bullets->begin());
            this->bullets->push_back(new Bullet(avatarXY, { this->bulletsVelocity * cos(this->angleShip * M_PI/ 180),-this->bulletsVelocity * sin(this->angleShip * M_PI/ 180)}, "bullet", this->textureManager, this->map));
        }
        return;
    }

    double toRad = M_PI / 180;
    double angle = this->angleOnTarget(this->target);;

    this->endAbilityTimer = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = this->endAbilityTimer - this->startAbilityTimer;
    if (duration.count() >= this->abilityDuration) {
        this->isMissileON = false;
    }

    if (this->numBullets < this->ammoLimit) {
        this->numBullets += 1;
        this->bullets->push_back(
                new Missile(avatarXY, {this->bulletsVelocity * cos(angle * toRad),
                                       -this->bulletsVelocity * sin(angle * toRad)}, "missile",
                            this->textureManager, this->map, this->target, this));
    } else {
        delete *this->bullets->begin();
        this->bullets->erase(this->bullets->begin());
        this->bullets->push_back(
                new Missile(avatarXY, {this->bulletsVelocity * cos(angle * toRad),
                                       -this->bulletsVelocity * sin(angle * toRad)}, "missile",
                            this->textureManager, this->map, this->target, this));
    }
}

void SpaceShip::autoShoot(GameObject* inTarget) {
    if (!isAutoShootON) return;
    this->endAbilityTimer = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = this->endAbilityTimer - this->startAbilityTimer;
    if (duration.count() >= this->abilityDuration) {
        this->isAutoShootON = false;
        return;
    }

    double toRad = M_PI / 180;
    Vector2D avatarXY = this->xy - this->map->getXY();
    double angle = this->angleOnTarget(inTarget);;

    std::chrono::duration<double> rechargeDuration = this->endRechargeTimer - this->startRechargeTimer;
    if (rechargeDuration.count() < 0.5) return;
    this->startRechargeTimer = std::chrono::high_resolution_clock::now();

    if (this->numBullets < this->ammoLimit) {
        this->numBullets += 1;
        this->bullets->push_back(
                new Bullet(avatarXY, {this->bulletsVelocity * cos(angle * toRad), -this->bulletsVelocity * sin(angle * toRad)}, "bullet",
                           this->textureManager, this->map));
    } else {
        delete *this->bullets->begin();
        this->bullets->erase(this->bullets->begin());
        this->bullets->push_back(
                new Bullet(avatarXY, {this->bulletsVelocity * cos(angle * toRad), -this->bulletsVelocity * sin(angle * toRad)}, "bullet",
                           this->textureManager, this->map));
    }

}

Reticle *SpaceShip::getReticle() const {
    return this->reticle;
}

int SpaceShip::getNumBullets() const {
    return this->numBullets;
}

void SpaceShip::setNumBullets(int amount) {
    this->numBullets = amount;
}

void SpaceShip::setAbility(Ability newAbility) {
    this->ability = newAbility;
}

void SpaceShip::setVxy(Vector2D vxy) {
    this->map->setVxy(vxy);
}

Vector2D SpaceShip::getVxy() const {
    return this->map->getVxy();
}

void SpaceShip::update() {
    GameObject::update();
    limitateXY();

    this->reticle->setXY(this->inputHandler->getMousePosition());
    this->angleShip = this->angleOnTarget(this->reticle);

    if (this->inputHandler->getMouseButtonState(LEFT) && !this->buttonLeftPress) {
        this->buttonLeftPress = true;
        this->makeShoot();
    } else if (!this->inputHandler->getMouseButtonState(LEFT)) {
        this->buttonLeftPress = false;
    }

    if (this->inputHandler->getMouseButtonState(RIGHT) && !this->buttonRightPress) {
        this->buttonRightPress = true;
        this->useAbility();
    } else if (!this->inputHandler->getMouseButtonState(RIGHT)) {
        this->buttonRightPress = false;
    }
    this->endRechargeTimer = std::chrono::high_resolution_clock::now();
}

void SpaceShip::render() {

    if (this->isShieldON) {
        int x1 = this->xy.getX() - this->shieldRadius;
        int y1 = this->xy.getY() - this->shieldRadius;
        this->textureManager->draw("shield", x1, y1, this->widthShield, this->heightShield, 0);
        this->endAbilityTimer = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = this->endAbilityTimer - this->startAbilityTimer;
        if (duration.count() >= this->abilityDuration) {
            this->isShieldON = false;
        }
    }
    int x = this->xy.getX() - this->radius;
    int y = this->xy.getY() - this->radius;
    this->textureManager->draw(this->textureID, x, y, this->wSprite, this->hSprite, 90 - this->angleShip);

}

void SpaceShip::useAbility() {
    switch (this->ability) {
        case SHIELD:
            this->isShieldON = true;
            this->startAbilityTimer = std::chrono::high_resolution_clock::now();
            break;
        case MISSILE:
            this->isMissileON = true;
            this->startAbilityTimer = std::chrono::high_resolution_clock::now();
            break;
        case AUTOSHOOT:
            this->isAutoShootON = true;
            this->startAbilityTimer = std::chrono::high_resolution_clock::now();
            this->startRechargeTimer = std::chrono::high_resolution_clock::now();
            break;
        case NONE:
            break;
    }
    this->ability = NONE;
}

double SpaceShip::getRadius() const {
    if (this->isShieldON) {
        return this->shieldRadius;
    }
    return this->radius;
}

bool SpaceShip::getIsShieldOn() const {
    return this->isShieldON;
}

bool SpaceShip::getIsAutoShootOn() const {
    return this->isAutoShootON;
}

bool SpaceShip::getIsMissileOn() const {
    return this->isMissileON;
}

double SpaceShip::getAutoShootRadius() const {
    return this->autoShootRadius;
}

void SpaceShip::setTarget(GameObject* definedTarget) {
    if (!definedTarget) {
        this->target = nullptr;
    } else {
        this->target = definedTarget;
    }
}
