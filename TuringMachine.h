#ifndef _TURING_TURING_H_
#define _TURING_TURING_H_

#include <sstream>
#include <string>
#include "globals.h"
#include "state.cpp"

using std::stringstream;
using std::string;

class TuringMachine 
{
    vector<State> states;
    string tape;
    
public:
    TuringMachine();
    
    int getTransitionIndex(string statename);
    int programMachine(string definition); 
    int parseTransition(string transition);
    int addState(string statename);
    int dumpMachineState();
};

#endif
