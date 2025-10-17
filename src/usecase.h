#include "Fraction.h"
#include <iostream>
#include <expected>
#include <tuple>
#include <format>
using std::cout, std::cin;
using std::format;
using std::expected;
using std::tuple, std::make_tuple;

expected<tuple<Fraction, Fraction>, string> executeGetInputUseCase();

Fraction executePrintAddFractionsUseCase(const Fraction& a, const Fraction& b);

Fraction executeSimplifyFractionUseCase(const Fraction& f);