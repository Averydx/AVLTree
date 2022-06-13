#pragma once
#include <cstddef>
#include <stdlib.h>
#include<string>

using namespace std; 

//node struct contains 3 elements; data, which is the node's data. A pointer to the left subtree's root node, and a pointer to the right subtree's root node
//The constructor initializes a node with left and right pointers set to null
struct Node
{
	int data;
	Node* left;
	Node* right;

	Node(int _data);

};

 class Tree
{

public: 

	//The class's only field, the root of the tree
	Node* root;

	//wrapper class for the node constructor 
	Node* GetNewNode(int data);

	//base constructor 
	Tree();

	//Inserts a Node, taking a reference to root and a data value to be entered
	Node* InsertRecursive(Node*&root, Node*&new_node);
	void TreeInsert(int data);

	//The following 3 functions traverse the tree, printing the traversal
	void preorder(Node* root,char ** sep);
	void inorder(Node* root, char** sep);
	void postorder(Node* root, char** sep); 

	//function returns the balance factor of the tree using the height function 
	int getBalanceFactor(Node* n);
	//helper function to find the height of a tree starting at node n
	int height(Node* n);

	//prints a graphical representation of the tree to the screen
	void printTree(Node* root, int space);

	//helper functions to rotate the tree
	Node* rightRotation(Node* n);
	Node* leftRotation(Node* n); 

	
};

 class Driver
 {
 public:
	 Driver();
	 int Menu();
 private:
	 Tree* tree;
	 int InternalMenu(Tree*& tree);
 };


