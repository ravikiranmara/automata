#ifndef _REGEX_NFA_NFA_CPP_
#define _REGEX_NFA_NFA_CPP_

#include <iostream>
#include <string>
#include <stack>
#include <locale>
#include "state.cpp"
#include "fa.h"
#include "nfa.h"

// namespace using
using std::string;
using std::stack;
using std::string;
using std::cout;
using std::endl;

Nfa::Nfa() 
{
    name = 0;
}

int Nfa::pushSingleSymbol(char symbol)
{
    StackFrame stackFrame;
    
    /*
    State *s1 = new State{++name};
    State *s2 = new State{++name};
    */
    
    State *s1 = automata.GetNextState();
    State *s2 = automata.GetNextState();
    
    //cout << "single symbol (" << symbol << "): " 
    //    << s1->getName() << ", " << s2->getName() << endl;
    
    s1->AddTransition(symbol, s2);
    
    stackFrame.start = s1;
    stackFrame.final = s2;
    
    this->stateStack.push(stackFrame);
    
    return status_success;
}

int Nfa::pushConcat()
{
    StackFrame sf1, sf2;
    State *f1, *s2;
    
    //cout << "push . " << endl;
    
    sf2 = this->stateStack.top();
    this->stateStack.pop();
    
    sf1 = this->stateStack.top();
    this->stateStack.pop();    
    
    f1 = sf1.final;
    s2 = sf2.start;
    
    f1->AddTransition('e', s2);
    
    sf1.final = sf2.final;
    this->stateStack.push(sf1);
    
    return status_success;
}

int Nfa::pushOr()
{
    StackFrame sf1, sf2;
    State *s1, *s2;
    State *f1, *f2;
    
    //cout << "Push | " << endl;
    
    State *sn1 = automata.GetNextState();
    State *sn2 = automata.GetNextState();
    
    sf2 = this->stateStack.top();
    this->stateStack.pop();
    
    sf1 = this->stateStack.top();
    this->stateStack.pop();
    
    s1 = sf1.start;
    s2 = sf2.start;
    f1 = sf1.final;
    f2 = sf2.final;
    
    sn1->AddTransition('e', s1);
    sn1->AddTransition('e', s2);
    f1->AddTransition('e', sn2);
    f2->AddTransition('e', sn2);

    sf1.start = sn1;
    sf1.final = sn2;
    
    this->stateStack.push(sf1);
    return status_success;
}

int Nfa::pushRepeat() 
{
    StackFrame sf1;
    State *s1;
    State *f1;
    
    //cout << "Push * " << endl;
    
    State *sn1 = automata.GetNextState();
    State *sn2 = automata.GetNextState();

    sf1 = this->stateStack.top();
    this->stateStack.pop();

    s1 = sf1.start;
    f1 = sf1.final;
    
    sn1->AddTransition('e', s1);
    sn1->AddTransition('e', sn2);
    f1->AddTransition('e', s1);
    f1->AddTransition('e', sn2);
    
    sf1.start = sn1;
    sf1.final = sn2;
    
    this->stateStack.push(sf1);
    return status_success;
}

int Nfa::convert(string &str, State **state, State **final)
{
    int status = status_success;
    int length = str.length();
    StackFrame sf;
    
    automata.Reset();
    for(int i=0; i<length; i++) {
        if ('*' == str[i]) {
            this->pushRepeat();
        } else if ('.' == str[i]) {
            this->pushConcat();
        } else if ('|' == str[i]) {
            this->pushOr();
        } else if(isalpha(str[i])) {
            this->pushSingleSymbol(str[i]);
        } else {
            //cout << "error : " << str[i] << endl;
            status = status_failure;
            goto exit1;
        }
    }
    
    sf = this->stateStack.top();
    this->stateStack.pop();
    
    sf.start->setStateType(startState);
    sf.final->setStateType(finalState);
    *state = sf.start;
    *final = sf.final;
    
exit1:
    return status;
}

#endif