
#include <cctype>
#include "HuffmanNode.h"
#include "huffmanutil.h"


HuffmanNode::HuffmanNode(int character, int count, HuffmanNode* zero, HuffmanNode* one) {
    this->character = character;
    this->count = count;
    this->zero = zero;
    this->one = one;
}

bool HuffmanNode::isLeaf() const {
    return zero == NULL && one == NULL;
}


