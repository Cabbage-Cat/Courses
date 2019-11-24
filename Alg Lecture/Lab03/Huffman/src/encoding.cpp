#include "encoding.h"
#include <queue>
#include "filelib.h"
Map<int, int> buildFrequencyTable(istream& input) {
    Map<int, int> freqTable;
    int character;
    while ((character=input.get())!=EOF){
        if (freqTable.containsKey(character)) freqTable[character]++;
        else freqTable.put(character,1);
    }
    freqTable.put(PSEUDO_EOF,1);
    return freqTable;
}
struct cmp {
  bool operator () (const HuffmanNode* a, const HuffmanNode* b) const {
    return a->count > b->count;
  }
};
HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    priority_queue<HuffmanNode*,vector<HuffmanNode*>,cmp> pq;
    for (int k : freqTable.keys()){
        int v = freqTable[k];
        HuffmanNode* node = new HuffmanNode(k,v);
        pq.push(node);
    }

    while (pq.size() != 1){
        HuffmanNode* n1 = pq.top(); pq.pop();
        HuffmanNode* n2 = pq.top(); pq.pop();
        HuffmanNode* node = new HuffmanNode(NOT_A_CHAR,n1->count+n2->count,n1,n2);
        pq.push(node);
    }
    return pq.top();
}

void buildEncodingMapHelper(const HuffmanNode* root,Map<int,string>& encodingMap,string s){
    if (root==NULL) return;
    if (root->zero==NULL && root->one==NULL){
        encodingMap.put(root->character,s);
        s="";
        return;
    }
    else{ buildEncodingMapHelper(root->zero,encodingMap,s+"0");
        buildEncodingMapHelper(root->one,encodingMap,s+"1"); }
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    buildEncodingMapHelper(encodingTree,encodingMap,"");
    return encodingMap;
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    int c;
    while ((c=input.get())!=EOF){
        string c_huff_code = encodingMap[c];
        for (char ch:c_huff_code) output.writeBit((int)(ch-'0'));  // ch is 0 or 1.
    }
    string eof_huff_code = encodingMap[PSEUDO_EOF];
    for (char ch:eof_huff_code) output.writeBit((int)(ch-'0'));  // ch is 0 or 1.
}

void decodeDataHelper(ibitstream& input,HuffmanNode* root,ostream& output,bool& flag){
    if (root->isLeaf()){
        if (root->character == PSEUDO_EOF) { flag=false; return; }
        output.put(root->character);
        return;
    }
    int bit = input.readBit();
    if (bit==1) { decodeDataHelper(input,root->one,output,flag); }
    else if (bit==0) { decodeDataHelper(input,root->zero,output,flag); }
    else { flag = false; cout << "Decoding huffmanTree error!\nThe file is not huffman file.\n"; return; }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    bool flag = true;
    while (flag){
        decodeDataHelper(input,encodingTree,output,flag);
    }
    freeTree(encodingTree);
}

void compress(istream& input, obitstream& output) {
    Map<int,int> freqTable = buildFrequencyTable(input);
    HuffmanNode* root = buildEncodingTree(freqTable);
    Map<int,string> encode_table = buildEncodingMap(root);
    output << freqTable;   // Map has overwrite "<<" op.
    rewindStream(input);
    encodeData(input,encode_table,output);
    freeTree(root);
}

void decompress(ibitstream& input, ostream& output) {
    Map<int,int> freqTable;
    input >> freqTable;
    HuffmanNode* encoding_tree = buildEncodingTree(freqTable);
    decodeData(input,encoding_tree,output);
}

void freeTree(HuffmanNode* node) {
    if (node!=NULL){
        freeTree(node->one); freeTree(node->zero);
        delete node;
    }
}
