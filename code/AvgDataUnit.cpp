#include "AvgDataUnit.h"

AvgDataUnit::AvgDataUnit(string ts, float t) {
	timestamp = ts;
	avgTemp = t;
}

string AvgDataUnit::getTimestamp() {
	return timestamp;
}

float AvgDataUnit::getAvgTemp() {
	return avgTemp;
}

void AvgDataUnit::setAvgTemp(float t) {
	avgTemp = t;;
}