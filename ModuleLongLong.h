#ifndef _XIE2YUE_MODLONGLONG_H
#define _XIE2YUE_MODLONGLONG_H

#include <iostream>
#include "BigIntNumberTheory.h"

#define ll long long
#define mll ModuleLongLong

extern BigInt Module;

class ModuleLongLong {
private:
    BigInt _data;
    
public:
    void moduleCheck() {
        _data %= Module;
        _data += Module;
        _data %= Module;
    }
    
    friend BigInt::BigInt(mll data);
    
    mll() {}
    
    mll(ll data) : _data(data) { moduleCheck(); }
    
    mll(int data) : _data(data) { moduleCheck(); }
    
    mll(BigInt data) : _data(data) { moduleCheck(); }
    
    mll operator -() const {
        return mll(Module - _data);
    }
    
    mll operator + (const mll t) const {
        return mll(_data + t._data);
    }
    
    mll operator - (const mll t) const {
        return mll(_data - t._data);
    }
    
    mll operator * (const mll t) const {
        return mll(_data * t._data);
    }
    
    mll inv() const {
        return mll(exGcd(_data, Module)._b);
    }
    
    mll operator / (const mll t) const {
        return *this * t.inv();
    }
    
    mll& operator *= (const mll t) {
        *this = *this * t;
        return *this;
    }
    
    mll& operator /= (const mll t) {
        *this = *this / t;
        return *this;
    }
    
    mll& operator += (const mll t) {
        *this = *this + t;
        return *this;
    }
    
    bool operator == (const mll t) const {
        return _data == t._data;
    }
    
    bool operator != (const mll t) const {
        return _data != t._data;
    }
    
    bool operator < (const mll t) const {
        return 0;
    }
    
    bool operator > (const mll t) const {
        return 1;
    }
    
    friend std::ostream& operator << (std::ostream &MLLout, mll t) {
        return MLLout << t._data;
    }
};

#undef mll
#undef ll
#endif