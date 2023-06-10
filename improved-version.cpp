#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#define V_MAX 5

static const int l = 10000;
static float meanVTemp;
static unsigned long long int change = 0;

struct particle{
    int pos;
    int vel;
    particle(int pos, int vel): pos(pos), vel(vel) {}
    particle(const particle& p): pos(p.pos), vel(p.vel) {}
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
    inline int operator-(const particle& p) const {
        return pos - p.pos;
    }
    inline bool operator>(const particle& p) const {
        return pos > p.pos;
    }
    inline bool operator<(const particle& p) const {
        return pos < p.pos;
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
    int left = 0; int right = size;
    int middle;
    while (left < right) {
        middle = (right + left) / 2;
        if (road[middle].pos < goal) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left == size && road[left].pos < goal? 0: left;
}

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
        int gap = (thisRoad[(i + 1)%size] - p + l) % l - 1;
        if (gap < p.vel) {
            if (getRandom() < sw) {
                int x = getAheadParticle(p, otherRoad);
                int otherGap = x == -1? V_MAX: (otherRoad[x] - p + l) % l - 1;
                bool backWontSlow = x == -1 || x == 0 || ((otherRoad[(x - 1)].pos + otherRoad[(x - 1)].vel) % l ) < p.pos ;
                if (otherGap > gap && otherRoad.size() < l - 1 && backWontSlow) {
                    if (x == -1) otherRoad.emplace_back(particle(p));
                    else if (x == 0) {
                       if (otherRoad[0] > p) {
                        otherRoad.insert(otherRoad.begin(), particle(p));
                       }
                       else {
                        otherRoad.emplace_back(particle(p));
                       }
                    } else {
                        otherRoad.insert(otherRoad.begin() + x, particle(p));
                    }
                    thisRoad.erase(thisRoad.begin() + i);
                    change++;
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
    if (size > 1) {
        if (thisRoad[size - 1].pos < thisRoad[size - 2].pos) {
            thisRoad.insert(thisRoad.begin(), particle(thisRoad[size - 1]));
            thisRoad.pop_back();
        }
    }
    meanVTemp /= size;
}

void appendToFile(const char* name, const char* data) {
    FILE* file = fopen(name, "a");
    if (file == nullptr) return (void)(std::cout<<"couldn't open file "<<name<<std::endl);
    fprintf(file, "%s", data);
    fclose(file);
}

void start(const int n, const float sto, const float sw) {
    vector lane1, lane2;
    for (int i = 0; i < n; i++) {
        if (getRandom() < 0.5f && lane1.size() < l)
            lane1.emplace_back(particle(lane1.size(), 0));
        else
            lane2.emplace_back(particle(lane2.size(), 0));
    }
    const int simulationTime = 8000;
    float meanV1 = 0, meanO1 = 0, meanV2 = 0, meanO2 = 0;
    std::cout<<"-----\t start \t-----"<<std::endl;
    std::cout<<"n "<<n<<"\t p = "<<sto<<"\t sw = "<<sw<<std::endl;;
    int t = 0;
    while (t < simulationTime) {
        doOperations(lane1, lane2, sto, sw);
        meanV1 = meanVTemp;
        meanO1 = (float)(lane1.size()) / l;
        doOperations(lane2, lane1, sto, sw);
        meanV2 = meanVTemp;
        meanO2 = (float)(lane2.size()) / l;
        t++;
        if (!(t%1000)) {
            std::cout<<"\r"<<(float)(t)/simulationTime*100<<"%....";
            std::cout.flush();
        }
    }
    std::string str = "N = " + std::to_string(n) + "\t sto = " + std::to_string(sto) + "\t sw = " + std::to_string(sw);
    str += "\tMeanV1 = "+std::to_string(meanV1)+"\tMeanO1 = "+std::to_string(meanO1);
    str += "\tMeanV2 = "+std::to_string(meanV2)+"\tMeanO2 = "+std::to_string(meanO2)+"\n";
    appendToFile("data.txt", str.c_str());
}


int main(int argc, char **argv) {
    std::srand(time(nullptr));
    int n = argc == 2? std::stoi(argv[1]): 5;
    for (n; n < l*3/4; n+=100) {
        start(n, 0.3f, 0.f);
        start(n, 0.3f, 1.f);
    }
}
