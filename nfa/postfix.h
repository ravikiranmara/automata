#ifndef _REGEX_NFA_POSTFIX_H_
#define _REGEX_NFA_POSTFIX_H_

#include <map>
#include <string>

using std::map;
using std::string;

class Postfix 
{
    map<char, int> prec;
    
  public:
    Postfix();
    int Convert(string &str);
};

#endif