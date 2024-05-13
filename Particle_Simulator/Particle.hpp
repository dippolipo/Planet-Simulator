#pragma once
#include "Vector2D.hpp"

class Particle {
public:
    Vector2D pos = Vector2D();
    Vector2D v = Vector2D();
    Vector2D str = Vector2D();
    std::string name;
    double mass;
    double radius;

    Particle(std::string nameStr, Vector2D posVal, double mVal, double radiusVal) : name(nameStr), pos(posVal), mass(mVal), radius(radiusVal) {};
    Particle(std::string nameStr, Vector2D posVal, double mVal, double radiusVal, Vector2D vVal) : name(nameStr), pos(posVal), mass(mVal), radius(radiusVal), v(vVal) {};
    Particle();
    void update_pos(int& time);
};