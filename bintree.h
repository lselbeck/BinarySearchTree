//-----------------------------------------------------------------------//
// BINTREE.H                                                             //
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
//   --     TODO                														 //
//-----------------------------------------------------------------------//

#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <string.h>
#include <algorithm>
#include "nodedata.h"
using namespace std;


class BinTree {
//-----------------------------  <<  --------------------------------------
// Overloaded output operator for class BinTree
// Preconditions:   NodeData has a working output operator overload
// Postconditions:  prints an in order traversal of the tree
friend ostream& operator<<(ostream&, const BinTree&);

//-----------------------------  >>  --------------------------------------
// Overloaded input operator for class BinTree; adds new nodes to BinTree
// 		-- each separate string inputted (separated by whitespace) is added
//         as a new node in BinTree
// 		-- input "$$" to end the input stream
// Preconditions:
//       -- insert(NodeData*) is working
// Postconditions:  All the tokens are a part of the tree
friend istream& operator>>(istream&, BinTree&);

public:
//-------------------------- Constructor ----------------------------------
// Default constructor for class BinTree
// Preconditions:   none
// Postconditions:  
//       -- a tree of size 0 is created  
BinTree();

//------------------------- Copy Constructor ------------------------------
// Constructor accepting a BinTree to be deep copied 
// Preconditions:  none
// Postconditions:
//       -- a BinTree an exact copy of the parameter is made
BinTree(const BinTree&);

//--------------------------- Destructor ----------------------------------
// Destructor for class BinTree
// Preconditions:   none
// Postconditions:
//       -- all Nodes and NodeDatas in BinTree are deallocated
//		 -- root = NULL
~BinTree();

//----------------------------- isEmpty -----------------------------------
// Returns true if tree is empty, AKA no Nodes
// Preconditions:   none
// Postconditions:  Returns true if there are no Nodes in BinTree, returns
//					false if otherwise
bool isEmpty() const;

//---------------------------- makeEmpty ----------------------------------
// Deallocate all Nodes and NodeDatas in BinTree
// Preconditions:   none
// Postconditions:  
//       -- no Nodes in BinTree, root = NULL
void makeEmpty();

//------------------------------ insert -----------------------------------
// Add a NodeData to BinTree, returns true if successful
// Preconditions:   none
// Postconditions:  
//       -- the NodeData is pointed to by a new Node which is correctly 
//			placed in BinTree
bool insert(NodeData*);

//---------------------------- retrieve -----------------------------------
// Retrieve a NodeData* of a given object in the tree, return true if found
// The second parameter will point to the actual object in the tree if 
// found, and return true if found
// Preconditions:   none
// Postconditions:  
//       -- the second parameter points to the found object
bool retrieve(const NodeData&, NodeData*&) const;

//------------------------------ getDepth ---------------------------------
// find the depth of a given value in the tree, return the toFind, if it is 
//			in the tree
// Preconditions:   none
// Postconditions:  none
int getDepth(const NodeData&) const;

//---------------------------- bstreeToArray ------------------------------
// A routine fills an array of NodeData* by using an inorder traversal of
// the tree, emptying the tree as well
// Preconditions:   array has no more than 100 nodes
// Postconditions:  tree is empty
void bstreeToArray(NodeData* []);

//---------------------------- arrayToBSTree ------------------------------
// A routine builds a balanced BinTree from a sorted array of NodeData* 
// Preconditions:   none
// Postconditions:  array is filled with NULLs; the root (recursively) is
//       at (low+high)/2 where low is the lowest subscript of the array
//       range and high is the highest
void arrayToBSTree(NodeData* []);

//------------------------- displaySideways -------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions:   none
// Postconditions:  none
void displaySideways() const;

//------------------------------  =  --------------------------------------
// Overloaded assignment operator; current object = parameter; deep copy
// Preconditions:   none
// Postconditions:
//       -- this tree's nodes are deallocated, and nodes containing the
//			data values as the parameter are inserted into this tree,
//			becoming an exact deep copy of the parameter
BinTree& operator=(const BinTree&);

//-----------------------------  ==  --------------------------------------
// Determine if two BinTrees are equal
// Preconditions:   none
// Postconditions:  
//       -- true is returned if all nodes in this object and rhs are equal
//       -- false is returned if otherwise
bool operator==(const BinTree&) const;

//-----------------------------  !=  --------------------------------------
// Determine if two BinTrees are not equal
// Preconditions:   none
// Postconditions:  
//       -- false is returned if all nodes in this object and rhs are equal
//       -- true is returned if otherwise
bool operator!=(const BinTree&) const;


private:
   
struct Node {
	NodeData* data; //pointer to data object
	Node* left;     //left subtree pointer
	Node* right;    //right subtree pointer
};

Node* root;         //root of the tree


//utility functions

//-----------------------------  copyTree  --------------------------------
// recursive helper function for copy constructor and assignment operator
// Preconditions:   this tree is empty; root of this tree and root of tree
//       to be copied is passed
// Postconditions:  this tree is a deep copy of the root passed
void copyTree(Node*&, Node*);

//---------------------------  makeEmptyHelper  ---------------------------
// recursive helper function for the makeEmpty function
// Preconditions:   root of this tree is passed
// Postconditions:  tree is empty of all nodes, root = NULL
void makeEmptyHelper(Node*);

//----------------------------  insertHelper  -----------------------------
// recursive helper function for the insert function and returns true if
// successful.  No duplicate NodeDatas are allowed
// Preconditions:   root of this tree is passed as second and third 
//			parameter
// Postconditions:  NodeData is inserted into tree in correct place
bool insertHelper(NodeData*, Node*, Node*, bool);

//----------------------------  retrieveHelper  ---------------------------
// recursive helper function for the retrieve function, and a general find 
// tool.  You have the option to have a NodeData* to the object found, or
// a Node* to the object found, or both, by passing in NULL ptrs
// Preconditions:   NodeData to find, NodeData to point to found, Node to
//			point to found, and root are passed
// Postconditions:  NodeDataPtr will point to found the NodeData if found,
//			NodePtr will point to found NodeData's Node, and will return
//			true if found
bool retrieveHelper(const NodeData&, NodeData*&, Node*) const;

//---------------------------  getDepthtHelper  ---------------------------
// recursive helper function for the getDepth function.  Searches the tree
// by inorder traversal, and keeps track of depth as it goes.  sets
// foundDepth to the depth of the object found, if found
// Preconditions:   the node which you want to find the depth of, the root,
// 			the int you want the foundDepth stored in, and the root depth
//			(1) is passed
// Postconditions:  none
void getDepthHelper(const NodeData&, Node*, int&, int) const;

//------------------------  bstreeToArrayHelper  --------------------------
// recursive helper function for bstreeToArray; fills an array of NodeData*
// by using an inorder traversal of the tree, emptying the tree as well
// Preconditions:   array has no less than 100 nodes
// Postconditions:  tree is empty
void bstreeToArrayHelper(NodeData*[], Node*, int&);

//------------------------  bstreeToArrayHelper  --------------------------
// recursive helper function for arrayToBSTree; fills a tree with NodeData*
// by inputting a NodeData*[], emptying the array as well
// Preconditions:   array has no less than 100 nodes
// Postconditions:  array is all NULL
void arrayToBSTreeHelper(NodeData*[], Node*&, int, int);

//-----------------------------  sideways  --------------------------------
// recursive helper function for display sideways
// Preconditions:   root is passed, with level 0
// Postconditions:  none
void sideways(Node*, int) const;

//---------------------------  comparisonHelper  --------------------------
// recursive helper function for the boolean operators (==, !=)
// Preconditions:   root of this tree and root of other tree is passed
// Postconditions:  sets bool to false if the trees are not the same
void comparisonHelper(Node*, Node*, bool&) const;

//------------------------  inorderOstreamHelper  -------------------------
// helper for inorderOstreamDump; recursively puts all node data on an
// output stream, inorder traversal
// Preconditions:   the root is passed as a second parameter
// Postconditions:  none
ostream& inorderOstreamHelper(ostream&, Node*) const;

};

#endif
