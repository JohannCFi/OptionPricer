#ifndef PUTOPTION_H
#define PUTOPTION_H
#include <algorithm>
#include "EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption
{

public:
	PutOption(double expiry, double strike)
		: EuropeanVanillaOption(expiry, strike) {
	}

	double payoff(double z) override {
		return std::max(GetStrike() - z, 0.0);
	}

	OptionType GetOptionType() override {
		return OptionType::put;
	}
};

#endif
