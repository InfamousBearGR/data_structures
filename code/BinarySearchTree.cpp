#include "BinarySearchTree.h"
#include <iostream>
#include "Searching.h"

BSTNode* sortedArrayToBST(vector<AvgDataUnit*>& arrayIn, int start, int end) { //given a sorted array, forms BST. start/end for recursive purposes
	if (start > end) //max depth reached
		return NULL;

	int middle = (start + end) / 2; //choose the middle as current
	while (middle < end - start) { //make sure all occurrences of "middle" are to its left. AKA no element EQUAL to middle goes RIGHT
		if (arrayIn[middle]->getAvgTemp() != arrayIn[middle + 1]->getAvgTemp()) {
			break;
		}
		middle++;
	}
	BSTNode* root = (BSTNode*)malloc(sizeof(BSTNode)); //recursively define all roots of subtrees
	root->data = arrayIn[middle]; //middle becomes the current root
	root->left = NULL;
	root->right = NULL;

	root->left = sortedArrayToBST(arrayIn, start, middle - 1); //recursive call for left subtree
	root->right = sortedArrayToBST(arrayIn, middle + 1, end); //recursive call for right subtree

	return root;
}

void inOrderTraversal(BSTNode* tree) { //prints all data in the tree, executing in-order traversal
	if (tree != NULL) { //check if max depth is reached
		inOrderTraversal(tree->left); //first traverse left subtree
		cout << tree->data->getTimestamp() << "    " << tree->data->getAvgTemp() << endl; //then root
		inOrderTraversal(tree->right); //then right subtree
	}
}

BSTNode* searchBST(BSTNode* tree, string timestamp) { //finds node with matching timestamp
	string cmp1 = tree->data->getTimestamp() + "T00:00:00"; //add these last characters to make dates comparable
	string cmp2 = timestamp + "T00:00:00";
	int cond = compareTimestamps(cmp1, cmp2);
	if (cond == 0) { //equal or error
		if (tree->data->getTimestamp() == timestamp) { //equal
			return tree;
		}
		else {//error
			cout << "No such day in record" << endl;
		}
	}
	else if (cond < 0) { //cmp2<cmp1
		if (tree->left != NULL) {
			return searchBST(tree->left, timestamp); //recursively search subtree
		}
		else {
			cout << "No such day in record" << endl;
		}
	}
	else { //cmp2>cmp1
		if (tree->right != NULL) {
			return searchBST(tree->right, timestamp); //recursively search subtree
		}
		else {
			cout << "No such day in record" << endl;
		}
	}
	return NULL;
}

BSTNode* BSTfindMin(BSTNode* tree) { //finds min entry. Essentially goes all-left
	if (tree->left != NULL) {
		return BSTfindMin(tree->left);
	}
	else {
		return tree;
	}
}

BSTNode* BSTfindMax(BSTNode* tree) { //finds max entry. Essentially goes all-right
	if (tree->right != NULL) {
		return BSTfindMax(tree->right);
	}
	else {
		return tree;
	}
}

void BSTdeleteNode(BSTNode* tree, BSTNode* node) {//deletes given node from tree
	string cmp1 = tree->data->getTimestamp() + "T00:00:00"; //add these last characters to make dates comparable
	string cmp2 = node->data->getTimestamp() + "T00:00:00";
	int cond = compareTimestamps(cmp1, cmp2);
	if (cond == 0) { //equal
		return;
	}
	else if (cond < 0) { //cmp2<cmp1
		if (tree->left == node) { //if node is left child, delete left child 
			tree->left = NULL;
		}
		else {
			if (tree->left != NULL) { //recursively move further down until parent of node is found
				BSTdeleteNode(tree->left, node);
			}
			else {
				return;
			}
		}
	}
	else { //cmp2>cmp1
		if (tree->right == node) { //if node is right child, delete right child 
			tree->right = NULL;
		}
		else {
			if (tree->right != NULL) { //recursively move further down until parent of node is found
				BSTdeleteNode(tree->right, node);
			}
			else {
				return;
			}
		}
	}
}

void BSTShowMin(BSTNode* tree) { //prints all days with min entry
	float min = BSTfindMin(tree)->data->getAvgTemp();
	BSTNode* curr = tree;

	cout << "The day(s) with the lowest average temperature (" << min << ") is/are:" << endl;

	while (curr != NULL) { //starts from the root and goes all left
		if (curr->data->getAvgTemp() == min) {
			cout << curr->data->getTimestamp() << endl;
		}
		curr = curr->left;
	}
}

void BSTShowMax(BSTNode* tree) { //prints all days with max entry
	float max = BSTfindMax(tree)->data->getAvgTemp();
	BSTNode* curr = tree;

	cout << "The day(s) with the highest average temperature (" << max << ") is/are:" << endl;

	while (curr != NULL) { //starts from the root and goes all right UNTIL it finds max. then goes all left to check for equals
		bool found = false;
		if (curr->data->getAvgTemp() == max) {
			cout << curr->data->getTimestamp() << endl;
			bool found = true;
		}
		if (found) {
			curr = curr->left;
		}else {
			curr = curr->right;
		}
	}
}
