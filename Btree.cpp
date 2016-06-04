#include <iostream>
#include <queue>
#include "Btree.h"
#include "Tuple.h"



using namespace std;

int _distinct_cnt;


BTree::BTree(int ISize, int LSize):internalSize(ISize), leafSize(LSize)
{
  distinct_cnt = 0;
  root = new LeafNode(LSize, NULL, NULL, NULL);
} // BTree::BTree()


void BTree::insert(const Tuple value)
{
  _distinct_cnt = distinct_cnt;
  //cout << distinct_cnt << " " << value.value.num << endl;
  BTreeNode *ptr = root->insert(value);
  if(ptr) // root split
  {
    InternalNode *IPtr = new InternalNode(internalSize, leafSize,
      NULL, NULL, NULL);
    IPtr->insert(root, ptr);
    root = IPtr;
  } // if root split

  distinct_cnt = _distinct_cnt; // update disctinct count;
} // BTree::insert()

void BTree::remove(Tuple value)
{
  BTreeNode * node = root->find( value );
  if( node )
  {
    for ( int i = 0; i < node->getCount() - 1; i++ )
      if ( ((LeafNode *)node)->get_values()[i] == value )
      {
        //cout << i << endl;
        for ( int j = 0; j < (int)  (( (LeafNode *) node)->get_values()[i].offset.size() - 1); j++ )
          if( ( (LeafNode *)node)->get_values()[i].offset[j] == value.offset[0] )
            ((LeafNode *)node)->get_values()[i].offset[j] = -1;
      }
  }
}

BTreeNode * BTree::find( Tuple value )
{
  return root->find( value );
} // return null if not found

BTreeNode * BTree::find_leq( Tuple value )
{
  return root->find_leq( value );
}

BTreeNode * BTree::find_geq( Tuple value )
{
  return root->find_geq( value );
}



void BTree::print()
{
  BTreeNode *BTreeNodePtr;
  queue<BTreeNode*> queue;

  queue.push(root);
  while(!queue.empty())
  {
    BTreeNodePtr = queue.front();
    queue.pop();
    BTreeNodePtr->print(queue);
  } // while
} // BTree::print()

BTreeNode * BTree::get_first ()
{
  return root->get_first();
}

int BTree::get_distinct_cnt()
{
  int cnt = 0;
  LeafNode * node = ( LeafNode * ) get_first();
  while ( node )
  {
    cnt += node->getCount();
//    cout << cnt << endl;
    node = ( LeafNode * ) node->getRightSibling();
  }

  return cnt;
}

BTreeNode::BTreeNode(int LSize, InternalNode *p, BTreeNode *left,
  BTreeNode *right) : count(0), leafSize(LSize), parent(p), leftSibling(left),
  rightSibling(right)
{
} // BTreeNode()

int BTreeNode::getCount() const
{
  return count;
} // getCount()


BTreeNode* BTreeNode::getLeftSibling()
{
  return leftSibling;
} // getLeftSibling()

void BTreeNode::setParent(InternalNode *p)
{
  parent = p;
} // setParent()

BTreeNode* BTreeNode::getRightSibling()
{
  return rightSibling;
} // getRightSibling()

void BTreeNode::setLeftSibling(BTreeNode *left)
{
  leftSibling = left;
} // setLeftSibling()

void BTreeNode::setRightSibling(BTreeNode *right)
{
  rightSibling = right;
} // setLeftSibling()

// internal node



InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new Tuple[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()

BTreeNode* InternalNode::addPtr(BTreeNode *ptr, int pos)
{ // called when original was full, pos is where the node belongs.
  if(pos == internalSize)
    return ptr;

  BTreeNode *last = children[count - 1];

  for(int i = count - 2; i >= pos; i--)
  {
    children[i + 1] = children[i];
    keys[i + 1] = keys[i];
  } // shift things to right to make room for ptr, i can be -1!

  children[pos] = ptr;  // i will end up being the position that it is inserted
  keys[pos] = ptr->getMinimum();
  ptr->setParent(this);
  return last;
} // InternalNode:: addPtr()


void InternalNode::addToLeft(BTreeNode *last)
{
  ((InternalNode*)leftSibling)->insert(children[0]);

  for(int i = 0; i < count - 1; i++)
  {
    children[i] = children[i + 1];
    keys[i] = keys[i + 1];
  }
  _distinct_cnt++;
  children[count - 1] = last;
  keys[count - 1] = last->getMinimum();
  last->setParent(this);
  if(parent)
    parent->resetMinimum(this);
} // InternalNode::ToLeft()

void InternalNode::addToRight(BTreeNode *ptr, BTreeNode *last)
{
  ((InternalNode*) rightSibling)->insert(last);
  _distinct_cnt++;
  if(ptr == children[0] && parent)
    parent->resetMinimum(this);
} // InternalNode::addToRight()



void InternalNode::addToThis(BTreeNode *ptr, int pos)
{  // pos is where the ptr should go, guaranteed count < internalSize at start
  int i;

  for(i = count - 1; i >= pos; i--)
  {
      children[i + 1] = children[i];
      keys[i + 1] = keys[i];
  } // shift to the right to make room at pos

  children[pos] = ptr;
  keys[pos] = ptr->getMinimum();
  count++;
  ptr->setParent(this);

  if(pos == 0 && parent)
    parent->resetMinimum(this);
} // InternalNode::addToThis()

Tuple InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return MIN;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(Tuple value)
{  // count must always be >= 2 for an internal node
  int pos; // will be where value belongs

  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

  BTreeNode *last, *ptr = children[pos]->insert(value);
  if(!ptr)  // child had room.
    return NULL;

  if(count < internalSize)
  {
    addToThis(ptr, pos + 1);
    return NULL;
  } // if room for value

  last = addPtr(ptr, pos + 1);

  if(leftSibling && leftSibling->getCount() < internalSize)
  {
    addToLeft(last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < internalSize)
    {
      addToRight(ptr, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(last);
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  children[0] = oldRoot;
  children[1] = node2;
  keys[0] = oldRoot->getMinimum();
  keys[1] = node2->getMinimum();
  count = 2;
  children[0]->setLeftSibling(NULL);
  children[0]->setRightSibling(children[1]);
  children[1]->setLeftSibling(children[0]);
  children[1]->setRightSibling(NULL);
  oldRoot->setParent(this);
  node2->setParent(this);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *newNode)
{ // called by sibling so either at beginning or end
  int pos;

  if(newNode->getMinimum() <= keys[0]) // from left sibling
    pos = 0;
  else // from right sibling
    pos = count;

  addToThis(newNode, pos);
} // InternalNode::insert(BTreeNode *newNode)

BTreeNode * InternalNode::find( Tuple value )
{
  int pos;

  for(pos = count - 1; pos >= 0 && value < keys[pos] ; pos--);

  return children[pos]->find( value );
} // return null if not found

BTreeNode * InternalNode::find_leq( Tuple value )
{
  int pos;

  for(pos = count - 1; pos >= 0 && value < keys[pos] ; pos--);

  return children[pos]->find_leq( value );
} // return null if not found

BTreeNode * InternalNode::find_geq( Tuple value )
{
  int pos;

  for(pos = count - 1; pos > 0 && value <= keys[pos] ; pos--);

  return children[pos]->find_geq( value );
} // return null if not found

void InternalNode::print(queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
  {
  	if ( keys[i].datatype == NUM)	
    	cout << keys[i].value.num << ' ';
	else
    	cout << keys[i].value.str << ' ';
  }
  cout << endl;

  for(i = 0; i < count; i++)
    queue.push(children[i]);

} // InternalNode::print()

BTreeNode * InternalNode::get_first()
{
  return children[ 0 ]->get_first();
}

void InternalNode::resetMinimum(const BTreeNode* child)
{
  for(int i = 0; i < count; i++)
    if(children[i] == child)
    {
      keys[i] = children[i]->getMinimum();
      if(i == 0 && parent)
        parent->resetMinimum(this);
      break;
    }
} // InternalNode::resetMinimum()


InternalNode* InternalNode::split(BTreeNode *last)
{
  InternalNode *newptr = new InternalNode(internalSize, leafSize,
    parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(newptr);

  rightSibling = newptr;

  for(int i = (internalSize + 1) / 2; i < internalSize; i++)
  {
    newptr->children[newptr->count] = children[i];
    newptr->keys[newptr->count++] = keys[i];
    children[i]->setParent(newptr);
  }

  newptr->children[newptr->count] = last;
  newptr->keys[newptr->count++] = last->getMinimum();
  last->setParent(newptr);
  count = (internalSize + 1) / 2;
  return newptr;
} // split()




LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new Tuple[LSize];
}  // LeafNode()

void LeafNode::addToLeft(Tuple value, Tuple last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft()

void LeafNode::addToRight(Tuple value, Tuple last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(Tuple value)
{
  int i;

  for(i = 0; i < count; i++ )
  {
    if ( values[i] == value )
    {
//cout << "repeat" << endl;
      values[i].insert( value.offset[0] );
      return;
    }
  } // if the key already in the tree, add one more offset to existing node.


  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];


  values[i + 1] = value;
  count++;
  _distinct_cnt++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()

/*
bool LeafNode::add_duplicate( Tuple value )
{
  for(int i = 0; i < count; i++ )
  {
    if ( values[i] == value )
    {
      values[i].insert( value.offset[0] );
      return true;
    }
  }
  return false
}
*/

void LeafNode::addValue(Tuple value, Tuple &last)
{


  int i;

  if(value > values[count - 1])
    last = value;
  else
  {
    last = values[count - 1];

    for(i = count - 2; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];
    // i may end up at -1
    values[i + 1] = value;
  }
} // LeafNode:: addValue()



Tuple LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return MIN;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(Tuple value)
{

  for(int i = 0; i < count; i++ )
  {
    if ( values[i] == value )
    {
      //cout << value.value.num << endl;
      values[i].insert( value.offset[0] );
      return NULL;
    }

  }

  Tuple last;

  if(count < leafSize)
  {
    addToThis(value);
    return NULL;
  } // if room for value

  addValue(value, last);
  //_distinct_cnt++;
  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addToLeft(value, last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
    {
      addToRight(value, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

BTreeNode * LeafNode::find( Tuple value )
{
  for ( int i = count - 1; i >= 0 ; i-- )
  {
    //cout << values[i].value.str << endl;
    if( value == values[i]  )
    {
      return this;
    }
  }
  return NULL;
}

BTreeNode * LeafNode::find_leq( Tuple value )
{
  for ( int i = count - 1; i >= 0 ; i-- )
  {
    //cout << values[i].value.str << endl;
    if( value <= values[i] )
    {
      return this;
    }
  }
  return NULL;
}

BTreeNode * LeafNode::find_geq( Tuple value )
{
  return this;
  /*
  //BTreeNode * to_return = NULL;
  for ( int i = count - 1; i >= 0 ; i-- )
  {
    //cout << values[i].value.num << endl;
    //if( value <= values[i] )

    if( value >= values[i] )
    {
      return this;
    }
  }
  //cout << "null" << endl;
  return NULL;
  */
}

void LeafNode::print(queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
  {
    if ( values[i].datatype == NUM )
      cout << values[i].value.num << ' ';// << values[i].offset[0] << " ";
    else
      cout << values[i].value.str << ' ';
  }
  cout << endl;
} // LeafNode::print()

BTreeNode * LeafNode::get_first()
{
  return this;
}

LeafNode* LeafNode::split(Tuple value, Tuple last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);

  //_distinct_cnt++;
  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()

Tuple * LeafNode::get_values()
{
  return values;
}
