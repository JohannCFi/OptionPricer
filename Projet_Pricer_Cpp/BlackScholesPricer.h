#ifndef BLACKSCHOLESPRICER_H
#define BLACKSCHOLESPRICER_H
#include <algorithm>
#include <iostream>
#include <cmath>
#include "EuropeanVanillaOption.h"

class BlackScholesPricer
{

private:
	EuropeanVanillaOption* _option;
	double _S0;
	double _r;
	double _sigma;

	double ComputeD1() {
		double K = _option->GetStrike();
		double T = _option->getExpiry();

		return (std::log(_S0 / K) + (_r + std::pow(_sigma, 2) / 2) * T) / (_sigma * std::sqrt(T));
	}

	double NormalCDF(double x) {
		return std::erfc(-x / std::sqrt(2)) * 0.5;
	}

public:

	BlackScholesPricer(EuropeanVanillaOption* option, double S0, double r, double sigma)
		: _option(option), _S0(S0), _r(r), _sigma(sigma) {
	}

	double price() {
		double T = _option->getExpiry();
		double K = _option->_strike;

		double d1 = ComputeD1();
		double d2 = d1 - _sigma * std::sqrt(T);

		double callPrice = _S0 * NormalCDF(d1) - K * std::exp(-_r * T) * NormalCDF(d2);

		double putPrice = -_S0 * NormalCDF(-d1) + K * std::exp(-_r * T) * NormalCDF(-d2);

		if (_option->GetOptionType() == OptionType::call)
			return callPrice;
		else
			return putPrice;
	}

	double delta() {

		double T = _option->getExpiry();
		double K = _option->_strike;

		double d1 = ComputeD1();
		if (_option->GetOptionType() == OptionType::call)
			return NormalCDF(d1);
		else
			return NormalCDF(d1) - 1;
	}
};
#endif