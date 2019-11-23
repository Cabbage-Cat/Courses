#include "huffman_node.h"
huffman_node::huffman_node(int c,int count,huffman_node* zero,huffman_node* one){
  this->character = c; this->count = count; this->zero = zero; this->one = one;
}

bool huffman_node::is_leaf() const{
  return zero==NULL && one==NULL;
}

string huffman_node::to_string() const{
  
}