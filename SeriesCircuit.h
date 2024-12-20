#pragma once
#ifndef SERIESCIRCUIT_H
#define SERIESCIRCUIT_H
#include"Circuit.h"
#include<stdexcept>

using namespace std;

class SeriesCircuit :public Circuit {
public:
	SeriesCircuit();
	double calculateOutputVoltage(double inputVoltage) const override;
	double calculateTotalResistance() const override;

	vector<double> calculateVoltageDrops(double inputVoltage) const;

	vector<double> calculatePowerDissipation(double inputVoltage) const;

};
#endif 