#include "ParallelCircuit.h"

ParallelCircuit::ParallelCircuit() : Circuit() {}

double ParallelCircuit::calculateOutputVoltage(double inputVoltage) const {
	//voltage is the same across all branches in a parallel circuit
	return inputVoltage;
}

double ParallelCircuit::calculateTotalResistance() const {
	double reciprocalSum = 0.0;
	for (const auto& component : components) {
		double value = component->getValue();
		if (value == 0.0) {
			throw runtime_error("Componnet with zero resistance detected in parallel circuit.");
		}
		reciprocalSum += 1.0 / value;
	}

	if (reciprocalSum == 0.0) {
		throw runtime_error("Total resistance is infinite in parallel circuit.");
	}

	return 1.0 / reciprocalSum;
}

vector<double> ParallelCircuit::calculateVoltageDrops(double inputVoltage) const {
	// in parallel, voltage is the same across all resistors
	vector<double> voltageDrops;
	voltageDrops.reserve(components.size());

	for (size_t i = 0; i < components.size(); ++i) {
		voltageDrops.push_back(inputVoltage);
	}

	return voltageDrops;
}

vector<double> ParallelCircuit::calculatePowerDissipation(double inputVoltage) const {
	vector<double> powerDissipation;
	powerDissipation.reserve(components.size());

	for (const auto& component : components) {
		double R = component->getValue();
		if (R == 0.0) {
			throw runtime_error("Component with zero resistance detected in parallel circuit.");
		}
		// Power: P = V^2 / R
		double P = (inputVoltage * inputVoltage) / R;
		powerDissipation.push_back(P);
	}

	return powerDissipation;
}