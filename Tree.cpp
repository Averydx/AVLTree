#include "Tree.h"
#include <cstddef>
#include <iostream>
#include<string>

//implementation of the node struct
Node::Node(int _data)
{
	data = _data;
	left = NULL;
	right = NULL;

}

//wrapper for the new node constructor to restrict access
Node* Tree::GetNewNode(int data)
{
	Node* newNode = new Node(data);
	return newNode; 
}

//base constructor
Tree::Tree()
{
	this->root = NULL; 
}

//Internal recursive insertion function 
Node* Tree::InsertRecursive(Node*&root, Node*&new_node)
{
	if (root == NULL)
	{
		root = new_node;
		return root; 
	}

	//recursive call into the left subtree if the value to be added is less than the value in root 
	if (new_node->data < root->data)
		InsertRecursive(root->left, new_node);
	//recursive call into the right subtree if the value to be added is greater than the value in root
	else if (new_node->data > root->data)
		InsertRecursive(root->right, new_node);
	//case if duplicate value
	else
		return root; 
	//The following is the rebalancing logic, calls functions getBalanceFactor, right rotation, and left rotation for  implementation
	int bf = getBalanceFactor(root);
	if (abs(bf) > 1)
		cout << "Tree has been rebalanced." << endl;
	if (bf > 1 && new_node->data < root->left->data) 
		return root = rightRotation(root);
	if (bf < -1 && new_node->data >root->right->data)
		return root = leftRotation(root); 
	if (bf >1 && new_node->data > root->left->data)
	{
		root->left = leftRotation(root->left);
		return root = rightRotation(root); 
	}
	if (bf < -1 && new_node->data <root->right->data)
	{
		root->right = rightRotation(root->right);
		return root = leftRotation(root);
	}
	return root; 
}

//public insertion function that passes a new node to the recursive insertion function
void Tree::TreeInsert(int data)
{
	Node* new_node = GetNewNode(data); 
	InsertRecursive(this->root, new_node); 
}


//These three functions implement the tree traversal and printing functions as in the menu  

void Tree::preorder(Node* root,char** sep)
{
	if (root != NULL)
	{
		std::cout << **sep << root->data; 
		*sep = (char*)", ";
		preorder(root->left, sep);
		preorder(root->right, sep);
		
	}
}

void Tree::inorder(Node* root, char** sep)
{
	if (root != NULL)
	{
			
		preorder(root->left, sep);
		*sep = (char*)", ";
		std::cout << **sep << root->data;
		preorder(root->right, sep);

	}
}

void Tree::postorder(Node* root, char** sep)
{
	if (root != NULL)
	{

		preorder(root->left, sep);
		preorder(root->right, sep);
		*sep = (char*)", ";
		std::cout << **sep << root->data;

	}
}






//helper function to return the balance factor of the tree at any node n
int Tree::getBalanceFactor(Node* n)
{
	if (n == NULL)
		return -1;
	else
		return (height(n->left) - height(n->right));
}

//helper function to return the height of the tree at any node n
int Tree::height(Node* n)
{
	{
		if (n == NULL)
		{
			return -1;
		}

		int leftHeight = height(n->left);
		int rightHeight = height(n->right);

		if (leftHeight >= rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
}

//helper function to print the tree 
void Tree::printTree(Node* root, int space)
{
	if (root == NULL)
		return; 
	space = space + 5; 
	printTree(root->right, space); 
	cout << "\n";
	for (int i = 5; i < space; i++)
		cout << " ";
	if (root->left == NULL && root->right == NULL)
		cout << "-" << root->data;
	else
		cout << root->data<<"<"<<endl;
	printTree(root->left, space);
}

Node* Tree::rightRotation(Node* n1)
{
	Node* n2 = n1->left; 
	Node* T2 = n2->right; 

	//rotation
	n2->right = n1;
	n1->left = T2; 
	return n2;
}

Node* Tree::leftRotation(Node* n1)
{
	Node* n2 = n1->right; 
	Node* T2 = n2->left; 
	//rotation
	n2->left = n1; 
	n1->right = T2; 
	return n2; 
}

Driver::Driver()
{
	tree = new Tree();
}

int Driver::Menu()
{
	return InternalMenu(this->tree);
}

int Driver::InternalMenu(Tree*& tree)
{

	int choice{};
	char* sep = (char*)"";
	string str_choice;
	cout << "		AVL Tree Implementation" << endl;
	cout << "A: Insert an integer to tree and show the balanced tree at each insertion." << endl;
	cout << "B: Display the balanced tree and show preorder traversal." << endl;
	cout << "C: Display the balanced tree and show inorder traversal." << endl;
	cout << "D: Display the balanced tree and show postorder traversal." << endl;
	cout << "E: Exit" << endl;

	cout << "" << endl;
	cout << "=";
	cin >> str_choice;

	for (int i = 0; i < str_choice.length(); i++)
	{
		str_choice = toupper(str_choice[i]);
	}

	if (str_choice == "A")
		choice = 1;
	else if (str_choice == "B")
		choice = 2;
	else if (str_choice == "C")
		choice = 3;
	else if (str_choice == "D")
		choice = 4;
	else if (str_choice == "E")
		choice = 5;

	switch (choice)
	{
	case 1:
		int data;
		cout << "Enter integer to be added to tree: ";
		cin >> data;
		tree->TreeInsert(data);
		cout << "Node(" << data << ") inserted" << endl;
		tree->printTree(tree->root, 0);
		cout << "\n";
		cout << "\n";
		break;

	case 2:

		tree->printTree(tree->root, 0);
		cout << endl;
		cout << "Preorder: {";
		tree->preorder(tree->root, &sep);
		cout << "}" << endl;
		cout << "\n";
		break;

	case 3:

		tree->printTree(tree->root, 0);
		cout << endl;
		cout << "Inorder: {";
		tree->inorder(tree->root, &sep);
		cout << "}" << endl;
		cout << "\n";
		break;

	case 4:
		tree->printTree(tree->root, 0);
		cout << endl;
		cout << "Postorder: {";
		tree->postorder(tree->root, &sep);
		cout << "}" << endl;
		cout << "\n";
		break;

	case 5:
		exit(0);

	}

	return 1;

}

