#include <cstring>
#include <queue>
//#include "std::queueAr.h"
#include "Tuple.h"


#ifndef BTreeNodeH
  #define BTreeNodeH

extern int _distinct_cnt;

class InternalNode;  // forward declaration

class BTreeNode
{
protected:
  int count;
  int leafSize;
  InternalNode *parent;
  BTreeNode *leftSibling;
  BTreeNode *rightSibling;
  Tuple MIN;
public:
  BTreeNode(int LSize, InternalNode *p, BTreeNode *left, BTreeNode *right);
  virtual ~BTreeNode() {}
  int getCount() const;
  BTreeNode* getLeftSibling();
  virtual Tuple getMinimum()const = 0;
  BTreeNode* getRightSibling();
  virtual BTreeNode * insert(Tuple value) = 0;
  //virtual void delete(Tuple value) = 0;

  virtual BTreeNode * find( Tuple value ) = 0; // return null if not found
  virtual BTreeNode * find_leq ( Tuple value ) = 0; // return null if not found
  virtual BTreeNode * find_geq ( Tuple value ) = 0; // return null if not found
  virtual BTreeNode * get_first () = 0;
  virtual void print(std::queue <BTreeNode*> &_queue) = 0;
  void setLeftSibling(BTreeNode *left);
  void setParent(InternalNode *p);
  void setRightSibling(BTreeNode *right);

}; //BTreeNode class

#endif


#ifndef InternalNodeH
  #define InternalNodeH


class InternalNode:public BTreeNode
{
  int internalSize;
  BTreeNode **children;
  Tuple *keys;
public:
  InternalNode(int ISize, int LSize, InternalNode *p,
    BTreeNode *left, BTreeNode *right);
  BTreeNode* addPtr(BTreeNode *ptr, int pos);
  void addToLeft(BTreeNode *last);
  void addToRight(BTreeNode *ptr, BTreeNode *last);
  void addToThis(BTreeNode *ptr, int pos); // pos is where the node should go
  Tuple getMinimum()const;
  InternalNode* insert(Tuple value); // returns pointer to new
  //void delete(Tuple value);
    // InternalNode it it splits else NULL
  void insert(BTreeNode *oldRoot, BTreeNode *node2); // if root splits use this
  void insert(BTreeNode *newNode); // from a sibling
  BTreeNode * find( Tuple value ); // return null if not found
  BTreeNode * find_leq ( Tuple value ); // return null if not foun
  BTreeNode * find_geq ( Tuple value ); // return null if not found
  void print(std::queue <BTreeNode*> &_queue);
  BTreeNode * get_first ();
  void resetMinimum(const BTreeNode* child);
  InternalNode* split(BTreeNode *last);
  // void updateChildSiblings(int pos);
}; // InternalNode class



#endif

#ifndef LeafNodeH
#define LeafNodeH


class LeafNode:public BTreeNode
{
  Tuple *values;
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  void addToLeft(Tuple value, Tuple last);
  void addToRight(Tuple value, Tuple last);
  void addToThis(Tuple value);
  void addValue(Tuple value, Tuple &last);
  Tuple getMinimum() const;
  LeafNode* insert(Tuple value); // returns pointer to new Leaf if splits
  //void delete(Tuple value);
  BTreeNode * find( Tuple value ); // return null if not found
  BTreeNode * find_leq ( Tuple value ); // return null if not found
  BTreeNode * find_geq ( Tuple value ); // return null if not found
  // else NULL
  void print(std::queue <BTreeNode*> &queue);
  BTreeNode * get_first ();
  LeafNode* split(Tuple value, Tuple last);
  Tuple * get_values();


}; //LeafNode class

#endif

#ifndef BTREE_H
  #define BTREE_H


class BTree
{
  BTreeNode *root;
  int internalSize;
  int leafSize;
  int distinct_cnt;
public:
  BTree(int ISize, int LSize);
  void insert(Tuple value);
  void remove(Tuple value);
  BTreeNode * find( Tuple value ); // return null if not found
  BTreeNode * find_leq ( Tuple value ); // return null if not found
  BTreeNode * find_geq ( Tuple value ); // return null if not found
  void print();
  BTreeNode * get_first ();
  int get_distinct_cnt();
}; // BTree class
#endif
