#ifndef _XIE2YUE_BIGINT_NUMBERTHEORY_H
#define _XIE2YUE_BIGINT_NUMBERTHEORY_H

#include "BigInt.h"

#define ll long long

template<typename _T>
class Trair {
public:
    _T _a, _b, _c;
    Trair() {}
    Trair(_T a, _T b, _T c) : _a(a), _b(b), _c(c) {}
};

template<typename _T>
Trair<_T> exGcd(_T a, _T b) {
    bool flaga = 0, flagb = 0;
    if (a < (_T)0) {
        a = -a;
        flaga = 1;
    }
    if (b < (_T)0) {
        b = -b;
        flagb = 1;
    }
    _T tmp, q, r, x0 = 1, y0 = 0, x1 = 0, y1 = 1;
    while (b != (_T)0) {
        q = a / b;
        r = a % b;

        tmp = x0;
        x0 = x1;
        x1 = tmp - q * x1;

        tmp = y0;
        y0 = y1;
        y1 = tmp - q * y1;

        a = b;
        b = r;
    }
    return Trair<_T>(a, flaga ? -x0 : x0, flagb ? -y0 : y0);
}

template<typename _T>
_T gcd(_T a, _T b) {
    _T r;
    if (b < (_T)0) b = -b;
    if (a < (_T)0) a = -a;
    while (b != (_T)0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

namespace bigIntNumberTheory {
    BigInt REDC(BigInt t);
    
    BigInt getInv(BigInt a, BigInt n);
    
    void init();
    
    BigInt quickPowerMontgomery(BigInt a, BigInt b);
    
    BigInt quickPowerMod(BigInt a, BigInt b, BigInt mod);
    
    bool MillerRabin(BigInt a);
    
    bool isPrime(BigInt n);
    
    BigInt randomPrime(ll k);
    
    BigInt PollardRho(BigInt n);
    
    std::vector<BigInt> PrimeFactorization(BigInt n);
    
    std::pair<bool, BigInt> havePrimitiveRootandGetPhi(BigInt n);
    
    BigInt getMinPrimitiveRoot(BigInt n);
}

#undef ll
#endif