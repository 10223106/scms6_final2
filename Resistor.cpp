#include "Resistor.h"

Resistor::Resistor(const string& name, const double& value) : Component(name, value) {} 

double Resistor::getValue() const {
    return value;  // Return the resistance value
}

string Resistor::getType() const {
    return "Resistor";  // Return the type of component
}