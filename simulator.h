//Jackson Loughmiller
//Last edited: 9/23/2024

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <math.h>
// #include <bits/stdc++.h>

using namespace std;

class Simulator{
    int nFlag, zFlag, cFlag, vFlag;
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7;

    string currentOperation;
    string currentLine;
    string destinationRegister;

    uint32_t intOp1; //decimal representation of operands
    uint32_t intOp2;
    uint32_t intOp3;

    string strOp1; //hex representation of operands
    string strOp2;
    string strOp3;

    bitset<32> binOp1;
    bitset<32> binOp2;
    
    bitset<32> binResult;
    string result;

    int32_t binToDec(bitset<32> b);

    public:
        Simulator();
        Simulator(string cO, uint32_t iOp1, 
                             uint32_t iOp2, string sOp1, 
                                            string sOp2, int n, 
                                                         int z, 
                                                         int c, 
                                                         int v, uint32_t reg0, 
                                                                uint32_t reg1, 
                                                                uint32_t reg2, 
                                                                uint32_t reg3, 
                                                                uint32_t reg4, 
                                                                uint32_t reg5, 
                                                                uint32_t reg6, 
                                                                uint32_t reg7);
        Simulator(const Simulator& rhs);

        string getCurrentOperation();
        uint32_t getIntOp1();
        uint32_t getIntOp2();
        string getStrOp1();
        string getStrOp2();

        bool processArgs(ifstream& inputFile);
        void setInputs(uint32_t &toChange1, uint32_t &toChange2, string op1, string op2);
        void setRegister(string reg, uint32_t num);
        uint32_t convertOperand(string op);
        string convertOperand(uint32_t op);
        string convertOperand(int32_t op);

        void add(bool s);
        void AND(bool s);
        void ASR(bool s);
        void LSR(bool s);
        void LSL(bool s);
        void NOT(bool s);
        void ORR(bool s);
        void SUB(bool s);
        void XOR(bool s);
        void MOV();

        void removeCommas(string &s);
        void printResult();
        int getLenOp(string op);
        void run(int numLines);
};

#endif