#ifndef _REGEX_NFA_DFA_H_
#define _REGEX_NFA_DFA_H_

#include <vector>
#include <map>
#include <set>
#include <queue>
#include "state.cpp"

using std::vector;
using std::map;
using std::set;
using std::queue;

class Dfa 
{
    map<set<int>, int> dfamap;
    queue<set<State*>> stateQueue;
    
  public:
    Dfa();
    void EpsilonClosure (State* start, set<State*> &group);
    void EpsilonClosureGroup (set<State*> stategroup, set<State*> &group);
    void MakeFinal (set<State*> group);
    int AddTransition(set<State*> temp, set<State*> &newGroup, char symbol);
    void GotoTransition(set<State*> &group, set<State*> &newgroup, char symbol);
    int checkInsertState(set<State*> &stategroup, int &dfanum);
    int convert(State *start, State *final);
    void DumpStateSet(set<State*> &state);
    int translateToSetInt(set<State*> &input, set<int> &output);
    void DumpStateSetInt(set<int> states);
    void DumpDfaMap();
    void MarkGroupsFinal(State *final);
}; 


#endif