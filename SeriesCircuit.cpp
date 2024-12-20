#include "SeriesCircuit.h"

SeriesCircuit::SeriesCircuit() : Circuit() {}

double SeriesCircuit::calculateOutputVoltage(double inputVoltage) const {
	//for a simple placeholder, assume output voltage = input voltage
	return inputVoltage;
}

double SeriesCircuit::calculateTotalResistance() const {
	double totalResistance = 0;
	for (const auto& component : components) {
		totalResistance += component->getValue();
	}
	return totalResistance; 
}

vector<double> SeriesCircuit::calculateVoltageDrops(double inputVoltage) const {
	vector<double> voltageDrops;
	double totalR = calculateTotalResistance();
	if (totalR == 0.0) {
		throw runtime_error("Total resistance is zero in the series circuit, cannot calculate voltage drops.");
	}

	double current = inputVoltage / totalR;

	//voltage drop across each resistor: V = I*R
	for (const auto& component : components) {
		double R = component->getValue();
		double V = current * R;
		voltageDrops.push_back(V);
	}

	return voltageDrops;
}

vector<double> SeriesCircuit::calculatePowerDissipation(double inputVoltage) const {
	vector<double> powerDissipation;
	double totalR = calculateTotalResistance();

	if (totalR == 0.0) {
		throw runtime_error("Total resistance is zero in the series circuit, cannot calculate voltage drops.");
	}

	double current = inputVoltage / totalR;

	//power dissipated in each resistor: P = I^2 * R
	for (const auto& component : components) {
		double R = component->getValue();
		double P = (current * current) * R;
		powerDissipation.push_back(P);
	}

	return powerDissipation;
}