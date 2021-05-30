#include<iostream>
#include "RedBlackTree.h"
using namespace std;


int main() {

	RedBlackTree* rbt = new RedBlackTree();
	rbt->Add(10);
	rbt->Add(5);
	rbt->Add(1);
	rbt->Add(20);
	rbt->Add(0);
	rbt->Add(15);
	rbt->Add(21);

	rbt->Delete(1);

}