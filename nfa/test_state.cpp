#include <iostream>
#include <string>

using std::string;

int test_state()
{
    State state1;
    State state2;
    State state3;
    State state4;
    
    state1.setName(1);
    state2.setName(2);
    state3.setName(3);
    state4.setName(4);
    
    state1.AddTransition('a', &state2);
    state3.AddTransition('b', &state4);
    state1.AddTransition('e', &state4);
    
    state1.DumpState();
    state2.DumpState();
    state3.DumpState();
    state4.DumpState();
    
    std::cout <<"-------" << std::endl;
    
    return 0;
}

int test_nfa(string &str)
{
    Nfa nfa;
    string exp;
    
    State *state, *final;
    nfa.convert(str, &state, &final);
    //cout << "Start State : " << state->getName() << endl;
    //cout << "Final State : " << final->getName() << endl;
    // automata.DumpTable();
    
    Dfa dfa;
    dfa.convert(state, final);
    dfaAutomata.DumpTable();
    
    SimulateDfa simdfa;
    bool result;
    
    //cout << "input string :";
    
    while (cin >> exp) {
        simdfa.simulate(dfaAutomata, 0, exp, result);
        if(result == true)
            cout <<"yes" << endl;
        else 
            cout << "no" << endl;
    }
    
    return 0;
}