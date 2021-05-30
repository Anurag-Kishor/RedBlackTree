#include<iostream>
#include "RedBlackTree.h"

using namespace std;


RedBlackTree::RedBlackTree() {
	head = NULL;
}

void RedBlackTree::Add(int data) {
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

RBNode* RedBlackTree::CreateNode(int data) {
	RBNode* node = new RBNode;
	node->info = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->color = Red;
	return node;
}

void RedBlackTree::InOrder(RBNode* node) {

	if (node != NULL) {
		InOrder(node->left);
		cout << node->info << " " << node->color << endl;
		InOrder(node->right);
	}
}

void RedBlackTree::FixRBTree(RBNode* node) {

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
		else if (sibling->color == Red) {						//Check if sibling is Red
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

RBNode* RedBlackTree::FindSibling(RBNode* node) {


	if (node->parent->right == node) {

		return node->parent->left;
	}
	else {
		return node->parent->right;
	}
}

void RedBlackTree::RightRotation(RBNode* node, bool check) {
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

void RedBlackTree::LeftRotation(RBNode* node, bool check) {

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

	temp->right = node->left;
	node->parent = temp->parent;
	node->left = temp;
	temp->parent = node;

	if (check) swap(node->color, temp->color);

}

void RedBlackTree::Delete(int data)
{
	auto node = Search(data, head);	//z
	auto temp = node;	//y
	RBNode* dbNode;		//x
	Color nodeColor = node->color;

	if (node->left == NULL) {		//Node has only left child
		dbNode = node->right;
		DeleteNode(head, node, node->right);
	}
	else if (node->right == NULL) {		//Node has only right child
		dbNode = node->left;
		DeleteNode(head, node, node->left);
	}
	else {	//Node has both children
		temp = Successor(head, node->right);
		nodeColor = temp->color;
		dbNode = temp->right;

		if (temp->parent == node) {
			dbNode->parent = node;
		}
		else {
			DeleteNode(head, temp, temp->right);
			temp->right = node->right;
			temp->right->parent = temp;
		}
		DeleteNode(head, node, temp);
		temp->left = node->left;
		temp->left->parent = temp;
		temp->color = node->color;
	}

	if (nodeColor == Black) {
		FixDeletion(head, dbNode);
	}

	InOrder(head);
}

void RedBlackTree::DeleteNode(RBNode* head, RBNode* node, RBNode* newNode)
{
	if (node->parent == NULL) {
		head = newNode;
	}
	else if (node == node->parent->left) {
		node->parent->left = newNode;
	}
	else if (node == node->parent->right) {
		node->parent->right = newNode;
	}

	if(newNode != NULL)	newNode->parent = node->parent;

}

RBNode* RedBlackTree::Search(int data, RBNode* node)
{

	
	if (node->info > data) {
		Search(data, node->left);
	}
	else if (node->info < data) {
		Search(data, node->right);
	}
	else {
		return node;
	}
}

void RedBlackTree::FixDeletion(RBNode* head, RBNode* node)
{
	while (node != head && node->color == Black) {
		if (node == node->parent->left) {
			auto sibling = node->parent->right;

			if (sibling->color == Red) {
				node->parent->color = Red;
				sibling->color = Black;
				LeftRotation(node, false);
			}
			if (sibling->left->color == Black && sibling->right->color == Black) {
				sibling->color = Red;
				node = node->parent;
			}
			else {
				if (sibling->right->color == Black) {
					sibling->left->color = Black;
					sibling->color = Red;
					RightRotation(sibling->left, false);
					sibling = node->parent->right;
				}

				sibling->color = node->parent->color;
				node->parent->color = Black;
				sibling->right->color = Black;
				LeftRotation(node->left, false);
				node = head;
			}
		}
		else {
			auto sibling = node->parent->left;
			if (sibling->color == Red) {
				sibling->color = Black;
				node->parent->color = Red;
				RightRotation(node, false);
				sibling = node->parent->left;
			}
			if (sibling->right->color == Black && sibling->left->color == Black) {
				sibling->color = Red;
				node = node->parent;
			}
			else {
				if (sibling->left->color == Black) {
					sibling->right->color = Black;
					sibling->color = Red;
					LeftRotation(sibling->right, false);
				}
				sibling->color = node->parent->color;
				node->parent->color = Black;
				sibling->left->color = Black;
				RightRotation(node, false);
				node = head;
			}
		}
	}
	node->color = Black;
}

RBNode* RedBlackTree::Successor(RBNode* head, RBNode* node)
{
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}
