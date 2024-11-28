//Jackson Loughmiller
//Last Edited: 9/23/2024

#include "simulator.h"
#include <algorithm>

Simulator::Simulator(){
   intOp1 = intOp2 = 0;
   r0 = r1 = r2 = r3 = r4 = r5 = r6 = r7 = 0x0;
   strOp1 = strOp2 = "0x0";
   nFlag = zFlag = cFlag = vFlag = 0;
}

Simulator::Simulator(string cO, uint32_t iOp1, 
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
                                                                   uint32_t reg7){
   currentOperation = cO;

   r0 = reg0;
   r1 = reg1;
   r2 = reg2;
   r3 = reg3;
   r4 = reg4;
   r5 = reg5;
   r6 = reg6;
   r7 = reg7;

   intOp1 = iOp1;
   intOp2 = iOp2;

   strOp1 = sOp1;
   strOp2 = sOp2;

   nFlag = n;
   zFlag = z;
   cFlag = c;
   vFlag = v;
}

Simulator::Simulator(const Simulator& rhs){
    currentOperation = rhs.currentOperation;

    r0 = rhs.r0;
    r1 = rhs.r1;
    r2 = rhs.r2;
    r3 = rhs.r3;
    r4 = rhs.r4;
    r5 = rhs.r5;
    r6 = rhs.r6;
    r7 = rhs.r7;

    intOp1 = rhs.intOp1;
    intOp2 = rhs.intOp2;

    strOp1 = rhs.strOp1;
    strOp2 = rhs.strOp2;

    nFlag = rhs.nFlag;
    zFlag = rhs.zFlag;
    cFlag = rhs.cFlag;
    vFlag = rhs.vFlag;
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
        currentLine = inputString;
        removeCommas(inputString);
        transform(inputString.begin(), inputString.end(), inputString.begin(), ::toupper);
        stringstream ss(inputString);
        strOp3 = "\0";
        ss >> currentOperation >> strOp1 >> strOp2 >> strOp3;

        // intOp1 = convertOperand(strOp1);
        // intOp2 = convertOperand(strOp2);
        if (strOp3 == "\0"){
            destinationRegister = strOp1;
            setInputs(intOp1, intOp2, strOp1, strOp2);
        }

        else{
            destinationRegister = strOp1;
            setInputs(intOp2, intOp3, strOp2, strOp3);
        }
        
        

        binOp1 = intOp1;
        binOp2 = intOp2;

        success = true;
    }

    return success;
}

void Simulator::setInputs(uint32_t &toChange1, uint32_t &toChange2, string op1, string op2){
    if (op1 == "R0"){
        toChange1 = r0;
    }
    else if (op1 == "R1"){
        toChange1 = r1;
    }
    else if (op1 == "R2"){
        toChange1 = r2;
    }
    else if (op1 == "R3"){
        toChange1 = r3;
    }
    else if (op1 == "R4"){
        toChange1 = r4;
    }
    else if (op1 == "R5"){
        toChange1 = r5;
    }
    else if (op1 == "R6"){
        toChange1 = r6;
    }
    else {
        toChange1 = r7;
    }

    if (op2 == "R0"){
        toChange2 = r0;
    }
    else if (op2 == "R1"){
        toChange2 = r1;
    }
    else if (op2 == "R2"){
        toChange2 = r2;
    }
    else if (op2 == "R3"){
        toChange2 = r3;
    }
    else if (op2 == "R4"){
        toChange2 = r4;
    }
    else if (op2 == "R5"){
        toChange2 = r5;
    }
    else if (op2 == "R6"){
        toChange2 = r6;
    }
    else if (op2 == "R7"){
        toChange2 = r7;
    }
    else {
        strOp2 = op2;
        toChange2 = convertOperand(strOp2);
    }
}

void Simulator::setRegister(string reg, uint32_t num){
    if (reg == "R0"){
        r0 = num;
    }
    else if (reg == "R1"){
        r1 = num;
    }
    else if (reg == "R2"){
        r2 = num;
    }
    else if (reg == "R3"){
        r3 = num;
    }
    else if (reg == "R4"){
        r4 = num;
    }
    else if (reg == "R5"){
        r5 = num;
    }
    else if (reg == "R6"){
        r6 = num;
    }
    else {
        r7 = num;
    }
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

void Simulator::add(bool s){
    if (s){
        uint32_t returnSum = intOp2 + intOp3;
        result = convertOperand(returnSum);
        setRegister(destinationRegister, convertOperand(result));
        nFlag = int(returnSum) < 0;
        zFlag = returnSum == 0;
        if (int(intOp2) > 0 && int(intOp3) > 0 && int(returnSum) < 0){
            vFlag = 1;
        }

        else{
            vFlag = 0;
        }
    }
    else{
        uint32_t returnSum = intOp2 + intOp3;
        result = convertOperand(returnSum);
        setRegister(destinationRegister, convertOperand(result));
    }
}

void Simulator::AND(bool s){
    if (s){
        result = convertOperand(intOp2 & intOp3);
        setRegister(destinationRegister, convertOperand(result));
        nFlag = (intOp2 & intOp3) < 0;
        zFlag = (intOp2 & intOp3) == 0;
    }
    else{
        result = convertOperand(intOp2 & intOp3);
        setRegister(destinationRegister, convertOperand(result));
    }
    // for (int i = 0; i < 32; i++){
    //     if (binOp1.test(i) && binOp2.test(i)){
    //         binResult.set(i);
    //     }

    //     else{
    //         binResult.reset(i); 
    //     }
    // }
    
    // result = convertOperand((uint32_t)binResult.to_ulong());//converts binResult from binary to uint_32t then to hex
}

void Simulator::ASR(bool s){
    binResult = binOp1;
    for (int i = 0; i < intOp3; i++){//loop however many times the shift amount is
        for (int j = 0; j < 31; j++){
            if (binResult.test(j+1) == 1){
                binResult.set(j);
            }

            else {
                binResult.reset(j);
            }
        }
    }
    result = convertOperand(binToDec(binResult));
    setRegister(destinationRegister, convertOperand(result));
}

void Simulator::LSR(bool s){
    if (s){
        nFlag = 0;
        cFlag = intOp2 & 1;
        
        intOp2 = intOp2 >> intOp3;
        result = convertOperand(intOp2);
        setRegister(destinationRegister, convertOperand(result));

        zFlag = intOp2 == 0;//I think this will work
    }

    else{
        intOp2 = intOp2 >> intOp3;
        result = convertOperand(intOp2);
    }
}

void Simulator::LSL(bool s){
    if (s){
        nFlag = 0;
        cFlag = intOp2 & 2147483648;//this number in binary only has one bit set, the MSB
        
        intOp2 = intOp2 << intOp3;
        result = convertOperand(intOp2);
        setRegister(destinationRegister, convertOperand(result));

        zFlag = intOp2 == 0;//I think this will work
    }

    else{
        intOp2 = intOp2 >> intOp3;
        result = convertOperand(intOp2);
        setRegister(destinationRegister, convertOperand(result));
    }
}

void Simulator::NOT(bool s){
    if (s){
        intOp2 = ~intOp2;
        result = convertOperand(intOp2);
        setRegister(destinationRegister, convertOperand(result));

        nFlag = intOp2 < 0;
        zFlag = intOp2 == 0;
    }
    else{
        intOp2 = ~intOp2;
        result = convertOperand(intOp2);
        setRegister(destinationRegister, convertOperand(result));
    }
}

void Simulator::ORR(bool s){
    if (s){
        result = convertOperand(intOp2 | intOp3);
        setRegister(destinationRegister, convertOperand(result));
        nFlag = intOp2 < 0;
        zFlag = intOp2 == 0;
    }
    else{
        result = convertOperand(intOp2 | intOp3);
        setRegister(destinationRegister, convertOperand(result));
    }
}

void Simulator::SUB(bool s){//need to finish implementing this. not sure how to do carry flag
    if (s){
        uint32_t returnSum = intOp2 - intOp3;
        result = convertOperand(returnSum);
        setRegister(destinationRegister, convertOperand(result));
        nFlag = (returnSum) < 0;
        zFlag = (returnSum) == 0;
        cFlag = (intOp2 >= intOp3);
    }
    else{
        result = convertOperand(intOp2 - intOp3);
        setRegister(destinationRegister, convertOperand(result));
    }
}

void Simulator::XOR(bool s){
    if (s){
        result = convertOperand(intOp2 ^ intOp3);
        setRegister(destinationRegister, convertOperand(result));
        nFlag = (intOp2 ^ intOp3) < 0;
        zFlag = (intOp2 ^ intOp3) == 0;
    }
    else{
        result = convertOperand(intOp2 ^ intOp3);
        setRegister(destinationRegister, convertOperand(result));
    }
}

void Simulator::MOV(){
    setRegister(strOp1, intOp2);
}

void Simulator::removeCommas(string &s){
    for (int i = 0; i < s.length(); i++){
        if (s[i] == ',' || s[i] == '#'){
            s.erase(i, 1);
        }
    }
}

void Simulator::printResult(){
    cout << currentLine << endl << 
    "R0: " << convertOperand(r0) << 
    " R1: " << convertOperand(r1) << 
    " R2: " << convertOperand(r2) << 
    " R3: " << convertOperand(r3) << endl << 
    " R4: " << convertOperand(r4) << 
    " R5: " << convertOperand(r5) << 
    " R6: " << convertOperand(r6) << 
    " R7: " << convertOperand(r7) << endl << 
    "N = " << nFlag << 
    " Z = " << zFlag << 
    " C = " << cFlag << 
    " V = " << vFlag << endl;
    // int op1Len = strOp1.length(), op2Len = strOp2.length();
    // string op1Spaces, op2Spaces;

    // for (int i = 0; i < 32-op1Len; i++){
    //     op1Spaces += ' ';
    // }

    // for (int i = 0; i < 32-op2Len; i++){
    //     op2Spaces += ' ';
    // }

    // if (currentOperation == "NOT" || currentOperation == "NOTS"){
    //     cout << currentOperation << op1Spaces << strOp1 << ": " << result << endl;
    // }

    // else{
    //     cout << currentOperation << op1Spaces << strOp1 << op2Spaces << strOp2 << ": " << result << endl;
    // }
    // cout << "N: " << nFlag << "Z: " << zFlag << endl;
}

void Simulator::run(int numLines){
    if (currentOperation == "ADD" || currentOperation == "ADDS"){
            bool s = currentOperation.length() == 4;
            add(s);
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

    else if (currentOperation == "MOV"){
        MOV();
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