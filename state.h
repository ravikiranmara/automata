#ifndef _TURING_STATE_H_
#define _TURING_STATE_H_

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <set>
#include <locale>

using std::string;
using std::stack;
using std::string;
using std::vector;
using std::cout;
using std::endl;

typedef enum TMStateType 
{
    StartState, 
    AcceptState, 
    RejectState,
    Unknown
} TMStateType;

typedef enum Direction {
    Left, 
    Right, 
    Invalid
} Direction;

class State;

class Transition 
{
  public:
    char symbol;
    string toStateName;
    char writeSymbol;
    Direction direction;

    Transition() 
    {
        this->symbol = 'z';
        this->writeSymbol = 'z';
        this->toStateName = "";
        this->direction = Invalid;
    }
    
    Transition(char symbol, string toStateName, char writeSymbol, Direction direction)
    {
        this->symbol = symbol;
        this->writeSymbol = writeSymbol;
        this->toStateName = toStateName;
        this->direction = direction;
    }
    
    Transition& operator=(Transition &transition)
    {
        this->symbol = transition.symbol;
        this->writeSymbol = transition.writeSymbol;
        this->toStateName = transition.toStateName;
        this->direction = transition.direction;
        
        return *this;
    }

    bool operator==(Transition &transition)
    {
        if(this->symbol == transition.symbol && 
            this->writeSymbol == transition.writeSymbol && 
            this->toStateName == transition.toStateName && 
            this->direction == transition.direction) {
            return true;
        }
                
        return false;
    }
    
    void dumpTransition() {
        cout << "\tread symbol:" << this->symbol << endl;
        cout << "\tto state:" << this->toStateName << endl;
        cout << "\twrite symbol:" << this->writeSymbol << endl;
        cout << "\tdirection:" << this->direction << endl;
    }
};

class State 
{
    string name;
    TMStateType stateType;
    
public:
    vector<Transition> transition;
    
    State();
    State(string name);
    State(string name, TMStateType stateType);
    int setName(string i);
    string getName();
    int transitionCount();
    int setStateType(TMStateType st);
    TMStateType getStateType();

    int AddTransition(Transition &transition);
    int AddTransition(char symbol, string tostatename, char writesym, Direction direction);
    vector<Transition> GetTransitions(char symbol);

    void Reset();
    void DumpState();
};

#endif