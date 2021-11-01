#include "postfix.h"
#include "stack.h"
#include <sstream>
#include <string>
#include <system_error>


template<class T>
void TPostfix::MakeOperation(const string& str, TStack<T>& stack, T first, T second) const {
  if(str == "+") stack.Push(first + second);
  if(str == "-") stack.Push(first - second);
  if(str == "/") stack.Push(first / second);
  if(str == "*") stack.Push(first * second);
  if(str == "^") stack.Push(pow(first , second));
  return;
}

double TPostfix::ToDoubleNum(const string& str)
{
  double tmp = stod(str);
  return tmp;
}

bool TPostfix::IfDoubleNum(const string& str)
{
  try{
    double tmp = stod(str);
    return 1;
  }
  catch(invalid_argument& ex){
    return 0;
  }
}


void TPostfix::InfixAnalyzer(const string& infix) const
{
  //Brackets
  int LBrackets = 0, RBrackets = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			LBrackets++;
		else if (infix[i] == ')')
			RBrackets++;
	}
	if (LBrackets != RBrackets) {
		throw EqExcepion(EqExcepion::zero_division, "Differnt count of left and right brackets");
  }

  //Expression don`t start and end with operation (start: except + and -)
  //Make infix without ()
  string t_infix = "";
  for(char c : infix){
    if(c!= '(' && c!= ')')
      t_infix+=c;
  }
  if(!(t_infix[0] == '+' || t_infix[0] == '-')) {
    for(auto map : op_data){
      if(map.first.find(t_infix[0]) != string::npos)
        throw EqExcepion(EqExcepion::start_with_incorrect_operator,
         "Expression start with operator except + and -");
    }
  }
  for(auto map : op_data){
    if(map.first.find(t_infix[t_infix.size()-1] != string::npos))
      throw EqExcepion(EqExcepion::end_with_operator,
        "Expression end with operator");
  }

  //Operators don`t go one to another
  bool op_pr = false;
  for(char c : infix){
    if(c!= '(' && c!= ')') {
      if(IsInclude(op_data, string(1,c)))
        if(op_pr){
          throw EqExcepion(EqExcepion::two_operator_side_by_side, "After operator go operator");
        }
        else{ op_pr = true;}
      else { op_pr = false;}
    }
    else {op_pr = false; }
  }

  // No open bracket before the operator
  bool open_bracket_pr = false;
  for(char c : infix){
    if(c == '('){
      open_bracket_pr = true;
    }
    else{
      open_bracket_pr = false;
      if(c != ')' && IsInclude(op_data, string(1,c)))
        if(open_bracket_pr)
          throw EqExcepion(EqExcepion::bracket_mistake, "Operator after the open bracket");
    }
  }
}


vector<string> TPostfix::Split(const string& str) const
{
  vector <string> tmp_vec;
  string tmp_str = "";
  bool isword = false;
  for (char c : str) {
      if (IsInclude(op_data, string(1, c))) {
          if (isword) {
              tmp_vec.push_back(tmp_str);
              tmp_str = "";
              isword = false;
          }
          tmp_vec.push_back(string(1, c));
          continue;
      }
      else if (c == ' ') {
          if (isword) {
            tmp_vec.push_back(tmp_str);
            tmp_str = "";
            isword = false;
          }
      }
      else {
          isword = true;
          tmp_str += c;
      }
  }
  if (isword) {
      tmp_vec.push_back(tmp_str);
  }
  return tmp_vec;
}

int TPostfix::Priority(const string& key)
{
  return op_data[key].priority;
}

int TPostfix::Operands(const string& key)
{
  return op_data[key].operands;
}

template<class T>
bool TPostfix::IsInclude(const map<string, T>& map, const string& key) const
{
  for(auto pair : map) {
    if(pair.first == key)
      return true;
  }
  return false;
}


string TPostfix::ToPostfix()
{
  TStack<string> OpStack(stacklen);
  postfix.clear();
  postfix_str = "";
  vector <string> vec_infix = Split(infix);
  for (int i = 0; i < stacklen; i++)
  {
      if (!IsInclude(op_data, vec_infix[i])) {
          postfix.push_back(vec_infix[i]);
          continue;
      }
      if (OpStack.IsEmpty()) {
          OpStack.Push(vec_infix[i]);
          continue;
      }
      if (vec_infix[i] == "(") {
          OpStack.Push(vec_infix[i]);
          continue;
      }
      if (vec_infix[i] == ")")
      {
          while (OpStack.Top() != "(")
          {
              postfix.push_back(OpStack.PopTop());
          }
          OpStack.PopTop();
          continue;
      }
      else
      {
          while (!OpStack.IsEmpty()) {
              if ((op_data[vec_infix[i]].priority >= op_data[OpStack.Top()].priority) && (OpStack.Top() != "(")) {
                  postfix.push_back(OpStack.PopTop());
              }
              else
                  break;
          }
          OpStack.Push(vec_infix[i]);
      }
  }
  while (!OpStack.IsEmpty())
  {
	  postfix.push_back(OpStack.PopTop());
  }
  for (string str : postfix)
      postfix_str += str;
  return postfix_str;
}



double TPostfix::Calculate()
{
  double first, second;
  double num;
  TStack<double> value(stacklen);
  vector<string> elements = postfix;
  map<string, double> operands;
  for (string element : elements){
      if(!IsInclude(op_data, element)){
        if(IsInclude(operands, element))
          value.Push(operands[element]);
        else if (IfDoubleNum(element)){
          num = ToDoubleNum(element);
          operands.emplace(element, num);
          value.Push(num);
        }
        else {
          double temp;
          cout << element << ":";
          cin >> temp;
          operands.emplace(element, temp);
          value.Push(temp);
          cout << "\n";
        }
      }
      else{
        second = value.PopTop();
        first = value.PopTop();
        MakeOperation(element, value, first, second); //Edit for 1 argument
      }
      
  }
  return value.PopTop();
}

