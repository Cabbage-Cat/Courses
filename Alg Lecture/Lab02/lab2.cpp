#include <bits/stdc++.h>
using namespace std;
stack<int> num_stack;
stack<char> sym_stack;
map<char,int> pq;
int main(){
  pq['('] = 0; pq['+'] = pq['-'] = 1; pq['*'] = pq['/'] = 2; pq[':'] = 0;
  string line;
  int quit_flag = 1;
  while (quit_flag){
    while (!num_stack.empty()) num_stack.pop();
    while (!sym_stack.empty()) sym_stack.pop();
    cout << "Please input expr:(q to quit):";
    cin >> line;
    if (line=="q") { quit_flag = 0; continue; }
    line.push_back(':'); // End symbol.
    int x = 0; int flag = 0;
    for (int i=0;i<line.length();i++){
      if (line[i] == '#') flag = 1;
      else if (isdigit(line[i])){
        x = x*10 + (line[i]-'0');
        if (!isdigit(line[i+1])) { if (flag) { flag = 0; x = -x; } num_stack.push(x);  x = 0; }
      }
      else{
        char e = line[i];
        if (e == '(') sym_stack.push(e);
        else if (e == ')'){
          while (sym_stack.top()!='('){
            char tmpe = sym_stack.top(); sym_stack.pop();
            int x1 = num_stack.top(); num_stack.pop();
            int x2 = num_stack.top(); num_stack.pop();
            switch (tmpe){
              case '+':
              num_stack.push(x2+x1);
              break;
              case '-':
              num_stack.push(x2-x1);
              break;
              case '*':
              num_stack.push(x2*x1);
              break;
              case '/':
              num_stack.push(x2/x1);
              break;
            }
          }
          sym_stack.pop();
        }
        else if (sym_stack.empty() || sym_stack.top()=='(' || pq[sym_stack.top()] < pq[e]) sym_stack.push(e);
        else{
          while (!sym_stack.empty() && pq[sym_stack.top()] >= pq[e]) {
            char tmpe = sym_stack.top(); sym_stack.pop();
            int x1 = num_stack.top(); num_stack.pop();
            int x2 = num_stack.top(); num_stack.pop();
            switch (tmpe){
              case '+':
              num_stack.push(x1+x2);
              break;
              case '-':
              num_stack.push(x1-x2);
              break;
              case '*':
              num_stack.push(x1*x2);
              break;
              case '/':
              num_stack.push(x1/x2);
              break;
            }
          }
          sym_stack.push(e);
        }
      }
    }
      cout << num_stack.top();
  }
  return 0;
}