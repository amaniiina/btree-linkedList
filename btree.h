#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>
using namespace std;
class LinkedList;

struct node
{
	int key_value;
	node *left;
	node *right;
};

class btree
{
	friend class LinkedList;

	int length;
	node* root;

	//private methods
	void inOrderPrint(node* curr);
	void copyBT(node* root);
	bool equal(const LinkedList& ls);
	bool equal(node* node1, node* node2);
	void postorder(node* node);
	void swapNodes(node*& temp);
	node* createNode(int key);
	void insertMirrored(int key);
	int treeDepth(node* temp);

public:
	// Default constructor
	btree();
	~btree();

	// Copy Constructor by list
	btree(LinkedList &list);

	// Copy Constructor by tree
	btree(btree & bt);

	// assignment operator from linked list
	btree & operator=(const LinkedList & ls);

	// assignment operator from tree
	btree& operator=(const btree &bt);

	// insert new value to binary tree
	void insert(int key);

	// mirror the tree
	void mirror();

	// return array of linked lists at each depth
	LinkedList* Tree2linkListbyDepth();

	// return depth of tree
	int getTreeDepth();

	// print tree (in order)
	friend ostream& operator<<(ostream& os, btree& dt);
};

#endif // !_BTREE_H_