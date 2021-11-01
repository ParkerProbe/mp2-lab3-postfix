#include <iostream>
#include <new>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression = "8 + 7 /  ( 2 + 5 )";
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
        cout << "WARNING\n" << "code:" << e.GetError() 
        << endl << "comment:" << e.GetComment() << endl;
        cout << "Please edit expression" << endl;
        string temp;
        cin >> temp;
        postfix.ChangeExpression(temp);
        goto postfix_calc;
    }
    else{
       cout << "WARNING\n" << "code:" << e.GetError() 
        << endl << "comment:" << e.GetComment() << endl;
        return 2;
    }
  }
  catch(bad_alloc& e){
    cout << "WARNING\n" << "Memory allocation error" << endl;
    return 1;
  }
  return 0;
}
