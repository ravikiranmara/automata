#ifndef _REGEX_NFA_SIMULATE_H_
#define _REGEX_NFA_SIMULATE_H_

#include "dfa.cpp"

using std::string;

class SimulateDfa
{
  public:
    int simulate(Automata &dfa, int start, string &str, bool &result);
};


#endif