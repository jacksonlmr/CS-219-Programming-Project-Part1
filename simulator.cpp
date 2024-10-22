//Jackson Loughmiller
//Last Edited: 9/23/2024

#include "simulator.h"

Simulator::Simulator(){
   intOp1 = 0;
   intOp2 = 0;
   strOp1 = "0x0";
   strOp2 = "0x0";
}

Simulator::Simulator(string cO, uint32_t iOp1, uint32_t iOp2, string sOp1, string sOp2){
   currentOperation = cO;
   intOp1 = iOp1;
   intOp2 = iOp2;
   strOp1 = sOp1;
   strOp2 = sOp2;
}

Simulator::Simulator(const Simulator& rhs){
    currentOperation = rhs.currentOperation;
    intOp1 = rhs.intOp1;
    intOp2 = rhs.intOp2;
    strOp1 = rhs.strOp1;
    strOp2 = rhs.strOp2;
}

string Simulator::getCurrentOperation(){
    return currentOperation;
}

uint32_t Simulator::getIntOp1(){
    return intOp1;
}

uint32_t Simulator::getIntOp2(){
    return intOp2;
}

string Simulator::getStrOp1(){
    return strOp1;
}

string Simulator::getStrOp2(){
    return strOp2;
}

bool Simulator::processArgs(ifstream& inputFile){
    bool success = false;
    string inputString;

    if (getline(inputFile, inputString, '\n')){
        stringstream ss(inputString);
        ss >> currentOperation >> strOp1 >> strOp2;

        intOp1 = convertOperand(strOp1);
        intOp2 = convertOperand(strOp2);

        binOp1 = intOp1;
        binOp2 = intOp2;

        success = true;
    }

    return success;
}

uint32_t Simulator::convertOperand(string op){
    uint32_t intOp;
    
    stringstream ss;
    ss << std::hex << op;
    ss >> intOp;

    return intOp;
}

string Simulator::convertOperand(uint32_t op){
    stringstream ss;
    ss << hex << op;
    string strOp = ss.str();
    strOp = "0x" + strOp;

    return strOp;
}

string Simulator::convertOperand(int32_t op){
    stringstream ss;
    ss << hex << op;
    string strOp = ss.str();
    strOp = "0x" + strOp;

    return strOp;
}

void Simulator::add(){
    uint32_t returnSum = intOp1 + intOp2;
    result = convertOperand(returnSum);
}

void Simulator::AND(bool s){
    for (int i = 0; i < 32; i++){
        if (binOp1.test(i) && binOp2.test(i)){
            binResult.set(i);
        }

        else{
            binResult.reset(i);
        }
    }
    
    result = convertOperand((uint32_t)binResult.to_ulong());//converts binResult from binary to uint_32t then to hex
}

void Simulator::ASR(bool s){
    binResult = binOp1;
    for (int i = 0; i < intOp2; i++){//loop however many times the shift amount is
//cout << "performing shift right" << endl; 
        for (int j = 0; j < 31; j++){
            if (binResult.test(j+1) == 1){
                binResult.set(j);
            }

            else {
                binResult.reset(j);
            }
        }
    }
    //cout << "binResult in ASR: " << binResult << endl;
    //cout << "binOp1 in ASR:    " << binOp1 << endl;
    result = convertOperand(binToDec(binResult));
    //cout << "bruh";
}

void Simulator::LSR(bool s){}

void Simulator::LSL(bool s){}

void Simulator::NOT(bool s){}

void Simulator::ORR(bool s){}

void Simulator::SUB(bool s){}

void Simulator::XOR(bool s){}


void Simulator::printResult(){
    int op1Len = strOp1.length(), op2Len = strOp2.length();
    string op1Spaces, op2Spaces;

    for (int i = 0; i < 32-op1Len; i++){
        op1Spaces += ' ';
    }

    for (int i = 0; i < 32-op2Len; i++){
        op2Spaces += ' ';
    }
    cout << currentOperation << op1Spaces << strOp1 << op2Spaces << strOp2 << ": " << result << endl;
}

void Simulator::run(int numLines){
    if (currentOperation == "ADD"){//need to change for ADDS
            add();
    }

    else if (currentOperation == "AND" || currentOperation == "ANDS"){
        bool s = currentOperation.length() == 4;
        AND(s);
    }

    else if (currentOperation == "ASR" || currentOperation == "ASRS"){
        bool s = currentOperation.length() == 4;
        ASR(s);
    }

    else if (currentOperation == "LSR" || currentOperation == "LSRS"){
        bool s = currentOperation.length() == 4;
        LSR(s);
    }

    else if (currentOperation == "LSL" || currentOperation == "LSLS"){
        bool s = currentOperation.length() == 4;
        LSL(s);
    }

    else if (currentOperation == "NOT" || currentOperation == "NOTS"){
        bool s = currentOperation.length() == 4;
        NOT(s);
    }

    else if (currentOperation == "ORR" || currentOperation == "ORRS"){
        bool s = currentOperation.length() == 4;
        ORR(s);
    }

    else if (currentOperation == "SUB" || currentOperation == "SUBS"){
        bool s = currentOperation.length() == 4;
        SUB(s);
    }

    else if (currentOperation == "XOR" || currentOperation == "XORS"){
        bool s = currentOperation.length() == 4;
        XOR(s);
    }

    printResult();
}

int32_t Simulator::binToDec(bitset<32> b){
    int decimal = 0;

    if (b.test(31)){
        b.flip();
        bool carry = true;

        for (int i = 0; i < 32 && carry; i++){
            if (b.test(i)){
                b.flip(i);
            }

            else{
                b.flip(i);
                carry = false;
            }
        }
    }

    for (int i = 0; i < 32; i++){
        if (b.test(i)){
            decimal += pow(2, i);
        }
    }

    return decimal;
}