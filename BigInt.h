#ifndef _XIE2YUE_BIGINT_H
#define _XIE2YUE_BIGINT_H

#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <random>

#define ll long long
#define mll ModuleLongLong

extern std::string BigIntBuf;

class Fraction;
class mll;

class BigInt {
	private:
	
	// 通过 vector 存储数据
	// 低位 vector 存储低位数据
    std::vector<ll> data_{};
    bool isNegative_;
    ll len_;
    
    // 采用1e8进制存储
    static const ll M = 100000000;
    static const int B = 8;
    
	public:

	// -------------------- 构造函数 -----------------------

    BigInt() { len_ = 0; isNegative_ = 0; }
    
    BigInt(int data) {
    	
        len_ = 0;
        isNegative_ = 0;
        data_.clear();
        
        if (data < 0) {
            data = -data;
            isNegative_ = 1;
        }
        
        while (data) {
            ++len_;
            data_.push_back(data % M);
            data /= M;
        }
        
    }
    
    BigInt(ll data) {
    	
        len_ = 0;
        isNegative_ = 0;
        data_.clear();
        
        if (data < 0) {
            data = -data;
            isNegative_ = 1;
        }
        
        while (data) {
            ++len_;
            data_.push_back(data % M);
            data /= M;
        }
        
    }
    
    BigInt(std::string data) {
    	
        isNegative_ = 0;
        
        if (data[0] == '-') isNegative_ = 1;
        
        // 如果是 正数 而且没有前导 +
        // 则添加一个符号方便处理
        else if (data[0] != '+') data = "-" + data;
        
        int bIDigit = 0, bIpos;
        data_.clear();
        
        
        for (int i = data.length() - 1; i >= 1; i -= 8) {
            bIpos = std::max(1, i - 7);
            bIDigit = 0;
            while (bIpos <= i) {
                bIDigit *= 10;
                bIDigit += data[bIpos] - '0';
                ++bIpos;
            }
            data_.push_back(bIDigit);
        }
        
        len_ = data_.size();
        clearPrev0();
        
    }
    
    BigInt(mll data);
    BigInt(Fraction t);
    
    // -------------------- 基础函数 ----------------------
    
    int size() const { return len_; }
    int len() const { return len_; }
    
    // 清除前导零
    void clearPrev0() {
    	
        while (data_.size() && data_.back() == 0) {
            data_.pop_back();
            --len_;
        }
        // 避免出现 -0
        if (len_ == 0) isNegative_ = 0;
        
    }
    
    std::string toString() {
        std::stringstream ret;
        
        if (!len_) { return "0"; }
        if (isNegative_) { ret << "-"; }
        
        if (len_ == 1) {
            ret << data_.back();
            return ret.str();
        }
        
        // 设置非首位的补齐 0
        ret << data_.back() << std::setfill('0');
        for (int i = len_ - 2; i >= 0; --i) {
            ret << std::setw(8) << data_[i];
        }
        // 恢复补齐
        ret << std::setfill(' ');
        return ret.str();
        
    }
    
    friend std::ostream& operator << (std::ostream &out, BigInt t) {
    	
    	return out<<t.toString();
    	
    }
    
    friend std::istream& operator >> (std::istream &in, BigInt &t) {
    	
        in >> BigIntBuf;
        t = BigInt(BigIntBuf);
        return in;
        
    }

	// -------------------- 判断条件函数 ---------------------

    bool operator < (const BigInt t) const {
    	
        if (isNegative_ ^ t.isNegative_) { return isNegative_; }
        
        if (isNegative_) {
            if (len_ < t.len_) { return 0; }
            if (len_ > t.len_) { return 1; }
            for (int i = len_ - 1; i >= 0; --i) {
                if (data_[i] < t.data_[i]) { return 0; }
                if (data_[i] > t.data_[i]) { return 1; }
            }
        }
		
		else {
            if (len_ < t.len_) { return 1; }
            if (len_ > t.len_) { return 0; }
            for (int i = len_ - 1; i >= 0; --i) {
                if (data_[i] < t.data_[i]) { return 1; }
                if (data_[i] > t.data_[i]) { return 0; }
            }
        }
        
        return 0;
        
    }
    
    bool operator <= (const BigInt t) const {
        
        if (isNegative_ ^ t.isNegative_) { return isNegative_; }
        
        if (isNegative_) {
            if (len_ < t.len_) { return 0; }
            if (len_ > t.len_) { return 1; }
            for (int i = len_ - 1; i >= 0; --i) {
                if (data_[i] < t.data_[i]) { return 0; }
                if (data_[i] > t.data_[i]) { return 1; }
            }
        }
        
        else {
            if (len_ < t.len_) { return 1; }
            if (len_ > t.len_) { return 0; }
            for (int i = len_ - 1; i >= 0; --i) {
                if (data_[i] < t.data_[i]) { return 1; }
                if (data_[i] > t.data_[i]) { return 0; }
            }
        }
        
        return 1;
        
    }
    
    bool operator > (const BigInt t) const {
        
        if (isNegative_ ^ t.isNegative_) { return t.isNegative_; }
        
        if (isNegative_) {
            if (len_ < t.len_) { return 1; }
            if (len_ > t.len_) { return 0; }
            for (int i = len_ - 1; i >= 0; --i) {
                if (data_[i] < t.data_[i]) { return 1; }
                if (data_[i] > t.data_[i]) { return 0; }
            }
        }
        
        else {
            if (len_ < t.len_) { return 0; }
            if (len_ > t.len_) { return 1; }
            for (int i = len_ - 1; i >= 0; --i) {
                if (data_[i] < t.data_[i]) { return 0; }
                if (data_[i] > t.data_[i]) { return 1; }
            }
        }
        
        return 0;
        
    }
    
    bool operator >= (const BigInt t) const {
        
        if (isNegative_ ^ t.isNegative_) { return t.isNegative_; }
        
        if (isNegative_) {
            if (len_ < t.len_) { return 1; }
            if (len_ > t.len_) { return 0; }
            for (int i = len_ - 1; i >= 0; --i) {
                if (data_[i] < t.data_[i]) { return 1; }
                if (data_[i] > t.data_[i]) { return 0; }
            }
        }
        
        else {
            if (len_ < t.len_) { return 0; }
            if (len_ > t.len_) { return 1; }
            for (int i = len_ - 1; i >= 0; --i) {
                if (data_[i] < t.data_[i]) { return 0; }
                if (data_[i] > t.data_[i]) { return 1; }
            }
        }
        
        return 1;
        
    }
    
    bool operator == (const BigInt t) {
        
        if (t.len_ == 0 && len_ == 1 && data_[0] == 0) {
            data_.clear();
            len_ = 0;
            return 1;
        }
        
        if (len_ ^ t.len_ || isNegative_ ^ t.isNegative_) { return 0; }
        
        for (int i = len_ - 1; i >= 0; --i) {
            if (data_[i] ^ t.data_[i]) { return 0; }
        }
        
        return 1;
        
    }
    
    bool operator != (const BigInt t) const {
        
        if (len_ ^ t.len_ || isNegative_ ^ t.isNegative_) { return 1; }
        
        for (int i = len_ - 1; i >= 0; --i) {
            if (data_[i] ^ t.data_[i]) { return 1; }
        }
        
        return 0;
        
    }
    
    bool isOdd() const { return data_[0] & 1; }
    
    // 能否作为蒙哥马利约化的 R
    // 要求 : 不是 2 和 5 的倍数
    bool canPassMontgomery() {
    	
        return
            data_[0] % 10 == 1 ||
            data_[0] % 10 == 3 ||
            data_[0] % 10 == 7 ||
            data_[0] % 10 == 9;

    }

    static BigInt abs(BigInt a) {
        return (a.isNegative_) ? -a : a;
    }
    
    
    // -------------------- 运算符重载 --------------------------
    

    BigInt operator -() const {
    	
        if (len_ == 0) return *this;
        
        BigInt ret = *this;
        ret.isNegative_ ^= 1;
        
        return ret;
        
    }
    
    BigInt operator + (const BigInt t) const {
    	
        if (isNegative_ ^ t.isNegative_) return *this - (-t);
        
        BigInt ret;
        ret.isNegative_ = isNegative_;
        ret.len_ = std::max(len_, t.len_) + 1;
        
        // 进位标识
        ll toHigher = 0;
        
        for (int i = 0; i < ret.len_; ++i) {
        	
            if (i < len_ && i < t.len_) {
                ret.data_.push_back(data_[i] + t.data_[i]);
            } else if (i < len_) {
                ret.data_.push_back(data_[i]);
            } else if (i < t.len_) {
                ret.data_.push_back(t.data_[i]);
            } else {
				ret.data_.push_back(0);
			}
			
            ret.data_[i] += toHigher;
            
            toHigher = ret.data_[i] / M;
            
            ret.data_[i] %= M;
            
        }
        
        ret.clearPrev0();
        
        return ret;
        
    }
    
    BigInt operator - (const BigInt t) const {
    	
        if (t.len_ == 0) { return *this; }
        
        if (isNegative_ ^ t.isNegative_) { return *this + (-t); }
        
        if (isNegative_ && *this > t) { return -(t - *this); }
        
        if (!isNegative_ && *this < t) { return -(t - *this); }
        
        BigInt ret;
        ret.isNegative_ = isNegative_;
        ret.len_ = len_;
        ret.data_.resize(len_);
        
        // 退位标识
        bool toHigher = 0;
        
        for (int i = 0; i < len_; ++i) {
        	
            if (i < t.len_) {
                ret.data_[i] = data_[i] - t.data_[i] - toHigher;
                toHigher = 0;
                
                if (ret.data_[i] < 0) {
                    toHigher = 1;
                    ret.data_[i] += M;
                }
            }
			
			else {
                ret.data_[i] = data_[i] - toHigher;
                toHigher = 0;
                
                if (ret.data_[i] < 0) {
                    toHigher = 1;
                    ret.data_[i] += M;
                }
            }
            
        }
        
        ret.clearPrev0();
        
        return ret;
    }
    
    BigInt operator * (const BigInt t) const {
    	
        BigInt ret;
        ret.isNegative_ = isNegative_ ^ t.isNegative_;
        ret.len_ = len_ + t.len_;
        ret.data_.resize(ret.len_);
        
        // 先乘再进位
        
        for (int i = 0; i < len_; ++i) {
            for (int j = 0; j < t.len_; ++j) {
            	
                ret.data_[i + j] += data_[i] * t.data_[j];
                
            }
        }
        
        
        ll toHigher = 0;
        
        for (int i = 0; i < ret.len_; ++i) {
        	
            ret.data_[i] += toHigher;
            toHigher = ret.data_[i] / M;
            ret.data_[i] %= M;
            
        }
        
        ret.clearPrev0();
        
        return ret;
        
    }
    
    // 位运算 相当于 * 10 ^ k
    BigInt operator << (const ll k) const {
    	
        BigInt ret;
        
        ret.isNegative_ = isNegative_;
        ret.len_ = len_ + (k - 1) / B + 1;
        ret.data_.resize(ret.len_);
        
        ll bigMove = k / B, bigMod = 1;
        
        for (int i = 1; i <= k % B; ++i) {
        	bigMod *= 10;
		}
        
        for (int i = ret.len_ - 1; i >= bigMove; --i) {
        	
            if (i - bigMove < len_ && i - bigMove - 1 >= 0) {
                ret.data_[i] = data_[i - bigMove] * bigMod % M + data_[i - bigMove - 1] * bigMod / M;
            } else if (i - bigMove - 1 >= 0) {
                ret.data_[i] = data_[i - bigMove - 1] * bigMod / M;
            } else {
                ret.data_[i] = data_[i - bigMove] * bigMod % M;
            }
            
        }
        
        ret.clearPrev0();
        
        return ret;
    }
    
    BigInt operator >> (const ll k) const {
    	
        BigInt ret;
        
        ret.isNegative_ = isNegative_;
        ll bigMove = k / B, bigMod = 1;
        
        for (int i = 1; i <= k % B; ++i) {
            bigMod *= 10;
        }
        
        if (bigMove >= len_) return ret;
        
        ret.len_ = std::max(1ll, len_ - bigMove);
        ret.data_.resize(ret.len_);
        
        for (int i = 0; i < ret.len_; ++i) {
        	
            if (i + bigMove + 1 < len_) {
            	ret.data_[i] = data_[i + bigMove + 1] * M / bigMod % M + data_[i + bigMove] / bigMod;
			}
			
            else {
            	ret.data_[i] = data_[i + bigMove] / bigMod;
			}
            
        }
        
        ret.clearPrev0();
        
        return ret;
        
    }
    
    // 模仿长除法，时间复杂度较高
    BigInt operator / (const BigInt t) const {
    	
        ll k = 0, dat = 0, num = 0, tot = 0;
        BigInt ret, a = abs(*this), b = abs(t);
        
        
        while (a >= b) {
            b <<= 1;
            ++k;
        }
        
        bool flag = isNegative_ ^ t.isNegative_;
        
        ret.len_ = tot = (k - 1) / B + 1;
        ret.data_.resize(ret.len_);
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
                ret.data_[tot] = dat;
                dat = 0;
                --tot;
            }
            
            b >>= 1;
            
        }
        
        if (flag) return -ret;
        
        return ret;
        
    }
    
    ll operator % (const ll p) const {
    	
        bool flag = isNegative_;
        
        ll ret = 0;
        
        for (int i = len_ - 1; i >= 0; --i) { ( ( ( ret *= M % p) %= p) += data_[i] % p) %= p; }
        
        if (flag) return p - ret;
        
        return ret;
        
    }
    
    // 和长除法类似
    BigInt operator % (const BigInt t) const {
    	
        bool flag = isNegative_;
        
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
        
        if (flag) { return abs(t) - ret; }
        
        return ret;
        
    }
	
	
	// -------------------- 自运算符重载 --------------------------
	
	
    BigInt& operator +=  (const BigInt t) { *this = *this +  t; return *this; }
    BigInt& operator -=  (const BigInt t) { *this = *this -  t; return *this; }
    BigInt& operator *=  (const BigInt t) { *this = *this *  t; return *this; }
    BigInt& operator <<= (const   ll   k) { *this = *this << k; return *this; }
    BigInt& operator >>= (const   ll   k) { *this = *this >> k; return *this; }
    BigInt& operator /=  (const BigInt t) { *this = *this /  t; return *this; }
    
    BigInt& operator %= (const BigInt t) {
    	
        BigInt b = abs(t);
        
        bool flag = isNegative_;
        
        if (flag) { *this = -*this; }
        
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
        
        if (flag) { *this = abs(t) - *this; }
        
        return *this;
        
    }


	// --------------------- 其他函数


	// 获得右子串，相当于 % 10 ^ k
    BigInt getRightSub(ll k) const {
    	
        ll siz = (k - 1) / B + 1, bigMod = M;
        
        for (int i = 1; i <= k % B; ++i) {
            if (i == 1) bigMod = 1;
            bigMod *= 10;
        }
        
        BigInt ret;
        ret.isNegative_ = isNegative_;
        ret.len_ = std::min(len_, siz);
        ret.data_.resize(ret.len_);
        
        for (int i = 0; i < ret.len_; ++i) {
            ret.data_[i] = data_[i];
        }
        
        if (ret.len_ == siz) { ret.data_[ret.len_ - 1] %= bigMod; }
        
        ret.clearPrev0();
        
        return ret;
        
    }
    
    BigInt& divBy2() {
    	
        BigInt ret;
        ret.len_ = len_;
        ret.isNegative_ = isNegative_;
        
        ll upperPlus = 0;
        
        ret.data_.resize(len_);
        
        for (int i = len_ - 1; i >= 0; --i) {
            ret.data_[i] = data_[i] + upperPlus * M;
            upperPlus = ret.data_[i] & 1;
            ret.data_[i] >>= 1;
        }
        
        ret.clearPrev0();
        
        return *this = ret;
        
    }
    
    BigInt& multiBy2() {
    	
        BigInt ret;
        ret.len_ = len_ + 1;
        
        ll toHigher = 0;
        
        ret.data_.resize(ret.len_);
        
        for (int i = 0; i < ret.len_; ++i) {
        	
            if (i < len_) {
                ret.data_[i] = data_[i] * 2 + toHigher;
                toHigher = ret.data_[i] / M;
                ret.data_[i] %= M;
            } else {
                ret.data_[i] = toHigher;
                toHigher = 0;
            }
            
        }
        
        ret.clearPrev0();
        
        return *this = ret;
        
    }
    
    BigInt& getRandom(ll k) {
    	
    	static std::random_device rd;
    	static std::mt19937 gen(rd());
    	
    	// dis1 作为最高位的随机数， dis2 作为后面的随机数，安排满
    	//
    	// 我不知道为什么用不了 64 位随机数，所以为了防止暴 int ，只能这么做
    	std::uniform_int_distribution<> dis1(0, (1 << ( (k - 1) % 30) ) - 1);
    	std::uniform_int_distribution<> dis2(0, (1 << 30) - 1 );
    	
        *this = BigInt((1 << ((k - 1) % 30)) + dis1(gen));
        
        k -= (((k - 1) % 30) + 1);
        
        while (k) {
        	
            *this *= BigInt(1ll << 30);
            *this += BigInt(dis2(gen));
            k -= 30;
            
        }
        
        return *this;
        
    }
    
    ll log2() {
    	
        ll ret = 0;
        
        BigInt a = *this;
        
        while (a.len_) {
            ++ret;
            a.divBy2();
        }
        
        return ret;
        
    }
    
    // 强转 ll ，但是不管溢出
    operator ll() const {
    	
        ll ret = 0;
        
        for (int i = len_ - 1; i >= 0; --i) { (ret *= M) += data_[i]; }
        
        if (isNegative_) return -ret;
        
        return ret;
        
    }
};

BigInt abs(BigInt a);

#undef ll
#endif