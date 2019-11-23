#ifndef _encoding_h
#define _encoding_h

#include "huffman_node.h"
#include "bitstream.h"
#include "map.h"
using namespace std;

Map<int,int> build_freq_table(istream& input);
huffman_node* build_huffman_tree(const map<int,int>& freq_table);
Map<int,string> build_encoding_map(const huffman_node* root);
void encoding_data(istream& input,const Map<int,string> encoding_map,obitstream& output);
void compress(istream& input,obitstream& output);

#endif