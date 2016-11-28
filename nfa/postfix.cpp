#ifndef _REGEX_NFA_POSTFIX_CPP_
#define _REGEX_NFA_POSTFIX_CPP_

#include "postfix.h"
#include <stack>
#include <locale>

using std::map;
using std::string;
using std::stack;

Postfix::Postfix() 
{
    prec['*'] = 30;
    prec['.'] = 40;
    prec['|'] = 50;
    prec['('] = 60; 
    prec['$'] = 80;
}

int Postfix::Convert(string &str) 
{
    int length = str.length();
    int status = status_success;
    stack<char> symStack; 
    char ch;
    string temp(str);
    str.clear();

    symStack.push('$');
    int j=0;
    for(int i=0; i<length; i++) {
        if(isalpha(temp[i])) {  // if alpha, write to output 
            str.push_back(temp[i]); 
        } else {    // is a symbol 
            if(')' == temp[i]) {
                while ('(' != (ch = symStack.top())) {
                    str.push_back(ch);
                    symStack.pop();
                }
                symStack.pop();  // to pop out (
            } else if ('(' == temp[i]) {   
                symStack.push(temp[i]);
            } else {     // for any other symbol
                while (prec[temp[i]] > prec[symStack.top()]) {
                    //std::cout << temp[i] << ":" << prec[temp[i]] 
                        //<<", " << symStack.top() << ":" << prec[symStack.top()]
                       // << std::endl;
                    str.push_back(symStack.top());
                    symStack.pop();
                }
                symStack.push(temp[i]);
            }
        }
    }

    while('$' != (ch=symStack.top())) {
        str.push_back(ch);
        symStack.pop();
    }

    return status;
}

#endif