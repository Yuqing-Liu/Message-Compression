#include "encoder.h"
#include "HuffmanTree.h"
#include "BinaryHeap.h"
#include "StackLi.h"
#include<iostream>
#include<cstring>
using namespace std;

const unsigned int initializer = 0x80000000;

Encoder::Encoder()
{
  leafSize = 0;
  memset(charpath,0,sizeof(unsigned int)*256*8);
  memset(lengths,0,sizeof(unsigned int)*256);
} // Encoder()


Encoder::~Encoder()
{
} // ~Encoder()


void Encoder::buildTree()
{
  treeSize=2*leafSize - 1;
  unsigned short Index=0;
  newNode leftside,rightside;
  BinaryHeap <newNode> newBinaryHeap(treeSize);

  huffmanTree.resize(treeSize); 
  for(unsigned short i=0;i<256;i++)
  {
    if(frequency[i]!=0)
    {
    huffmanTree[Index]=newNode((unsigned)char(i),-1,-1,frequency[i],Index);     
    newBinaryHeap.insert(huffmanTree[Index]);
     Index++;
    }
  }
  for(unsigned short k=1;k<=leafSize-1;k++)
  {
   leftside=newBinaryHeap.findMin();
   newBinaryHeap.deleteMin();
   rightside=newBinaryHeap.findMin();
   newBinaryHeap.deleteMin();

   huffmanTree[Index]=newNode((unsigned) char(0),leftside.index,rightside.index,leftside.freq+rightside.freq,Index);
   newBinaryHeap.insert(huffmanTree[Index]);
   huffmanTree[leftside.index].parent=Index;
   huffmanTree[rightside.index].parent=Index;
   Index++;
  }
}

void Encoder::encode(const unsigned char *message, const int size, 
  unsigned char *encodedMessage, 
    int *encodedSize)
{
  int counts[256]={0};
  for(int i=0;i<size;i++){
     counts[message[i]]++;
  }
  frequency.resize(256);
  for(int i=0;i<256;i++){
    if(counts[i]!=0)
    {
      frequency[i]=counts[i];
      leafSize++;
    }
}
buildTree();
creatBit();
compress(message,size,encodedMessage,encodedSize);
}  // encode()

void Encoder::creatBit()
{
    newNode tmpNode;
    StackLi<bool> path;
    for(unsigned short i=0;i<leafSize;i++)
    {
      int count=0;
      tmpNode=huffmanTree[i];
      while(tmpNode.index+1!=(huffmanTree.size()))
      { 
       if(tmpNode.index==huffmanTree[tmpNode.parent].right)
          path.push(1);
       else
          path.push(0);
       tmpNode=huffmanTree[tmpNode.parent];    
      }
      while(!path.isEmpty())
     {
       if(path.top()==1)
         charpath[huffmanTree[i].ch][0] |= (initializer>>count);
       path.pop();
       count++;
     }
    huffmanTree[i].numbits=count;
    lengths[huffmanTree[i].ch]=count;
    for(unsigned short j=1;j<8;j++)
     charpath[huffmanTree[i].ch][j] |= (charpath[huffmanTree[i].ch][j-1]>>1);

   count=0;

  }
}

bool Encoder::compress(const unsigned char *message,const int size,unsigned char *encodedMessage, int *encodedSize)
{
  int altnum=1024;
  int pos=0;
unsigned int adjcharpath[1];
  for(unsigned short j=0;j<256;j++)
  {
    encodedMessage[4*j+0] |= ((char*)&charpath[j])[3];
    encodedMessage[4*j+1] |= ((char*)&charpath[j])[2];
    encodedMessage[4*j+2] |= ((char*)&charpath[j])[1];
    encodedMessage[4*j+3] |= ((char*)&lengths[j])[0];
  }
  for(int k=0;k<size;k++)
  {
    encodedMessage[altnum+0] |= ((char*)&charpath[message[k]][pos])[3];
    encodedMessage[altnum+1] |= ((char*)&charpath[message[k]][pos])[2];
    encodedMessage[altnum+2] |= ((char*)&charpath[message[k]][pos])[1];
    encodedMessage[altnum+3] |= ((char*)&charpath[message[k]][pos])[0];
    altnum = altnum+(pos+lengths[message[k]])/8;
    pos=(pos+lengths[message[k]])%8;
  }
  //encodedMessage[1024]=((char*)&pos)[0];
    if(pos==0)
      *encodedSize=altnum;
    else
      *encodedSize=altnum+1;
    return true;
}
