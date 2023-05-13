#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#define V_MAX 5

static const int l = 50000;
static float meanVTemp;

struct particle{
    int pos;
    int vel;
    particle(int pos, int vel): pos(pos), vel(vel) {}
    particle(const particle& p): pos(p.pos), vel(p.pos) {}
    inline void move() {
        pos = (pos + vel) % l;
    }
    inline void accelarate() {
        vel++;
        if (vel > V_MAX) vel = V_MAX;
    }
    inline void deaccelarate() {
        if (vel > 0) vel--;
    }
};

typedef std::vector<particle> vector;

float getRandom() {
    return (float)(std::rand()) / RAND_MAX;
}

int getAheadParticle(const particle& p, const vector& road) {
    const int goal = p.pos;
    const int size = road.size();
    if (size == 0) return -1;
    int left = 0; int right = size - 1;
    int middle;
    while (left < right) {
        middle = (right + left) / 2;
        if (road[middle].pos <= goal) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}
// gap = ((i+1).pos - (i).pos - 1 + l)%l
void doOperations(vector& thisRoad, vector& otherRoad, const float sto, const float sw) {
    int size = thisRoad.size();
    if (size == 0) {
        meanVTemp = V_MAX;
        return ;
    }
    meanVTemp = 0;
    for (int i = 0; i < size; i++) {
        particle& p = thisRoad[i];
        p.accelarate();
        int gap = (thisRoad[(i + 1)%l].pos - p.pos - 1 + l) % l;
        if (gap < p.vel) {
            if (getRandom() < sw) {
                //std::cout<<"x"<<std::endl;
                int x = getAheadParticle(p, otherRoad);
                int otherGap = x == -1? V_MAX: (otherRoad[x].pos - p.pos - 1 + l) % l;
                if (otherGap > gap) {
                    if (x == -1) otherRoad.emplace_back(particle(p));
                    else if (x == 0) {
                        if (otherRoad[0].pos > p.pos) otherRoad.insert(otherRoad.begin(), particle(p));
                        else otherRoad.emplace_back(particle(p));
                    } else {
                        otherRoad.insert(otherRoad.begin() + x, particle(p));
                    }
                    thisRoad.erase(thisRoad.begin() + i);
                    //std::cout<<"switch"<<std::endl;
                    i--;
                    size--;
                    continue;
                }
            }
            p.vel = gap;
        }
        if (getRandom() < sto) p.deaccelarate();
        meanVTemp += p.vel;
        p.move();
        if (p.vel > V_MAX)
            std::cout<<p.vel<<std::endl;
    }
    meanVTemp /= size;
    //std::cout<<meanVTemp<<std::endl;
}

void appendToFile(const char* name, const char* data) {
    FILE* file = fopen(name, "a");
    if (file == nullptr) return (void)(std::cout<<"couldn't open file "<<name<<std::endl);
    fprintf(file, "%s", data);
    fclose(file);
}

void start(const int n, const float sto, const float sw) {
    vector lane1, lane2;
    int X = 0, Y = 0;
    for (int i = 0; i < n; i++) {
        lane1.emplace_back(particle(X++, 0));
        lane2.emplace_back(particle(Y++, 0));
    }
    const int simulationTime = 4000;
    float meanV1 = 0, meanO1 = 0, meanV2 = 0, meanO2 = 0;
    int t = 0;
    while (t < simulationTime) {
        doOperations(lane1, lane2, sto, sw);
        meanV1 = (meanVTemp + meanV1 * t) / (t + 1);
        meanO1 = ((float)(lane1.size()) / l + meanO1 * t) / (t + 1);
        doOperations(lane2, lane1, sto, sw);
        meanV2 = (meanVTemp + meanV2 * t) / (t + 1);
        meanO2 = ((float)(lane2.size()) / l + meanO2 * t) / (t + 1);
        t++;
    }
    std::string str = "----- Summary -----";
    str += "\nN = " + std::to_string(n) + "\t sto = " + std::to_string(sto) + "\t sw = " + std::to_string(sw);
    str += "\nMeanV1 "+std::to_string(meanV1)+"\tMeanO1 "+std::to_string(meanO1);
    str += "\nMeanV2 "+std::to_string(meanV2)+"\tMeanO2 "+std::to_string(meanO2)+"\n";
    appendToFile("data.txt", str.c_str());
}


int main(int argc, char **argv) {
    std::srand(time(nullptr));
    for (int n = 10; n < l; n+=20) {
        start(n, 0.f, 0.5f);
        start(n, 0.2f, 0.5f);
    }
}
