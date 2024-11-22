#include"Wordlist.h"
#include<iostream>


using namespace std;


int main()
{
   Wordlist* ws = new Wordlist("tiny_shakespeare.txt"); 
   cout << ws->differentWords() << endl;
   cout << ws->mostFrequent() << endl;
   cout << ws->singletons() << endl;


    return 0;
}