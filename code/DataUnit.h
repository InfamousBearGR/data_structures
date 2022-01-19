#pragma once
#include <string>

using namespace std;

//stores timestamp, temperature and humidity. Represents one record in given files
class DataUnit
{
private:
	string timestamp;
	int temp = 0;
	int hum = 0;
	
public:
	DataUnit(string, int, int = 0);
	void setHum(int h);
	int getTemp();
	int getHum();
	string getTimestamp();
};

