#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Particle.h"
#include <vector>
#include <bits/stdc++.h>
/*
 * Function Name: appendToFile
 * Args: 
 ** fileName (string): name of the file
 ** data (string): to append
 * Description: Appends data to the file given 
*/
inline void appendToFile(const char*, const char*);

/*
 * Function Name: mean
 * Args: 
 ** arr (float[]): array to calculate its mean
 ** size (int): size of array
 * Description: Calculates the mean of a float array
*/
float mean(float*, int);

/*
 * Function Name: mean
 * Args:
 ** vector (std::vector<Particle>): vector to which the mean is caluclated
 * Description: Calculates the Mean of velocities for a vector of particles
*/
float mean(std::vector<Particle>&);

/*
 * Function Name: getRandom
 * Args:
 ** None
 * Description: gets a random number between 0 and 1
*/
inline float getRandom();

/*
 * Function Name: accelarate
 * Args:
 ** vector (std::vector<Particle>)
 * Description: adds 1 to every particle velocity if it have a velocity less than V_MAX
*/
void accelarate(std::vector<Particle>&, std::vector<Particle>&);

/*
 * Function Name: deaccelarationAndSwitching
 * Args:
 ** thisRoad (std::vector<Particle>): the road to deaccelarate
 ** otherRoad (std::vector<Particle>): the other road which some particles may switch to
 * Description: Deaccelarte the particles and may switch particle road if the gap is less than its velocity & the other road have a higher gap
*/
void deaccelarationAndSwitching(std::vector<Particle>&, std::vector<Particle>&, int , bool);

/*
 * Function Name: nextRoadHeadWay
 * Args:
 ** p (Particle): the particle to witch the head way is calculated
 ** otherRoad (std::vector<Particle>): the other road
 ** l (int): road length
 * Desciption: returns the index of particle in the other roaed that is straight ahead of p 
*/
int nextRoadHeadWay(Particle&, std::vector<Particle>&, int l);

/*
 * Function Name: randomBraking
 * Args:
 ** vector (std::vector<Particle>): the vector to random brake its particles
 ** sto (float): stochasisity parameter
 * Desciption: decrements the velocity of some particles by 1 if it has velocity more than 0
*/
void randomBraking(std::vector<Particle>&, float);

/*
 * Function Name: move
 * Args:
 ** vector (std::vector<Particle>): the vector to which its particles positions will be updated
 * Desciption: Updates the position of particles
*/
void move(std::vector<Particle>&, std::vector<Particle>&);

/*
 * Function Name: start
 * Args:
 ** n (int): number of particles
 ** l (int): length of each road
 ** sto (float): stochasisity
 ** simulationTime (int): simulation time
 * Desciption: starts the simulation of particles for the given time then prints a report to the command line and to a file called Nasch_Report
*/
void start(int, int, float, int);


int main(int argc, char** argv) {
    if (argc > 2) return -1;
    std::srand(time(NULL));
    int simulationTime = argc == 1? 4000: std::stoi(argv[1]);
    int n = 4750, l = 50000;
    while (n < l) {
        start(n, l, 0.f, simulationTime);
        start(n, l, 0.2f, simulationTime);
        n += 10;
    }
}

void start(int n, int l, float sto, int simulationTime) {
    if (n < 1 || n > l) return void(std::cout<<"Invalid N or L"<<std::endl);
    float velocityMeanOne[simulationTime];
    float velocityMeanTwo[simulationTime];
    float occupancyMeanOne[simulationTime];
    float occupancyMeanTwo[simulationTime];
    int t = 0;
    // Initialization
    std::vector<Particle> roadOne;
    std::vector<Particle> roadTwo;
    Particle::roadSize = l;
    int i1 = 0, i2 = 0;
    while (t < n) {
        float rand = getRandom();
        if (rand > 0.5f && i1 < l || i2 >= l)
            roadOne.push_back(Particle(i1++));
        else 
            roadTwo.push_back(Particle(i2++));
        t++;
    }
    // Begining of Simulation
    t = 0;
    while (t < simulationTime) {
		if (roadOne.size() > roadTwo.size())
			accelarate(roadOne, roadTwo);	
		else 
			accelarate(roadTwo, roadOne);
        deaccelarationAndSwitching(roadOne, roadTwo, l, true);
        randomBraking(roadOne, sto);
        std::sort(roadTwo.begin(), roadTwo.end(), compare());
        deaccelarationAndSwitching(roadTwo, roadOne, l, true);
        randomBraking(roadTwo, sto);
		if (roadOne.size() > roadTwo.size())
			move(roadOne, roadTwo);	
		else 
			move(roadTwo, roadOne);
        std::sort(roadOne.begin(), roadOne.end(), compare());
        std::sort(roadTwo.begin(), roadTwo.end(), compare());
        velocityMeanOne[t] = mean(roadOne);
        velocityMeanTwo[t] = mean(roadTwo);
        occupancyMeanOne[t] = (float)roadOne.size() / l;
        occupancyMeanTwo[t] = (float)roadTwo.size() / l;
        t++;
    }
    float vel1 = mean(velocityMeanOne, simulationTime);
    float vel2 = mean(velocityMeanTwo, simulationTime);
    float occ1  = mean(occupancyMeanOne, simulationTime);
    float occ2  = mean(occupancyMeanTwo, simulationTime);
    std::string report = "Summary Report for N: " + std::to_string(n) + ", L: " + std::to_string(l) + ", sto: " + std::to_string(sto);
    report += "\nRoad One:\n\t Occupancy Mean: " + std::to_string(occ1) + "\n\t Velocity Mean: " + std::to_string(vel1);
    report += "\nRoad Two:\n\t Occupancy Mean: " + std::to_string(occ2) + "\n\t Velocity Mean: " + std::to_string(vel2);
    report += "\nBoth Occupancy\n\t Occupancy Mean: " + std::to_string((occ1 + occ2)/2) + "\n\t Velocity Mean: " + std::to_string((vel1 + vel2)/2);
    report += "\n-----------------------------------------------";
    std::cout<<report<<std::endl;
    appendToFile("Nasch_Report.txt", report.c_str());
}

inline void appendToFile(const char* fileName, const char* data) {
    FILE* file = fopen(fileName, "a");
    if (file == NULL)
        return void(std::cout<<"couldnt open file "<<fileName<<std::endl);
    fprintf(file, "\n%s", data);
    fclose(file);
}

float mean(float* arr, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum / size;
}

float mean(std::vector<Particle>& vector) {
    int size = vector.size();
    if (size == 0) return 0;
    float sum = 0;
    for (int i = 0; i < size; i++) 
        sum += vector[i].vel;
    return sum / size;
}

inline float getRandom() {
    return (float)(std::rand()) / RAND_MAX;
}

void accelarate(std::vector<Particle>& one, std::vector<Particle>& two) {
	int max = one.size();
	int min = two.size();
	int i = 0;
	while (i < min) {
		if (one[i].vel < V_MAX)
			one[i].vel++;
		if (two[i].vel < V_MAX)
			two[i].vel++;
		i++;
	}
	while (i < max) {
		if (one[i].vel < V_MAX)
			one[i].vel++;
		i++;
	}
}

void deaccelarationAndSwitching(std::vector<Particle>& thisRoad, std::vector<Particle>& otherRoad, int l, bool removeAccelaration) {
    int size = thisRoad.size();
    if (size <= 1) return;
    for (int i = 0; i < thisRoad.size() - 1; i++) {
        int gap = thisRoad[i + 1].pos - thisRoad[i].pos;
        if (thisRoad[i].vel > gap) {
            float wantToSwitch = getRandom();
            if (wantToSwitch > 0.5) {
                int nextRoadP = nextRoadHeadWay(thisRoad[i], otherRoad, l);
                int nextRoadGap = nextRoadP == -1 ? V_MAX: nextRoadP == 0? l - thisRoad[i].pos + otherRoad[0].pos - 1 : otherRoad[nextRoadP].pos - thisRoad[i].pos - 1;
                if (nextRoadGap > gap) {
                    Particle p(thisRoad[i].pos);
                    p.vel = (thisRoad[i].vel > nextRoadGap ? nextRoadGap : thisRoad[i].vel) - removeAccelaration ? 1 : 0;
                    otherRoad.push_back(p);
                    thisRoad.erase(thisRoad.begin() + i);
                    i--;
                } else 
                    thisRoad[i].vel = gap;
            } else
                thisRoad[i].vel = gap;
        }
    }
    int gap = l - thisRoad[size - 1].pos + thisRoad[0].pos - 1;
    if (thisRoad[size - 1].vel > gap) {
        float wantToSwitch = getRandom();
        if (wantToSwitch > 0.5) {
            int nextRoadP = nextRoadHeadWay(thisRoad[size - 1], otherRoad, l);
            int nextRoadGap = nextRoadP == -1 ? V_MAX: nextRoadP == 0? l - thisRoad[size - 1].pos + otherRoad[nextRoadP].pos - 1 : otherRoad[nextRoadP].pos - thisRoad[size - 1].pos - 1;
            if (nextRoadGap > gap) {
                Particle p(thisRoad[size - 1].pos);
                p.vel = thisRoad[size - 1].vel > nextRoadGap ? nextRoadGap : thisRoad[size - 1].vel;
                p.vel -= removeAccelaration ? 1 : 0;
                otherRoad.push_back(p);
                thisRoad.pop_back();
            }
        } else 
            thisRoad[size - 1].vel = gap;
    }
}

int nextRoadHeadWay(Particle& p, std::vector<Particle>& otherRoad, int l) {
    int size = otherRoad.size();
    if (size == 0) return -1;
    for (int i = 0; i < size - 1; i++)
        if (otherRoad[i].pos >= p.pos)
            return i;
    return 0;
}

void randomBraking(std::vector<Particle>& vector, float sto) {
    int size = vector.size();
    for (int i = 0; i < size; i++)
        if (getRandom() < sto && vector[i].vel){
            vector[i].vel--;
        }
}

void move(std::vector<Particle>& one, std::vector<Particle>& two) {
	int max = one.size();
	int min = two.size();
	int i = 0;
	while ( i < min ) {
		one[i].move();
		two[i].move();
		i++;
	}
	while (i < max) {
		one[i].move();
		i++;
	}
}
