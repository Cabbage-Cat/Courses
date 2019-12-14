#include "graph_main.h"
#include <iostream>
graph g;
graph_data data;

int main(){
  input_data(g,data);
  while(input_begin_and_end(g,data));
  return 0;
}