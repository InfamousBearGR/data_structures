#pragma once
#include <string>
#include <vector>
#include "DataUnit.h"

using namespace std;

string binarySearch(vector<DataUnit*>&, string);
string interpolationSearch(vector<DataUnit*>&, string);
int compareTimestamps(string, string);
string BIS(vector<DataUnit*>&, string);
string BIS2(vector<DataUnit*>&, string);

