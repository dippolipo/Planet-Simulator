#include "Particle.hpp"

Particle::Particle() {
    name = "";
    mass = 0;
    radius = 0;
}

void Particle::update_pos(int& time) {
    v += (str / mass) * time;
    pos += v * time;
    str = Vector2D();
}