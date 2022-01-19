#pragma once
#include <vector>
#include "DataUnit.h"
#include "AvgDataUnit.h"

void readTemp(vector<DataUnit*>&);
void readHum(vector<DataUnit*>&);
vector<AvgDataUnit*> readAvgTemp(vector<DataUnit*>&);


