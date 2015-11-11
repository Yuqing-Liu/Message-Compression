//  Author: Sean Davis
#include "HuffmanTree.h"
#include "decoder.h"
#include <iostream>
using namespace std;
const unsigned char mask=0x80;

Decoder::Decoder()
{
} // Decoder()


Decoder::~Decoder()
{
} // ~Decoder()


void Decoder::decode(const unsigned char* encodedMessage, const int encodedSize, 
  unsigned char* decodedMessage, int *decodedSize)
{
  createTree(encodedMessage,encodedSize);
  decompress(encodedMessage,encodedSize,decodedMessage,decodedSize);
} // decode()

bool Decoder::createTree(const unsigned char* encodedMessage,const int encodedSize)
{
  deHuffmanTree.resize(2*256-1);
  int pos=1;
   deHuffmanTree[0]=newNode(char(0),NTL,NTL,0);

  for(unsigned short byte_idx=0;byte_idx<256;byte_idx++)
  {
    int current=0;
    int length=(int)encodedMessage[byte_idx*4+3];
    for(int j=0;j<length;j++)
    {
      if((mask>>j%8)==((mask>>j%8)&encodedMessage[byte_idx*4+(j/8)]))
      {
        if(deHuffmanTree[current].right==NTL)
        {
          if(j!=length-1)
            deHuffmanTree[pos]=newNode(char(0),NTL,NTL,0,pos,current);
          else
            deHuffmanTree[pos]=newNode(char(byte_idx),NTL,NTL,1,pos,current);

          deHuffmanTree[current].right=pos;
          current=pos;
          pos++;
        }else
          current=deHuffmanTree[current].right;
      }else{
        if(deHuffmanTree[current].left==NTL)
        {
           if(j!=length-1)
            deHuffmanTree[pos]=newNode(char(0),NTL,NTL,0,pos,current);
           else
            deHuffmanTree[pos]=newNode(char(byte_idx),NTL,NTL,1,pos,current);

           deHuffmanTree[current].left=pos;
           current=pos;
           pos++;
        }else
          current=deHuffmanTree[current].left;
      }
    }
  }
  return true;
}

bool Decoder::decompress(const unsigned char* encodedMessage,const int encodedSize, unsigned char* decodedMessage, int* decodedSize)
{
  int byte_idx=1024;
  int pos = 0;
  *decodedSize=0;
  while(byte_idx<encodedSize)
  {
    int index=0;
    while(deHuffmanTree[index].freq==0)
    {
      if((mask>>pos%8)==((mask>>pos%8)&encodedMessage[byte_idx]))
        index=deHuffmanTree[index].right;
      else
        index=deHuffmanTree[index].left;
      pos++;
      if(byte_idx>=encodedSize&&deHuffmanTree[index].freq==0)
        return false;
      if(pos>=8)
      {
        byte_idx++;
        pos=0;
      }
      if(byte_idx>=encodedSize&&deHuffmanTree[index].freq==0)
        return true;
    }
    if(byte_idx>=encodedSize&&deHuffmanTree[index].freq==0)
      break;
    decodedMessage[*decodedSize]=deHuffmanTree[index].ch;
    (*decodedSize)++; 
  }
  return true;
}
