#include <iostream>
#include <new>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression = "sin(a) + cos(ab+c)";
  TPostfix postfix(expression);
  double res;

  setlocale(LC_ALL, "Russian");
  //cout << "Введите арифметическое выражение: ";
  //cin >> expression;
  //cout << expression << endl;
  postfix_calc:
  try{
      postfix.ToPostfix();
      cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
      cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
      res = postfix.Calculate();
      cout << res << endl;
  }
  catch(const EqExcepion& e){
    if(e.GetError() == EqExcepion::incorrect_expression){
        cout << "Warning:\n" << "code:" << e.GetError() 
        << endl << "comment:" << e.GetComment() << endl;
        cout << "Please edit expression" << endl;
        string temp;
        cin >> temp;
        postfix.ChangeExpression(temp);
        goto postfix_calc;
    }
    else{
       cout << "Warning:\n" << "code:" << e.GetError() 
        << endl << "comment:" << e.GetComment() << endl;
        return 2;
    }
  }
  catch(bad_alloc& e){
    cout << "Warning:\n" << "Memory allocation error" << endl;
    return 1;
  }
  return 0;
}
