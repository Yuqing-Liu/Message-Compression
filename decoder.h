// Author: Sean Davis
#ifndef DECODER_H
#define	DECODER_H
#include "HuffmanTree.h"
#include "vector.h"
using namespace std;

class Decoder
{
public:
  Decoder();
  ~Decoder();
  void decode(const unsigned char* encodedMessage, const int encodedSize, 
    unsigned char* decodedMessage, int *decodedSize);
  bool createTree(const unsigned char* encodedMessage,const int encodedSize);
  bool decompress(const unsigned char* encodedMessage,const int encodedSizem,unsigned char* decodedMessage,int* decodedSize);
private:
  vector<newNode> deHuffmanTree;
};

#endif	/* DECODER_H */

