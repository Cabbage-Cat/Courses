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

struct vertex{
  std::string name;
  int pos_x; int pos_y;
};

std::map<vertex,int> id_cache;
std::map<int,vertex> vertex_cache;
std::map<std::string,int> name_cache;
int get_vertex_id(vertex& v,std::map<vertex,int>& map,std::map<int,vertex>& v_map){
  if (!map.count(v)){
    map[v] = map.size();
    v_map[map.size()-1] = v;
    name_cache[v.name] = map.size() -1;
  } 
  return map[v];
}

/*
  Suppose always return vertex object.
*/
vertex& get_vertex(int idx,std::map<int,vertex>& map){
  return map[idx];
}



int V;
void init(){
  for (int i=0;i<maxv;i++)
    for (int j=0;j<maxv;j++)
      cost[i][j] = 1e7;
}
void dijkstra(int s){
  std::fill(d,d+V,1e7);
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
  init();
  std::cin >> V; std::cin.ignore();
  std::string line;

  for (int i=0;i<V;i++){
    std::getline(std::cin,line);
    std::stringstream ss(line);

    std::string name, x, y;
    std::getline(ss,name,';');
    std::getline(ss,x,';');
    std::getline(ss,y,';');
    int xx = std::stoi(x); 
    int yy = std::stoi(y);
    vertex v; v.name = name; v.pos_x = xx; v.pos_y = yy;
    get_vertex_id(v,id_cache,vertex_cache);
  }

  std::cin >> V; std::cin.ignore();
  for (int i=0;i<V;i++){
    std::getline(std::cin,line);
    std::stringstream ss(line);

    std::string city_x,city_y,distance;
    std::getline(ss,city_x,';');
    std::getline(ss,city_y,';');
    std::getline(ss,distance,';');
    int dis = std::stoi(distance);
    cost[name_cache[city_x]][name_cache[city_y]] = dis;
  }




  for (int i=0;i<V;i++)
    for (int j=0;j<V;j++)
      std::cin >> cost[i][j];
  
  int s; std::cin >> s;
  int end; std::cin >> end;
  dijkstra(s);
  std::vector<int> path = get_path(end);
  for (int v : path)
    std::cout << v << " ";
  std::cout << std::endl << d[end];
  return 0;
}