#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include "MixedFraction.h"

class Emitter
{
public:
	
	MixedFraction getResult() const {
		if (!polynomials.empty()) {
			return polynomials.top();
		}
		else {
			return MixedFraction(0, 0);
		}
		
	}

	void normilizeAnswer() {
		if (!polynomials.empty()) {
			polynomials.top().normilize();
		}
	}

	void addition() {
		MixedFraction firstPolinom = polynomials.top();
		polynomials.pop();

		polynomials.top().addition(firstPolinom);
	}

	void substraction() {
		MixedFraction firstPolinom = polynomials.top();
		polynomials.pop();

		polynomials.top().substraction(firstPolinom);
	}

	void multiplication() {
		MixedFraction firstPolinom = polynomials.top();
		polynomials.pop();

		polynomials.top().multiplication(firstPolinom);

	}

	void division() {
		MixedFraction firstPolinom = polynomials.top();
		polynomials.pop();

		if (!firstPolinom.isZero()) {
			polynomials.top().division(firstPolinom);
		}
		else {
			throw std::runtime_error("zero division");
		}
	}

	void power() {
		MixedFraction firstFraction = polynomials.top();
		polynomials.pop();

		if (firstFraction.isInteger()) {
			int power = firstFraction.getFreeMember();
			if (power > 0) {
				MixedFraction multi = polynomials.top();
				for (int i = 1; i < power; ++i) {
					polynomials.top().multiplication(multi);
				}
			}
			else if (power < 0) {
				MixedFraction divider = polynomials.top();
				polynomials.pop();
				polynomials.push({ 0,1 });
				for (int i = 0; i > power; --i) {
					polynomials.top().division(divider);
				}
			}
			else {
				polynomials.pop();
				polynomials.push({ 0, 1 });
			}
		}
		else {
			throw std::runtime_error("Non-integer power");
		}
	}

	void pushX() {
		polynomials.push({ 1, 1 });
	}

	void pushNumber(int num) {
		polynomials.push({ 0, num });
	}

	void pushZero() {
		polynomials.push({ 0, 0 });
	}

private:
	
	std::stack<MixedFraction> polynomials;

	
};

