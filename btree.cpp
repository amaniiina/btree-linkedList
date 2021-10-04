#include<iostream>
#include <queue>
#include "btree.h"
#include "LinkedList.h"


// boolean variable for mirroring the tree
bool mirrored = false;

btree::btree() {
	mirrored = false;
	root =  NULL;
	length = 0;
}

// copy constructor by linked list; initializes boolean mirrored to false and inserts each node from the list
btree::btree(LinkedList &list) {
	mirrored = false;	
	Node* temp = list.head;
	while (temp != NULL) {
		insert(temp->data);
		temp = temp->next;
	}
}

// recursive method that copies a tree node by node in preorder traversal
void btree::copyBT(node* root) {
	if (root == NULL)
		return;
	insert(root->key_value);
	copyBT(root->left);
	copyBT(root->right);
}

// copy constructor by tree that initializes boolean mirrored to false and copies the tree
btree::btree(btree & bt) {
	mirrored = false;
	copyBT(bt.root);
}

// recursive method that deletes each node in postorder
void btree::postorder(node* node) {
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		delete(node);
	}
}

// deconstructor using postorder method
btree::~btree() {
	postorder(root);
}



// recursive method that prints each node in inorder order
void btree::inOrderPrint(node* curr) {
	if (curr == NULL)
		return;
	inOrderPrint(curr->left);
	cout<< curr->key_value<< ", ";
	inOrderPrint(curr->right);
}

// output operator reimplementation
ostream& operator<<(ostream& os, btree& dt) {
	os << "Tree: ";
	dt.inOrderPrint(dt.root);
	os << endl;
	return os;
}



// private method returns true if this list is the same as the list passed as a parameter
bool btree::equal(const LinkedList& ls) {
	LinkedList l(*this);
	Node* temp = l.head;
	Node* temp2 = ls.head;
	if(l.length != ls.length)
		return false;
	for (int i = 0; i < l.length; i++) {
		if (temp->data != temp2->data)
			return false;
	}
	return true;	
}

btree& btree::operator=(const LinkedList & ls) {
	//if list passed in parameter is empty destruct this
	if (ls.length == 0){
		this->~btree();	
		return *this;
	}
	//if assigning same tree return this without change
	if (this->equal(ls))
		return *this;
	//else destruct current tree and copy values from list to this 
	this->~btree();
	Node* temp = ls.head;
	while (temp != NULL) {
		insert(temp->data);
		temp = temp->next;
	}
	return *this;
}


// private recursive method to check whether all node values are equal
bool btree::equal(node* node1, node* node2) {
	if (node1 == NULL)
		return true;
	if (node1->key_value != node2->key_value)
		return false;
	equal(node1->left, node2->left);
	equal(node1->right, node2->right);
}

btree& btree::operator=(const btree &bt) {
	//if assigning same tree return this without change
	if (this->length == bt.length) {
		if(equal(this->root, bt.root))
			return *this;
	}
	//else destruct this tree and copy values from tree in  parameters to this
	this->~btree();
	copyBT(bt.root);
	return *this;
}



//private method creates node for tree
node* btree::createNode(int key) {
	node* insert = new node;
	insert->left = NULL;
	insert->right = NULL;
	insert->key_value = key;
	return insert;
}

//inserts values to tree as nodes where smaller values are inserted to the left while bigger values to the right
void btree::insert(int key) {
	length++;
	node* insert = createNode(key);
	//insert root
	if (root == NULL) {
		root = insert;
		root->left = NULL;
		root->right = NULL;
		return;
	}
	//if tree is mirrored insert in the opposite way
	if (mirrored) {
		insertMirrored(key);
		return;
	}

	node* temp = root;
	// while there's still nodes break if reached right place else continue going over nodes
	while (temp->left != NULL || temp->right != NULL) {
		if (key > temp->key_value) {
			if (temp->right == NULL)
				break;
			temp = temp->right;
		}
		else {
			if (temp->left == NULL)
				break;
			temp = temp->left;
		}
	}
	// insert value in right place
	if (temp->key_value <= key)
		temp->right = insert;
	else
		temp->left = insert;
}

//inserts values to tree as nodes where bigger values are inserted to the left while smaller values to the right
void btree::insertMirrored(int key) {
	node* insert = createNode(key);
	node* temp = root;
	while (temp->left != NULL || temp->right != NULL) {
		if (key < temp->key_value) {
			if (temp->right == NULL)
				break;
			temp = temp->right;
		}
		else {
			if (temp->left == NULL)
				break;
			temp = temp->left;
		}
	}
	if (temp->key_value >= key)
		temp->right = insert;
	else
		temp->left = insert;
}



// private recursive method swaps left and right nodes of each node starting from node passed in parameters 
void btree::swapNodes(node*& temp) {
	if (temp == NULL)
		return;
	swapNodes(temp->left);
	swapNodes(temp->right);

	node* curr = temp->left;
	temp->left = temp->right;
	temp->right = curr;
}

// changes boolean mirrored and swaps left and right nodes of each node
void btree::mirror() {
	mirrored = !mirrored;
	swapNodes(root);
}



// returns array of linked lists at each depth using breadth first search
LinkedList* btree::Tree2linkListbyDepth() { 
	queue<node*> q;			// initialize queue
	if (root == NULL)
		return NULL;
	int count = 0, i = 1, j = 0;
	q.push(root);			// insert root to q
	int depth = this->getTreeDepth();
	int* numNodes = new int[depth];		// array to count nodes at each depth
	numNodes[0] = 1;					// at depth 0 only there is always only one node (root)
	for (; i < depth; i++)
		numNodes[i] = 0;				// initialize the rest of the array to 0
	LinkedList* res= new LinkedList[depth]; // the array of linked lists
	i = 1;
	while (!q.empty()) {		
		node* curr = q.front();		// curr is first node in q
		if (curr->left != NULL) {
			q.push(curr->left);		// if not null insert left node of curr to q
			count++;
		}
		if (curr->right != NULL) {
			q.push(curr->right);	// if not null insert right node of curr to q
			count++;
		}
		if(i< depth)
			numNodes[i] += count;	// increment number of nodes at next depth
		res[j].add(curr->key_value);
		q.pop();
		numNodes[i-1]--;
		if (numNodes[i - 1] == 0) {	//if nodes the current depth are done increment i & j
			i++;
			j++;
		}
		count = 0;
	}
	return res;
}

//private recursive method returns maximum depth of tree from given node
int btree::treeDepth(node* temp) {
	if (temp == NULL)
		return 0;
	if (temp->left == NULL && temp->right == NULL)
		return 1;
	if (temp->left == NULL)
		return treeDepth(temp->right) + 1;
	if (temp->right == NULL)
		return treeDepth(temp->left) + 1;
	return max(treeDepth(temp->left), treeDepth(temp->right))+1;
}

// returns maximum depth of tree
int btree::getTreeDepth() {
	return treeDepth(this->root);
}
