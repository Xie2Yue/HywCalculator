#include "PolynomialFactorization.h"
#include <sstream>

#define mll ModuleLongLong
#define ll long long
#define Q Fraction
#define Z BigInt

namespace PolynomialFactorization {
    
    Polynomial<Z> makeSquareFree(Polynomial<Q> tar) {
        if (tar.deg() == 0) return 1;
        Polynomial<Q> tarpi, targcd, ret;
        tarpi = tar.differentiation();
        targcd = gcd(tar, tarpi).makePrimitive();
        tar /= targcd;
        return tar.as<Z>().makePrimitive();
    }
    
    static const ll P[] = {0,
        2,   3,   5,   7,   11,  13,  17,  19,  23,  29,
        31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
        73,  79,  83,  89,  97,  101, 103, 107, 109, 113,
        127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
        179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
        233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
        283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
        353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
        419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
        467, 479, 487, 491, 499, 503, 509, 521, 523, 541
    };
    
    std::vector<Polynomial<Z> > AnswerFactors;
    std::vector<Polynomial<mll> > HenselFactors;
    
    bool checkPrimeForHensel(Polynomial<Z> f, Z p) {
        Module = p;
        if (f.first() % Module == (BigInt)0) return 0;
        auto tar = f.as<mll>();
        auto tarpi = tar.differentiation();
        if (tarpi.deg() == 0) return 1;
        else if (tarpi.deg() == -1) return 0;
        auto targcd = gcd(tar, tarpi);
        return targcd.deg() == 0;
    }
    
    ll findPrimeForHensel(Polynomial<Z> f, BigInt lastModule) {
        for (int i = 1; i <= 100; ++i) {
            if (P[i] <= lastModule) continue;
            if (checkPrimeForHensel(f, P[i])) return P[i];
        }
        return -1;
    }
    
    std::vector<Polynomial<mll> > firstFactorization(Polynomial<mll> f, Z p) {
        using std::cout;
        using std::endl;
        
        Polynomial<mll> fac = Polynomial<Z>((std::string)"X").as<mll>();
        std::vector<Polynomial<mll> > ret;
        for (int i = 0; i < p; ++i, fac += 1) {
            if (f.deg() == 1) break;
            if (f % fac == 0) {
                ret.push_back(fac);
                f /= fac;
            }
        }
        ret.push_back(f);
        return ret;
    }
    
    #define gn g.back()
    void LiftingStep(Polynomial<Z> f, std::vector<Polynomial<mll> > g, Z p, Z p2) {
        Module = p2;
        HenselFactors.clear();
        Polynomial<mll> Delta, G(1), ex;
        for (auto gi : g) G *= gi;
        while (g.size() >= 2) {
            Module = p2;
            
            G = Polynomial<mll>(1);
            
            for (auto gi : g) G *= gi;
            
            Delta = f.as<mll>() - G;
            
            G /= gn;
            
            ex = (Delta.as<Z>() / p).as<mll>();
            
            Module = p;
            auto [tx, ux, vx] = exGcd(G, gn);
            Module = p;
            
            Module = p2;
            
            auto ax = ux * tx / p;
            auto bx = vx * tx / p;
            
            Module = p;
            
            ax *= ex;
            bx *= ex;
            
            bx %= G;
            ax %= gn;
            
            Module = p2;
            
            G += (bx * mll(p));
            gn += (ax * mll(p));
            
            G.makePrimitive();
            gn.makePrimitive();
            
            HenselFactors.push_back(gn);
            
            if (G.deg() == 1) {
                HenselFactors.push_back(G);
                return;
            }
            
            f = G.as<Z>();
            g.pop_back();
        }
    }
    #undef gn
    
    void HelselLifting(Polynomial<Q> finQ) {
        Module = 1;
        AnswerFactors.clear();
        
        if (finQ.deg() <= 1) {
            AnswerFactors.push_back(finQ.as<Z>());
            return;
        }
        
        auto f = makeSquareFree(finQ);
        
        if (f.deg() <= 1) {
            AnswerFactors.push_back(f);
            return;
        }
        
        int cnt = 0, testcnt1 = 0;
        BigInt prim = 1;
        while (1) {
            ++testcnt1;
            while (1) {
                cnt = 0;
                findPrimeForHensel(f, prim);
                HenselFactors = firstFactorization(f.as<mll>(), Module);
                for (auto it = HenselFactors.begin(); it != HenselFactors.end();) {
                    if (f % ((*it).as<Z>()) == 0) {
                        ++cnt;
                        AnswerFactors.push_back(*it);
                        f /= ((*it).as<Z>());
                        it = HenselFactors.erase(it);
                    } else if (f % ((*it).as<Z>() - Module) == 0) {
                        ++cnt;
                        AnswerFactors.push_back((*it).as<Z>() - Module);
                        f /= ((*it).as<Z>() - Module);
                        it = HenselFactors.erase(it);
                    } else {
                    	++it;
					}
                }
                if (f.deg() <= 0) return;
                if (f.deg() == 1) {
                    AnswerFactors.push_back(f);
                    return;
                }
                if (cnt == 0) break;
            }
            
            bool flag;
            prim = Module;
            for (int k = 2; k <= 10; ++k) {
                LiftingStep(f, HenselFactors, Module, Module * prim);
                flag = 0;
                for (auto it = HenselFactors.begin(); it != HenselFactors.end();) {
                    if (f % ((*it).as<Z>()) == 0) {
                        flag = 1;
                        AnswerFactors.push_back((*it).as<Z>());
                        f /= ((*it).as<Z>());
                        it = HenselFactors.erase(it);
                    } else if (f % ((*it).as<Z>() - Module) == 0) {
                        flag = 1;
                        AnswerFactors.push_back((*it).as<Z>() - Module);
                        f /= ((*it).as<Z>() - Module);
                        it = HenselFactors.erase(it);
                    } else ++it;
                }
                if (f.deg() <= 0) return;
                if (f.deg() == 1) {
                    AnswerFactors.push_back(f);
                    return;
                }
                if (flag) {
                    Module /= prim;
                    for (auto &fac : HenselFactors) {
                        fac = fac.as<mll>();
                    }
                }
            }
            if (f == 1) break;
            if (testcnt1 > 10) break;
        }
    }
    
    std::string Factorization(Polynomial<Q> f) {
        auto finZ = f.as<Z>();
        HelselLifting(f);
        int cnt;
        bool flag = 1;
        std::sort(AnswerFactors.begin(), AnswerFactors.end());
        std::stringstream ret;
        for (auto fac : AnswerFactors) {
            cnt = 0;
            while (f % fac == 0) {
                ++cnt;
                f /= fac;
            }
            if (cnt == 1 && AnswerFactors.size() == 1 && f == 1) {
                ret << fac;
                return ret.str();
            } else {
                flag = 0;
                if (fac == MonomialX) {
                    ret << "x";
                } else {
                    ret << "(" << fac << ")";
                }
                if (cnt > 1) {
                    ret << "^" << cnt;
                }
            }
            if (fac != AnswerFactors.back()) {
                ret << "*";
            }
        }
        if (f != 1) {
            if (flag) {
                ret << f;
            } else ret << "*" << "(" << f << ")";
        }
        return ret.str();
    }
}

#undef mll
#undef ll
#undef Z
#undef Q