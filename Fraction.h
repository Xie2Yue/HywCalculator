#ifndef _XIE2YUE_FRACTION_H
#define _XIE2YUE_FRACTION_H

#include <iostream>
#include <cstring>
#include "BigInt.h"
#include "BigIntNumberTheory.h"

extern std::string FractionBuf;

class Fraction {
private:
    BigInt _numer, _denomin;
    
public:
    friend BigInt::BigInt(Fraction t);
    
    Fraction() : _denomin(1) {}
    
    template<typename _U>
    Fraction(_U p, _U q) : _numer(p), _denomin(q) { reduce(); }
    
    template<typename _U>
    Fraction(_U m) : _numer(m), _denomin(1) {}
    
    Fraction(std::string data) {
        int slashPos = data.find('/');
        if (slashPos == std::string::npos) {
            _numer = BigInt(data);
            _denomin = 1;
        } else {
            _numer = BigInt(data.substr(0, slashPos));
            _denomin = BigInt(data.substr(slashPos + 1));
        }
        reduce();
    }
    
    void reduce() {
        if (_numer == BigInt(0)) {
            _denomin = 1;
            return;
        }
        if (_denomin < BigInt(0)) {
            _denomin = -_denomin;
            _numer = -_numer;
        }
        if (_denomin == BigInt(1)) return;
        BigInt d = gcd(_numer, _denomin);
        _denomin /= d;
        _numer /= d;
    }
    
    std::pair<BigInt, Fraction> getMixedFraction() {
        BigInt ret(_numer / _denomin);
        return {ret, *this - ret};
    }
    
    friend std::istream& operator >> (std::istream &Fin, Fraction &t) {
        Fin >> FractionBuf;
        t = Fraction(FractionBuf);
        return Fin;
    }
    
    std::string toString() {
        if (_denomin == BigInt(1)) return _numer.toString();
        return _numer.toString() + "/" + _denomin.toString();
    }
    friend std::ostream& operator << (std::ostream &out, Fraction t) {
    	return out << t.toString();
    }
    
    bool operator < (const Fraction t) const {
        return _numer * t._denomin < t._numer * _denomin;
    }
    
    bool operator <= (const Fraction t) const {
        return _numer * t._denomin <= t._numer * _denomin;
    }
    
    bool operator > (const Fraction t) const {
        return _numer * t._denomin > t._numer * _denomin;
    }
    
    bool operator >= (const Fraction t) const {
        return _numer * t._denomin >= t._numer * _denomin;
    }
    
    bool operator == (const Fraction t) const {
        return _numer * t._denomin == t._numer * _denomin;
    }
    
    bool operator != (const Fraction t) const {
        return _numer * t._denomin != t._numer * _denomin;
    }
    
    Fraction operator -() {
        return Fraction(-_numer, _denomin);
    }
    
    Fraction operator + (const Fraction t) const {
        Fraction ret(_numer * t._denomin + t._numer * _denomin, t._denomin * _denomin);
        ret.reduce();
        return ret;
    }
    
    Fraction operator - (const Fraction t) const {
        Fraction ret(_numer * t._denomin - t._numer * _denomin, t._denomin * _denomin);
        ret.reduce();
        return ret;
    }
    
    Fraction operator * (const Fraction t) const {
        Fraction ret(_numer * t._numer, _denomin * t._denomin);
        ret.reduce();
        return ret;
    }
    
    Fraction operator / (const Fraction t) const {
        Fraction ret(_numer * t._denomin, _denomin * t._numer);
        ret.reduce();
        return ret;
    }
    
    Fraction& operator += (const Fraction t) {
        *this = *this + t;
        return *this;
    }
    
    Fraction& operator -= (const Fraction t) {
        *this = *this - t;
        return *this;
    }
    
    Fraction& operator *= (const Fraction t) {
        *this = *this * t;
        return *this;
    }
    
    Fraction& operator /= (const Fraction t) {
        *this = *this / t;
        return (*this);
    }
    
};

Fraction abs(Fraction a);

#endif