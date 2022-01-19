#include "DataUnit.h"

DataUnit::DataUnit(string ts, int t, int h) {
	timestamp = ts;
	temp = t;
	hum = h;
}

void DataUnit::setHum(int h) {
	hum = h;
}

int DataUnit::getHum() {
	return hum;
}

int DataUnit::getTemp() {
	return temp;
}

string DataUnit::getTimestamp() {
	return timestamp;
}

