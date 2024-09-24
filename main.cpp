//Jackson Loughmiller
//Last edited: 9/21/2024

#include <iostream>
#include <fstream>
#include <string>
#include "simulator.h"

using namespace std;

void runSimulator(Simulator sim, ifstream& file);
int getNumLines(ifstream& file);

int main(int argc, char *argv[]){
    Simulator simulator1;

    if (argc <= 1){
        cout << "Please provide txt file with desired operations" << endl;
        return 1;
    }

    ifstream file(argv[1]);

    if(file.is_open()){
        runSimulator(simulator1, file);
    }

    else{
        cout << "please provide a valid filename" << endl;
    }

    return 0;
}

void runSimulator(Simulator sim, ifstream& file){

    int numLines = getNumLines(file);

    for (int i = 0; i < numLines; i++){
        sim.processArgs(file);
        sim.run(numLines);
    }
}

int getNumLines(ifstream& file){
    int numLines = 0;
    string trash;

    while(getline(file, trash, '\n')){
        numLines++;
    }

    file.clear();
    file.seekg(0);
    return numLines;
}