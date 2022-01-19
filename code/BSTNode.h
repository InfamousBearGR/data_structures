#pragma once

#include "AvgDataUnit.h"

//represents one node in a BST. Only stores one piece of data and left/right pointers
class BSTNode
{
public:
	AvgDataUnit* data;
	BSTNode* left;
	BSTNode* right;

};

