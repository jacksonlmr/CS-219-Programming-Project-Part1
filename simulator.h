//Jackson Loughmiller
//Last edited: 9/21/2024

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <fstream>

using namespace std;

class Simulator{
    string* operations;
    int numOperations;
    int maxNumOperations;

    public:
        Simulator();
        Simulator(int maxNO);
        Simulator(const Simulator& rhs);

        void processArgs(ofstream inputFile);
        void addOperation(string op);
        uint32_t add(uint32_t op1, uint32_t op2);

};

#endif