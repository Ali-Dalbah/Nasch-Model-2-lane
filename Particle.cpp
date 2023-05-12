#include "Particle.h"

int Particle::roadSize = 0;

Particle::Particle() {
    Particle::pos = 0;
    Particle::vel = 0;
}

Particle::Particle(int pos): Particle() {
    Particle::pos = pos;
}

Particle::~Particle() {

}

void Particle::move() {
    pos += vel;
    if (pos >= roadSize)
        pos -= roadSize;
}
