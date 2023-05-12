#ifndef PARTICLE_H
#define PARTICLE_H
#define V_MAX 5

class Particle {
public:
    // l for moving
    static int roadSize;
    // Constructors
    Particle();
    Particle(int);
    ~Particle();
    // velocity
    int vel;
    // position
    int pos;
    // updating position
    void move(void);
};

// Struct for Sorting
struct compare {
    inline bool operator()(const Particle& x, const Particle& y) const {
        return x.pos < y.pos;
    }
};

#endif
