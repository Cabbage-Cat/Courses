#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
const int maxv = 1000+ 10;
int prev[maxv];
bool used[maxv];
int d[maxv];
int cost[maxv][maxv];

typedef struct vertex{
  std::string name;
  int pos_x; int pos_y;
  bool operator<(const struct vertex &l) const {
    return name < l.name;
  }
  bool operator == (const struct vertex &l) const{
    return name == l.name && pos_x == l.pos_x && pos_y == l.pos_y;
  }
}vertex;

std::map<vertex,int> id_cache;
std::map<int,vertex> vertex_cache;
std::map<std::string,vertex> string_to_vertex;
int get_vertex_id(vertex& v,std::map<vertex,int>& map){
  if (!map.count(v)){
    map[v] = map.size();
    vertex_cache[map.size()-1] = v;
    string_to_vertex[v.name] = v;
  } 
  return map[v];
}

vertex& get_vertex(int idx,std::map<int,vertex>& map){
  return map[idx];
}



int V;
void dijkstra(int s){
  for (int i=0;i<V;i++) d[i] = 10000000;
  std::fill(used,used+V,false);
  std::fill(prev,prev+V,-1);
  d[s] = 0;

  while (true){
    int v = -1;
    for (int u = 0;u<V;u++)
      if (!used[u] && (v==-1||d[u]<d[v])) v = u;
    if (v==-1) break;
    used[v] = true;

    for (int u=0;u<V;u++){
      if (d[u]>d[v]+cost[v][u]){
        d[u] = d[v] + cost[v][u];
        prev[u] = v;
      }
    }
  }
}

std::vector<int> get_path(int t){
  std::vector<int> path;
  for (; t!=-1; t = prev[t]) path.push_back(t);
  std::reverse(path.begin(),path.end());
  return path;
}


int main(){
  std::string line;
  std::cin >> V; std::cin.ignore();
  for (int i=0;i<V;i++)
    for (int j=0;j<V;j++) cost[i][j] = 10000000;
  vertex v;
  for (int i=0;i<V;i++){
    std::getline(std::cin,line);
    
    std::stringstream ss(line);
    std::string token;
    std::getline(ss,token,';');
    v.name = token;
    std::getline(ss,token,';');
    v.pos_x = std::stoi(token);
    std::getline(ss,token,';');
    v.pos_y = std::stoi(token);

    get_vertex_id(v,id_cache);
  }

  int dis_count; std::cin >> dis_count; std::cin.ignore();
  for (int i=0;i<dis_count;i++){
    std::getline(std::cin,line);
    std::stringstream ss(line);
    std::string city_one,city_two;
    std::string token;
    std::getline(ss,city_one,';');
    std::getline(ss,city_two,';');
    std::getline(ss,token,';');
    
    int v1 = id_cache[string_to_vertex[city_one]]; 
    int v2 = id_cache[string_to_vertex[city_two]]; 
    cost[v1][v2] = std::stoi(token);
  }

  //std::cout << "Please input begin city :";
  std::string begin;
  std::getline(std::cin,begin);

  //std::cout << "Please input end city :";
  std::string end;
  std::getline(std::cin,end);

  if (!string_to_vertex.count(begin) || !string_to_vertex.count(end)){
    std::cout << "Your input / output is wrong. Please input again.\n";
    return 0;
  }

  int bgn_id = id_cache[string_to_vertex[begin]]; 
  int end_id = id_cache[string_to_vertex[end]]; 
  dijkstra(bgn_id);
  std::vector<int> path = get_path(end_id);
  std::cout << "Your path from " << begin << " to " << end << " is:\n";
  if (path.size() <= 1)
    std::cout << "Can't arrive.\n";
  else{
    for (int v : path){
      std::cout << vertex_cache[v].name <<  "(" << vertex_cache[v].pos_x
        << "," << vertex_cache[v].pos_y << ")" <<  " -> ";
    }
    std::cout << std::endl;
    std::cout << "Cost is: " << d[end_id];
  }

  return 0;
}