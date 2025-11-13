#include "Fraction.h"

std::string FractionBuf;

Fraction abs(Fraction a) {
    return a < 0 ? -a : a;
}