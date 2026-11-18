#ifndef CALLOPTION_H
#define CALLOPTION_H
#include <algorithm>
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption
{

public:
	CallOption(double expiry, double strike)
		: EuropeanVanillaOption(expiry, strike) {
	}

	double payoff(double z) override {
		return std::max(z - GetStrike(), 0.0);
	}

	OptionType GetOptionType() override {
		return OptionType::call;
	}

};

#endif
