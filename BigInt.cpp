#include "BigInt.h"
#include "Fraction.h"
#include "ModuleLongLong.h"
#define mll ModuleLongLong

std::string BigIntBuf;

BigInt abs(BigInt a) {
    return (a < BigInt(0)) ? -a : a;
}

BigInt::BigInt(Fraction t) {
    *this = t._numer;
}

BigInt::BigInt(mll data) {
    *this = data._data;
}