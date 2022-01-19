#pragma once
#include <vector>
#include "AvgDataUnit.h"
#define HASHTABLE_SIZE 11  //number of buckets
#define BUCKET_SIZE 20  //number of items per bucket

using namespace std;

AvgDataUnit*** createHashTable(vector<AvgDataUnit*>);
int hashFunction(string);
AvgDataUnit* hashSearch(AvgDataUnit**, string);
void hashDelete(AvgDataUnit**, string);
void showDistribution(AvgDataUnit*** hashtable);

