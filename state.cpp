#ifndef _TURING_STATE_CPP_
#define _TURING_STATE_CPP_

#include <iostream>
#include <string>
#include <stack>
#include <locale>
#include "globals.h"
#include "state.h"

// namespace using
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stack;
using std::string;

State::State()
{
    this->Reset();
}

State::State(string name)
{
    State(name, Unknown);
}

State::State(string name, TMStateType stateType)
{
    this->name = name;
    this->stateType = stateType;
}

void State::Reset()
{
    this->transition.clear();
    this->name = "";
    this->stateType = Unknown;
}

int State::setName(string i)
{
    this->name = i;
}

string State::getName() 
{
    return this->name;
}

int State::transitionCount() 
{
    return this->transition.size();
}

int State::AddTransition(Transition &transition)
{
    this->transition.push_back(transition);
    return status_success;
}

int State::AddTransition(char symbol, string tostatename, char writesym, Direction direction)
{
    Transition transition (symbol, tostatename, writesym, direction);
    this->transition.push_back(transition);
    return status_success;
}

int State::setStateType(TMStateType st)
{
    this->stateType = st;
}

TMStateType State::getStateType()
{
    return this->stateType;
}

vector<Transition> State::GetTransitions(char symbol) {
    vector<Transition> rval;
    for(auto it=this->transition.begin(); it != this->transition.end(); it++) {
        if(it->symbol == symbol) 
            rval.push_back(*it);
    }
    return rval;
}

void State::DumpState()
{
    std::cout << "----   STATE   ----" << std::endl;
    std::cout << "Name:" << this->name << std::endl;
    std::cout << "state type:" << this->stateType << std::endl;
    std::cout <<"Transitions:(" << this->transitionCount() << ")" << endl;

    for(auto &it : this->transition) 
        it.dumpTransition();
    
    std::cout <<"-------" << std::endl;
    
    return;
}


#endif