#ifndef _XIE2YUE_MODLONGLONG_H
#define _XIE2YUE_MODLONGLONG_H

#include <iostream>
#include "BigIntNumberTheory.h"

#define ll long long
#define mll ModuleLongLong

extern BigInt Module;

class ModuleLongLong {
private:
    BigInt data_;
    
public:
    void moduleCheck() {
        data_ %= Module;
        data_ += Module;
        data_ %= Module;
    }
    
    friend BigInt::BigInt(mll data);
    
    mll() {}
    
    mll(ll data) : data_(data) { moduleCheck(); }
    
    mll(int data) : data_(data) { moduleCheck(); }
    
    mll(BigInt data) : data_(data) { moduleCheck(); }
    
    mll operator -() const {
        return mll(Module - data_);
    }
    
    mll operator + (const mll t) const {
        return mll(data_ + t.data_);
    }
    
    mll operator - (const mll t) const {
        return mll(data_ - t.data_);
    }
    
    mll operator * (const mll t) const {
        return mll(data_ * t.data_);
    }
    
    mll inv() const {
        return mll(exGcd(data_, Module)._b);
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
        return data_ == t.data_;
    }
    
    bool operator != (const mll t) const {
        return data_ != t.data_;
    }
    
    bool operator < (const mll t) const {
        return 0;
    }
    
    bool operator > (const mll t) const {
        return 1;
    }
    
    friend std::ostream& operator << (std::ostream &MLLout, mll t) {
        return MLLout << t.data_;
    }
};

#undef mll
#undef ll
#endif