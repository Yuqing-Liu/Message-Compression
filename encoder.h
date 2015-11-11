// Author: Sean Davis
#ifndef ENCODER_H
#define	ENCODER_H
#include "HuffmanTree.h"
#include "vector.h"
using namespace std;

class Encoder
{
public:
  Encoder();
  void buildTree();
  //void buildTree(const unsigned char* message,const int size,int* frequency);
  void encode(const unsigned char *message, const int size, 
    unsigned char *encodedMessage, int *encodedSize);
  ~Encoder();
  //void creatBit();
  //bool compress(const unsigned char *message,const int size,unsigned char *encodedMessage,int *encodedSize);

private:
  vector<newNode> huffmanTree;
  unsigned long leafSize;
  unsigned long treeSize;
  vector<int> frequency;
  unsigned int lengths[256];
  unsigned int charpath[256][8];
  unsigned long fileSize;
  void creatBit();
  bool compress(const unsigned char *message,const int size,unsigned char *encodedMessage,int *encodedSize);
};

#endif	/* ENCODER_H */

