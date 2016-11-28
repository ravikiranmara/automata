#ifndef _TURING_TURING_CPP_
#define _TURING_TURING_CPP_

#include <sstream>
#include <string>
#include "TuringMachine.h"

using std::stringstream;
using std::string;

TuringMachine::TuringMachine() {
    states.clear();
    tape.clear();
    numtransition = 0;
    numstate = 0;
}

void TuringMachine::appendTape() {
    for(int i=0; i<100; i++) 
        this->tape.push_back('_');
}
    
int TuringMachine::programMachine(string definition) {
    vector<string> transition;
    stringstream stream(definition);
    string word;
    bool first = true; 
    
    this->machinestring = definition.substr(
                0, definition.find("##")+1);
    
    while (getline(stream, word, '#')) {
        if(word.empty() && first == true) { 
            first = false;
            continue;
        }
        
        if(word.empty() && first == false) 
            break;
        
        parseTransition(word);
    }
    
    getline(stream, word, '#');
    this->orgtape = word;
    if(word != "e")
        this->tape = word;
    this->appendTape();
    
    return status_success;
}

int TuringMachine::getStateIndex(string statename) {
    int size = this->states.size();
    for(int i=0; i<size; i++) 
        if(this->states[i].getName() == statename) 
            return i;
            
    return -1;
}

int TuringMachine::getStateIndex(TMStateType statetype) {
    int size = this->states.size();
    for(int i=0; i<size; i++) 
        if(this->states[i].getStateType() == statetype) 
            return i;
            
    return -1;
}

int TuringMachine::addState(string statename) {
    TMStateType statetype = Unknown;
    if(statename == "q0") statetype = StartState;
    else if (statename == "qa") statetype = AcceptState;
    else if (statename == "qr") statetype = RejectState;
    
    State state(statename, statetype);
    this->states.push_back(state);
    this->numstate += 1;
    
    return status_success;
}

int TuringMachine::parseTransition(string transition) {
    string fromstatename = transition.substr(0,2);
    string tostatename = transition.substr(6,2);
    char readsym = transition[3];
    char writesym = transition[9];
    char dir = transition[11];
    
    // cout << fromstatename << "," << readsym << "->" << tostatename 
       // << "," << writesym << "," << dir << endl;
        
    // load transition
    int fromstateindex = this->getStateIndex(fromstatename);;
    int tostateindex = this->getStateIndex(tostatename);

    // add state if not present
    if(-1 == fromstateindex) 
        this->addState(fromstatename);
    if(-1 == tostateindex) 
        this->addState(tostatename);
        
    int fromindex = this->getStateIndex(fromstatename);
    int toindex = this->getStateIndex(tostatename);
    
    // add transitions
    Direction direction = (dir == 'R')? Right : Left;
    Transition transitionState(readsym, tostatename, writesym, direction);
    this->states[fromindex].AddTransition(transitionState);
    this->numtransition += 1;
    
    return status_success;
}

int TuringMachine::runTurn(int stateindex, int tapepos, int runcount) {
    State &current = this->states[stateindex];
    char tapechar = this->tape[tapepos];
    string tape = "";
    int newstateindex;
    int newtapepos = -1;
    int status = -1;
    bool running = false;
    
    // if accept, return
    if(AcceptState == current.getStateType()) 
        return runcount;
        
    if(RejectState == current.getStateType()) 
        return -1;
        
    if(runcount > MaxRunCount) 
        return -2;
    
    // get all transitions
    vector<Transition> allTransition = current.GetTransitions(tapechar);
    
    for(auto &transition : allTransition) {
        // save tape
        tape = this->tape;
        newstateindex = this->getStateIndex(transition.toStateName);
        tape[tapepos] = transition.writeSymbol;
        
        if(Right == transition.direction) 
            newtapepos = tapepos + 1;
        if(Left == transition.direction) 
            newtapepos = (tapepos == 0)? tapepos : tapepos-1; 
        
        status = runTurn(newstateindex, newtapepos, runcount +1);
        
        if(-2 == status) 
            running = true;
        
        if(-1 == status || -2 == status) 
            this->tape = tape;
        
        // accept exits from here
        else return status;
    }
    
    return (running == true)? -2 : -1;
}

int TuringMachine::simulate() {
    int runcount = 0;
    int tapepos = 0;
    int currentstate = this->getStateIndex(StartState);
    
    int status = this->runTurn(currentstate, tapepos, runcount);
    
    // print output
    cout << this->machinestring << endl;
    cout << this->orgtape << endl;
    cout << this->numtransition << endl;;
    cout << this->numstate << endl;
    if(-1 == status) cout << "M stops and rejects w" << endl;
    else if(-2 == status) cout << "M is still running" << endl;
    else cout << "M stops and accepts w" << endl;
    
    return status_success;
}

int TuringMachine::dumpMachineState() {
    cout << "=========      Turing Machine       ==========" << endl;
    cout << "Tape : " << tape << endl;
    cout << "States" << endl;
    for(auto &state : states)
        state.DumpState();
    cout << "================================================" << endl;
}

#endif