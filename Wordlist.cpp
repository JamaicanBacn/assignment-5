#include "Wordlist.h"
#include <iomanip>
using std::setprecision;
using std::fixed;
using std::max;
using std::to_string;

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
		this->insert(next);
	}

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

	/*
	
		Insertion function for the node with value data
		handles the balancing and the insertion for the underlying avl tree
	
	*/

	// each time this funciton is called there is one word added
	// set root to the return value the final return is the root

	root = Avl_insertion_handling(root,data); 

}

AVLTreeNode* Wordlist::Avl_insertion_handling( AVLTreeNode* node, string data)
{

	// check if the first node is the nullptr to being the avl tree
	if( node == nullptr)
	{
		nodes++; // each time a new node is made there is one more to the count
		return new AVLTreeNode(data);
	}

	// basic bst mapping down to the next open leaf node

	if(data < node->word)
	{
		node->left = Avl_insertion_handling(node->left , data);
		node->left->parent = node;
	}
	else if( data > node->word)
	{
		node->right = Avl_insertion_handling(node->right,data);
		node->right->parent = node;
	}
	else
	{
		// check the work on this function it is never getting inside
		node->count += 1;
		return node;
	}

	// take the height of the node to check for the balance 

	node->height = 1 + max(height(node->left) , height(node->right));

	int balance = balance_factor(node);

	// rotation for type of node im-balance

	if( balance > 1 && data < node->left->word )
	{
		return right_rotation(node);
	}

	if( balance < -1 && data > node->right->word)
	{
		return left_rotation(node);
	}

	if( balance > 1 && data > node->left->word)
	{
		node->left = left_rotation(node->left);
		return right_rotation(node);
	}

	if( balance < -1 && data < node->right->word)
	{
		node->right = right_rotation(node->right);
		return left_rotation(node);
	}


	return node;
	


}

int Wordlist::differentWords()
{
	return nodes;
}

int Wordlist::totalWords()
{
	return total_words;
}

string Wordlist::mostFrequent()
{

	// put the exception code here 
	AVLTreeNode* temp = root;
	AVLTreeNode* largest = findMaximum(temp);
	


	return( largest->word + " " + to_string(largest->count));

}

AVLTreeNode* Wordlist::findMaximum( AVLTreeNode* node )
{
	// uses the in order traversal to find the max value 

	AVLTreeNode* min_node = new AVLTreeNode("");

	if( node == nullptr)
	{
		return min_node;
	}

	AVLTreeNode* left = findMaximum(node->left);
	AVLTreeNode* right = findMaximum(node->right);
	AVLTreeNode* ret = node;


	if( left->count > node->count)
	{
		ret = left;
	}
	if(right->count  > ret->count )
	{
		ret = right;
	}

	return ret;
	
}

int Wordlist::singleton_travesal(AVLTreeNode* node)
{
	if( node == nullptr)
	{
		return 0;
	}

	if( node->count == 1)
	{
		return 1 + singleton_travesal(node->left) + singleton_travesal(node->right);
	}
	else{
		return singleton_travesal(node->left) + singleton_travesal(node->right);
	}
}

int Wordlist::singletons()
{
	return singleton_travesal(root);
}