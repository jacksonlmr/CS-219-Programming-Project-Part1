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
        success = true;
        intOp1 = convertOperand(strOp1);
        intOp2 = convertOperand(strOp2);
    }

    else{
        cout << "Failed to read given file" << endl;
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

void Simulator::add(){
    uint32_t returnSum = intOp1 + intOp2;
    result = convertOperand(returnSum);
}

void Simulator::printResult(){
    int op1Len = strOp1.length();
    int op2Len = strOp2.length();

    string op1Spaces;
    string op2Spaces;
    for (int i = 0; i < 32-op1Len; i++){
        op1Spaces += ' ';
    }

    for (int i = 0; i < 32-op2Len; i++){
        op2Spaces += ' ';
    }
    cout << currentOperation << op1Spaces << strOp1 << op2Spaces << strOp2 << ": " << result << endl;
}

void Simulator::run(int numLines){
    
    if (currentOperation == "ADD"){
            add();
            printResult();
    }
        
    
    

}
