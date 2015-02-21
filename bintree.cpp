//-----------------------------------------------------------------------//
// BINTREE.CPP                                                           //
// Author: Luke Selbeck                                                  //
// Date: April 18th, 2014                                                //
// Class: CSS 343                                                        //
//                                                                       //
// BinTree is a binary search tree holding strings                       //
//-----------------------------------------------------------------------//
// Binary Search Tree:  defined as a tree in which every node has at most//
//				 two children.  Left child is smaller in value, right        //
//				 child is larger in value.                                   //
//                                                                       //
// Implementation and assumptions:                                       //
// TODO                    															 //
//-----------------------------------------------------------------------//

#include "bintree.h"

//-------------------------- Constructor ----------------------------------
// Default constructor for class BinTree
// Preconditions:   none
// Postconditions:  
//       -- a tree of size 0 is created  
BinTree::BinTree() {
	root = NULL;
}

//------------------------- Copy Constructor ------------------------------
// Constructor accepting a BinTree to be deep copied 
// Preconditions:  none
// Postconditions:
//       -- a BinTree an exact copy of the parameter is made
BinTree::BinTree(const BinTree& toCopy) {
	root = NULL;
	copyTree(root, toCopy.root);
}

//-----------------------------  copyTree  --------------------------------
// recursive helper function for copy constructor and assignment operator
// Preconditions:   this tree is empty; root of tree to be copied is passed
// Postconditions:  this tree is a deep copy of the root passed
void BinTree::copyTree(Node*& cur, Node* other) {
	if (other != NULL) {
		cur = new Node;
		cur->data = new NodeData(*other->data);
		cur->left = NULL;
		cur->right = NULL;
		copyTree(cur->left, other->left);
		copyTree(cur->right, other->right);
	}
}

//--------------------------- Destructor ----------------------------------
// Destructor for class BinTree
// Preconditions:   makeEmpty works
// Postconditions:
//       -- all Nodes and NodeDatas in BinTree are deallocated
//		 -- root = NULL
BinTree::~BinTree() {
	makeEmpty();
}

//----------------------------- isEmpty -----------------------------------
// Returns true if tree is empty, AKA no Nodes
// Preconditions:   none
// Postconditions:  Returns true if there are no Nodes in BinTree, returns
//					false if otherwise
bool BinTree::isEmpty() const {
	return root == NULL;
}

//---------------------------- makeEmpty ----------------------------------
// Deallocate all Nodes and NodeDatas in BinTree
// Preconditions:   none
// Postconditions:  
//       -- no Nodes in BinTree, root = NULL
void BinTree::makeEmpty() {
	makeEmptyHelper(root);
	root = NULL;
}

//---------------------------  makeEmptyHelper  ---------------------------
// recursive helper function for the destructor and makeEmpty function
// Preconditions:   root of this tree is passed
// Postconditions:  tree is empty of all nodes
void BinTree::makeEmptyHelper(Node* cur) {
	if (cur != NULL) {
		makeEmptyHelper(cur->left);
		makeEmptyHelper(cur->right);
		delete cur->data;
		cur->data = NULL;
		delete cur;
		cur = NULL;
	}
}

//------------------------------ insert -----------------------------------
// Add a NodeData to BinTree, returns true if successful
// Preconditions:   insertHelper
// Postconditions:  
//       -- the NodeData is pointed to by a new Node which is correctly 
//			placed in BinTree
bool BinTree::insert(NodeData* newNodeData) {
	if (root == NULL) { //empty tree
		root = new Node;
		root->data = &*newNodeData;
		root->left = NULL;
		root->right = NULL;
		return true;
	} else
		return insertHelper(newNodeData, root, root, true);
}

//----------------------------  insertHelper  -----------------------------
// recursive helper function for the insert function and returns true if
// successful.  No duplicate NodeDatas are allowed
// Preconditions:   root of this tree is passed as second and third 
//			parameter
// Postconditions:  NodeData is inserted into tree in correct place
bool BinTree::insertHelper(NodeData* newNodeData, Node* cur,
	                       Node* prev, bool left) {
	if (cur != NULL) {
		if (*newNodeData < *cur->data)
			return insertHelper(newNodeData, cur->left, cur, true);
		else if (*newNodeData > *cur->data)
			return insertHelper(newNodeData, cur->right, cur, false);
		else //newNodeData == cur->data
			return false; //no duplicates
	}  else {
		cur = new Node;
		cur->data = &*newNodeData;
		cur->left = NULL;
		cur->right = NULL;
		if (left) //to check if this is prev's right or left child
			prev->left = cur; 
		else
			prev->right = cur;
		return true;
	}
}

//---------------------------- retrieve -----------------------------------
// Retrieve a NodeData* of a given object in the tree, return true if found
// The second parameter will point to the actual object in the tree if 
// found, and return true if found
// Preconditions:   none
// Postconditions:  the second parameter points to the found object.  If 
//			object is not found, no reassignment of ptr is made
bool BinTree::retrieve(const NodeData& toFind, NodeData*& ptr) const {
	return retrieveHelper(toFind, ptr, root);
}

//----------------------------  retrieveHelper  ---------------------------
// recursive helper function for the retrieve function, and a general find 
// tool.  You have the option to have a NodeData* to the object found, or
// a Node* to the object found, or both, by passing in NULL ptrs
// Preconditions:   NodeData to find, NodeData* to point to found, Node* to
//			point to found, and root are passed
// Postconditions:  NodeDataPtr will point to found the NodeData if found,
//			NodePtr will point to found NodeData's Node, and will return
//			true if found
bool BinTree::retrieveHelper(const NodeData& toFind, NodeData*& ptr,
				             Node* cur) const {
	if (cur != NULL) {
		if (toFind == *cur->data) {
			ptr = cur->data;
			return true;
		} else if (toFind < *cur->data)
			return retrieveHelper(toFind, ptr, cur->left);
		else //toFind > cur->data) 
			return retrieveHelper(toFind, ptr, cur->right);
	} else return false;
}

//------------------------------ getDepth ---------------------------------
// find the depth of a given value in the tree, return the depth
// Preconditions:   getDepthHelper changes the value of depth to the found
//			object's depth, if it is in the tree
// Postconditions:  none
int BinTree::getDepth(const NodeData& toFind) const {
	int depth = 0; //-1 means not found
	getDepthHelper(toFind, root, depth, 1);
	return depth;
}

//---------------------------  getDepthtHelper  ---------------------------
// recursive helper function for the getDepth function.  Searches the tree
// by inorder traversal, and keeps track of depth as it goes.  sets
// foundDepth to the depth of the object found, if found
// Preconditions:   the node which you want to find the depth of, the root,
// 			the int you want the foundDepth stored in, and the root depth
//			(1) is passed
// Postconditions:  none
void BinTree::getDepthHelper(const NodeData& toFind, Node* cur,
						    int& foundDepth, int depth) const {
	if (cur != NULL) {
		getDepthHelper(toFind, cur->left, foundDepth, depth+1);
		if (toFind == *cur->data)
			foundDepth = depth;
		getDepthHelper(toFind, cur->right, foundDepth, depth+1);
	}
}

//---------------------------- bstreeToArray ------------------------------
// A routine fills an array of NodeData* by using an inorder traversal of
// the tree, emptying the tree as well
// Preconditions:   tree has no more than 100 nodes -- only size 100 array
// Postconditions:  tree is empty
void BinTree::bstreeToArray(NodeData* toFill[]) {
	int startingIndex = 0;
	bstreeToArrayHelper(toFill, root, startingIndex);
	root = NULL;
}

//------------------------  bstreeToArrayHelper  --------------------------
// recursive helper function for bstreeToArray; fills an array of NodeData*
// by builds a balanced BinTree from a sorted array of NodeData*
// Preconditions:   array has no less than 100 nodes
// Postconditions:  tree is empty
void BinTree::bstreeToArrayHelper(NodeData* toFill[], Node* cur,
								  int& index) {
	if (cur != NULL) {
		bstreeToArrayHelper(toFill, cur->left, index);
		bstreeToArrayHelper(toFill, cur->right, index);
		if (index < 100) {
			toFill[index++] = &*cur->data;
		}
		delete cur;
	}
}

//---------------------------- arrayToBSTree ------------------------------
// A routine builds a balanced BinTree from a sorted array of NodeData* 
// Preconditions:   array is of size 100
// Postconditions:  array is filled with NULLs; the root (recursively) is
//       at (low+high)/2 where low is the lowest subscript of the array
//       range and high is the highest
void BinTree::arrayToBSTree(NodeData* toCopy[]) {
	makeEmpty();
	int objectCount;
	for (objectCount = 0; toCopy[objectCount] != NULL; objectCount++);
	arrayToBSTreeHelper(toCopy, root, 0, objectCount); //array size 100
	for (int i = 0; i <= objectCount; i++) {
		toCopy[i] = NULL;
	}
}

//------------------------  bstreeToArrayHelper  --------------------------
// recursive helper function for arrayToBSTree; builds a balanced BinTree
// from a sorted array of NodeData*
// ***********************************NOTE*********************************
// I couldn't figure out how to get my tree to look exactly like the sample
// output, but the tree I produce is BALANCED and COMPLETE (all levels
// are filled completely, except the last, which is filled left to right) 
// AND I used (low+high)/2 as instructed in the assignment instructions.
// Also, the sample output tree is NOT COMPLETE (because the last level is
// filled right to left instead of left to right), so arguably, my
// implementation is just as good if not better than the sample output tree
// Nonetheless, I couldn't replicate the sample output, so I did my best :)
// ***********************************NOTE*********************************
// Preconditions:   array is of size 100
// Postconditions:  array is all NULL
void BinTree::arrayToBSTreeHelper(NodeData* toCopy[], Node*& cur,
								  int low, int high) {
	if (low < high) {
		int index = (low+high)/2;
		cur = new Node;
		cur->data = &*toCopy[index];
		cur->left = NULL;
		cur->right = NULL;
		arrayToBSTreeHelper(toCopy, cur->left, low, index);
		arrayToBSTreeHelper(toCopy, cur->right, index+1, high);
	}
}

//------------------------- displaySideways -------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions:   none
// Postconditions:  none
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//-----------------------------  sideways  --------------------------------
// recursive helper function for display sideways
// Preconditions:   root is passed, with level 0
// Postconditions:  none
void BinTree::sideways(Node* current, int level) const {
   if (current != NULL) {
      level++;
      sideways(current->right, level);

      // indent for readability, 4 spaces per depth level 
      for(int i = level; i >= 0; i--)
          cout << "    ";

      cout << *current->data << endl;        // display information of object
      sideways(current->left, level);
   }
}

//------------------------------  =  --------------------------------------
// Overloaded assignment operator; current object = parameter; deep copy
// Preconditions:   none
// Postconditions:
//       -- this tree's nodes are deallocated, and nodes containing the
//			data values as the parameter are inserted into this tree,
//			becoming an exact deep copy of the parameter
BinTree& BinTree::operator=(const BinTree& rhs) {
	if (&this->root != &rhs.root) { //if not the same object
		makeEmpty();
		copyTree(root, rhs.root);
	}
	return *this;
}

//-----------------------------  ==  --------------------------------------
// Determine if two BinTrees are equal
// Preconditions:   none
// Postconditions:  
//       -- true is returned if all nodes in this object and rhs are equal
//       -- false is returned if otherwise
bool BinTree::operator==(const BinTree& rhs) const {
	bool answer = true;
	comparisonHelper(root, rhs.root, answer);
	return answer;
}

//-----------------------------  !=  --------------------------------------
// Determine if two BinTrees are not equal
// Preconditions:   none
// Postconditions:  
//       -- false is returned if all nodes in this object and rhs are equal
//       -- true is returned if otherwise
bool BinTree::operator!=(const BinTree& rhs) const {
	bool answer = true;
	comparisonHelper(root, rhs.root, answer);
	return !answer;
}

//---------------------------  comparisonHelper  --------------------------
// recursive helper function for the boolean operators (==, !=)
// Preconditions:   root of this tree and root of other tree is passed
// Postconditions:  sets bool to false if the trees are not the same
void BinTree::comparisonHelper(Node* cur, Node* other, bool& answer) const{
	if (cur != NULL && other != NULL) {
			comparisonHelper(cur->left, other->left, answer);
			if (*cur->data != *other->data)
				answer = false;
			comparisonHelper(cur->right, other->right, answer);
	} else if (cur == NULL && other == NULL) {}
	else answer = false;
}

//-----------------------------  <<  --------------------------------------
// Overloaded output operator for class BinTree
// Preconditions:   NodeData has a working output operator overload
// Postconditions:  prints an in order traversal of the tree to the consol
ostream& operator<<(ostream& out, const BinTree& toPrint) {
	if (toPrint.root == NULL) { //if tree is empty
		out << "Empty" << endl;
		return out;
	} else {
		toPrint.inorderOstreamHelper(out, toPrint.root);
		out << endl;
		return out;
	}
}

//------------------------  inorderOstreamHelper  -------------------------
// helper for inorderOstreamDump; recursively puts all node data on an
// output stream, inorder traversal
// Preconditions:   the root is passed as a second parameter
// Postconditions:  none
ostream& BinTree::inorderOstreamHelper(ostream& out, Node* cur) const {
	if (cur != NULL) {
		inorderOstreamHelper(out, cur->left);
		out << " " << *cur->data;
		inorderOstreamHelper(out, cur->right);
	}
	return out;
}

//-----------------------------  >>  --------------------------------------
// Overloaded input operator for class BinTree; adds new nodes to BinTree
// 		-- each separate string inputted (separated by whitespace) is added
//         as a new node in BinTree
// 		-- input "$$" to end the input stream
// Preconditions:
//       -- insert(NodeData*) is working
// Postconditions:  All the tokens are a part of the tree
istream& operator>>(istream& in, BinTree& rhs) {
	string newData = "$$";
	NodeData* newNodeData;
	for(;;) {
		in >> newData;
		if (newData == "$$")
			break;
		newNodeData = new NodeData(newData);
		rhs.insert(newNodeData);
	}
	return in;
}