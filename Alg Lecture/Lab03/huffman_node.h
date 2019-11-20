typedef unsigned char uchar;
typedef unsigned int uint;
const unsigned int NUM_CHARS = 255;
typedef struct {
  uint char_num;
  uchar freqs[NUM_CHARS];
}file_header;

typedef struct huffman_node{
  char ch;
  uint val;
  struct huffman_node* self,*left,*right;
}huffman_node;

