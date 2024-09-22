# CS-219-Programming-Project-Part1

## Classes
### Simulator
    Attributes:
        string* operations
        int numOperations
        int maxNumOperations
        
    Functions:
            Simulator():
                Default constructor
            Simulator(int maxNO):
                parametrized constructor
            Simulator(const Simulator& rhs)
                copy constructor

            void processArgs(ofstream inputFile):
                reads from input file, adds each operation to array of operations
                
            void addOperation(string op1):
                adds string containing the operation and operands to operations array
                
            uint32_t add(uint32_t op1, uint32_t op2):
                adds 2 hexadecimal values
    
