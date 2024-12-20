#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

using namespace std;

class Component {
protected:
	string name;
	double value;        //R,L,C value

public:
	Component(const string& name, const double& value);
	virtual ~Component() {}
	virtual double getValue() const = 0;       //pure virtual function
	virtual string getType() const = 0;
};

#endif // !COMPONENT_H

