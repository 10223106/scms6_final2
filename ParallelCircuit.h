#pragma once
#ifndef PARALLELCIRCUIT_H
#define PARALLELCIRCUIT_H

#include"Circuit.h"
#include <stdexcept>

using namespace std;

class ParallelCircuit : public Circuit {
public:
	ParallelCircuit();
	double calculateOutputVoltage(double inputVoltage) const override;
	double calculateTotalResistance() const override;

	vector<double> calculateVoltageDrops(double inputVoltage) const;

	vector<double> calculatePowerDissipation(double inputVoltage) const;
};
#endif // !PARALLELCIRCUIT_H