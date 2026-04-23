#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include "Lexer.h"
#include <map>
#include <functional>
#include "Fraction.h"
#include "MixedFraction.h"
#include "parametres.h"

using namespace parameters;

class Emitter
{
public:
	Emitter(std::queue<Lexem> queueLexem) : queueLexem(std::move(queueLexem)) {}

	void trasmittion() {
		
		Lexem curLexem;
		try
		{
			while (!queueLexem.empty()) {
				curLexem = queueLexem.front();
				queueLexem.pop();

				switch (curLexem.token)
				{
				case X:
					polynomials.push({ 1,1 });
					break;
				case NUM:
				{
					long long number = std::stoll(curLexem.value);
					polynomials.push({ 0, number });
					break;
				}
				case PLUS:
					addition();
					break;
				case MINUS:
					substraction();
					break;
				case MUL:
					multiplication();
					break;
				case DIV:
					division();
					break;
				case POWER:
					power();
					break;
				default:
					break;
				}
			}

			if (!polynomials.empty()) {
				polynomials.top().normilize();
			}
		}
		catch (const std::overflow_error& e) {
			std::cerr << "\nOverflow Error: " << e.what() << "\n";
			exit(1);
		}
		catch (const std::exception& e)
		{
			std::cerr << "\nERROR: " << e.what() << "\n";
			exit(1);
		}
		catch (...) {
			std::cerr << "\nUndefind Error";
			exit(1);
		}
	}

	MixedFraction getResult() const {
		if (!polynomials.empty()) {
			return polynomials.top();
		}
		else {
			return MixedFraction(0, 0);
		}
		
	}

private:
	std::queue<Lexem> queueLexem;
	std::stack<MixedFraction> polynomials;

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
			long long power = firstFraction.getFreeMember();
			if (power > 0) {
				MixedFraction multi = polynomials.top();
				for (long long i = 1; i < power; ++i) {
					polynomials.top().multiplication(multi);
				}
			}
			else if (power < 0) {
				MixedFraction divider = polynomials.top();
				polynomials.pop();
				polynomials.push({ 0,1 });
				for (long long i = 0; i > power; --i) {
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
		polynomials.push({0, num});
	}

	void pushZero() {
		polynomials.push({0, 0});
	}
};

