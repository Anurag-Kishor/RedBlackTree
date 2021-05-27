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

private:
	RBNode* head;

public:
	RedBlackTree() {
		head = NULL;
	}

	RBNode* CreateNode(int data) {
		RBNode* node = new RBNode;
		node->info = data;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->color = Red;
		return node;
	}

	void Add(int data) {
		auto newNode = CreateNode(data);

		if (head == NULL) {
			head = newNode;
			head->color = Black;
			
		}
		else {
			auto temp = head;
			while (temp != NULL) {
				if (newNode->info > temp->info) {

					if (temp->right == NULL) {
						temp->right = newNode;
						newNode->parent = temp;
						break;
					}
					temp = temp->right;
				}
				else if (newNode->info < temp->info) {

					if (temp->left == NULL) {
						temp->left = newNode;
						newNode->parent = temp;
						break;
					}
					temp = temp->left;
				}
			}
		}

		FixRBTree(newNode);
		InOrder(head);
		cout << endl;
	}

	void InOrder(RBNode* node) {

		if (node != NULL) {
			InOrder(node->left);
			cout << node->info << " " << node->color << endl;
			InOrder(node->right);
		}
	}

	void FixRBTree(RBNode* node) {			

		if (node->parent == NULL) {
			return;
		}

		if (node->parent->color == Red && node->color == Red) {		//If Parent and child both have Red nodes

			auto sibling = FindSibling(node->parent);

			if (sibling == NULL || sibling->color == Black) {	//Check if Sibling is either NULL or Black

				if (node->parent->parent->right == node->parent && node->parent->right == node) {	//RR tree, Perform Left Rotation
					LeftRotation(node->parent, true);
				}
				else if (node->parent->parent->left == node->parent && node->parent->right == node) { //LR Tree, Perform Double Rotation
					LeftRotation(node, false);
					RightRotation(node, true);

				}
				else if (node->parent->parent->right == node->parent && node->parent->left == node) { //RL Tree
					RightRotation(node, false);
					LeftRotation(node, true);
				}
				else if (node->parent->parent->left == node->parent && node->parent->left == node) {
					RightRotation(node->parent, true);
				}
				FixRBTree(node);

			}
			else if(sibling->color == Red){						//Check if sibling is Red
				node->parent->color = sibling->color = Black;			//Just Switch both to Black 
				
				if (node->parent->parent != head) {
					if (node->parent->parent->color == Red) {
						node->parent->parent->color = Black;
					}
					else {
						node->parent->parent->color = Red;
					}
					FixRBTree(node->parent->parent);
				}
			}
		}

	}

	RBNode* FindSibling(RBNode* node) {

		
		if (node->parent->right == node) {
			
			return node->parent->left;
		}
		else {
			return node->parent->right;
		}
	}

	void RightRotation(RBNode* node, bool check) {
		auto temp = node->parent;

		if (temp->parent == NULL) {
			head = node;
			node->parent = NULL;

		}
		else if (temp->parent->right == node->parent) {
			temp->parent->right = node;
		}
		else if (temp->parent->left == node->parent) {
			temp->parent->left = node;
		}

		temp->left = node->right;
		node->parent = temp->parent;
		node->right = temp;
		temp->parent = node;

		if (check) swap(node->color, temp->color);
	}
	
	void LeftRotation(RBNode* node, bool check) {

		auto temp = node->parent;
		
		if (temp->parent == NULL) {
			head = node;
			node->parent = NULL;
		}else if (temp->parent->right == node->parent) {
			temp->parent->right = node;
		}else if (temp->parent->left == node->parent) {
			temp->parent->left = node;
		}

		temp->right = node->left;
		node->parent = temp->parent;
		node->left = temp;
		temp->parent = node;

		if (check) swap(node->color, temp->color);

	}
	
};



