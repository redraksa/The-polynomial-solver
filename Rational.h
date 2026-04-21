#pragma once
#include <iostream>
#include <numeric>
#include <ostream>

class Rational
{
private:
	int numenator;
	int denumenator;

	void reduceFraction() {
		int gcd = std::gcd(numenator, denumenator);
		if (gcd != 0) {
			numenator /= gcd;
			denumenator /= gcd;
		}

		if ((numenator > 0 && denumenator < 0) || (numenator < 0 && denumenator < 0)) {
			numenator *= -1;
			denumenator *= -1;
		}
	}
public:
	Rational() : numenator(0), denumenator(1) {}

	Rational(int numenator, int denumenator) : numenator(numenator), denumenator(denumenator) {
		if (denumenator == 0) {
			throw std::runtime_error("Denumenator of coefficient can't be equal to 0");
		}
		reduceFraction();
	}

	Rational(int number) : numenator(number), denumenator(1) {}

	Rational& operator+=(const Rational& other) {
		int commonDenumenator = denumenator * other.denumenator;
		int newNumenator = numenator * other.denumenator + other.numenator * denumenator;

		numenator = newNumenator;
		denumenator = commonDenumenator;

		if (denumenator == 0) {
			throw std::runtime_error("Denumenator of coefficient can't be equal to 0");
		}

		reduceFraction();

		return *this;
	}

	Rational& operator-=(const Rational& other) {
		int commonDenumenator = denumenator * other.denumenator;
		int newNumenator = numenator * other.denumenator - other.numenator * denumenator;

		numenator = newNumenator;
		denumenator = commonDenumenator;

		if (denumenator == 0) {
			throw std::runtime_error("Denumenator of coefficient can't be equal to 0");
		}

		reduceFraction();

		return *this;
	}

	Rational& operator*=(const Rational& other) {
		numenator *= other.numenator;
		denumenator *= other.denumenator;

		if (denumenator == 0) {
			throw std::runtime_error("Denumenator of coefficient can't be equal to 0");
		}

		reduceFraction();

		return *this;
	}

	Rational& operator/=(const Rational& other) {
		numenator *= other.denumenator;
		denumenator *= other.numenator;

		reduceFraction();

		if (denumenator == 0) {
			throw std::runtime_error("Denumenator of coefficient can't be equal to 0");
		}

		return *this;
	}

	Rational& operator=(const int number) {
		numenator = number;
		denumenator = 1;
		return *this;
	}

	friend Rational operator+(Rational first, const Rational& second) {
		return first += second;
	}
	friend Rational operator-(Rational first, const Rational& second) {
		return first -= second;
	}
	friend Rational operator*(Rational first, const Rational& second) {
		return first *= second;
	}
	friend Rational operator/(Rational first, const Rational& second) {
		return first /= second;
	}

	friend Rational operator+(Rational first, const int integer) {
		Rational second(integer);
		return first += second;
	}
	friend Rational operator-(Rational first, const int integer) {
		Rational second(integer);
		return first -= second;
	}
	friend Rational operator*(Rational first, const int integer) {
		Rational second(integer);
		return first *= second;
	}
	friend Rational operator/(Rational first, const int integer) {
		Rational second(integer);
		return first /= second;
	}

	friend bool operator==(const Rational& first, const Rational& second) {
		return first.numenator * second.denumenator == first.denumenator * second.numenator;
	}

	friend bool operator!=(const Rational& first, const Rational& second) {
		return !(first == second);
	}

	friend bool operator==(const Rational& first, const int integer) {
		Rational other(integer);
		return first == other;
	}

	friend bool operator!=(const Rational& first, const int integer) {
		return !(first == integer);
	}

	friend bool operator>(const Rational& first, const Rational& second) {
		return first.numenator * second.denumenator > second.numenator * first.denumenator;
	}

	friend bool operator<(const Rational& first, const Rational& second) {
		return first.numenator * second.denumenator < second.numenator * first.denumenator;
	}

	friend bool operator>(const Rational& first, const int number) {
		Rational second(number);
		return first > second;
	}

	friend bool operator<(const Rational& first, const int number) {
		Rational second(number);
		return first < second;
	}

	friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
		os << r.numenator;
		if (r.denumenator != 1) {
			os << "/" << r.denumenator;
		}

		return os;
	}

	bool isInteger() const {
		return denumenator == 1;
	}

	operator int() const {
		return numenator / denumenator;
	}

	friend Rational abs(const Rational& r) {
		return Rational(std::abs(r.numenator), std::abs(r.denumenator));
	}
};

