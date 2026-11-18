#ifndef EUROPEANVANILLAOPTION_H
#define EUROPEANVANILLAOPTION_H
#include <iostream>
#include <stdexcept>
#include "Option.h"

enum class OptionType {

	call,
	put
};

class EuropeanVanillaOption : public Option
{
private:

	double _strike{};

public:
	EuropeanVanillaOption(double expiry, double strike)
		: Option(expiry), _strike(strike)
	{
		if (expiry < 0.0 || strike < 0.0)
			throw std::runtime_error("invalide expiry or strike");
	}
	virtual OptionType GetOptionType() = 0;

	friend class BlackScholesPricer;

protected:

	double GetStrike() {
		return _strike;
	}
};
#endif