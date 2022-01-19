#include <iostream>
#include "HashTable.h"

using namespace std;

AvgDataUnit*** createHashTable(vector<AvgDataUnit*> input) { //make hash table from array
	AvgDataUnit*** output = new AvgDataUnit **[HASHTABLE_SIZE]; //defined size
	for (int i = 0; i < HASHTABLE_SIZE; i++) { //clear previous trash
		output[i] = NULL; 
	}

	for (AvgDataUnit* data : input) { //iterate over all data
		string ts = data->getTimestamp(); //get current timestamp
		if (output[hashFunction(ts)] == NULL) { //if bucket is not initialized
			output[hashFunction(ts)] = (AvgDataUnit**)malloc(sizeof(AvgDataUnit*) * BUCKET_SIZE); //set memory to bucket
			for (int i = 0; i < BUCKET_SIZE; i++) { //clear previous trash
				output[hashFunction(ts)][i] = NULL; 
			}
			output[hashFunction(ts)][0] = data; //set the current data as first data
		}
		else { //if bucket is already initialized
			int i = 0;
			while (output[hashFunction(data->getTimestamp())][i] != NULL) { //find latest entry
				i++;
			}
			output[hashFunction(data->getTimestamp())][i] = data; //insert data after latest entry
		}
	}

	return output;
}

int hashFunction(string date) { //generate the hash for a given date
	int result = 0;
	for (char c : date) { //add up all ASCII values
		result += (int)c;
	}
	result = result % HASHTABLE_SIZE; //modulo to stay within hash table indices
	return result;
}

AvgDataUnit* hashSearch(AvgDataUnit** bucket, string ts) { //given timestamp, find entry in given BUCKET
	int i = 0;
	while (bucket[i] != NULL) { //find last entry
		if (bucket[i]->getTimestamp() == ts || i == BUCKET_SIZE - 1) break; //break if it's found, or if out of bounds
		i++;
	}
	if (bucket[i] == NULL) { //if it's not found
		cout << "No such day in record" << endl;
		return NULL;
	}
	return bucket[i];
}

void hashDelete(AvgDataUnit** bucket, string ts) { //given a timestamp, delete data from bucket
	int last = 0; //init last entry in bucket
	bool found = false; 
	int search = 0; //init entry we're looking for
	while (bucket[last] != NULL) { //calculate both values with 1 iteration
		if (!found && ts == bucket[last]->getTimestamp()) {
			search = last;
			found = true;
		}
		last++;
	}
	last--; //last ends up 1 greater than needed
	if (bucket[search]->getTimestamp() != ts) { //check if incorrect data is found
		cout << "No such day in record" << endl;
	}
	else { //switch search for last, and make the last entry NULL. Switching needs to be done because of how search works
		bucket[search] = bucket[last];
		bucket[last] = NULL;
	}
}

void showDistribution(AvgDataUnit*** hashtable) { //cosmetic function that shows distribution of elements amongst buckets
	for (int i = 0; i < HASHTABLE_SIZE; i++) {
		if (hashtable[i] != NULL) {
			int j = 0;
			while (hashtable[i][j] != NULL) {
				cout << " I "; //place an "I" wherever item exists
				j++;
			}
		}
		else {
			cout << "Bucket "<< i<< " is empty";
		}
		cout << endl; //switch lines between buckets
	}
}