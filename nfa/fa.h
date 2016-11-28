#ifndef _REGEX_NFA_FA_H_
#define _REGEX_NFA_FA_H_

#include <string>
#include <stack>
#include <vector>
#include "state.cpp"

const int StateMax = 100000;

using std::vector;

class Automata 
{
    int curr;
    vector<State> states;
    
  public:
    Automata() 
    {
        curr = -1;
        states.resize(StateMax);
    }
    
    State* GetNextState()
    {
        if(++curr < StateMax) {
            states[curr].setName(curr);
            return &states[curr];            
        } else {
            return nullptr;
        }
    }
    
    State *getState(int pos) {
        return &states[pos];
    }
    
    void Reset()
    {
        for(int i=0; i<=curr; i++) 
            states[i].Reset();
        curr = -1;
        return;
    }
    
    void DumpTable()
    {
        cout <<"Dump Table" << endl;
        for(int i=0; i<=curr; i++) {
            states[i].DumpState();
        }
    }
};

Automata automata;
Automata dfaAutomata;

#endif