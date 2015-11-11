#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
using namespace std;

const short NTL=-1;
class TreeNode
{
  public:
    TreeNode(char c=0,int Lleafage=NTL,int Rleafage=NTL):ch(c),left(Lleafage),right(Rleafage){};
  unsigned char ch;
  int left;
  int right;
};

class newNode:public TreeNode
{
public:
  int index;
  int freq;
  int parent;
  int numbits;
  newNode(char c=0, int Lleafage=NTL,int Rleafage=NTL,int f=0,int indx=NTL,int p=0,int nb=0):TreeNode(c,Lleafage,Rleafage),freq(f),index(indx),parent(p),numbits(nb){};
  //newNode(char* msg,int num):letter(msg),freq(num){};
  bool operator< (const newNode& rhs)const
  {
    return freq<rhs.freq;
  }
};

#endif
