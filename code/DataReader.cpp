#include <fstream>
#include <iostream>
#include <string>
#include "DataReader.h"

using namespace std;

void readTemp(vector<DataUnit*> & datalist) { //Also reads timestamps. Essentially reads all data within " "
	ifstream file("tempm.txt");
	string line;
	while (getline(file, line)) {
		line.erase(0, line.find('"')+1);
		while (line != "}") {
			string timestamp = line.substr(0, line.find('"'));
			line = line.erase(0, line.find('"') + 1); //delete timestamp"
			line = line.erase(0, line.find('"') + 1); //delete junk"
			string temp = line.substr(0, line.find('"'));
			line = line.erase(0, line.find('"') + 1); //delete temp"
			line = line.erase(0, line.find('"') + 1); //delete junk"

			datalist.push_back(new DataUnit(timestamp, stoi(temp)));
		}
	}
}

void readHum(vector<DataUnit*> & datalist) { //similar to readTemp, but doesn't read timestamps
	ifstream file("hum.txt");
	string line;
	int i = 0;
	while (getline(file, line)) {
		line.erase(0, line.find('"') + 1);
		while (line != "}") {
			line = line.erase(0, line.find('"') + 1); //delete timestamp"
			line = line.erase(0, line.find('"') + 1); //delete junk"
			string hum = line.substr(0, line.find('"'));
			line = line.erase(0, line.find('"') + 1); //delete temp"
			line = line.erase(0, line.find('"') + 1); //delete junk"
			datalist[i]->setHum(stoi(hum));
			i++;
		}
	}
}

vector<AvgDataUnit*> readAvgTemp(vector<DataUnit*>& datalist) { //transforms the full array of records into an array of avg temperature per day
	vector<AvgDataUnit*> result; //this will be returned
	int sum = 0;
	int number = 0;
	string prevDay = datalist[0]->getTimestamp().substr(0, 10); //only get the day, don't need hours etc
	for (DataUnit* data : datalist) { //accumulate the average
		if (data->getTimestamp().substr(0, 10) == prevDay) {
			sum += data->getTemp();
			number++;
		}
		else {
			AvgDataUnit* addition = new AvgDataUnit(prevDay, (float)sum / number);
			prevDay = data->getTimestamp().substr(0, 10);
			result.push_back(addition);
			sum = 0;
			number = 0;
		}
	}
	AvgDataUnit* addition = new AvgDataUnit(datalist[datalist.size() - 1]->getTimestamp().substr(0, 10), (float)sum / number); //current new element
	result.push_back(addition);

	return result;
}
