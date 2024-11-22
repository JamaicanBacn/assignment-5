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



	AVLTreeNode( string data) : word(data) , left(nullptr) , right(nullptr) , parent(nullptr) , height(0) , count(0) {};
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
	int nodes;
	int total_words;

	int balance_factor(AVLTreeNode* node);
	int height(AVLTreeNode* node);
	AVLTreeNode* right_rotation(AVLTreeNode* node);
	AVLTreeNode* left_rotation(AVLTreeNode* node);
	AVLTreeNode* Avl_insertion_handling( AVLTreeNode* node , string data);
	AVLTreeNode* findMaximum(AVLTreeNode* node);
	int singleton_travesal(AVLTreeNode* node);

public:
	// public methods go here

	Wordlist();
	Wordlist(string fname);

	void insert(string data);
	int differentWords();
	int totalWords();
	string mostFrequent();
	int singletons();
	// Prints useful statistics about the word list
	//void Wordlist::printStatistics() const;

	// Returns the root of the AVL tree
	AVLTreeNode* getRoot() const { return root; }; // DO NOT REMOVE
};
