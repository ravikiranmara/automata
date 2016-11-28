#ifndef _REGEX_NFA_UTILS_CPP_
#define _REGEX_NFA_UTILS_CPP_

#include <string>
#include <locale>
#include "globals.h"

using std::string;

class Utils 
{
  public:
    Utils() { };

    int AddConcatSymbol(string &str)
    {
        int status = status_success;
        int length = str.length();
        string temp(str);

        str.clear();
        int j=0;
        for(int i=0;i<length-1; i++) {
            str.push_back(temp[i]);               
            if((isalpha(temp[i]) && temp[i+1] == '(') ||
                (isalpha(temp[i]) && isalpha(temp[i+1])) ||
                (temp[i] == ')' && isalpha(temp[i+1])) ||
                (temp[i] == '*' && isalpha(temp[i+1])) ||
                (temp[i] == ')' && temp[i+1] == '(') ||
                (temp[i] == '*' && temp[i+1] == '(')) {
                str.push_back('.');
            }
        }

        // assign the final character
        str.push_back(temp[length-1]);

        return status;
    }
};

#endif