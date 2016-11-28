#ifndef _REGEX_NFA_SIMULATE_CPP_
#define _REGEX_NFA_SIMULATE_CPP_

#include "simulate.h"
#include "state.cpp"

using std::string;

int SimulateDfa::simulate(Automata &dfa, int start, string &str, bool &result)
{
    int length = str.length();
    State *curr, *next;
    int currindex, nextindex;
    
    //cout << "Dfa path " << endl;
    currindex = start;
    for(int i=0; i<length; i++) {
        cout << currindex << " -> " ;
        curr = dfa.getState(currindex);
        if(str[i] == 'e') {
            next = curr;
            break;
        }
        next = curr->GetTransitionIndex(str[i]);
        nextindex = next->getName();
        currindex = nextindex;
    }
    // cout << endl;
    
    if(finalState == next->getStateType())
        result = true;
    else result = false;
    
    return status_success;
}


#endif