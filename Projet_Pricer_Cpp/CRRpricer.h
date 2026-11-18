#ifndef CRRPRICER_H
#define CRRPRICER_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "Option.h"
#include "BinaryTree.h"

class CRRPricer {

private:
	Option* _option;
	int _depth;
	double _asset_price;
	double _up;
	double _down;
	double _interest_rate;
	BinaryTree<double> _pricetree;

public:
	CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate, BinaryTree<double> pricetree)
		: _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate)
		{
			if (interest_rate >= up || interest_rate <= down)
				throw std::runtime_error("invalid risk free rate");
			_pricetree.setDepth(depth);

	}

	void Compute() 
	{

		double q = (_interest_rate - _down) / (_up - _down);

		for (int i = 0; i <= _depth; ++i) 
		{
			double S = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
			double payoff = _option->payoff(S);
			_pricetree.setNode(_depth, i, payoff);
		}

		for (int n = _depth - 1; n >= 0; --n) 
		{
			for (int i = 0; i <= n; ++i) {
				double H_up = _pricetree.getNode(n + 1, i + 1);
				double H_down = _pricetree.getNode(n + 1, i);

				double H = (q * H_up + (1 - q) * H_down) / (1 + _interest_rate);
				_pricetree.setNode(n, i, H);
			}
		}
	}

	double get(int n, int i) const 
	{
		return _pricetree.getNode(n, i);
	}
};
#endif