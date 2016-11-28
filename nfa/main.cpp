#include <iostream>
#include <string>
#include <vector>
#include "globals.h"
#include "zlog.h"
#include "utils.cpp"
#include "postfix.cpp"
#include "state.cpp"
#include "fa.h"
#include "nfa.cpp"
#include "dfa.cpp"
#include "simulate.cpp"
#include "test_state.cpp"

/* using std */
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

using std::ifstream;
using std::ofstream;

/* functions prototypes */
int init_zlog();
void finalize_zlog();

int main(int argc, char *argv[]) 
{
    int status = status_success;
    string str, exp;
    Postfix postfix; 
    Utils utils;

    /* logging stuff */

    // read line 
    getline(cin, str);
    //cout << "main::Input String : " << str << endl;

    utils.AddConcatSymbol(str);
    //cout << "main::after concat symbol : " << str << endl;

    // convert to postfix
    postfix.Convert(str);
    //cout << "main::after postfix : " << str << endl;

    Nfa nfa;
    State *state, *final;
    nfa.convert(str, &state, &final);

    Dfa dfa;
    dfa.convert(state, final);
    dfaAutomata.DumpTable();
    
    SimulateDfa simdfa;
    bool result;
    
    while (cin>>str) {
        simdfa.simulate(dfaAutomata, 0, str, result);
        if(result == true)
            cout <<"yes" << endl;
        else 
            cout << "no" << endl;
    }
    
    return status;
}


/**** logging related - ignore ****/
/* we'll refine this a bit more later */
int init_zlog()
{
    /* initialize to stdout */
    zlog_init_stdout();

    /* initialize to file */
    //zlog_init("vmm.log");

    /* the output is stored in buffer and flushed
    periodically. we initialize the thread . zlog-config.h
    contains the timing value */
    zlog_init_flush_thread();

    // sample log
    zlog(ZLOG_LOC, "Global::init_zlog - initialized log params\n");

    return 0;
}

void finalize_zlog()
{
    zlog_finish();
}