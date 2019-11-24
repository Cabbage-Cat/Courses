#ifndef _huffmannode_h
#define _huffmannode_h

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "bitstream.h"
using namespace std;

/* Type: HuffmanNode
 * A node inside a Huffman encoding tree.	 Each node stores four
 * values - the character stored here (or NOT_A_CHAR if the value
 * is not a character), pointers to the 0 and 1 subtrees, and the
 * character count (weight) of the tree.
 */
struct HuffmanNode {
    int character;       // character being represented by this node
    int count;           // number of occurrences of that character
    HuffmanNode* zero;   // 0 (left) subtree (NULL if empty)
    HuffmanNode* one;    // 1 (right) subtree (NULL if empty)

    /*
     * Constructs a new node to store the given character and its count,
     * along with the given child pointers.
     */
    HuffmanNode(int character = NOT_A_CHAR, int count = 0,
                HuffmanNode* zero = NULL, HuffmanNode* one = NULL);

    /*
     * Returns true if this node is a leaf (has NULL children).
     */
    bool isLeaf() const;


};

#endif
