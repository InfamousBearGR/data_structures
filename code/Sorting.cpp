#include <iostream>
#include <cmath>
#include "Sorting.h"

using namespace std;

vector<DataUnit*> mergeSortTemp(vector<DataUnit*>& arrayIn) {
	if (arrayIn.size() > 1) {
		int mid = (arrayIn.size()-1) / 2; //split the array
		vector<DataUnit*> left(arrayIn.begin(), arrayIn.begin() + mid + 1); //first half
		vector<DataUnit*> right(arrayIn.begin() + mid + 1, arrayIn.begin() + arrayIn.size()); //second half
		vector<DataUnit*> sortedleft = mergeSortTemp(left); //resursively sort the left sub-array
		vector<DataUnit*> sortedright = mergeSortTemp(right); //resursively sort the right sub-array
		return merge(sortedleft, sortedright); //merge the 2 sorted subarrays
	}
	return arrayIn; //if size=1 just return the item
}

vector<DataUnit*> quickSortTemp(vector<DataUnit*>& arrayIn, int left, int right) {
	int pivot, lArrow, rArrow;
	lArrow = left;
	rArrow = right;
	pivot = arrayIn[(left + right) / 2]->getTemp(); //pick middle item as pivot
	do
	{
		while (arrayIn[rArrow]->getTemp() > pivot) //try to find entry bigger than pivot, from right to left
			rArrow--;
		while (arrayIn[lArrow]->getTemp() < pivot) //try to find entry lesser than pivot, from left to right
			lArrow++;
		if (lArrow <= rArrow) //if a pair of those is found, switch them
		{
			DataUnit* temp = arrayIn[lArrow];
			arrayIn[lArrow] = arrayIn[rArrow];
			arrayIn[rArrow] = temp;
			lArrow++;
			rArrow--;
		}
	} while (rArrow >= lArrow); //if we found a pair
	if (left < rArrow) 
		quickSortTemp(arrayIn, left, rArrow); //recursive call for left
	if (lArrow < right)
		quickSortTemp(arrayIn, lArrow, right); //recursive call for right

	return arrayIn;
}

vector<DataUnit*> heapSortHum(vector<DataUnit*>& arrayIn) {
	int s = arrayIn.size();

	for (int i = s / 2 - 1; i >= 0; i--) { //make heap, by heapifying all non leaf nodes
		heapify(arrayIn, s, i);
	}
 
	for (int i = s - 1; i > 0; i--) { //create sorted array from heap (extract largest entry)
		DataUnit* temp = arrayIn[0];
		arrayIn[0] = arrayIn[i];
		arrayIn[i] = temp;

		heapify(arrayIn, i, 0); //fix the tree after extraction
	}
	
	return arrayIn;
}

vector<DataUnit*> heapify(vector<DataUnit*>& arrayIn, int size, int pos) {//function to fix heap
	int max = pos; //max=root
	int left = 2 * pos + 1; //left child
	int right = 2 * pos + 2; //right child

	if (left<size && arrayIn[left]->getHum()>arrayIn[max]->getHum()) { //if left>current max
		max = left; //update max
	}

	if (right<size && arrayIn[right]->getHum()>arrayIn[max]->getHum()) { //if right>current max
		max = right; //update max
	}

	if (max != pos) { //if new max is not root, swap the two
		DataUnit* temp = arrayIn[max];
		arrayIn[max] = arrayIn[pos];
		arrayIn[pos] = temp;

		return heapify(arrayIn, size, max); //heapify the affected subtree
	}

	return arrayIn;
}

vector<DataUnit*> countingSortHum(vector<DataUnit*>& arrayIn) {
 
	vector<DataUnit*> out(arrayIn.size());
	int count[101] = {}; //0 to 100 accepted humidities

	for (DataUnit* data : arrayIn) { //for each entry in arrayIn
		count[data->getHum()]++; //increment the entry of the count array
	}

	for (int i = 1; i < 101; i++) { //for the entire count array
		count[i] += count[i - 1]; //add to each entry the sum of the previous entries
	}
 
	for (DataUnit* data : arrayIn) //add each input element at the right position of the output
	{
		out[count[data->getHum()] - 1] = data; //create output
		count[data->getHum()]--; //decrement count, for repeating entries
	}

	return out;
}

vector<DataUnit*> merge(vector<DataUnit*>& left, vector<DataUnit*>& right) { //used in mergesort
	vector<DataUnit*> output;
	int imax = left.size();
	int jmax = right.size();
	int i = 0; //iterates over left subarray
	int j = 0; //iterates over right subarray

	while (i < imax && j < jmax) { //if we haven't reached the end of any array
		if (left[i]->getTemp() < right[j]->getTemp()) { //insert the entry with the least temperature
			output.push_back(left[i]);
			i++;
		}
		else {
			output.push_back(right[j]);
			j++;
		}
	}
	while (i < imax) { //if right array is over, only look at left
		output.push_back(left[i]);
		i++;
	}
	while (j < jmax) { //if left array is over, only look at right
		output.push_back(right[j]);
		j++;
	}
	return output;
}

vector<DataUnit*> quickSortTimestamp(vector<DataUnit*>& arrayIn, int left, int right) { //same as quicksortTemp, but for timestamps
	int lArrow, rArrow;
	string pivot;
	lArrow = left;
	rArrow = right;
	pivot = arrayIn[(left + right) / 2]->getTimestamp();
	do
	{
		while (strcmp(arrayIn[rArrow]->getTimestamp().c_str(), pivot.c_str()) > 0)
			rArrow--;
		while (strcmp(arrayIn[lArrow]->getTimestamp().c_str(), pivot.c_str()) < 0)
			lArrow++;
		if (lArrow <= rArrow)
		{
			DataUnit* temp = arrayIn[lArrow];
			arrayIn[lArrow] = arrayIn[rArrow];
			arrayIn[rArrow] = temp;
			lArrow++;
			rArrow--;
		}
	} while (rArrow >= lArrow);
	if (left < rArrow)
		quickSortTimestamp(arrayIn, left, rArrow);
	if (lArrow < right)
		quickSortTimestamp(arrayIn, lArrow, right);

	return arrayIn;
}

vector<AvgDataUnit*> quickSortAvg(vector<AvgDataUnit*>& arrayIn, int left, int right) { //same as quicksortTemp, but for average data
	int lArrow, rArrow;
	float pivot;
	lArrow = left;
	rArrow = right;
	pivot = arrayIn[(left + right) / 2]->getAvgTemp();
	do
	{
		while (arrayIn[rArrow]->getAvgTemp() > pivot)
			rArrow--;
		while (arrayIn[lArrow]->getAvgTemp() < pivot)
			lArrow++;
		if (lArrow <= rArrow)
		{
			AvgDataUnit* temp = arrayIn[lArrow];
			arrayIn[lArrow] = arrayIn[rArrow];
			arrayIn[rArrow] = temp;
			lArrow++;
			rArrow--;
		}
	} while (rArrow >= lArrow);
	if (left < rArrow)
		quickSortAvg(arrayIn, left, rArrow);
	if (lArrow < right)
		quickSortAvg(arrayIn, lArrow, right);

	return arrayIn;
}

