#ifndef _REGEX_NFA_STATE_CPP_
#define _REGEX_NFA_STATE_CPP_

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

State::State(int name)
{
    State(name, unknown);
}

State::State(int name, FaStateType stateType)
{
    this->name = name;
    this->stateType = stateType;
}

void State::Reset()
{
    this->transition.clear();
    this->name = -1;
    this->stateType = unknown;
}

int State::setName(int i)
{
    this->name = i;
}

int State::getName() 
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

int State::AddTransition(char symbol, State *state)
{
    Transition transition (symbol, state);
    this->transition.push_back(transition);
    return status_success;
}

int State::setStateType(FaStateType st)
{
    this->stateType = st;
}

FaStateType State::getStateType()
{
    return this->stateType;
}

State* State::GetTransitionIndex(char symbol){
    for(auto it=this->transition.begin(); it != this->transition.end(); it++) {
        if(it->symbol == symbol) 
            return it->to;
    }
}

void State::DumpState()
{
    State *state;
    std::cout << "name:" << this->name << std::endl;
    std::cout << "state type:" << this->stateType << std::endl;
    std::cout <<"Transitions:(" << this->transitionCount() << ")" << endl;
    
    
    for(auto &it : this->transition) {
        state = it.to;
        cout << "\tsymbol:" << it.symbol << endl;
        cout << "\tstate:" << state->name << endl;
    }
    
    std::cout <<"-------" << std::endl;
    
    return;
}


#endif