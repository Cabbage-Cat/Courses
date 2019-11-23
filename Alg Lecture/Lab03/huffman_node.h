#ifndef _huffman_node_h
#define _huffman_node_h

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "bitstream.h"
using namespace std;

struct huffman_node{
  int character;
  int count;
  huffman_node* zero; //left
  huffman_node* one; //right
  huffman_node(int character=NOT_A_CHAR,int count=0,huffman_node* zero=NULL,huffman_node* one=NULL);
  bool is_leaf() const;
  string to_string() const;
};



#endif