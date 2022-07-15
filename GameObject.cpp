#include "GameObject.h"
#include <cmath>

void GameObject::limitateCoord() {
    double minXCoord = 0 - map->getMapOffsetCoord().x;
    double maxXCoord = map->getWMap() - map->getMapOffsetCoord().x;
    double minYCoord = 0 - map->getMapOffsetCoord().y;
    double maxYCoord = map->getHMap() - map->getMapOffsetCoord().y;

    if (this->coord.x >= maxXCoord) {
        this->coord.x = minXCoord;
    } else if (this->coord.x < minXCoord) {
        this->coord.x = maxXCoord;
    }

    if (this->coord.y >= maxYCoord) {
        this->coord.y = minYCoord;
    } else	if (this->coord.y < minYCoord) {
        this->coord.y = maxYCoord;
    }

}

GameObject::GameObject(Vector2D coord, double velocity, double theta, Sprite* sprite, Map* map) {
    int wSprite, hSprite;
    double d = 0;
    //theta *= -1;
    sprite->getSize(wSprite,hSprite);

    if (wSprite % hSprite == wSprite) {
        d = hSprite - (hSprite % wSprite) / 2;
    } else {
        d = wSprite - (wSprite % hSprite) / 2;
    }
    this->map = map;
    this->radius = d / 2;
    this->coord = coord;
    this->Vxy.x = velocity * cos(theta * RAD);
    this->Vxy.y = -velocity * sin(theta * RAD);
    this->sprite = sprite;
    this->mass = 1;
    this->V.v = velocity;
    this->V.theta = theta;
    this->xOf = 0;
    this->yOf = 0;
}

void GameObject::calcCoord(Vector2D Vxy, double step) {
    this->coord.x += Vxy.x * step;
    this->coord.y += Vxy.y * step;
    this->limitateCoord();

}

void GameObject::setX(double x) {
    this->coord.x = x;
}
void GameObject::setY(double y) {
    this->coord.y = y;
}

void GameObject::setXof(double x){
    this->xOf = x;
}

void GameObject::setYof(double y) {
    this->yOf = y;
}

void GameObject::setVxy(Vector2D vxy) {
    this->Vxy = vxy;
}

void GameObject::setV(double v, double theta) {
    this->V.v = v;
    this->V.theta = theta;
    this->Vxy.x = v * cos(theta * RAD);
    this->Vxy.y = -v * sin(theta * RAD);
}

double GameObject::getX() const {
    return this->coord.x;
}

double GameObject::getY() const {
    return this->coord.y;
}

double GameObject::getXrel() const {
    return this->coord.x + this->xOf;
}
double GameObject::getYrel() const {
    return this->coord.y + this->yOf;
}

Vector2D GameObject::getVxy() const {
    return this->Vxy;
}

Velocity GameObject::getV() const {
    return this->V;
}

double GameObject::getMass() const {
    return this->mass;
}

double GameObject::getRadius() const {
    return this->radius;
}

void GameObject::render() const {

    int x = this->coord.x + this->xOf - this->radius;
    int y = this->coord.y + this->yOf - this->radius;

    this->sprite->draw(x, y);
}

SmallAsteroid::SmallAsteroid(Vector2D coord, int velocity, int theta, Sprite* sprite, Map* map) : GameObject(coord, velocity, theta, sprite, map) {
    this->mass = 1;
}

BigAsteroid::BigAsteroid(Vector2D coord, int velocity, int theta, Sprite* sprite, Map* map) : GameObject(coord, velocity, theta, sprite, map) {
    this->mass = 2;
}

void BigAsteroid::divide(std::vector<GameObject*>& objects) {
    int x = 0, y = 0, r = 0;
    Velocity v = { 0,0 };

    x = this->getXrel();
    y = this->getYrel();
    Vector2D xy1;
    Vector2D xy2;
    xy1.x= x + this->radius;
    xy1.y= y + this->radius;
    xy2.x= x - this->radius;
    xy2.y= y - this->radius;

    objects.push_back(new SmallAsteroid(xy1, this->V.v, this->V.theta - 45, this->map->getUnitSprites().smallAsteroidSprite, this->map));
    objects.push_back(new SmallAsteroid(xy2, this->V.v, this->V.theta + 45, this->map->getUnitSprites().smallAsteroidSprite, this->map));
}

void Avatar::limitateCoord() {
    double minXCoord = 0 - this->map->getMapOffsetCoord().x;
    double maxXCoord = this->map->getWMap() - this->map->getMapOffsetCoord().x;
    double minYCoord = 0 - this->map->getMapOffsetCoord().y;
    double maxYCoord = this->map->getHMap() - this->map->getMapOffsetCoord().y;
    double x = this->coord.x + this->xOf;
    double y = this->coord.y + this->yOf;

    if (x >= maxXCoord) {
        this->map->setX(minXCoord - this->map->getX());
//        std::cout <<"Map XY offset "<< this->map->getMapOffsetCoord().x << ", " <<  this->map->getMapOffsetCoord().y << std::endl;
//        std::cout <<"MaxCoordX "<< maxXCoord << std::endl;
//        std::cout <<"Coords "<< x << ", " <<  y<< std::endl;
    }
    else if (x < minXCoord) {
        this->map->setX(maxXCoord + this->map->getX());
//        std::cout <<"Map XY offset "<< this->map->getMapOffsetCoord().x << ", " <<  this->map->getMapOffsetCoord().y << std::endl;
//        std::cout <<"MinCoordX "<< minXCoord << std::endl;
//        std::cout <<"Coords "<< x << ", " <<  y<< std::endl;
    }

    if (y >= maxYCoord) {
        this->map->setY(minYCoord - this->map->getY());
//        std::cout <<"Map XY offset "<< this->map->getMapOffsetCoord().x << ", " <<  this->map->getMapOffsetCoord().y << std::endl;
//        std::cout <<"MaxCoordY "<< maxYCoord << std::endl;
//        std::cout <<"Coords "<< x << ", " <<  y<< std::endl;
    }
    else if (y < minYCoord) {
        this->map->setY(maxYCoord + this->map->getY());
//        std::cout <<"Map XY offset "<< this->map->getMapOffsetCoord().x << ", " <<  this->map->getMapOffsetCoord().y << std::endl;
//        std::cout <<"MinCoordY "<< minYCoord << std::endl;
//        std::cout <<"Coords "<< x << ", " <<  y<< std::endl;
    }
    //std::cout <<"MaxCoordY"<< x << ", " <<  y<< std::endl;
}

Avatar::Avatar(Vector2D coord, int velocity, int theta, Sprite* sprite, int ammoLimit, Map* map) : GameObject(coord, velocity, theta, sprite, map) {
    this->reticle = new Reticle( map->getUnitSprites().reticleSprite, map );
    this->angleShip = 0;
    this->ammoLimit = ammoLimit;
    this->numBullets = 0;
}
Avatar::~Avatar() {
    delete this->reticle;
}

double Avatar::getXrel() const {
    return this->coord.x;
}

double Avatar::getYrel() const {
    return this->coord.y;
}


void Avatar::shipHeadAngle() {
    int xAvatar = this->coord.x;
    int yAvatar = this->coord.y;
    double xRet = this->reticle->getX();
    double yRet = this->reticle->getY();
    if (this->map->getV().v > 0) {
        xAvatar -= this->map->getX();
        yAvatar -= this->map->getY();
        xRet -= this->map->getX();
        yRet -= this->map->getY();
    }
    double alpha = 0;
    Vector2D xyDirVector = {xAvatar - xRet, yAvatar - yRet };
    double dist = hypot(xyDirVector.x, xyDirVector.y) ;

    if ((xyDirVector.x == 0) && (xyDirVector.y < 0)) {
        alpha = -M_PI / 2;
    } else if ((xyDirVector.x == 0) && (xyDirVector.y > 0)) {
        alpha = M_PI / 2;
    } else {
        alpha = M_PI - atan2(xyDirVector.y, xyDirVector.x);
    }
    alpha = alpha * 180 / M_PI;
    this->angleShip = alpha; // для розрахунку направлення корабля
}

void Avatar::makeShoot(std::vector<GameObject*>& objects) {
    Vector2D avatarCoord{this->coord.x, this->coord.y};
    this->shipHeadAngle();
    if (this->map->getV().v > 0) {
        avatarCoord.x -= this->map->getX();
        avatarCoord.y -= this->map->getY();
    }
    if (this->numBullets < this->ammoLimit) {
         this->numBullets += 1;
         objects.push_back(new Bullet(avatarCoord, 800, this->angleShip, this->map->getUnitSprites().bulletSprite, this->map));
    } else {
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            if (dynamic_cast<Bullet*>(*it)) {
                delete (*it);
                objects.erase(it);
                objects.push_back(new Bullet(avatarCoord, 800, this->angleShip, this->map->getUnitSprites().bulletSprite, this->map));
                return;
            }
        }
    }
}


Reticle *Avatar::getReticle() const {
    return this->reticle;
}

void Avatar::render() const {
    int x = this->coord.x - this->radius;
    int y = this->coord.y - this->radius;

    this->sprite->draw(x, y,90 - this->angleShip);
}

int Avatar::getNumBullets() const {
    return this->numBullets;
}

void Avatar::setNumBullets(int amount) {
    this->numBullets = amount;
}


Bullet::Bullet(Vector2D coord, int velocity, int theta, Sprite* sprite, Map* map) : GameObject(coord, velocity, theta, sprite, map) {
}

Reticle::Reticle(Sprite *sprite, Map *map): GameObject(Vector2D{0, 0}, 0, 0, sprite, map) {
    int wSprite, hSprite;
    this->sprite->getSize(wSprite, hSprite);
    this->xOf = wSprite / 2;
    this->yOf = hSprite / 2;
}

void Reticle::render() const {
    int x = this->coord.x - this->xOf;
    int y = this->coord.y - this->yOf;
    this->sprite->draw(x,y);
}
