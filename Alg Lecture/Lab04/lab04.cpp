#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
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
int get_vertex_id(vertex& v,std::map<vertex,int>& map){
  if (!map.count(v)) map[v] = map.size();
  return map[v];
}

vertex& get_vertex(int idx,std::map<int,vertex>& map){
  
}



int V;
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
  std::cin >> V;
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