#include "graph.h"

int get_vertex_id(vertex& v,graph& g){
  if (!g.id_cache.count(v)){
    g.id_cache[v] = g.id_cache.size();
    g.vertex_cache[g.id_cache.size()-1] = v;
    g.string_to_vertex[v.name] = v;
  } 
  return g.id_cache[v];
}

vertex& get_vertex(int idx,graph& g){
  return g.vertex_cache[idx];
}

void init_data(graph_data& data){
  int v = data.V;
  data.d.resize(v);
  data.prev.resize(v);
  data.used.resize(v);
  data.cost.resize(v);
  for (int i=0;i<v;i++)
    data.cost[i].resize(v);
  for (int i=0;i<v;i++)
  for (int j=0;j<v;j++) data.cost[i][j] = 10000000;
}

void dijkstra(int s,graph_data& data){
  std::fill(data.d.begin(),data.d.end(),10000000);
  std::fill(data.used.begin(),data.used.end(),false);
  std::fill(data.prev.begin(),data.prev.end(),-1);
  data.d[s] = 0;

  while (true){
    int v = -1;
    for (int u = 0;u<data.V;u++)
      if (!data.used[u] && (v==-1||data.d[u]<data.d[v])) v = u;
    if (v==-1) break;
    data.used[v] = true;

    for (int u=0;u<data.V;u++){
      if (data.d[u]>data.d[v]+data.cost[v][u]){
        data.d[u] = data.d[v] + data.cost[v][u];
        data.prev[u] = v;
      }
    }
  }
}

std::vector<int> get_path(int t,graph_data& data){
  std::vector<int> path;
  for (; t!=-1; t = data.prev[t]) path.push_back(t);
  std::reverse(path.begin(),path.end());
  return path;
}


