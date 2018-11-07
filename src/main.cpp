#include "network.h"
#include "random.h"
#include "simulation.h"
#include <iostream>

RandomNumbers RNG;

int main(int argc, char **argv) {
    Network net;
    Simulation sim(&net);
    int errcode = 0;
    try {
        sim.initialize(argc, argv);
        sim.run();
    } catch(TCLAP::ArgException &e) {
        std::cerr << "Error: " + e.error() + " " + e.argId();
        errcode = 2;
    }
    return errcode;
}



// value= chaleurs d'un point
// diffusion de la chaleur en fonction du réseau et des liens entre les noeuds
// jusqu'à arriver à une température d'équilibre
