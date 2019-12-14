#include <string>
#include <map>
#include <vector>
#include <algorithm>
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

typedef struct {
  std::map<vertex,int> id_cache;
  std::map<int,vertex> vertex_cache;
  std::map<std::string,vertex> string_to_vertex;
}graph;

typedef struct{
  int V;
  std::vector<int> prev;
  std::vector<int> d;
  std::vector<bool> used;
  std::vector<std::vector<int>> cost;
}graph_data;

void init_data(graph_data&);
int get_vertex_id(vertex&,graph&);

vertex& get_vertex(int,graph&);

void dijkstra(int,graph_data&);

std::vector<int> get_path(int t,graph_data& data);
