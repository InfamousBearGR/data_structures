#include <time.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Searching.h"
#include "Sorting.h"

using namespace std;

string binarySearch(vector<DataUnit*>& arrayIn, string timestamp) {

	int i = arrayIn.size() / 2; //each time split in HALF
	int condition = strcmp(arrayIn[i]->getTimestamp().c_str(), timestamp.c_str()); //compare timestamps

	if (arrayIn.size() == 1 && arrayIn[i]->getTimestamp() != timestamp) { //error case
		return "Error, timestamp does not exist";
	}
	else if (condition == 0) { //found
		return "Humidity: " + to_string(arrayIn[i]->getHum()) + "    Temperature: " + to_string(arrayIn[i]->getTemp());
	}
	else if (condition < 0) { //timestamp < middle
		vector<DataUnit*> half(arrayIn.begin() + i, arrayIn.begin() + arrayIn.size());
		return binarySearch(half, timestamp); //recursive call on the selected subarray
	}
	else if (condition > 0) { //timestamp > middle
		vector<DataUnit*> half(arrayIn.begin(), arrayIn.begin() + i);
		return binarySearch(half, timestamp); //recursive call on the selected subarray
	}
}

string interpolationSearch(vector<DataUnit*>& arrayIn, string timestamp) { //almost identical to binary search, but i is different
	int i = (double)arrayIn.size() * //this time split the array in fraction of the entire size, depending on relative size of timestamp
		compareTimestamps(arrayIn[0]->getTimestamp(), timestamp) / //uses helper function "compareTimestamps"
		compareTimestamps(arrayIn[0]->getTimestamp(), arrayIn[arrayIn.size() - 1]->getTimestamp());
	if (i >= arrayIn.size()) { //in case it gets out of bounds
		i = arrayIn.size() - 1;
	}
	int condition = strcmp(arrayIn[i]->getTimestamp().c_str(), timestamp.c_str());

	if (arrayIn.size() == 1 && arrayIn[i]->getTimestamp() != timestamp) {
		return "Error, timestamp does not exist";
	}
	else if (condition == 0) {
		return "Humidity: " + to_string(arrayIn[i]->getHum()) + "    Temperature: " + to_string(arrayIn[i]->getTemp());
	}
	else if (condition < 0) {
		vector<DataUnit*> part(arrayIn.begin() + i, arrayIn.begin() + arrayIn.size());
		return interpolationSearch(part, timestamp);
	}
	else if (condition > 0) {
		vector<DataUnit*> part(arrayIn.begin(), arrayIn.begin() + i);
		return interpolationSearch(part, timestamp);
	}
}

int compareTimestamps(string timestamp1, string timestamp2) {//helper function to compare 2 given timestamps
	tm t1 = {}; //create empty tm
	istringstream ss1(timestamp1); //make a string stream from the timestamp
	ss1 >> get_time(&t1, "%Y-%m-%dT%H:%M:%S"); //parse in specific format
	time_t time1 = mktime(&t1); //finally make time_t object

	tm t2 = {}; //same for the second timestamp
	istringstream ss2(timestamp2);
	ss2 >> get_time(&t2, "%Y-%m-%dT%H:%M:%S");
	time_t time2 = mktime(&t2);

	return difftime(time2, time1); //easily compare time_t objects
}

string BIS(vector<DataUnit*>& arrayIn, string timestamp) { //similar to interpolation, but now splits array into sqrt(size) parts
	int left = 0;
	int right = arrayIn.size() - 1;
	int size = right - left + 1;

	int i = (double)arrayIn.size() * //interpolation estimated step
		compareTimestamps(arrayIn[0]->getTimestamp(), timestamp) /
		compareTimestamps(arrayIn[0]->getTimestamp(), arrayIn[right]->getTimestamp());

	while (i < arrayIn.size() && i >= 0 && timestamp != arrayIn[i]->getTimestamp() && right - left + 1>0) {
		int j = 1; //multiplier of the sqrts
		size = right - left + 1;
		if (size <= 3) { //if size is small, linear search
			left++;
			i = left;
		}
		else if (compareTimestamps(arrayIn[i]->getTimestamp(), timestamp) >= 0) { //timestamp>guess
			while (compareTimestamps(arrayIn[i + j * sqrt(size)]->getTimestamp(), timestamp) > 0) {//keep checking subarrays of size sqrt(size)
				if (i + (j + 1) * sqrt(size) - 1 >= size) { //if next overflows
					break;
				}
				else {
					j++;
				}
			}
			right = i + j * sqrt(size); //update right
			left = i + (j - 1) * sqrt(size);//update left
		}
		else if (compareTimestamps(arrayIn[i]->getTimestamp(), timestamp) < 0) {//timestamp<guess
			while (compareTimestamps(arrayIn[i - j * sqrt(size)]->getTimestamp(), timestamp) < 0) {//keep checking subarrays of size sqrt(size)
				if (i - (j + 1) * sqrt(size) + 1 < 0) {//if next underflows
					break;
				}
				else {
					j++;
				}
			}
			right = i - (j - 1) * sqrt(size); //update right
			left = i - j * sqrt(size);//update left
		}

		if (left != right) { //if size is not 1
			i = left + (double)(right - left + 1) * //update i
				compareTimestamps(arrayIn[left]->getTimestamp(), timestamp) /
				compareTimestamps(arrayIn[left]->getTimestamp(), arrayIn[right]->getTimestamp());
		}
		else { //if size is 1
			i = left;
		}
	}

	if (i < arrayIn.size() && i >= 0 && timestamp == arrayIn[i]->getTimestamp()) { //check if we are inside bounds and if guess is junk
		return "Humidity: " + to_string(arrayIn[i]->getHum()) + "    Temperature: " + to_string(arrayIn[i]->getTemp());
	}
	else { //otherwise error
		return "Error, timestamp does not exist";
	}
}

string BIS2(vector<DataUnit*>& arrayIn, string timestamp) { //similar to BIS but now increments the sqrt multiplier "j" with powers of 2
	int left = 0;
	int right = arrayIn.size() - 1;
	int size = right - left + 1;

	int i = (double)arrayIn.size() *
		compareTimestamps(arrayIn[0]->getTimestamp(), timestamp) /
		compareTimestamps(arrayIn[0]->getTimestamp(), arrayIn[right]->getTimestamp());

	while (i < arrayIn.size() && i >= 0 && timestamp != arrayIn[i]->getTimestamp() && right - left + 1>0) {
		int j = 1;
		size = right - left + 1;
		if (size <= 3) {
			left++;
			i = left;
		}
		else if (compareTimestamps(arrayIn[i]->getTimestamp(), timestamp) >= 0) {
			while (compareTimestamps(arrayIn[i + pow(2, j - 1) * sqrt(size)]->getTimestamp(), timestamp) > 0) { //here pow is used
				if (i + pow(2, j) * sqrt(size) - 1 >= size) { //here pow is used
					break;
				}
				else {
					j++;
				}
			}
			right = i + pow(2, j - 1) * sqrt(size); //here pow is used
			left = i + pow(2, j - 2) * sqrt(size); //here pow is used
		}
		else if (compareTimestamps(arrayIn[i]->getTimestamp(), timestamp) < 0) {
			while (compareTimestamps(arrayIn[i - pow(2, j - 1) * sqrt(size)]->getTimestamp(), timestamp) < 0) { //here pow is used
				if (i - pow(2, j) * sqrt(size) + 1 < 0) { //here pow is used
					break;
				}
				else {
					j++;
				}
			}
			right = i - pow(2, j - 2) * sqrt(size); //here pow is used
			left = i - pow(2, j - 1) * sqrt(size); //here pow is used
		}

		if (left != right) {
			i = left + (double)(right - left + 1) *
				compareTimestamps(arrayIn[left]->getTimestamp(), timestamp) /
				compareTimestamps(arrayIn[left]->getTimestamp(), arrayIn[right]->getTimestamp());
		}
		else {
			i = left;
		}
	}

	if (i < arrayIn.size() && i >= 0 && timestamp == arrayIn[i]->getTimestamp()) {
		return "Humidity: " + to_string(arrayIn[i]->getHum()) + "    Temperature: " + to_string(arrayIn[i]->getTemp());
	}
	else {
		return "Error, timestamp does not exist";
	}
}

