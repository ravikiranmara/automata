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
}
    
int TuringMachine::programMachine(string definition) {
    vector<string> transition;
    stringstream stream(definition);
    string word;
    bool first = true; 
    
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
    this->tape = word;
    
    return status_success;
}

int TuringMachine::getTransitionIndex(string statename) {
    int size = this->states.size();
    for(int i=0; i<size; i++) 
        if(this->states[i].getName() == statename) 
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
    
    return status_success;
}

int TuringMachine::parseTransition(string transition) {
    string fromstatename = transition.substr(0,2);
    string tostatename = transition.substr(6,2);
    char readsym = transition[3];
    char writesym = transition[9];
    char dir = transition[11];
    
    cout << fromstatename << "," << readsym << "->" << tostatename 
        << "," << writesym << ",," << dir << endl;
        
    // load transition
    int fromstateindex = this->getTransitionIndex(fromstatename);;
    int tostateindex = this->getTransitionIndex(tostatename);

    // add state if not present
    if(-1 == fromstateindex) 
        this->addState(fromstatename);
    if(-1 == tostateindex) 
        this->addState(tostatename);
        
    int fromindex = this->getTransitionIndex(fromstatename);
    int toindex = this->getTransitionIndex(tostatename);
    
    // add transitions
    Direction direction = (dir == 'R')? Right : Left;
    Transition transitionState(readsym, tostatename, writesym, direction);
    this->states[fromindex].AddTransition(transitionState);
    
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