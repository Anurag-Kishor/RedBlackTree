#pragma once

#include<iostream>
using namespace std;

enum Color {Red, Black} ;

struct RBNode {
	int info;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	Color color;
};
class RedBlackTree {



public:
	RedBlackTree();
	void Add(int data);
	void Delete(int data);


private:
	RBNode* head;
	RBNode* CreateNode(int data);
	void InOrder(RBNode* node);
	void FixRBTree(RBNode* node);
	RBNode* FindSibling(RBNode* node);
	void RightRotation(RBNode* node, bool check);
	void LeftRotation(RBNode* node, bool check);
	void DeleteNode(RBNode* head, RBNode* node, RBNode* nodeRight);
	RBNode* Search(int data, RBNode* node);
	void FixDeletion(RBNode* head, RBNode* node);
	RBNode* Successor(RBNode* head, RBNode* node);
};



