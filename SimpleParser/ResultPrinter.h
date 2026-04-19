#pragma once
#include <iostream>
#include "Emitter.h"

class ResultPrinter
{
private:
	MixedFraction result;

	void printPolynom(const Polynom& polynom) {
		for (auto it = polynom.crbegin(); it != polynom.crend(); ++it) {
			if (it != polynom.crbegin()) {
				if (it->second > 0) {
					std::cout << " + ";
				}
				else {
					std::cout << " - ";
				}
			}
			else {
				if (it->second < 0) {
					std::cout << "-";
				}
			}
			if (abs(it->second) != 1 || it->first == 0) std::cout << abs(it->second);
			if (it->first != 0) {
				std::cout << "X";
				if (it->first != 1) {
					std::cout << "^" << it->first;
				}
			}
		}
	}

public:
	ResultPrinter(MixedFraction result) : result(std::move(result)) {}

	void printResult() {
		if (result.isZero()) {
			printPolynom(result.getWholePart());
		}
		else {
			bool isFraction = result.isFraction();
			if (!result.isZeroWhole()) {
				printPolynom(result.getWholePart());
				if (isFraction) {
					std::cout << " + ";
				}
			}
			if (isFraction) {
				if (result.getFractionPart().getNumerator().size() > 1) {
					std::cout << "(";
					printPolynom(result.getFractionPart().getNumerator());
					std::cout << ")";
				}
				else {
					printPolynom(result.getFractionPart().getNumerator());
				}
				std::cout << " / ";
				if (result.getFractionPart().getDenumenator().size() != 1) {
					std::cout << "(";
					printPolynom(result.getFractionPart().getDenumenator());
					std::cout << ")";
				}
				else {
					printPolynom(result.getFractionPart().getDenumenator());
				}
			}
		}
	}
};

