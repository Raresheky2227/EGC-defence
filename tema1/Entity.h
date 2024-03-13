#pragma once
#include <string>

class Entity {
public:
    Entity(std::string type, int color, int isDying, int dir, int hp, float x, float y, float turretSpawnCycle, float hexDeathScaleFactor, float angularMotion);

    std::string getType() const;
    int getColor() const;
    int getIsDying() const;
    int getDirection() const;
    int getHP() const;
    float getX() const;
    float getY() const;
    float getTurretSpawnCycle() const;
    float getHexDeathScaleFactor() const;
    float getAngularMotion() const;

    void setType(std::string newType);
    void setColor(int newColor);
    void setIsDying(int newIsDying);
    void setDirection(int newDir);
    void setHP(int newHP);
    void setX(float newX);
    void setY(float newY);
    void setTurretSpawnCycle(float newTurretSpawnCycle);
    void setHexDeathScaleFactor(float newHexDeathSacleFactor);
    void setAngularMotion(float newAngularMotion);

private:
    std::string type;
    int color;
    int isDying;
    int dir;
    int hp;
    float x;
    float y;
    float turretSpawnCycle;
    float hexDeathScaleFactor;
    float angularMotion;
    std::string hexColor;
};



