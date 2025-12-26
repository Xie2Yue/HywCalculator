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

/*

这位更是石中之石

*/


extern std::string PolynomialBuf;

template<typename _T = Fraction>
class Polynomial {
private:
	// 本来想搞树状存储的，但是无奈能力有限
    std::vector<_T> data_;
    ll _deg;
    
public:
    template<typename U> friend class Polynomial;
    
    
    Polynomial() : _deg(0), data_() {}
    
    // 字符串处理多项式
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
        data_.resize(_deg = mx + 1);
        for (auto u : vecs) {
            if (int mpos = u.find('^'); mpos != std::string::npos) {
                std::string tmp = u.substr(0, mpos - 1);
                if ((mpos == 2 && u[0] == '+') || mpos == 1) {
                    data_[(ll)BigInt(u.substr(mpos + 1))] = 1;
                } else if (mpos == 2 && u[0] == '-') {
                	data_[(ll)BigInt(u.substr(mpos + 1))] = -1;
				} else {
                	data_[(ll)BigInt(u.substr(mpos + 1))] = _T(tmp);
				}
            } else if (int Xpos = u.find_first_of("Xx"); Xpos != std::string::npos) {// 只支持单元 X/x 喵
                if ((Xpos == 1 && u[0] == '+') || Xpos == 0) {
                	data_[1] = 1;
				} else if (Xpos == 1 && u[0] == '-') {
                	data_[1] = -1;
				} else {
                	data_[1] = _T(u.substr(0, Xpos));
				}
            } else {
                data_[0] = _T(u);
            }
        }
        while (data_.back() == (_T)0 && _deg > 1) {
            data_.pop_back();
            --_deg;
        }
    }
    
    // 从其他类型的多项式转变而来
    template<typename _U>
    Polynomial(Polynomial<_U> t) {
        _deg = t._deg;
        for (auto digit : t.data_) data_.push_back(_T(digit));
    }
    
    
    template<typename _U>// 这个其实可以使用 c++20 的 concept 实现
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
            data_.resize(1);
            data_[0] = _T(digit);
        } else {
        	_deg = 0;
		}
    }
    
    // 这个是主动显示转化
    template<typename _U>
    Polynomial<_U> as() {
        Polynomial<_U> ret;
        ret._deg = _deg;
        if constexpr (std::is_same_v<_U, mll> && std::is_same_v<_T, mll>) {
            for (auto digit : data_) {
                digit.moduleCheck();
                ret.data_.push_back(digit);
            }
        } else {
            for (auto digit : data_) ret.data_.push_back(_U(digit));
        }
        ret.clearPrev0();
        return ret;
    }
    
    // 清除前导 0
    void clearPrev0() {
        while (data_.size() && data_.back() == (_T)0) {
            data_.pop_back();
            --_deg;
        }
    }
    
    // 输出流
    friend std::ostream& operator << (std::ostream &Pout, Polynomial t) {
        if (t._deg == 0) {
            return Pout << 0;
        }
        if (t._deg == 1) {
            return Pout << t.data_[0];
        } else if (t._deg == 2) {
            if (t.data_[1] == (_T)0) return Pout << t.data_[0];
            else if (t.data_[1] == (_T)1);
            else if (t.data_[1] > (_T)0) Pout << t.data_[1];
            else if (t.data_[1] == (_T)-1) Pout << "-";
            else Pout << t.data_[1];
            
            Pout << "x";
            
            if (t.data_[0] == (_T)0) return Pout;
            else if (t.data_[0] < (_T)0) return Pout << t.data_[0];
            else return Pout << "+" << t.data_[0];
        } else {
            if (t.data_[t._deg - 1] == (_T)1);
            else if (t.data_[t._deg - 1] > (_T)0) Pout << t.data_[t._deg - 1];
            else if (t.data_[t._deg - 1] == (_T)-1) Pout << "-";
            else Pout << t.data_[t._deg - 1];
            
            Pout << "x^" << t._deg - 1;
            for (int i = t._deg - 2; i >= 0; --i) {
                if (t.data_[i] == (_T)0) continue;
                else if (i != 0 && t.data_[i] == (_T)1) Pout << "+";
                else if (t.data_[i] > (_T)0) Pout << "+" << t.data_[i];
                else if (i != 0 && t.data_[i] == (_T)-1) Pout << "-";
                else Pout << t.data_[i];
                
                if (i == 0) continue;
                else if (i == 1) Pout << "x";
                else Pout << "x^" << i;
            }
        }
        return Pout;
    }
    
    // 偷懒的输入流
    friend std::istream& operator >> (std::istream &Pin, Polynomial &t) {
        Pin >> PolynomialBuf;
        t = Polynomial(PolynomialBuf);
        return Pin;
    }
    
    // 这个大小比较主要是为了处理首项系数的大小，只能说为了这盘醋包了这碟饺子
    bool operator < (const Polynomial t) const {
        if (_deg == 0) {
            return (_T)0 < t.data_[0];
        }
        if (t._deg == 0) {
            return data_[0] < (_T)0;
        }
        
        if (data_[0] > (_T)0 && t.data_[0] < (_T)0) {
        	return 0;
		}
        else if (data_[0] < (_T)0 && t.data_[0] > (_T)0) {
        	return 1;
		} else if (data_[0] > (_T)0 && t.data_[0] > (_T)0) {
            if (_deg ^ t._deg) return _deg < t._deg;
            for (int i = 0; i < _deg; ++i) {
                if (data_[i] != t.data_[i]) return data_[i] < t.data_[i];
            }
            return 0;
        } else if (data_[0] < (_T)0 && t.data_[0] < (_T)0) {
            if (_deg ^ t._deg) return _deg > t._deg;
            for (int i = 0; i < _deg; ++i) {
                if (data_[i] != t.data_[i]) return data_[i] > t.data_[i];
            }
            return 0;
        }
        return 0;
    }
    
    bool operator == (const Polynomial t) const {
        if (_deg ^ t._deg) return 0;
        for (int i = 0; i < _deg; ++i) {
            if (data_[i] != t.data_[i]) return 0;
        }
        return 1;
    }
    
    bool operator != (const Polynomial t) const {
        if (_deg ^ t._deg) return 1;
        for (int i = 0; i < _deg; ++i) {
            if (data_[i] != t.data_[i]) return 1;
        }
        return 0;
    }
    
    Polynomial operator -() const {
        Polynomial ret = *this;
        for (auto &digit : ret.data_) {
            digit = -digit;
        }
        return ret;
    }
    
    // 这个还是比 BigInt 简单的
    Polynomial operator + (const Polynomial t) const {
        Polynomial ret;
        ret._deg = std::max(_deg, t._deg);
        ret.data_.resize(ret._deg);
        for (int i = 0; i < ret._deg; ++i) {
            if (i < _deg && i < t._deg) {
                ret.data_[i] = data_[i] + t.data_[i];
            } else if (i < _deg) {
                ret.data_[i] = data_[i];
            } else if (i < t._deg) {
                ret.data_[i] = t.data_[i];
            }
        }
        ret.clearPrev0();
        return ret;
    }
    
    // 无需多言，恨透了 BigInt
    Polynomial operator - (const Polynomial t) const {
        return *this + (-t);
    }
    
    // 统一乘以一个系数
    friend Polynomial operator * (Polynomial a, _T k) {
        Polynomial ret = a;
        for (auto &digit : ret.data_) {
            digit = k * digit;
        }
        return ret;
    }
    
    // 无需多言，简单，我再也不想写 BigInt 了
    Polynomial operator * (const Polynomial t) const {
        Polynomial ret;
        ret.data_.resize(ret._deg = (_deg + t._deg));
        for (int i = 0; i < _deg; ++i) {
            for (int j = 0; j < t._deg; ++j) {
                ret.data_[i + j] = data_[i] * t.data_[j] + ret.data_[i + j];
            }
        }
        ret.clearPrev0();
        return ret;
    }
    
    // 等于 *x^k
    Polynomial operator << (const ll k) const {
        if (k <= 0) return *this;
        Polynomial ret;
        for (int i = 0; i < k; ++i) ret.data_.push_back(0);
        for (auto digit : data_) ret.data_.push_back(digit);
        ret._deg = ret.data_.size();
        return ret;
    }
    
    // 等于 /x^k
    Polynomial operator >> (const ll k) const {
        if (k <= 0) return *this;
        if (k > _deg) return 0;
        Polynomial ret = *this;
        ret.data_.erase(ret.data_.begin(), ret.data_.begin() + k);
        ret._deg = ret.data_.size();
        ret.clearPrev0();
        return ret;
    }
    
    Polynomial operator / (const Polynomial t) const {
        if (_deg < t._deg) return 0;
        Polynomial a = *this, b = t, ret;
        ll k, adeg = a._deg;
        _T digit;
        b <<= (k = (a._deg - b._deg));
        ret.data_.resize(ret._deg = k + 1);
        for (int i = adeg - 1; i >= adeg - 1 - k; --i) {
            if (i < a._deg) {
                digit = a.data_[i] / b.data_.back();
                a -= b * digit;
                ret.data_[i - adeg + k + 1] = digit;
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
                digit = a.data_[i] / b.data_.back();
                a -= b * digit;
            }
            b = b >> 1;
        }
        return a;
    }
    
    
    // 自运算 --------------------------------------------------------------------------------------------------------------------------
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
                digit = data_[i] / b.data_.back();
                *this -= b * digit;
            }
            b = b >> 1;
        }
        return *this;
    }
    
    // 求导
    Polynomial& getDifferentiation() {
        for (int i = 0; i < data_.size(); ++i) {
            data_[i] *= i;
        }
        data_.erase(data_.begin());
        --_deg;
        clearPrev0();
        return *this;
    }
    
    // 导数
    Polynomial differentiation() {
        Polynomial ret = *this;
        for (int i = 0; i < ret.data_.size(); ++i) {
            ret.data_[i] *= i;
        }
        ret.data_.erase(ret.data_.begin());
        --ret._deg;
        ret.clearPrev0();
        return ret;
    }
    
    // 首一约化
    Polynomial& makePrimitive() {
        if constexpr (std::is_same_v<_T, Fraction>) {
            Fraction constant = data_.back();
            for (auto &digit : data_) {
                digit /= constant;
            }
        } else if constexpr (std::is_same_v<_T, BigInt>) {
            BigInt constant = data_[0];
            for (auto digit : data_) {
                constant = gcd(digit, constant);
            }
            for (auto &digit : data_) {
                digit /= constant;
            }
        } else if constexpr (std::is_same_v<_T, mll>) {
            mll constant = data_.back().inv();
            for (auto &digit : data_) {
                digit *= constant;
            }
        }
        clearPrev0();
        return *this;
    }
    
    ll deg() { return _deg - 1; }
    
    // 首相系数
    _T first() {
        return data_.back();
    }
};

extern Polynomial<BigInt> MonomialX;

#undef mll
#undef ll
#endif