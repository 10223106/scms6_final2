#include "VoltageDivider.h"
#include <stdexcept>

VoltageDivider::VoltageDivider() : Circuit() {} //explicitly calls Circuit constructor

double VoltageDivider::calculateOutputVoltage(double inputVoltage) const {
	if (components.size() != 2) {
		throw runtime_error("Voltage divider requires exactly two resistors.");
	}
	double r1 = components[0]->getValue();
	double r2 = components[1]->getValue();
	return (r2 / (r1 + r2)) * inputVoltage;
}

double VoltageDivider::calculateTotalResistance() const {
	if (components.size() != 2) {
		throw runtime_error("Voltage divider requires exactly two resistors.");
	}
	double r1 = components[0]->getValue();
	double r2 = components[1]->getValue();
	return r1 + r2;
}