#include "Wordlist.h"
#include <iomanip>
using std::setprecision;
using std::fixed;
using std::max;
using std::to_string;
using std::invalid_argument;

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

Wordlist::~Wordlist()
{
	//breaks down the tree
	Decomposition(root); // reccursive function to break down tree
}

Wordlist::Wordlist(string fname)
{

	root = nullptr;
	nodes = 0;
	total_words =0;

	ifstream myFile; // file ptr
	myFile.open(fname);
	string next;

	while( myFile >> next )
	{
		//insert each word into the file
		this->insert(next);
	}

	myFile.close();


}

Wordlist::Wordlist(const Wordlist& reference)
{
	// tree copy function returns the root of a deep copy of reference
	root = this->treeCopy(reference.getRoot());
	nodes = reference.nodes;
	total_words = reference.total_words;
}

Wordlist& Wordlist::operator=(const Wordlist& reference)
{
	//check for self assignment 
	if( this == &reference )
	{
		return *this;
	}

	root = this->treeCopy(reference.getRoot());
	nodes = reference.nodes;
	total_words = reference.total_words;

	return *this;

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

bool Wordlist::remove(string data)
{
	//check if the tree even contains the word
	if( !this->contains(data))
	{
		return false;
	}

	//return the root of the tree without the node
	root = Avl_removal_handling(root,data);
	return true;
	
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

AVLTreeNode* Wordlist::Avl_removal_handling(AVLTreeNode* node, string data)
{
	//  if the node is the nu

	if( node == nullptr)
	{
		return node;
	}

	if( data < node->word)
	{
		node->left = Avl_removal_handling(node->left, data);
	}
	else if( data > node->word)
	{
		node->right = Avl_removal_handling(node->right , data);	
	}
	else{
		
		nodes --;
		total_words -= node->count;

		// check if the node has a child
		if( (node->left == nullptr) || (node->right == nullptr) )
		{	
			// assign temp to the child node that is not the nullptr
			AVLTreeNode* temp = node->left ? node->left : node->right;


			// if both are the nullptr then there is no replacment
			if(temp == nullptr)
			{
				temp = node;
				node = nullptr;
			}
			else{
				//if there is a child node make node == temp
				node->word = temp->word;
				node->count = temp->count;

				node->right = temp->right;
				node->left = temp->left;

			}
			// free temp to remove the node from the tree 
			free(temp);
		}
		else{
			/*
			
				if there are two children find the sucessor for replacment
				then do a search for the temp node as it must be removed

			*/
			AVLTreeNode* temp = predecessor(node->right);
			node->count = temp->count;
			node->word = temp->word;
			node->right = Avl_removal_handling(node->right, temp->word);

		}

	}

	/*
	
		check that the current node isnt the nullptr
		from the inital ternary statment 

		this is so that the calls after this do not break the process
	
	*/

	if(node == nullptr)
	{
		return node; 
	}

	/*
	
		check for node rotations
		for the removal check for imbalences in the current node
		and the node bellow to know the type of rotation that is needed
	
	*/

	node->height = 1 + max( height(node->left) , height(node->right));

	int balance = balance_factor(node);

	if( balance > 1 && balance_factor(node->left) >= 0)
	{
		return right_rotation(node);
	}

	if( balance < -1 && balance_factor(node->right) <= 0)
	{
		return left_rotation(node);
	}

	if( balance > 1 && balance_factor(node->left) < 0)
	{
		node->left = left_rotation(node->left);
		return right_rotation(node);
	}

	if(balance < -1 && balance_factor(node->right) > 0)
	{
		node->right = right_rotation(node->right);
		return left_rotation(node);
	}

	// if the subtree is balanced then return the node 
	return node;


}

int Wordlist::differentWords()
{
	return nodes; // keeps track of all unique nodes
}

int Wordlist::totalWords()
{
	return total_words; // the sum of all word counts
}

string Wordlist::mostFrequent()
{

	try
	{
		if(nodes == 0)
		{
			throw std::invalid_argument("runtime error");
		}	
	}
	catch( std::runtime_error& e)
	{
		std::cerr << "Exception: " << e.what() << endl;
		exit(0);
	}

	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
		
	// put the exception code here 
	AVLTreeNode* temp = root;
	AVLTreeNode* largest = findMaximum(temp);
	

	// returns tha most common word in the list
	return( largest->word + " " + to_string(largest->count));

}

AVLTreeNode* Wordlist::findMaximum( AVLTreeNode* node )
{
	// uses the in order traversal to find the max value 

	// make a node with a count of zero
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

	// if the node has a count of one return one plus the traversal on the children
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

void Wordlist::printWords()
{
	postOrderTraversal(root,0);
}

int Wordlist::postOrderTraversal(AVLTreeNode* node , int print_order)
{
	if( node == nullptr)
	{
		return print_order;
	}

	print_order = postOrderTraversal(node->left , print_order);
	print_order++;

	cout << print_order << "." << node->word << " " << node->count << endl;

	print_order = postOrderTraversal(node->right , print_order);

	return print_order;
}

AVLTreeNode* Wordlist::treeCopy(const AVLTreeNode* node)
{
	if( node == nullptr )
	{
		return nullptr;
	}

	// for each node in the reference tree make a new node
	//  copy all of the arributtes then make deeps copies for the rest
	AVLTreeNode* current = new AVLTreeNode(node->word);
	current->count = node->count;
	current->height = node->height;

	current->left = treeCopy(node->left);
	current->right = treeCopy(node->right);

	return current;



}

void Wordlist::Decomposition(AVLTreeNode* node)
{
	if(node == nullptr)
	{
		return;
	}

	Decomposition(node->left);
	Decomposition(node->right);

	// if the node is a leaf remove it
	//uses dsf do so it can return 
	delete node;
	


}

int Wordlist::getCount(string data)
{
	AVLTreeNode* iterate = root;

	/*
	
		checks the path the node would be on
		if found returns the nodes count
		if not found returns 0 as the word does not occur

	*/


	while(iterate != nullptr)
	{
		if( data < iterate->word)
		{
			iterate = iterate->left;
		}
		else if( data > iterate->word)
		{
			iterate = iterate->right;
		}
		else
		{
			return iterate->count;
		}
	}

	return 0;
}

bool Wordlist::contains(string data)
{
	// if the count is less than 1 it has not appeared
	return this->getCount(data) > 0;
}

AVLTreeNode* Wordlist::predecessor(AVLTreeNode* node)
{
	AVLTreeNode* iterate = node;

	while( iterate->left != nullptr )
	{
		iterate = iterate->left;
	}

	return iterate;
}