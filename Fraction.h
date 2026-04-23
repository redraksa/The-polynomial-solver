#pragma once
#include <iostream>
#include <map>
#include "Rational.h"

enum COMPARES {
	GREATER, SMALLER, EQUAL
};

enum RETURNTYPEDIVIDEPOLYNOMS {
	REMAINDER, QUOTIENT
};

typedef std::map<long long, Rational> Polynom;

class Fraction {
private:
	Polynom numerator;
	Polynom denumerator;

	Polynom multiplicationPolynoms(const Polynom& firstPolynom, const Polynom& secondPolynom) {
		Polynom resultPolynom;

		for (auto& member1 : firstPolynom) {
			for (auto& member2 : secondPolynom) {
				std::pair<long long, Rational> resultMember = member2;
				resultMember.first += member1.first;
				resultMember.second *= member1.second;
				resultPolynom[resultMember.first] += resultMember.second;
			}
		}
		return resultPolynom;
	}

	Polynom additionPolynoms(const Polynom& firstPolynom, const Polynom& secondPolynom) {
		Polynom resultPolynom = secondPolynom;

		for (auto& member : firstPolynom) {
			if (resultPolynom.find(member.first) != resultPolynom.end()) {
				resultPolynom[member.first] += member.second;
			}
			else {
				resultPolynom[member.first] = member.second;
			}
		}

		return resultPolynom;
	}

	Polynom substractionPolynoms(const Polynom& firstPolynom, const Polynom& secondPolynom) {
		Polynom resultPolynom = firstPolynom;

		for (auto& member : secondPolynom) {
			if (resultPolynom.find(member.first) != resultPolynom.cend()) {
				resultPolynom[member.first] -= member.second;
			}
			else {
				resultPolynom[member.first] = member.second * (-1);
			}
		}

		return resultPolynom;
	}

	Polynom dividePolynoms(Polynom divisible, Polynom divider, RETURNTYPEDIVIDEPOLYNOMS returnType) {
		long long orderPower = divisible.crbegin()->first - divider.crbegin()->first;

		Polynom tempNumenator = divisible;
		addZeros(tempNumenator);
		Polynom diffNumenator;
		Polynom resultNumenator;
		std::pair<long long, Rational> multiplier;
		for (long long i = orderPower; i >= 0; --i) {
			multiplier.first = i;
			multiplier.second = std::next(tempNumenator.rbegin(), orderPower - i)->second / divider.crbegin()->second;
			diffNumenator = std::move(multiplicationPolynoms(divider, { multiplier }));
			tempNumenator = std::move(substractionPolynoms(tempNumenator, diffNumenator));
			resultNumenator[multiplier.first] = multiplier.second;

		}

		if (returnType == REMAINDER) {
			eraseZeros(tempNumenator);
			return tempNumenator;
		}
		else {
			eraseZeros(resultNumenator);
			return resultNumenator;
		}
	}

	/*	Polynom GCD(Polynom first, Polynom second) {
		std::reference_wrapper<Polynom> biggerPolynom = first;
		std::reference_wrapper<Polynom> smallerPolynom = second;

		COMPARES compare = comparePolynoms(biggerPolynom, smallerPolynom);
		if (compare != EQUAL) {
			if (compare == SMALLER) {
				biggerPolynom = second;
				smallerPolynom = first;
			}

			Polynom temp1 = biggerPolynom, temp2 = smallerPolynom;
			biggerPolynom = temp1;
			smallerPolynom = temp2;
			while (!isZero(smallerPolynom)) {
				temp1 = std::move(dividePolynoms(biggerPolynom, smallerPolynom, REMAINDER));
				std::swap(temp1, temp2);
			}

			return biggerPolynom;
		}
		else {
			return first;
		}
	}

	void reduceFraction() {
		auto divider = GCD(numerator, denumerator);
		if (!isZero(divider)) {
			numerator = std::move(dividePolynoms(numerator, divider, QUOTIENT));
			denumerator = std::move(dividePolynoms(denumerator, divider, QUOTIENT));
			eraseZeros();
		}
	}*/
	Polynom simpleGCD(Polynom first, Polynom second) {
		std::reference_wrapper<Polynom> biggerPolynom = first;
		std::reference_wrapper<Polynom> smallerPolynom = second;

		COMPARES compare = comparePolynoms(biggerPolynom, smallerPolynom);
		if (compare != EQUAL) {
			if (compare == SMALLER) {
				biggerPolynom = second;
				smallerPolynom = first;
			}

			Polynom temp1 = biggerPolynom, temp2 = smallerPolynom;
			biggerPolynom = temp1;
			smallerPolynom = temp2;
			while (!isZero(smallerPolynom)) {
				temp1 = dividePolynoms(biggerPolynom, smallerPolynom, REMAINDER);
				std::swap(temp1, temp2);
			}

			return biggerPolynom;
		}
		else {
			return first;
		}
	}

	long long getLCM(const long long first, const long long second) {
		if (first == 0 || second == 0) {
			return 0;
		}

		long long gcd = std::gcd(first, second);
		long long temp = first / gcd;
		return Rational::saveMul(temp, second);
	}

	Polynom CollinsGCD(Polynom first, Polynom second) {
		std::reference_wrapper<Polynom> biggerPolynom = first;
		std::reference_wrapper<Polynom> smallerPolynom = second;

		COMPARES compare = comparePolynoms(biggerPolynom, smallerPolynom);
		if (compare != EQUAL) {
			if (compare == SMALLER) {
				biggerPolynom = second;
				smallerPolynom = first;
			}

			Polynom temp1 = biggerPolynom.get(), temp2 = smallerPolynom.get();

			long long lcmDenom = 1;

			for (const auto& member : temp1) {
				lcmDenom = getLCM(lcmDenom, member.second.getDenumenator());
			}

			for (const auto& member : temp2) {
				lcmDenom = getLCM(lcmDenom, member.second.getDenumenator());
			}

			Polynom lcmPolynom;
			lcmPolynom[0] = Rational(lcmDenom, 1);
			temp1 = multiplicationPolynoms(temp1, lcmPolynom);
			temp2 = multiplicationPolynoms(temp2, lcmPolynom);

			long long prev_d = 0;
			long long prev_lc = 0;
			long long psi = -1;
			bool isFirstIteration = true;

			while (!isZero(temp2)) {
				long long d = temp1.crbegin()->first - temp2.crbegin()->first;
				long long lc = temp2.crbegin()->second.getNumenator();


				Polynom R;
				R[0] = Rational::savePow(lc, d + 1);
				Polynom dividend = multiplicationPolynoms(temp1, R);
				Polynom prem = dividePolynoms(dividend, temp2, REMAINDER);


				Polynom beta;
				if (isFirstIteration) {
					long long sign = ((d + 1) % 2 == 0) ? 1 : -1;
					beta[0] = sign;
				}
				else {
					long long beta_val = Rational::savePow(psi, prev_d);
					beta_val = Rational::saveMul(beta_val, -prev_lc);
					beta[0] = beta_val;
				}


				Polynom nextPolynom = dividePolynoms(prem, beta, QUOTIENT);


				if (!isFirstIteration) {
					long long num = Rational::savePow(-prev_lc, prev_d);
					long long den = Rational::savePow(psi, prev_d - 1);
					psi = num / den;
				}


				prev_d = d;
				prev_lc = lc;
				temp1 = temp2;
				temp2 = nextPolynom;
				isFirstIteration = false;
			}


			long long gcd_content = 0;
			for (auto& member : temp1) {
				gcd_content = std::gcd(gcd_content, std::abs(member.second.getNumenator()));
			}
			if (gcd_content > 1) {
				Polynom contentPolynom;
				contentPolynom[0] = gcd_content;
				temp1 = dividePolynoms(temp1, contentPolynom, QUOTIENT);
			}

			return temp1;
		}
		else {
			return first;
		}
	}

	Polynom GCD(const Polynom& first, const Polynom& second) {
		try
		{
			return simpleGCD(first, second);
		}
		catch (const std::overflow_error&)
		{
			try
			{
				return CollinsGCD(first, second);
			}
			catch (const std::overflow_error& e)
			{
				throw std::overflow_error("Error in finding GCD: " + std::string(e.what()));
			}
		}

	}

	void reduceFraction() {
		try {
			auto divider = GCD(numerator, denumerator);
			if (!isZero(divider)) {
				numerator = dividePolynoms(numerator, divider, QUOTIENT);
				denumerator = dividePolynoms(denumerator, divider, QUOTIENT);
				eraseZeros();
			}
		}
		catch (const std::overflow_error&) {
			return;
		}
	}

	COMPARES comparePolynoms(Polynom& first, Polynom& second) {
		auto it1 = first.crbegin(), it2 = second.crbegin();
		for (; it1 != first.crend() && it2 != second.crend(); ++it1, ++it2) {
			if (it1->first > it2->first || (it1->first == it2->first && it1->second > it2->second)) {
				return GREATER;
			}
			else if (it1->first < it2->first || (it1->first == it2->first && it1->second < it2->second))
			{
				return SMALLER;
			}
		}
		if (it1 != first.crend()) {
			return GREATER;
		}
		else if (it2 != second.crend()) {
			return SMALLER;
		}
		else {
			return EQUAL;
		}
	}


	void eraseZeros(Polynom& polynom) {
		for (auto it = polynom.begin(); it != polynom.end();) {
			if (it->second == 0) {
				it = polynom.erase(it);
			}
			else {
				++it;
			}
		}

		if (polynom.empty()) {
			polynom[0] = 0;
		}
	}

	void addZeros(Polynom& polynom) {
		long long power = polynom.crbegin()->first;
		for (long long i = 0; i < power; ++i) {
			if (polynom.find(i) == polynom.end()) {
				polynom[i] = 0;
			}
		}
	}
	void eraseZeros() {
		for (auto it = numerator.begin(); it != numerator.end();) {
			if (it->second == 0) {
				it = numerator.erase(it);
			}
			else {
				++it;
			}
		}

		if (numerator.empty()) {
			numerator[0] = 0;
		}

		for (auto it = denumerator.begin(); it != denumerator.end();) {
			if (it->second == 0) {
				it = denumerator.erase(it);
			}
			else {
				++it;
			}
		}

		if (denumerator.empty()) {
			denumerator[0] = 1;
		}
	}


public:
	Fraction(long long power, long long number) {
		numerator.insert({ power, number });
		denumerator.insert({ 0, 1 });
	}

	Fraction(const Polynom& numenatorPolynom) {
		numerator = numenatorPolynom;
		denumerator.insert({ 0, 1 });
	}

	void setNumenator(Polynom polynom) {
		numerator = std::move(polynom);
	}

	void setDenumenator(Polynom polynom) {
		denumerator = std::move(polynom);
	}

	void addition(const Fraction& other) {
		Polynom otherNumerator = other.numerator;
		if (denumerator != other.denumerator) {
			otherNumerator = std::move(multiplicationPolynoms(other.numerator, denumerator));
			numerator = std::move(multiplicationPolynoms(numerator, other.denumerator));
			denumerator = std::move(multiplicationPolynoms(other.denumerator, denumerator));
		}

		numerator = std::move(additionPolynoms(numerator, otherNumerator));

		eraseZeros();
		if (isFraction()) {
			reduceFraction();
		}

	}

	void substraction(const Fraction& other) {
		Polynom otherNumerator = other.numerator;
		if (denumerator != other.denumerator) {
			otherNumerator = std::move(multiplicationPolynoms(other.numerator, denumerator));
			numerator = std::move(multiplicationPolynoms(numerator, other.denumerator));
			denumerator = std::move(multiplicationPolynoms(other.denumerator, denumerator));
		}

		numerator = std::move(substractionPolynoms(numerator, otherNumerator));

		eraseZeros();
		if (isFraction()) {
			reduceFraction();
		}
	}

	void multiplication(const Fraction& other) {
		numerator = std::move(multiplicationPolynoms(numerator, other.numerator));
		denumerator = std::move(multiplicationPolynoms(other.denumerator, denumerator));

		eraseZeros();
		if (isFraction()) {
			reduceFraction();
		}
	}

	void division(const Fraction& other) {
		numerator = std::move(multiplicationPolynoms(numerator, other.denumerator));
		denumerator = std::move(multiplicationPolynoms(other.numerator, denumerator));

		eraseZeros();
		if (isFraction()) {
			reduceFraction();
		}
	}

	Polynom getMixedFraction(RETURNTYPEDIVIDEPOLYNOMS returnType) {
		return dividePolynoms(numerator, denumerator, returnType);
	}

	bool isInteger() {
		return numerator.size() == 1 && numerator.find(0) != numerator.cend() && !isFraction();
	}

	void normilizeFraction() {
		Polynom p;
		p[0] = denumerator.crbegin()->second;
		numerator = std::move(dividePolynoms(numerator, p, QUOTIENT));
		denumerator = std::move(dividePolynoms(denumerator, p, QUOTIENT));
	}

	bool isZero() {
		bool isZero = true;
		for (auto& member : numerator) {
			if (member.second != 0) {
				isZero = false;
			}
		}
		return isZero;
	}

	bool isZero(const Polynom& polynom) {
		bool isZero = true;
		for (auto& member : polynom) {
			if (member.second != 0) {
				isZero = false;
			}
		}
		return isZero;
	}

	Rational getFreeMember() {
		if (numerator.find(0) != numerator.cend()) {
			return numerator[0];
		}
		else {
			return Rational(0, 1);
		}
	}

	bool isFraction() {
		return !(denumerator.size() == 1 && denumerator.find(0) != denumerator.end() && denumerator[0] == 1);
	}

	void eraseFraction() {
		numerator.clear();
		denumerator.clear();
		numerator[0] = 0;
		denumerator[0] = 1;
	}

	Polynom getNumerator() const {
		return numerator;
	}

	Polynom getDenumenator() const {
		return denumerator;
	}
};

