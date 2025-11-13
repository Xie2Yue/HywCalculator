#ifndef _XIE2YUE_BIGINT_H
#define _XIE2YUE_BIGINT_H

#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

#define ll long long
#define mll ModuleLongLong

extern std::string BigIntBuf;

class Fraction;
class mll;

class BigInt {
private:
    std::vector<ll> _data{};
    bool _isNegative;
    ll _len;
    static const int N = 2000;
    static const ll M = 100000000;
    static const int B = 8;
    
public:
    BigInt() { _len = 0; _isNegative = 0; }
    
    BigInt(int data) {
        _len = 0;
        _isNegative = 0;
        _data.clear();
        if (data < 0) {
            data = -data;
            _isNegative = 1;
        }
        while (data) {
            ++_len;
            _data.push_back(data % M);
            data /= M;
        }
    }
    
    BigInt(ll data) {
        _len = 0;
        _isNegative = 0;
        _data.clear();
        if (data < 0) {
            data = -data;
            _isNegative = 1;
        }
        while (data) {
            ++_len;
            _data.push_back(data % M);
            data /= M;
        }
    }
    
    BigInt(std::string data) {
        _isNegative = 0;
        if (data[0] == '-') _isNegative = 1;
        else if (data[0] != '+') data = "-" + data;
        int bIDigit = 0, bIpos;
        _data.clear();
        for (int i = data.length() - 1; i >= 1; i -= 8) {
            bIpos = std::max(1, i - 7);
            bIDigit = 0;
            while (bIpos <= i) {
                bIDigit *= 10;
                bIDigit += data[bIpos] - '0';
                ++bIpos;
            }
            _data.push_back(bIDigit);
        }
        _len = _data.size();
        clearPrev0();
    }
    
    BigInt(mll data);
    BigInt(Fraction t);
    
    int size() { return _len; }
    int len() { return _len; }
    
    void clearPrev0() {
        while (_data.size() && _data.back() == 0) {
            _data.pop_back();
            --_len;
        }
        if (_len == 0) _isNegative = 0;
    }
    
    friend std::ostream& operator << (std::ostream &bIout, BigInt t) {
        if (!t._len) {
            return bIout << 0;
        }
        ll tDigit;
        if (t._isNegative) bIout << "-";
        if (t._len == 1) return bIout << t._data.back();
        bIout << t._data.back() << std::setfill('0');
        for (int i = t._len - 2; i >= 0; --i) {
            bIout << std::setw(8) << t._data[i];
        }
        bIout << std::setfill(' ');
        return bIout;
    }
    
    friend std::istream& operator >> (std::istream &bIin, BigInt &t) {
        bIin >> BigIntBuf;
        t = BigInt(BigIntBuf);
        return bIin;
    }

    bool operator < (const BigInt t) const {
        if (_isNegative ^ t._isNegative) return _isNegative;
        if (_isNegative) {
            if (_len < t._len) return 0;
            if (_len > t._len) return 1;
            for (int i = _len - 1; i >= 0; --i) {
                if (_data[i] < t._data[i]) return 0;
                if (_data[i] > t._data[i]) return 1;
            }
        } else {
            if (_len < t._len) return 1;
            if (_len > t._len) return 0;
            for (int i = _len - 1; i >= 0; --i) {
                if (_data[i] < t._data[i]) return 1;
                if (_data[i] > t._data[i]) return 0;
            }
        }
        return 0;
    }
    
    bool operator <= (const BigInt t) const {
        if (_isNegative ^ t._isNegative) return _isNegative;
        if (_isNegative) {
            if (_len < t._len) return 0;
            if (_len > t._len) return 1;
            for (int i = _len - 1; i >= 0; --i) {
                if (_data[i] < t._data[i]) return 0;
                if (_data[i] > t._data[i]) return 1;
            }
        } else {
            if (_len < t._len) return 1;
            if (_len > t._len) return 0;
            for (int i = _len - 1; i >= 0; --i) {
                if (_data[i] < t._data[i]) return 1;
                if (_data[i] > t._data[i]) return 0;
            }
        }
        return 1;
    }
    
    bool operator > (const BigInt t) const {
        if (_isNegative ^ t._isNegative) return t._isNegative;
        if (_isNegative) {
            if (_len < t._len) return 1;
            if (_len > t._len) return 0;
            for (int i = _len - 1; i >= 0; --i) {
                if (_data[i] < t._data[i]) return 1;
                if (_data[i] > t._data[i]) return 0;
            }
        } else {
            if (_len < t._len) return 0;
            if (_len > t._len) return 1;
            for (int i = _len - 1; i >= 0; --i) {
                if (_data[i] < t._data[i]) return 0;
                if (_data[i] > t._data[i]) return 1;
            }
        }
        return 0;
    }
    
    bool operator >= (const BigInt t) const {
        if (_isNegative ^ t._isNegative) return t._isNegative;
        if (_isNegative) {
            if (_len < t._len) return 1;
            if (_len > t._len) return 0;
            for (int i = _len - 1; i >= 0; --i) {
                if (_data[i] < t._data[i]) return 1;
                if (_data[i] > t._data[i]) return 0;
            }
        } else {
            if (_len < t._len) return 0;
            if (_len > t._len) return 1;
            for (int i = _len - 1; i >= 0; --i) {
                if (_data[i] < t._data[i]) return 0;
                if (_data[i] > t._data[i]) return 1;
            }
        }
        return 1;
    }
    
    bool operator == (const BigInt t) {
        if (t._len == 0 && _len == 1 && _data[0] == 0) {
            _data.clear();
            _len = 0;
            return 1;
        }
        if (_len ^ t._len || _isNegative ^ t._isNegative) return 0;
        for (int i = _len - 1; i >= 0; --i) {
            if (_data[i] ^ t._data[i]) return 0;
        }
        return 1;
    }
    
    bool operator != (const BigInt t) const {
        if (_len ^ t._len || _isNegative ^ t._isNegative) return 1;
        for (int i = _len - 1; i >= 0; --i) {
            if (_data[i] ^ t._data[i]) return 1;
        }
        return 0;
    }
    
    bool isOdd() { return _data[0] & 1; }
    
    bool canPassMontgomery() {
        return
            _data[0] % 10 == 1 ||
            _data[0] % 10 == 3 ||
            _data[0] % 10 == 7 ||
            _data[0] % 10 == 9;
    }

    static BigInt abs(BigInt a) {
        return (a._isNegative) ? -a : a;
    }

    BigInt operator -() const {
        if (_len == 0) return *this;
        BigInt ret = *this;
        ret._isNegative ^= 1;
        return ret;
    }
    
    BigInt operator + (const BigInt t) const {
        BigInt ret;
        if (_isNegative ^ t._isNegative) return *this - (-t);
        ret._isNegative = _isNegative;
        ret._len = std::max(_len, t._len) + 1;
        ll toHigher = 0;
        for (int i = 0; i < ret._len; ++i) {
            if (i < _len && i < t._len) {
                ret._data.push_back(_data[i] + t._data[i]);
            } else if (i < _len) {
                ret._data.push_back(_data[i]);
            } else if (i < t._len) {
                ret._data.push_back(t._data[i]);
            } else {
				ret._data.push_back(0);
			}
            ret._data[i] += toHigher;
            toHigher = ret._data[i] / M;
            ret._data[i] %= M;
        }
        ret.clearPrev0();
        return ret;
    }
    
    BigInt operator - (const BigInt t) const {
        if (t._len == 0) {
            return *this;
        }
        if (_isNegative ^ t._isNegative) {
            return *this + (-t);
        }
        if (_isNegative && *this > t) {
            return -(t - *this);
        }
        if (!_isNegative && *this < t) {
            return -(t - *this);
        }
        BigInt ret;
        ret._isNegative = _isNegative;
        ret._len = _len;
        ret._data.resize(_len);
        bool toHigher = 0;
        for (int i = 0; i < _len; ++i) {
            if (i < t._len) {
                ret._data[i] = _data[i] - t._data[i] - toHigher;
                toHigher = 0;
                if (ret._data[i] < 0) {
                    toHigher = 1;
                    ret._data[i] += M;
                }
            } else {
                ret._data[i] = _data[i] - toHigher;
                toHigher = 0;
                if (ret._data[i] < 0) {
                    toHigher = 1;
                    ret._data[i] += M;
                }
            }
        }
        ret.clearPrev0();
        return ret;
    }
    
    BigInt operator * (const BigInt t) const {
        BigInt ret;
        ret._isNegative = _isNegative ^ t._isNegative;
        ret._len = _len + t._len;
        ret._data.resize(ret._len);
        for (int i = 0; i < _len; ++i) {
            for (int j = 0; j < t._len; ++j) {
                ret._data[i + j] += _data[i] * t._data[j];
            }
        }
        ll toHigher = 0;
        for (int i = 0; i < ret._len; ++i) {
            ret._data[i] += toHigher;
            toHigher = ret._data[i] / M;
            ret._data[i] %= M;
        }
        ret.clearPrev0();
        return ret;
    }
    
    BigInt operator << (const ll k) const {
        BigInt ret;
        ret._isNegative = _isNegative;
        ret._len = _len + (k - 1) / B + 1;
        ret._data.resize(ret._len);
        ll bigMove = k / B, bigMod = 1;
        for (int i = 1; i <= k % B; ++i) bigMod *= 10;
        for (int i = ret._len - 1; i >= bigMove; --i) {
            if (i - bigMove < _len && i - bigMove - 1 >= 0) {
                ret._data[i] = _data[i - bigMove] * bigMod % M + _data[i - bigMove - 1] * bigMod / M;
            } else if (i - bigMove - 1 >= 0) {
                ret._data[i] = _data[i - bigMove - 1] * bigMod / M;
            } else {
                ret._data[i] = _data[i - bigMove] * bigMod % M;
            }
        }
        ret.clearPrev0();
        return ret;
    }
    
    BigInt operator >> (const ll k) const {
        BigInt ret;
        ret._isNegative = _isNegative;
        ll bigMove = k / B, bigMod = 1;
        for (int i = 1; i <= k % B; ++i) {
            bigMod *= 10;
        }
        if (bigMove >= _len) return ret;
        ret._len = std::max(1ll, _len - bigMove);
        ret._data.resize(ret._len);
        for (int i = 0; i < ret._len; ++i) {
            if (i + bigMove + 1 < _len) ret._data[i] = _data[i + bigMove + 1] * M / bigMod % M + _data[i + bigMove] / bigMod;
            else ret._data[i] = _data[i + bigMove] / bigMod;
        }
        ret.clearPrev0();
        return ret;
    }
    
    BigInt operator / (const BigInt t) const {
        ll k = 0, dat = 0, num = 0, tot = 0;
        BigInt ret, a = abs(*this), b = abs(t);
        while (a >= b) {
            b <<= 1;
            ++k;
        }
        bool flag = _isNegative ^ t._isNegative;
        ret._len = tot = (k - 1) / B + 1;
        ret._data.resize(ret._len);
        --tot;
        b >>= 1;
        while (k--) {
            num = 0;
            while (a >= b) {
                a -= b;
                ++num;
            }
            dat = dat * 10 + num;
            if (k % B == 0) {
                ret._data[tot] = dat;
                dat = 0;
                --tot;
            }
            b >>= 1;
        }
        if (flag) return -ret;
        return ret;
    }
    
    ll operator % (const ll p) const {
        bool flag = _isNegative;
        ll ret = 0;
        for (int i = _len - 1; i >= 0; --i) {
            (((ret *= M % p) %= p) += _data[i] % p) %= p;
        }
        if (flag) return p - ret;
        return ret;
    }
    
    BigInt operator % (const BigInt t) const {
        bool flag = _isNegative;
        BigInt ret = abs(*this), b = abs(t);
        
        if (ret < b) {
            if (flag) return abs(t) - ret;
            return ret;
        }
        int k = 0;
        while (ret >= b) {
            b <<= 1;
            ++k;
        }
        b >>= 1;
        while (k--) {
            while (ret >= b) {
                ret -= b;
            }
            b >>= 1;
        }
        if (flag) return abs(t) - ret;
        return ret;
    }

    BigInt& operator += (const BigInt t) {
        *this = *this + t;
        return *this;
    }
    
    BigInt& operator -= (const BigInt t) {
        *this = *this - t;
        return *this;
    }
    
    BigInt& operator *= (const BigInt t) {
        *this = *this * t;
        return *this;
    }
    
    BigInt& operator <<= (const ll k) {
        *this = *this << k;
        return *this;
    }
    
    BigInt& operator >>= (const ll k) {
        *this = *this >> k;
        return *this;
    }
    
    BigInt& operator /= (const BigInt t) {
        *this = *this / t;
        return *this;
    }
    
    BigInt& operator %= (const BigInt t) {
        BigInt b = abs(t);
        bool flag = _isNegative;
        if (flag) *this = -*this;
        if (*this < b) {
            if (flag) *this = abs(t) - *this;
            return *this;
        }
        int k = 0;
        while (*this >= b) {
            b <<= 1;
            ++k;
        }
        b >>= 1;
        while (k--) {
            while (*this >= b) {
                *this -= b;
            }
            b >>= 1;
        }
        if (flag) *this = abs(t) - *this;
        return *this;
    }

    BigInt getRightSub(ll k) {
        ll siz = (k - 1) / B + 1, bigMod = M;
        for (int i = 1; i <= k % B; ++i) {
            if (i == 1) bigMod = 1;
            bigMod *= 10;
        }
        BigInt ret;
        ret._isNegative = _isNegative;
        ret._len = std::min(_len, siz);
        ret._data.resize(ret._len);
        for (int i = 0; i < ret._len; ++i) {
            ret._data[i] = _data[i];
        }
        if (ret._len == siz) ret._data[ret._len - 1] %= bigMod;
        ret.clearPrev0();
        return ret;
    }
    
    BigInt& divBy2() {
        BigInt ret;
        ret._len = _len;
        ret._isNegative = _isNegative;
        ll upperPlus = 0;
        ret._data.resize(_len);
        for (int i = _len - 1; i >= 0; --i) {
            ret._data[i] = _data[i] + upperPlus * M;
            upperPlus = ret._data[i] & 1;
            ret._data[i] >>= 1;
        }
        ret.clearPrev0();
        return *this = ret;
    }
    
    BigInt& multiBy2() {
        BigInt ret;
        ret._len = _len + 1;
        ll toHigher = 0;
        ret._data.resize(ret._len);
        for (int i = 0; i < ret._len; ++i) {
            if (i < _len) {
                ret._data[i] = _data[i] * 2 + toHigher;
                toHigher = ret._data[i] / M;
                ret._data[i] %= M;
            } else {
                ret._data[i] = toHigher;
                toHigher = 0;
            }
        }
        ret.clearPrev0();
        return *this = ret;
    }
    
    BigInt getRandom(ll k) {
        *this = BigInt((1ll << ((k - 1) % 32)) + rand() % (1ll << ((k - 1) % 32)));
        k -= (((k - 1) % 32) + 1);
        while (k) {
            *this *= BigInt(1ll << 32);
            *this += BigInt(rand() % (1ll << 32));
            k -= 32;
        }
        return *this;
    }
    
    ll log2() {
        ll ret = 0;
        BigInt a = *this;
        while (a._len) {
            ++ret;
            a.divBy2();
        }
        return ret;
    }
    
    operator ll() const {
        ll ret = 0;
        for (int i = _len - 1; i >= 0; --i) {
            (ret *= M) += _data[i];
        }
        if (_isNegative) return -ret;
        return ret;
    }
    
    std::string toString() {
        std::stringstream ret;
        if (!_len) {
            return "0";
        }
        if (_isNegative) {
            ret << "-";
        }
        if (_len == 1) {
            ret << _data.back();
            return ret.str();
        }
        ret << _data.back() << std::setfill('0');
        for (int i = _len - 2; i >= 0; --i) {
            ret << std::setw(8) << _data[i];
        }
        ret << std::setfill(' ');
        return ret.str();
    }
};

BigInt abs(BigInt a);

#undef ll
#endif