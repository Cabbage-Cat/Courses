#include <bits/stdc++.h>
using namespace std;
stack<int> num_stack;
stack<char> e_stack;
map<char,int> pq;
int main(){
  pq['+'] = pq['-'] = 1;
  pq['*'] = pq['/'] = 1;
  pq['('] = 0;
  string line;
  do{
    cout << "Please input expr(q to exit):";
    cin >> line;
    int x = 0; int flag = 0;
    for (char c : line){
      if (c == '#') flag = 1;
      else if (isdigit(c)) { x = x*10  + (c-'0'); }
      else{
        if (!x) { if(flag) x=-x; num_stack.push(x); x = 0; }
        if (c==')'){
          while (e_stack.top() != '('){
            char e = e_stack.top(); e_stack.pop();
            int x1 = num_stack.top(); num_stack.pop();
            int x2 = num_stack.top(); num_stack.pop();
            switch (e)
              {
              case '+':
                num_stack.push(x2+x1);
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
          e_stack.pop();
        }
        else if (e_stack.empty() || pq[e_stack.top()] <= pq[c]) e_stack.push(c);
        else{
          while (pq.empty() || pq[e_stack.top()] > pq[c]){
            char e = e_stack.top(); e_stack.pop();
            int x1 = num_stack.top(); num_stack.pop();
            int x2 = num_stack.top(); num_stack.pop();
            switch (e)
            {
            case '+':
              num_stack.push(x2+x1);
              break;
            case '-':
              num_stack.push(x1-x2);
              break;
            }
          }
        }
      }
    }
    while (!num_stack.empty()) { cout << num_stack.top();}
  }while (line!="q");

  
  return 0;
}