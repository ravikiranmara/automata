#ifndef _REGEX_NFA_DFA_CPP_
#define _REGEX_NFA_DFA_CPP_

#include <vector>
#include <map>
#include <set>
#include <queue>
#include "dfa.h"

using std::vector;
using std::map;
using std::set;
using std::queue;

Dfa::Dfa() 
{
    dfamap.clear();
    queue<set<State*>> empty;
    swap(stateQueue, empty);
}


void Dfa::EpsilonClosureGroup (set<State*> stategroup, set<State*> &group)
{
    for(auto it=stategroup.begin(); it != stategroup.end(); it++) {
        group.insert(*it);
        EpsilonClosure((*it), group);
    }
    
    return;
}

void Dfa::EpsilonClosure (State* state, set<State*> &group)
{
        for(auto it=state->transition.begin(); it != state->transition.end(); it++) {
            if(it->symbol == 'e') {
                group.insert(it->to);
                EpsilonClosure(it->to, group);
            }
        }        
    
    return;
}

void Dfa::MakeFinal (set<State*> group) 
{
}

void Dfa::GotoTransition(set<State*> &group, set<State*> &newgroup, char symbol)
{
    State *state;
    for(auto it = group.begin(); it != group.end(); it++) {
        state = *it;
        for(auto tr = state->transition.begin(); tr != state->transition.end(); tr++)
            if (tr->symbol == symbol) 
                newgroup.insert(tr->to);
    }
    
    return;
}

int Dfa::AddTransition(set<State*> temp, set<State*> &newGroup, char symbol) 
{
    set<int> tempint, newGroupint;
    translateToSetInt(temp, tempint);
    translateToSetInt(newGroup, newGroupint);
    
    int from = dfamap[tempint];
    int to = dfamap[newGroupint];
    
    State *s1, *s2;
    s1 = dfaAutomata.getState(from);
    s2 = dfaAutomata.getState(to);
    
    s1->AddTransition(symbol, s2);
    
    return status_success;
}

int Dfa::checkInsertState(set<State*> &stategroup, int &dfanum) 
{
    set<int> stategroupint;
    translateToSetInt(stategroup, stategroupint);
    
    auto it = dfamap.find(stategroupint);
    
    if(it != dfamap.end()) {
        // cout << "match : " << dfamap[stategroupint] << " " << stategroupint.size()<< endl;
    }
    
    if(it == dfamap.end()) {
        State *state = dfaAutomata.GetNextState();
        dfamap.insert(std::pair<set<int>, int> (stategroupint, state->getName()));
        
        dfanum = state->getName();
        stateQueue.push(stategroup);
        //cout << "check Insert dfanum(" << dfanum << ")" << endl;
    }
    // DumpDfaMap();
    
    return status_success;
}

void Dfa::MarkGroupsFinal(State *final) 
{
    int finalname = final->getName();
    bool flag = false;
    
    for (auto it = dfamap.begin(); it != dfamap.end(); it++) {
        flag = false;
        auto state = it->first;
        for(auto jt = state.begin(); jt != state.end(); jt++) {
            if(*jt == finalname) {
                // cout << "found final" << endl;
                flag = true;
            }
        }
        
        if(true == flag) {
            dfaAutomata.getState(it->second)->setStateType(finalState);
        }
    }
}

int Dfa::convert(State *start, State *final)
{
    set<State*> startEpsilon;
    int dfanum;
    int startIndex;
    
    startEpsilon.insert(start);
    EpsilonClosure(start, startEpsilon);
    
    checkInsertState(startEpsilon, dfanum);
    // dfaAutomata.getState(0)->setStateType(startState);
    startIndex = dfanum;
    
    //cout << "Start epsilon" << endl;
    // DumpStateSet(startEpsilon);
    
    set<State*> temp;
    set<State*> newgroup, newgroupepsilon;
    while(stateQueue.size() != 0) {
        temp.clear();
        temp = stateQueue.front();
        
        for(char ch : {'a', 'b'}) {
            newgroup.clear();
            newgroupepsilon.clear();
            //cout << "State " << ch << " : " << endl;
            this->GotoTransition(temp, newgroup, ch);
            EpsilonClosureGroup(newgroup, newgroupepsilon);
            checkInsertState(newgroupepsilon, dfanum);
            this->AddTransition(temp, newgroupepsilon, ch);
            // DumpStateSet(newgroupepsilon);
        }
        
        stateQueue.pop();
        //cout << "queue size : " << stateQueue.size() << endl;
    }
    
    MarkGroupsFinal(final);
    
    // dfaAutomata.DumpTable();
    return status_success;
}

void Dfa::DumpStateSet(set<State*> &states)
{
    cout <<"-----  DFA Dump States   ------" << endl;
    for(auto it = states.begin(); it != states.end(); it++) {
        cout << "\t" << (*it)->getName() << endl;
    }
    
    return;
}

int Dfa::translateToSetInt(set<State*> &input, set<int> &output)
{
    for(auto it=input.begin(); it != input.end(); it++) {
        output.insert((*it)->getName());
    }
    
    return 0;
}

void Dfa::DumpStateSetInt(set<int> states)
{
    cout <<"-----  DFA Dump States  Int ------" << endl;
    for(auto it = states.begin(); it != states.end(); it++) {
        cout << "\t" << *it << endl;
    }
    
    return;
}

void Dfa::DumpDfaMap()
{
    cout << "dfamap dump" << endl;
    for (auto it = dfamap.begin(); it != dfamap.end(); it++) {
        DumpStateSetInt(it->first);
        cout << "second : " << it->second << endl;
    }
}

#endif