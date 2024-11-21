#include "Wordlist.h"
#include <iomanip>
using std::setprecision;
using std::fixed;
using std::max;

// Prints useful statistics about the word list

/*


void Wordlist::printStatistics() const
{
	cout << "Number of different words: " << differentWords() << endl;
	cout << "    Total number of words: " << totalWords() << endl;
	cout << "       Most frequent word: " << mostFrequent() << endl;
	cout << "     Number of singletons: " << singletons()
		<< setprecision(0) << fixed
		<< " (" << 100.0 * singletons() / differentWords() << "%)"
		<< endl;
}

*/




Wordlist::Wordlist()
{
	root = nullptr;
	nodes = 0;
	total_words = 0;

}

Wordlist::Wordlist(string fname)
{

	root = nullptr;
	nodes = 0;
	total_words =0;

	ifstream myFile;
	myFile.open(fname);
	string next;

	while( myFile >> next )
	{
		cout << next << endl;
		this->insert(next);
	}

	cout << "file has been completely read" << endl;
	myFile.close();


}

int Wordlist::height( AVLTreeNode* node)
{
	if( node == nullptr)
	{
		return 0;
	}
	return node->height;
}

int Wordlist::balance_factor(AVLTreeNode* node)
{
	// if the node called on is nullptr then return the no change 
	if( node == nullptr)
	{
		return 0;
	}

	// if the difference is greater than one or less than one this will return unbalanced
	return height(node->left) - height(node->right);
}

AVLTreeNode* Wordlist::right_rotation(AVLTreeNode* node)
{
	//make the new nodes



	AVLTreeNode* new_root = node->left;
	cout << ( new_root == nullptr ) << endl;
	AVLTreeNode* right_content = node->left->right; // breaking here because node->left == nullptr

	/*
		prod issue
		The function is calling the left right rotation on the nodes when there is no left node
		meaing that the incorrect roation is being called
		this can imply that the heigth of the nodes is incorrect 
		this would make the balance factor have an incorrect value 
		meaing that the incorrect roation would be called 

		where the height could be going wrong.
		after the insertion the rebalancing of the nodes up the tree

	*/

	// make the new root point to the old root
	// make the new roots parent the old roots parent

	
	new_root->right = node;
	new_root->parent = node->parent;



	//make the old roots parent the new root
	// make the old root point to the right content from the new root
	node->parent = new_root;
	node->left = right_content;

	// make the parent of the right content point to old root

	if( right_content != nullptr)
	{
		right_content->parent = node;
	}


	//update the height of the nodes
	node->height = max( height(node->left) , height(node->right)) + 1;
	new_root->height = max( height(new_root->left) , height(new_root->right)) + 1;

	return new_root;


}

AVLTreeNode* Wordlist::left_rotation(AVLTreeNode* node)
{
	AVLTreeNode* new_root = node->right;
	AVLTreeNode* left_content = node->right->left;

	// swaps the nodes
	new_root->left = node;
	new_root->parent = node->parent;


	node->parent = new_root;
	node->right = left_content;

	/*
	
		resons that the assignment bellow could be breaking
		- left content is the nullptr and trying to call the parent fuction is bearking it

		found that the left content is the nullptr

		fix:
			make check if the nullptr is the left content
			if it is then no need to reassign the pointer
	
	*/


	// check if the left_content is the nullptr to avoid crashing
	if( left_content != nullptr)
	{
		left_content->parent = node;
	}
	



	

	node->height = max( height(node->left) , height(node->right) ) + 1;
	new_root->height = max( height(new_root->left) , height(new_root->right)) + 1;


	return new_root;
}

void Wordlist::insert( string data ) 
{
	AVLTreeNode* iterate = root; // make a temp ptr
	AVLTreeNode* prev = nullptr; // make a ptr to the node that will be the new nodes parent
	total_words++; // each insertion means one new word is added 

	/*
	
		using the prev and iterate, go through the avl tree.
		if the current node is geater than the data then go left and vice versa

		if the data is already in the tree then increment the word couter for that node
		if the iterate pointer becomes the nullptr then we have found a new leaf spot for
		the new node
	
	*/

	// if the root is the nullptr
	if(root == nullptr)
	{
		nodes++;
		root = new AVLTreeNode(data);
		return;
	}

	while( iterate != nullptr )
	{
		prev = iterate; // set the prev node to the iterate before it moves down

		if( data > iterate->word )
		{
			iterate = iterate->right;
		}
		else if( data < iterate->word)
		{
			iterate = iterate->left;
		}
		else if(data == iterate->word)
		{
			iterate->word_count++;
			return;
		}
	}

	// make iterate the new node with the data pointed to by prev

	nodes++;
	iterate = new AVLTreeNode(data);
	
	if( prev->word < data)
	{
		prev->right = iterate;
	}
	else
	{
		prev->left = iterate;
	}

	int balance; // initialize balance monitering variable

	/*
	
		the prev node is the parent of the iterate node
		take the prev node and change it to the new height and check balance

		decide what rotations to make
		by handing back the rotation as a pointer the parent node will point to the newly
		rotated node in the tree hence making it all connected 

		repeat this process until current node is the nullptr meaning that we are above the root
	
	*/

	/*
	
		prod issue

		i think the pointer 
	
	*/

	

	while( prev != nullptr)
	{

		prev->height = 1 + max( height(prev->left) , height(prev->right) ); // set height
		balance = balance_factor(prev); // check if the current node is balance

		//check if the left is heavier and the node is to the left of the left child

		if( balance > 1 && data < prev->left->word)
		{	
			//right rotation
			prev = right_rotation(prev);
		}
		else if( balance < -1 && data > prev->right->word)
		{
			//single left
			prev = left_rotation(prev);

		}
		else if( balance > 1 && data > prev->left->word)
		{	
			//left right case
			prev->left = left_rotation(prev->left);
			prev = right_rotation(prev);

		}
		else if( balance < -1 && data < prev->right->word  )
		{	
			cout << "right left" << endl;	
			prev->right = right_rotation(prev->right);
			prev = left_rotation(prev);
		}

		prev = prev->parent;

	}


}

int Wordlist::differentWords()
{
	return nodes;
}