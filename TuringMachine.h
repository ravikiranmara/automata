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
    int numtransition;
    int numstate;
    string machinestring;
    string orgtape; 
    
public:
    TuringMachine();
    
    int runTurn(int stateindex, int tapepos, int runcount);
    int getStateIndex(TMStateType statetype);
    int getStateIndex(string statename);
    int programMachine(string definition); 
    int parseTransition(string transition);
    int addState(string statename);
    int dumpMachineState();
    void appendTape();
    int simulate();
};

#endif
