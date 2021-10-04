#ifndef _LinkedList_H_
#define _LinkedList_H_ 

#include <iostream>
using namespace std;
class btree;


class Node { 
public: 
	Node* next; 
	int data; 
private:
	Node & operator=(const Node& node) {
		this->data = node.data;
		this->next = node.next;
		return *this;
	}
};


class LinkedList {
	friend class btree;

	void addAtEnd(int data);
	void inOrder(node* curr);
	bool equal(node* node1, node* node2);
	bool equal(const LinkedList & bt);

public: 
	int length; 
	Node* head; 
	// Default constructor
	LinkedList();
	// Copy Constructor by tree
	LinkedList(btree &bt); 
	// Copy Constructor by list
	LinkedList(LinkedList &bt);
	//destructor
	~LinkedList();

	// add value as node to linked list 
	void add(int data);

	// assignment operator from linked list
	LinkedList & operator=(const LinkedList & bt);

	// assignment operator from btree
	LinkedList& operator=(const btree &bt);

	// print linked list
	friend ostream& operator<<(ostream& os, LinkedList& l);
};

#endif // !_LinkedList_H_