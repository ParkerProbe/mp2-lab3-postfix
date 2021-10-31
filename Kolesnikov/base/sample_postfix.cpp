#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression = "(a-b)*c";
  TPostfix postfix(expression);
  double res;

  setlocale(LC_ALL, "Russian");
  //cout << "Введите арифметическое выражение: ";
  //cin >> expression;
  //cout << expression << endl;
  postfix.ToPostfix();
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << res << endl;

  return 0;
}
