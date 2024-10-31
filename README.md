# CS-219-Programming-Project-Part1

## How to Run
To run the program, just use the following command: ./simulator <fileName.txt>, where fileName is the name of the file containing the operations and operands to run. 

## Working Process
The code runs in the following manner:
User runs executable, along with an argument containing the txt file with the operations. In the main function, we check that the correct arguments were given, if they were, we open the file and run the simulator. The runSimulator function is given the simulator to run, and the file to use. RunSimulator will run functions to process the arguments given in the txt file, and perform the desired operations. The processArgs function makes use of stringstream objects to get the desired information from the txt file and save it into the Simulator object. After this is done, the run function within Simulator will sum and print out the result of the operation. 
