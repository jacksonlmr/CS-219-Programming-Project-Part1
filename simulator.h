//Jackson Loughmiller
//Last edited: 9/23/2024

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <bits/stdc++.h>

using namespace std;

class Simulator{
    string currentOperation;
    uint32_t intOp1; //decimal representation of operands
    uint32_t intOp2;

    string strOp1; //hex representation of operands
    string strOp2;

    bitset<32> binOp1;
    bitset<32> binOp2;
    
    bitset<32> binResult;
    string result;

    int32_t binToDec(bitset<32> b);

    public:
        Simulator();
        Simulator(string cO, uint32_t iOp1, uint32_t iOp2, string sOp1, string sOp2);
        Simulator(const Simulator& rhs);

        string getCurrentOperation();
        uint32_t getIntOp1();
        uint32_t getIntOp2();
        string getStrOp1();
        string getStrOp2();

        bool processArgs(ifstream& inputFile);
        uint32_t convertOperand(string op);
        string convertOperand(uint32_t op);
        string convertOperand(int32_t op);

        void add();
        void AND(bool s);
        void ASR(bool s);
        void LSR(bool s);
        void LSL(bool s);
        void NOT(bool s);
        void ORR(bool s);
        void SUB(bool s);
        void XOR(bool s);

        void printResult();
        int getLenOp(string op);
        void run(int numLines);
};

#endif