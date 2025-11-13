#include "BigIntNumberTheory.h"
#define ll long long

Trair<BigInt> Bezout;

namespace bigIntNumberTheory {
    static BigInt R, R2, negR, Rpi, m, mpi, d, z;
    static ll kR, r;
    static const ll p[] = {0,
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
    
    BigInt REDC(BigInt t) {
        BigInt ret = (t + ((t * mpi).getRightSub(kR) * m)) >> kR;
        if (ret >= m) ret = ret - m;
        return ret;
    }
    
    BigInt getInv(BigInt a, BigInt n) {
        std::cout << exGcd(a, n)._b << std::endl;
        return (exGcd(a, n)._b % n + n) % n;
    }
    
    void init() {
        R = 1;
        kR = 0;
        while (R < m) {
            ++kR;
            R <<= 1;
        }
        R2 = R * R % m;
        mpi = (exGcd(R - m, R)._b + R) % R;
        Rpi = (exGcd(m, R)._c + m) % m;
        R = REDC(R2);
        negR = (REDC((m - R) * R) + m) % m;
    }
    
    BigInt quickPowerMontgomery(BigInt a, BigInt b) {
        BigInt ret = R;
        a = REDC(a * R2);
        while (b != (BigInt)0) {
            if (b.isOdd()) ret = REDC(ret * a);
            a = REDC(a * a);
            b.divBy2();
        }
        return ret;
    }
    
    BigInt quickPowerMod(BigInt a, BigInt b, BigInt mod) {
        BigInt ret = 1;
        while (b != (BigInt)0) {
            if (b.isOdd()) (ret *= a) %= mod;
            (a *= a) %= mod;
            b.divBy2();
        }
        return ret;
    }
    
    bool MillerRabin(BigInt a) {
        z = quickPowerMontgomery(a, d);
        if (z == R || z == negR) return 1;
        for (ll i = 1; i <= r; ++i) {
            if (z == negR) return 1;
            z = REDC(z * z);
        }
        return 0;
    }
    
    bool isPrime(BigInt n) {
        if (n == (BigInt)1) return 0;
        if (n == (BigInt)2 || n == (BigInt)5) return 1;
        if (!n.canPassMontgomery()) return 0;
        m = n;
        init();
        d = m - BigInt(1);
        r = 0;
        while (!d.isOdd()) {
            d.divBy2();
            ++r;
        }
        for (int i = 1; i <= 10; ++i) {
            if (m == (BigInt)p[i]) return 1;
            if (m % p[i] == 0) return 0;
            if (!MillerRabin(p[i])) return 0;
        }
        return 1;
    }
    
    BigInt randomPrime(ll k) {
        while (1) {
            while (1) {
                m.getRandom(k);
                if (m.canPassMontgomery()) break;
            }
            if (isPrime(m)) break;
        }
        return m;
    }
    
    BigInt PollardRho(BigInt n) {
        auto f = [](BigInt a, BigInt c) {
            return REDC(a * a) + c;
        };
        m = n;
        init();
        BigInt c, goal, step, d, val = R;
        ll k = m.log2(), tim = 1;
        c.getRandom(m.log2() + 2);
        c = REDC(c * R);
        if (c == (BigInt)0) c = 1;
        c = REDC(c * R2);
        BigInt s = 0, t = 0;
        for (goal = 1; tim <= k; goal.multiBy2(), s = t, val = 1, ++tim) {
            for (step = 1; step <= goal; step += 1) {
                t = f(t, c);
                if (t > n * (BigInt)10) t = REDC(REDC(t) * R2);
                val = REDC(val * abs(t - s));
                if (val == (BigInt)0) return m;
                if ((step % 127ll) == 0) {
                    d = gcd(REDC(val), m);
                    if (d > (BigInt)1) return d;
                }
            }
            d = gcd(REDC(val), m);
            if (d > (BigInt)1) return d;
        }
        return m;
    }
    
    std::vector<BigInt> PrimeFactorization(BigInt n) {
        std::vector<BigInt> ret;
        for (int i = 1; i <= 20; ++i) {
            while (n % p[i] == 0) {
                ret.push_back(p[i]);
                n /= p[i];
            }
            if (n == (BigInt)1) return ret;
        }
        auto insideSolve = [&ret](BigInt n, auto self) {
            if (isPrime(n)) {
                ret.push_back(n);
                return;
            } else {
                BigInt t;
                do {
                    t = PollardRho(n);
                } while (t == n);
                self(t, self);
                self(n / t, self);
            }
            return;
        };
        insideSolve(n, insideSolve);
        std::sort(ret.begin(), ret.end());
        return ret;
    }
    
    std::pair<bool, BigInt> havePrimitiveRootandGetPhi(BigInt n) {
        if (n == BigInt(2) || n == BigInt(4)) return {1, n.divBy2()};
        if (isPrime(n)) return {1, n - BigInt(1)};
        bool flag = 0;
        if (!n.isOdd()) {
            n.divBy2();
            flag = 1;
            if (!n.isOdd()) return {0, 0};
        }
        std::vector<BigInt> Fac = PrimeFactorization(n);
        if (std::unique(Fac.begin(), Fac.end()) - Fac.begin() > 1) return {0, 0};
        if (Fac.front() == (BigInt)2) return {0, 0};
        if (flag) Fac.push_back(2);
        std::sort(Fac.begin(), Fac.end());
        BigInt phi = 1, lastVal = 1;
        for (auto u : Fac) {
            if (u == lastVal) phi *= u;
            else phi *= u - (BigInt)1;
            lastVal = u;
        }
        return {1, phi};
    }
    
    BigInt getMinPrimitiveRoot(BigInt n) {
        if (n == (BigInt)2) return 1;
        if (n == (BigInt)4) return 3;
        auto [is, phi] = havePrimitiveRootandGetPhi(n);
        if (is == 0) return 0;
        std::vector<BigInt> Fac = PrimeFactorization(phi);
        std::sort(Fac.begin(), Fac.end());
        Fac.erase(std::unique(Fac.begin(), Fac.end()), Fac.end());
        bool flag;
        if (isPrime(n)) {
            for (BigInt g = 2;; g += 1) {
                if (gcd(g, n) > (BigInt)1) continue;
                flag = 1;
                for (auto factor : Fac) {
                    if (quickPowerMontgomery(g, phi / factor) == R) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) return g;
            }
        }
        if (n.canPassMontgomery()) {
            m = n;
            init();
            for (BigInt g = 2, gpi, pi;; g += 1) {
                if (gcd(g, n) > (BigInt)1) continue;
                flag = 1;
                pi = gpi = REDC(g * R2);
                for (BigInt i = 2; i < phi; i += 1) {
                    pi = REDC(gpi * pi);
                    if (pi == R) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) return g;
            }
        }
		else {
            for (BigInt g = 2, gpi, pi;; g += 1) {
                if (gcd(g, n) > (BigInt)1) continue;
                flag = 1;
                pi = gpi = g;
                for (BigInt i = 2; i < phi; i += 1) {
                    (pi *= gpi) %= n;
                    if (pi == (BigInt)1) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) return g;
            }
        }
    }
}

#undef ll