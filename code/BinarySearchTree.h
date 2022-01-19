#pragma once
#include <vector>
#include "AvgDataUnit.h"
#include "BSTNode.h"

using namespace std;

BSTNode* sortedArrayToBST(vector<AvgDataUnit*>&, int, int);
void inOrderTraversal(BSTNode*);
BSTNode* searchBST(BSTNode*, string);
BSTNode* BSTfindMin(BSTNode*);
void BSTdeleteNode(BSTNode*, BSTNode*);
void BSTShowMin(BSTNode*);
void BSTShowMax(BSTNode*);
BSTNode* BSTfindMax(BSTNode*);