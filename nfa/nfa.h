#ifndef _REGEX_NFA_NFA_H_
#define _REGEX_NFA_NFA_H_

using std::string;
using std::stack;
using std::string;

typedef struct StackFrame 
{
    State *start, *final;
} StackFrame;

class Nfa 
{
    stack<StackFrame> stateStack;
    int name;

  public:
    Nfa();
    
    int pushSingleSymbol(char symbol);
    int pushConcat();
    int pushOr();
    int pushRepeat();

    int convert(string &str, State **state, State **final);
};


#endif