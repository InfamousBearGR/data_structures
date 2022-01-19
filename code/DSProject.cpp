#include <chrono>
#include "Menus.h"
#include "DataUnit.h"
#include "DataReader.h"
#include "HashTable.h"
#include "Searching.h"
#include "Sorting.h"
#include "BinarySearchTree.h"
#include <iostream>

using namespace std;

int main()
{
	//setup
	vector<DataUnit*> dataList; //empty data vector
	readTemp(dataList);   //read data
	readHum(dataList);   //read data
	vector<AvgDataUnit*> avgDataList = readAvgTemp(dataList); //create the average data
	vector<DataUnit*> copy(dataList); //make a copy of data
	quickSortTimestamp(dataList, 0, dataList.size() - 1); //sort if needed (eg for a search)

	MainMenu(avgDataList); //menu

	//mergeSortTemp(dataList); //how a call might look

	return 0;
}

