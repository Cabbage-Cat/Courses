#include "graph_main.h"
#include <iostream>
#include <sstream>
#include <fstream>
void input_data(graph& g,graph_data& data){
  std::ifstream file;
  std::string filename;
  std::cout << "Please input mapdata filename:";
  std::cin >> filename; std::cin.ignore();
  file.open(filename);
  
  std::string line;
  file >> data.V; file.ignore();
  init_data(data);

  vertex v;
  for (int i=0;i<data.V;i++){
    //std::getline(std::cin,line);
    std::getline(file,line);
    
    std::stringstream ss(line);
    std::string token;
    std::getline(ss,token,';');
    v.name = token;
    std::getline(ss,token,';');
    v.pos_x = std::stoi(token);
    std::getline(ss,token,';');
    v.pos_y = std::stoi(token);

    get_vertex_id(v,g);
  }

  int dis_count; 
  file >> dis_count; file.ignore();

  for (int i=0;i<dis_count;i++){
    std::getline(file,line);

    std::stringstream ss(line);
    std::string city_one,city_two;
    std::string token;
    std::getline(ss,city_one,';');
    std::getline(ss,city_two,';');
    std::getline(ss,token,';');
    
    int v1 = g.id_cache[g.string_to_vertex[city_one]]; 
    int v2 = g.id_cache[g.string_to_vertex[city_two]]; 
    data.cost[v1][v2] = std::stoi(token);
  }
}

bool input_begin_and_end(graph& g,graph_data& data){  
  std::cout << "Please input begin city :";
  std::string begin;
  std::getline(std::cin,begin,'\n');

  std::cout << "Please input end city :";
  std::string end;
  std::getline(std::cin,end,'\n');

  if (!g.string_to_vertex.count(begin) || !g.string_to_vertex.count(end)){
    std::cout << "Your input / output is wrong. Please input again.\n";
    return false;
  }

  int bgn_id = g.id_cache[g.string_to_vertex[begin]]; 
  int end_id = g.id_cache[g.string_to_vertex[end]]; 
  dijkstra(bgn_id,data);
  std::vector<int> path = get_path(end_id,data);
  std::cout << "Your path from " << begin << " to " << end << " is:\n";
  if (path.size() <= 1)
    std::cout << "Can't arrive.\n";
  else{
    for (int v : path){
      std::cout << g.vertex_cache[v].name <<  "(" << g.vertex_cache[v].pos_x
        << "," << g.vertex_cache[v].pos_y << ")" <<  " -> ";
    }
    std::cout << std::endl;
    std::cout << "Cost is: " << data.d[end_id] << std::endl;
  }
  return true;
}