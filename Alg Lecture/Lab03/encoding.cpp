#include "encoding.h"
#include <queue>
using namespace std;

struct compare {
  bool operator () (const huffman_node* a, const huffman_node* b) const {
    return a->count < b->count;
  }
};
Map<int,int> build_freq_table(istream& input){
  Map<int,int> freq_table;
  int c;
  while ((c=input.get())!=EOF){
    if (freq_table.containsKey(c)) freq_table[c]++;
    else freq_table.put(c,1);
  }
  freq_table.put(PSEUDO_EOF,1); // use for decompress.
  return freq_table;
}

huffman_node* build_huffman_tree(const map<int,int>& freq_table){
  priority_queue<huffman_node*,vector<huffman_node*>,compare> pq;
  for (pair<int,int> p : freq_table){
    huffman_node* node = new huffman_node(p.first,p.second);
    pq.push(node);
  }

  while (pq.size() != 1){
    huffman_node* n1 = pq.top(); pq.pop();
    huffman_node* n2 = pq.top(); pq.pop(); 
    huffman_node* node = new huffman_node(NOT_A_CHAR,n1->count+n2->count,n1,n2);
    pq.push(node);
  }
  return pq.top();
}

void build_encoding_map_helper(const huffman_node* root,Map<int,string>& encoding_map,string s){
  if (root==NULL) return;
  if (root->zero==NULL && root->one==NULL){
    encoding_map.put(root->character,s);
    s="";
  }
  else{ build_encoding_map_helper(root->zero,encoding_map,s+"0");
        build_encoding_map_helper(root->one,encoding_map,s+"1"); }
}

Map<int,string> build_encoding_map(const huffman_node* root){
  Map<int,string> encoding_map;
  build_encoding_map_helper(root,encoding_map,"");
  return encoding_map;
}

void encoding_data(istream& input,const Map<int,string> encoding_map,obitstream& output){
  int c;
  while ((c=input.get())!=EOF){
    string c_huff_code = encoding_map[c];
    for (char ch:c_huff_code) output.writeBit(ch-'0');  // ch is 0 or 1.
  }
  string eof_huff_code = encoding_map[PSEUDO_EOF];
  for (char ch:eof_huff_code) output.writeBit(ch-'0');  // ch is 0 or 1.
}
