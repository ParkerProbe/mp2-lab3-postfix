#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include "eq_exception.h"

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <sstream>

#include "stack.h"

using namespace std;

struct OpData
{
    int operands;
    int priority;
};

class TPostfix
{
  string infix;
  string postfix;
  int stacklen;

  map<string, OpData> op_data = {
    {"(",{0,0}},
    {")",{0,0}},
    {"+",{2,1}},
    {"-",{2,1}},
    {"*",{2,2}},
    {"/",{2,2}},
    {"^",{2,2}}
  };

  template<class T>
  bool IsInclude(const map<string, T>& map, const string& key) const; 
  vector<string> Split(const string& str) const;
  int Priority(const string& key);
  int Operands(const string& key);
  double ToDoubleNum(const string& str);
  bool IfDoubPleNum(const string& str);


  template<class T>
  void MakeOperation(const string& str, TStack<T>& stack, T first, T second) const;
public:
  TPostfix() : infix(""), postfix("") {}
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  void InfixAnalyzer(const string& infix) const;
  string ToPostfix(const string& infx);
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
