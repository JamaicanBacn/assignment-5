#pragma once
#include <string>
#include <iostream>
#include<fstream>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

class AVLTreeNode {
public:


	AVLTreeNode* parent;
	AVLTreeNode* right;
	AVLTreeNode* left;

	string word;
	unsigned int count;
	unsigned int height;



	AVLTreeNode( string data) : word(data) , left(nullptr) , right(nullptr) , parent(nullptr) , height(0) , count(1) {};
	// Should have attributes named:
	// parent - pointer to parent
	// left - pointer to left child
	// right - pointer to right child
	// word - node's string data
	// count - number of times the word appears
	// height - node's height

	// Constructors ...
};

// Wordlist class
class Wordlist
{
private:
	// Class attributes go here
	// Your class MUST have a root node named root (below)
	AVLTreeNode* root; // DO NOT REMOVE
	int nodes; // unqie nodes
	int total_words; // count of all words

	int balance_factor(AVLTreeNode* node); // checks balance 
	AVLTreeNode* predecessor(AVLTreeNode* node); // finds the predecesor node
	int height(AVLTreeNode* node); // returns the heigth of the node

	AVLTreeNode* right_rotation(AVLTreeNode* node); 
	AVLTreeNode* left_rotation(AVLTreeNode* node);
	AVLTreeNode* Avl_insertion_handling( AVLTreeNode* node , string data); // recursive insertion
	AVLTreeNode* Avl_removal_handling(AVLTreeNode* node, string data); // recursive removal

	AVLTreeNode* findMaximum(AVLTreeNode* node); // returns the node with max count
	int singleton_travesal(AVLTreeNode* node); // retursn the number of singleton words
	int postOrderTraversal(AVLTreeNode* node , int print_order); 
	AVLTreeNode* treeCopy(const AVLTreeNode* node); // makes a deep copy of the tree
	void Decomposition(AVLTreeNode* node); // deletes the tree

public:
	// public methods go here

	Wordlist();
	~Wordlist();
	Wordlist(string fname);
	Wordlist(const Wordlist& reference);
	Wordlist& operator=(const Wordlist& reference);

	void insert(string data);
	bool remove(string data);

	int getCount(string data); // gets the count of a node 
	bool contains(string data); // true if the tree has the node with word data
	int differentWords(); // number of unique nodes
	int totalWords(); // total number of words 
	string mostFrequent(); // wors with highest count 
	int singletons(); // number of nodes with count one  
	void printWords(); // prints all the words in the given format
	// Prints useful statistics about the word list
	void printStatistics() const;

	// Returns the root of the AVL tree
	AVLTreeNode* getRoot() const { return root; }; // DO NOT REMOVE
};
