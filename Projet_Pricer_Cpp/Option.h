#ifndef OPTION_H
#define OPTION_H
#include <iostream>
#include <stdexcept>

class Option
{
private:

	double _expiry{};

public:
	Option(double expiry) : _expiry(expiry) {}

	virtual double payoff(double) = 0;

	double getExpiry() const {
		return _expiry;
	}
};
#endif 
