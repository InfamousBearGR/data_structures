#pragma once
#include <vector>
#include "DataUnit.h"
#include "AvgDataUnit.h"
#include "BSTNode.h"

using namespace std;

vector<DataUnit*> mergeSortTemp(vector<DataUnit*>&);
vector<DataUnit*> quickSortTemp(vector<DataUnit*>&, int, int);
vector<DataUnit*> merge(vector<DataUnit*>&, vector<DataUnit*>&);
vector<DataUnit*> heapify(vector<DataUnit*>&, int, int);
vector<DataUnit*> heapSortHum(vector<DataUnit*>&);
vector<DataUnit*> countingSortHum(vector<DataUnit*>&);
vector<DataUnit*> quickSortTimestamp(vector<DataUnit*>&, int, int);
vector<AvgDataUnit*> quickSortAvg(vector<AvgDataUnit*>&, int, int);
