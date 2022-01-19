#pragma once
#include <string>

using namespace std;

//stores timestamp and average temperature. Represents one record in BSTs and the hash table 
class AvgDataUnit {
private:
	string timestamp;
	float avgTemp; //temp needs to be float here

public:
	AvgDataUnit(string, float = 0);
	string getTimestamp();
	float getAvgTemp();
	void setAvgTemp(float);
};

