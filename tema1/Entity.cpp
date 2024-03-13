#include "Entity.h"

Entity::Entity(std::string type, int color, int isDying, int dir, int hp, float x, float y, float turretSpawnCycle, float hexDeathScaleFactor, float angularMotion)
    : type(type), color(color), isDying(isDying), dir(dir), hp(hp), x(x), y(y),turretSpawnCycle(turretSpawnCycle), hexDeathScaleFactor(hexDeathScaleFactor), angularMotion(angularMotion) {
}

std::string Entity::getType() const {
    return type;
}

int Entity::getColor() const {
    return color;
}

int Entity::getIsDying() const {
    return isDying;
}

int Entity::getDirection() const {
    return dir;
}

int Entity::getHP() const {
    return hp;
}

float Entity::getX() const {
    return x;
}

float Entity::getY() const {
    return y;
}

float Entity::getTurretSpawnCycle() const {
    return turretSpawnCycle;
}

float Entity::getHexDeathScaleFactor() const { 
    return hexDeathScaleFactor;
}

float Entity::getAngularMotion() const {
    return angularMotion;
}


void Entity::setType(std::string newType) {
    type = newType;
}

void Entity::setColor(int newColor) {
    color = newColor;
}

void Entity::setIsDying(int newIsDying) {
    isDying = newIsDying;
}

void Entity::setDirection(int newDir) {
    dir = newDir;
}

void Entity::setHP(int newHP) {
    hp = newHP;
}

void Entity::setX(float newX) {
    x = newX;
}

void Entity::setY(float newY) {
    y = newY;
}

void Entity::setTurretSpawnCycle(float newTurretSpawnCycle) {
    turretSpawnCycle = newTurretSpawnCycle;
}
void Entity::setHexDeathScaleFactor(float newHexDeathSacleFactor) {
    hexDeathScaleFactor = newHexDeathSacleFactor;
}

void Entity::setAngularMotion(float newAngularMotion) {
    angularMotion = newAngularMotion;
}
