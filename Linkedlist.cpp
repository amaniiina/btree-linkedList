#include <iostream> 
#include "btree.h"
#include "Linkedlist.h"


LinkedList::LinkedList() {
	head = NULL;
	length = 0;
}

// copy constructor by linked list adds each node to new list
LinkedList::LinkedList(LinkedList &bt) {
	Node* temp = head;
	Node* tempBt = bt.head;
	while (tempBt != NULL) {
		this->addAtEnd(tempBt->data);
		tempBt = tempBt->next;
	}
}

//private recursive method that adds given tree nodes at head of this list in inorder order so list is in postorder
void LinkedList::inOrder(node* curr) {
	if (curr == NULL)
		return;
	inOrder(curr->left);
	add(curr->key_value);
	inOrder(curr->right);
}

// copy constructor by btree adds each node to new list where list becomes posorder traversal of btree
LinkedList::LinkedList(btree &bt) {
	inOrder(bt.root);
}

// destructor that deletes all nodes and returns length to zero
LinkedList::~LinkedList() {
	Node* next = head;
	Node* curr = head;
	while(next!=NULL) {
		curr = next;
		next = next->next;
		delete curr;
	}
	length = 0;
}



// adds values as nodes to head of linked list
void LinkedList:: add(int data) {
	Node* node = new Node;
	node->data = data;
	node->next = head;
	head = node;
	length++;
}

// private recursive method returns true if all values both trees starting from passed nodes are equal
bool LinkedList::equal(node* node1, node* node2) {
	if (node1 == NULL)
		return true;
	if (node1->key_value != node2->key_value)
		return false;
	equal(node1->left, node2->left);
	equal(node1->right, node2->right);
}



// copy constructor from btree uses
LinkedList& LinkedList:: operator=(const btree &bt) {
	if (bt.length == 0) {		// if tree in parameters is empty delete this and return empty list
		this->~LinkedList();
		return *this;
	}
	// if tree passed in parameters is the same as this return this without change
	btree b(*this);
	if (b.length == bt.length) {
		if (equal(b.root, bt.root))
			return *this;
	}
	// else delete current list and add each node of btree in parameters so this list is postorder traversal of given tree
	this->~LinkedList();
	inOrder(bt.root);
	return *this;
}

// private method returns true if all value is both linked lists are true
bool LinkedList::equal(const LinkedList & bt) {
	if (this->length == bt.length)
		return true;
	Node* temp = this->head;
	Node* temp2 = bt.head;
	for (int i = 0; i < this->length; i++) {
		if (temp->data != temp2->data)
			return false;
	}
	return true;
}



// assingment operator from linked list
LinkedList& LinkedList:: operator=(const LinkedList & bt) {
	if (this->equal(bt))
		return *this;

	if (bt.length == 0) {		// if list passed in parameters is empty delete this and return empty list
		this->~LinkedList();
		head = NULL;
		this->length = 0;
		return *this;
	}
	// else delete current list and add each node of list in parameters starting from head to the tail of this
	Node* temp = head;			
	this->~LinkedList();
	Node* tempBt = bt.head;
	while (tempBt != NULL) {
		this->addAtEnd(tempBt->data);	
		tempBt = tempBt->next;
	}
	return *this;
}

// add value as node to end of linked list
void LinkedList::addAtEnd(int data) {
	Node* node = new Node;
	node->data = data;
	node->next = NULL;
	if (head == NULL) {
		length++;
		head = node;
		return;
	}
	Node* temp = head;
	for (; temp->next != NULL; temp = temp->next);
	temp->next = node;
	length++;
}



// output operator reimplementation  
ostream& operator<<(ostream& os, LinkedList& l) {
	os << "List: (";							
	for (Node* temp = l.head; temp != NULL; temp=temp->next) {
		os << temp->data << ",";
	}
	os << ")" << endl;
	return os;
}
