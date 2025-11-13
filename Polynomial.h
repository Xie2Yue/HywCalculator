#ifndef _XIE2YUE_POLYNOMIAL_H
#define _XIE2YUE_POLYNOMIAL_H

#include <vector>
#include <iostream>
#include <string>
#include <type_traits>
#include "Fraction.h"
#include "BigIntNumberTheory.h"
#include "ModuleLongLong.h"

#define ll long long
#define mll ModuleLongLong

extern std::string PolynomialBuf;

template<typename _T = Fraction>
class Polynomial {
private:
    std::vector<_T> _data;
    ll _deg;
    
public:
    template<typename U> friend class Polynomial;
    
    Polynomial() : _deg(0), _data() {}
    
    Polynomial(std::string s) {
        int pos = 0, lpos = 0;
        ll mx = 1;
        std::string now;
        std::vector<std::string> vecs;
        for (;;) {
            pos = s.find_first_of("+-", lpos + 1);
            if (pos == std::string::npos) {
                vecs.push_back(now = s.substr(lpos));
                if (int mpos = now.find('^'); mpos != std::string::npos) {
                    mx = std::max(mx, (ll)BigInt(now.substr(mpos + 1)));
                }
                break;
            }
            vecs.push_back(now = s.substr(lpos, pos - lpos));
            if (int mpos = now.find('^'); mpos != std::string::npos) {
                mx = std::max(mx, (ll)BigInt(now.substr(mpos + 1)));
            }
            lpos = pos;
        }
        _data.resize(_deg = mx + 1);
        for (auto u : vecs) {
            if (int mpos = u.find('^'); mpos != std::string::npos) {
                std::string tmp = u.substr(0, mpos - 1);
                if ((mpos == 2 && u[0] == '+') || mpos == 1) {
                    _data[(ll)BigInt(u.substr(mpos + 1))] = 1;
                } else if (mpos == 2 && u[0] == '-') {
                	_data[(ll)BigInt(u.substr(mpos + 1))] = -1;
				} else {
                	_data[(ll)BigInt(u.substr(mpos + 1))] = _T(tmp);
				}
            } else if (int Xpos = u.find_first_of("Xx"); Xpos != std::string::npos) {
                if ((Xpos == 1 && u[0] == '+') || Xpos == 0) {
                	_data[1] = 1;
				} else if (Xpos == 1 && u[0] == '-') {
                	_data[1] = -1;
				} else {
                	_data[1] = _T(u.substr(0, Xpos));
				}
            } else {
                _data[0] = _T(u);
            }
        }
        while (_data.back() == (_T)0 && _deg > 1) {
            _data.pop_back();
            --_deg;
        }
    }
    
    template<typename _U>
    Polynomial(Polynomial<_U> t) {
        _deg = t._deg;
        for (auto digit : t._data) _data.push_back(_T(digit));
    }
    
    template<typename _U>
    Polynomial(_U digit,
        typename std::enable_if<0
            || std::is_same<_U, int>::value
            || std::is_same<_U, ll>::value
            || std::is_same<_U, BigInt>::value
            || std::is_same<_U, Fraction>::value
            || std::is_same<_U, ModuleLongLong>::value
        >::type* = nullptr) {
        if (digit != (_U)0) {
            _deg = 1;
            _data.resize(1);
            _data[0] = _T(digit);
        } else {
        	_deg = 0;
		}
    }
    
    template<typename _U>
    Polynomial<_U> as() {
        Polynomial<_U> ret;
        ret._deg = _deg;
        if constexpr (std::is_same_v<_U, mll> && std::is_same_v<_T, mll>) {
            for (auto digit : _data) {
                digit.moduleCheck();
                ret._data.push_back(digit);
            }
        } else {
            for (auto digit : _data) ret._data.push_back(_U(digit));
        }
        ret.clearPrev0();
        return ret;
    }
    
    void clearPrev0() {
        while (_data.size() && _data.back() == (_T)0) {
            _data.pop_back();
            --_deg;
        }
    }
    
    friend std::ostream& operator << (std::ostream &Pout, Polynomial t) {
        if (t._deg == 0) {
            return Pout << 0;
        }
        if (t._deg == 1) {
            return Pout << t._data[0];
        } else if (t._deg == 2) {
            if (t._data[1] == (_T)0) return Pout << t._data[0];
            else if (t._data[1] == (_T)1);
            else if (t._data[1] > (_T)0) Pout << t._data[1];
            else if (t._data[1] == (_T)-1) Pout << "-";
            else Pout << t._data[1];
            
            Pout << "x";
            
            if (t._data[0] == (_T)0) return Pout;
            else if (t._data[0] < (_T)0) return Pout << t._data[0];
            else return Pout << "+" << t._data[0];
        } else {
            if (t._data[t._deg - 1] == (_T)1);
            else if (t._data[t._deg - 1] > (_T)0) Pout << t._data[t._deg - 1];
            else if (t._data[t._deg - 1] == (_T)-1) Pout << "-";
            else Pout << t._data[t._deg - 1];
            
            Pout << "x^" << t._deg - 1;
            for (int i = t._deg - 2; i >= 0; --i) {
                if (t._data[i] == (_T)0) continue;
                else if (i != 0 && t._data[i] == (_T)1) Pout << "+";
                else if (t._data[i] > (_T)0) Pout << "+" << t._data[i];
                else if (i != 0 && t._data[i] == (_T)-1) Pout << "-";
                else Pout << t._data[i];
                
                if (i == 0) continue;
                else if (i == 1) Pout << "x";
                else Pout << "x^" << i;
            }
        }
        return Pout;
    }
    
    friend std::istream& operator >> (std::istream &Pin, Polynomial &t) {
        Pin >> PolynomialBuf;
        t = Polynomial(PolynomialBuf);
        return Pin;
    }
    
    bool operator < (const Polynomial t) const {
        if (_deg == 0) {
            return (_T)0 < t._data[0];
        }
        if (t._deg == 0) {
            return _data[0] < (_T)0;
        }
        
        if (_data[0] > (_T)0 && t._data[0] < (_T)0) {
        	return 0;
		}
        else if (_data[0] < (_T)0 && t._data[0] > (_T)0) {
        	return 1;
		} else if (_data[0] > (_T)0 && t._data[0] > (_T)0) {
            if (_deg ^ t._deg) return _deg < t._deg;
            for (int i = 0; i < _deg; ++i) {
                if (_data[i] != t._data[i]) return _data[i] < t._data[i];
            }
            return 0;
        } else if (_data[0] < (_T)0 && t._data[0] < (_T)0) {
            if (_deg ^ t._deg) return _deg > t._deg;
            for (int i = 0; i < _deg; ++i) {
                if (_data[i] != t._data[i]) return _data[i] > t._data[i];
            }
            return 0;
        }
        return 0;
    }
    
    bool operator == (const Polynomial t) const {
        if (_deg ^ t._deg) return 0;
        for (int i = 0; i < _deg; ++i) {
            if (_data[i] != t._data[i]) return 0;
        }
        return 1;
    }
    
    bool operator != (const Polynomial t) const {
        if (_deg ^ t._deg) return 1;
        for (int i = 0; i < _deg; ++i) {
            if (_data[i] != t._data[i]) return 1;
        }
        return 0;
    }
    
    Polynomial operator -() const {
        Polynomial ret = *this;
        for (auto &digit : ret._data) {
            digit = -digit;
        }
        return ret;
    }
    
    Polynomial operator + (const Polynomial t) const {
        Polynomial ret;
        ret._deg = std::max(_deg, t._deg);
        ret._data.resize(ret._deg);
        for (int i = 0; i < ret._deg; ++i) {
            if (i < _deg && i < t._deg) {
                ret._data[i] = _data[i] + t._data[i];
            } else if (i < _deg) {
                ret._data[i] = _data[i];
            } else if (i < t._deg) {
                ret._data[i] = t._data[i];
            }
        }
        ret.clearPrev0();
        return ret;
    }
    
    Polynomial operator - (const Polynomial t) const {
        return *this + (-t);
    }
    
    friend Polynomial operator * (Polynomial a, _T k) {
        Polynomial ret = a;
        for (auto &digit : ret._data) {
            digit = k * digit;
        }
        return ret;
    }
    
    Polynomial operator * (const Polynomial t) const {
        Polynomial ret;
        ret._data.resize(ret._deg = (_deg + t._deg));
        for (int i = 0; i < _deg; ++i) {
            for (int j = 0; j < t._deg; ++j) {
                ret._data[i + j] = _data[i] * t._data[j] + ret._data[i + j];
            }
        }
        ret.clearPrev0();
        return ret;
    }
    
    Polynomial operator << (const ll k) const {
        if (k <= 0) return *this;
        Polynomial ret;
        for (int i = 0; i < k; ++i) ret._data.push_back(0);
        for (auto digit : _data) ret._data.push_back(digit);
        ret._deg = ret._data.size();
        return ret;
    }
    
    Polynomial operator >> (const ll k) const {
        if (k <= 0) return *this;
        if (k > _deg) return 0;
        Polynomial ret = *this;
        ret._data.erase(ret._data.begin(), ret._data.begin() + k);
        ret._deg = ret._data.size();
        ret.clearPrev0();
        return ret;
    }
    
    Polynomial operator / (const Polynomial t) const {
        if (_deg < t._deg) return 0;
        Polynomial a = *this, b = t, ret;
        ll k, adeg = a._deg;
        _T digit;
        b <<= (k = (a._deg - b._deg));
        ret._data.resize(ret._deg = k + 1);
        for (int i = adeg - 1; i >= adeg - 1 - k; --i) {
            if (i < a._deg) {
                digit = a._data[i] / b._data.back();
                a -= b * digit;
                ret._data[i - adeg + k + 1] = digit;
            }
            b = b >> 1;
        }
        ret.clearPrev0();
        return ret;
    }
    
    Polynomial operator % (const Polynomial t) const {
        if (_deg < t._deg) return *this;
        Polynomial a = *this, b = t;
        ll k, adeg = a._deg;
        _T digit;
        b <<= (k = (a._deg - b._deg));
        for (int i = adeg - 1; i >= adeg - 1 - k; --i) {
            if (i < a._deg) {
                digit = a._data[i] / b._data.back();
                a -= b * digit;
            }
            b = b >> 1;
        }
        return a;
    }
    
    Polynomial& operator += (const Polynomial t) {
        *this = *this + t;
        return *this;
    }
    
    Polynomial& operator -= (const Polynomial t) {
        *this = *this - t;
        return *this;
    }
    
    friend Polynomial& operator *= (Polynomial &a, _T k) {
        a = a * k;
        return a;
    }
    
    Polynomial& operator *= (const Polynomial t) {
        *this = *this * t;
        return *this;
    }
    
    Polynomial& operator <<= (const ll k) {
        *this = *this << k;
        return *this;
    }
    
    Polynomial& operator >>= (const ll k) {
        *this = *this >> k;
        return *this;
    }
    
    Polynomial& operator /= (const Polynomial t) {
        *this = *this / t;
        return *this;
    }
    
    Polynomial& operator %= (const Polynomial t) {
        if (_deg < t._deg) return *this;
        Polynomial b = t;
        ll k, adeg = _deg;
        _T digit;
        b <<= (k = (_deg - b._deg));
        for (int i = adeg - 1; i >= adeg - 1 - k; --i) {
            if (i < _deg) {
                digit = _data[i] / b._data.back();
                *this -= b * digit;
            }
            b = b >> 1;
        }
        return *this;
    }
    
    Polynomial& getDifferentiation() {
        for (int i = 0; i < _data.size(); ++i) {
            _data[i] *= i;
        }
        _data.erase(_data.begin());
        --_deg;
        clearPrev0();
        return *this;
    }
    
    Polynomial differentiation() {
        Polynomial ret = *this;
        for (int i = 0; i < ret._data.size(); ++i) {
            ret._data[i] *= i;
        }
        ret._data.erase(ret._data.begin());
        --ret._deg;
        ret.clearPrev0();
        return ret;
    }
    
    Polynomial& makePrimitive() {
        if constexpr (std::is_same_v<_T, Fraction>) {
            Fraction constant = _data.back();
            for (auto &digit : _data) {
                digit /= constant;
            }
        } else if constexpr (std::is_same_v<_T, BigInt>) {
            BigInt constant = _data[0];
            for (auto digit : _data) {
                constant = gcd(digit, constant);
            }
            for (auto &digit : _data) {
                digit /= constant;
            }
        } else if constexpr (std::is_same_v<_T, mll>) {
            mll constant = _data.back().inv();
            for (auto &digit : _data) {
                digit *= constant;
            }
        }
        clearPrev0();
        return *this;
    }
    
    ll deg() { return _deg - 1; }
    
    _T first() {
        return _data.back();
    }
};

extern Polynomial<BigInt> MonomialX;

#undef mll
#undef ll
#endif