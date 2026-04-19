#pragma once
#include "Fraction.h"
class MixedFraction
{
private:
	Polynom whole;
	Fraction remainder;

	void eraseZeros() {
		for (auto it = whole.begin(); it != whole.end();) {
			if (it->second == 0) {
				it = whole.erase(it);
			}
			else {
				++it;
			}
		}

		if (whole.empty()) {
			whole[0] = 0;
		}
	}
public:
	MixedFraction(int power, int coefficient) : remainder(0, 0) {
		whole[power] = coefficient;
	}

	void addition(const MixedFraction& other) {

		for (auto& member : other.whole) {
			whole[member.first] += member.second;
		}

		remainder.addition(other.remainder);

		Polynom temp = remainder.getMixedFraction(QUOTIENT);
		remainder.setNumenator(remainder.getMixedFraction(REMAINDER));

		for (auto& member : temp) {
			whole[member.first] += member.second;
		}

		eraseZeros();
		
	}

	void substraction(const MixedFraction& other) {

		for (auto& member : other.whole) {
			whole[member.first] -= member.second;
		}

		remainder.substraction(other.remainder);

		Polynom temp = remainder.getMixedFraction(QUOTIENT);
		remainder.setNumenator(remainder.getMixedFraction(REMAINDER));

		for (auto& member : temp) {
			whole[member.first] += member.second;
		}

		eraseZeros();
	}

	void multiplication(const MixedFraction& other) {
		Polynom tempWhole;

		for (auto& member1 : whole) {
			for (auto& member2 : other.whole) {
				std::pair<int, Rational> resultMember = member2;
				resultMember.first += member1.first;
				resultMember.second *= member1.second;
				tempWhole[resultMember.first] += resultMember.second;
			}
		}

		Fraction tempFraction1(whole);
		tempFraction1.multiplication(other.remainder);

		Fraction tempFraction2(other.whole);
		tempFraction2.multiplication(remainder);

		remainder.multiplication(other.remainder);

		remainder.addition(tempFraction1);
		remainder.addition(tempFraction2);

		Polynom temp = remainder.getMixedFraction(QUOTIENT);
		remainder.setNumenator(remainder.getMixedFraction(REMAINDER));

		whole = std::move(tempWhole);

		for (auto& member : temp) {
			whole[member.first] += member.second;
		}

		eraseZeros();
	}

	void division(const MixedFraction& other) {
		Fraction divider(other.whole);
		divider.addition(other.remainder);

		Fraction divisible(whole);
		divisible.addition(remainder);

		divisible.division(divider);

		whole = std::move(divisible.getMixedFraction(QUOTIENT));
		remainder.setNumenator(divisible.getMixedFraction(REMAINDER));
		remainder.setDenumenator(divisible.getDenumenator());

		eraseZeros();
	}

	void normilize() {
		remainder.normilizeFraction();
	}
	
	bool isZero() {
		return isZeroWhole() && remainder.isZero();
	}

	bool isZeroWhole() {
		return whole.size() == 1 && whole.find(0) != whole.end() && whole[0] == 0;
	}

	bool isInteger() {
		return remainder.isZero() && whole.size() == 1 && whole.find(0) != whole.end();
	}

	bool isFraction() {
		return !remainder.isZero();
	}

	int getFreeMember() {
		if (whole.find(0) != whole.end()) {
			return whole[0];
		}
		else {
			return 0;
		}
	}

	Polynom getWholePart() const {
		return whole;
	}

	Fraction getFractionPart() const {
		return remainder;
	}
};

