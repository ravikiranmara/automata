#include <iostream>
#include <string>
#include <vector>
#include "globals.h"
#include "utils.h"
#include "state.cpp"
#include "TuringMachine.cpp"

/* using std */
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

using std::ifstream;
using std::ofstream;

int main(int argc, char **argv)
{
    TuringMachine turingMachine;
    string defn; // = "#q0,a->qa,a,R#q0,a->q1,a,R#q0,b->q1,b,R#q0,_->q1,_,R#q1,b->q1,b,R#q1,_->q1,_,R#q1,a->qr,a,R#q1,b->qr,b,R##ab#";
    
    cin >> defn;

    // program machine
    turingMachine.programMachine(defn);
    // turingMachine.dumpMachineState();
    
    // simulate
	// cout << "Simulate Turing Machine" << endl;
    turingMachine.simulate();
    
	return 0;
}
