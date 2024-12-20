#pragma once
// Resistor.h
#ifndef RESISTOR_H
#define RESISTOR_H

#include "Component.h"

class Resistor : public Component {
public:
	Resistor(const string& name, const double& value);
	double getValue() const override;
	string getType() const override;
};


#endif // !RESISTOR_H 