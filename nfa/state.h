#ifndef _REGEX_NFA_STATE_H_
#define _REGEX_NFA_STATE_H_

#include <string>
#include <stack>
#include <vector>
#include <set>
#include <locale>

using std::string;
using std::stack;
using std::string;
using std::vector;

typedef enum FaStateType 
{
    startState, 
    finalState, 
    intermediate,
    unknown
} FaStateType;

class State;

class Transition 
{
  public:
    char symbol;
    State *to;

    Transition() 
    {
        this->symbol = 'z';
        this->to = nullptr;
    }
    
    Transition(char symbol, State *to)
    {
        this->symbol = symbol;
        this->to = to;
    }
    
    Transition& operator=(Transition &transition)
    {
        this->symbol = transition.symbol;
        this->to = transition.to;
        
        return *this;
    }

    bool operator==(Transition &transition)
    {
        if(this->symbol == transition.symbol && 
            this->to == transition.to) {
            return true;
        }
                
        return false;
    }
};

class State 
{
    int name;
    FaStateType stateType;
    
public:
    vector<Transition> transition;
    
    State();
    State(int name);
    State(int name, FaStateType stateType);
    int setName(int i);
    int getName();
    int transitionCount();
    int setStateType(FaStateType st);
    FaStateType getStateType();

    int AddTransition(Transition &transition);
    int AddTransition(char symbol, State *state);
    State* GetTransitionIndex(char symbol);

    void Reset();
    void DumpState();
};

#endif