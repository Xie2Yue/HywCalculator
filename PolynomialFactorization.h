#ifndef _XIE2YUE_POLYNOMIALFRACTORIZATION_H
#define _XIE2YUE_POLYNOMIALFRACTORIZATION_H

#include "Polynomial.h"
#include "ModuleLongLong.h"

#define mll ModuleLongLong
#define ll long long
#define Z BigInt
#define Q Fraction

namespace PolynomialFactorization {
    
    extern std::vector<Polynomial<BigInt> > AnswerFactors;
    extern std::vector<Polynomial<mll> > HenselFactors;
    
    Polynomial<Z> makeSquareFree(Polynomial<Q> tar);
    
    bool checkPrimeForHensel(Polynomial<Z> f, BigInt p);

    ll findPrimeForHensel(Polynomial<Z> f, BigInt lastModule);
    
    std::vector<Polynomial<mll> > firstFactorization(Polynomial<mll> f, BigInt p);
    
    void LiftingStep(Polynomial<Z> f, std::vector<Polynomial<mll> > g, Z pk, Z pkp1);
    
    void HelselLifting(Polynomial<Q> finQ);
    
    std::string Factorization(Polynomial<Q> f);
}

#undef mll
#undef ll
#undef Z
#undef Q
#endif