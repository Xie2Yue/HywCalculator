#ifndef _XIE2YUE_FRACTION_H
#define _XIE2YUE_FRACTION_H

#include <iostream>
#include <cstring>
#include "BigInt.h"
#include "BigIntNumberTheory.h"

extern std::string FractionBuf;

class Fraction {
	
	private:
		
    BigInt numer_, denomin_;
    
    // 约分
    void reduce() {
    	
        if (numer_ == BigInt(0)) {
        	
            denomin_ = 1;
            return;
            
        }
        
        if (denomin_ < BigInt(0)) {
        	
            denomin_ = -denomin_;
            numer_ = -numer_;
            
        }
        
        if (denomin_ == BigInt(1)) { return; }
        
        BigInt d = gcd(numer_, denomin_);
        denomin_ /= d;
        numer_ /= d;
        
    }
    
	public:
		
	// ----------------------------- 构造函数 -------------------------
    friend BigInt::BigInt(Fraction t);
    
    Fraction() : denomin_(1) {}
    
    template<typename _U>
    Fraction(_U p, _U q) : numer_(p), denomin_(q) { reduce(); }
    
    template<typename _U>
    Fraction(_U m) : numer_(m), denomin_(1) {}
    
    Fraction(std::string data) {
    	
        int slashPos = data.find('/');
        
        if (slashPos == std::string::npos) {
        	
            numer_ = BigInt(data);
            denomin_ = 1;
            
        } else {
        	
            numer_ = BigInt(data.substr(0, slashPos));
            denomin_ = BigInt(data.substr(slashPos + 1));
            
        }
        
        reduce();
        
    }
    
    // 获得带分数
    // 但是毫无卵用
    std::pair<BigInt, Fraction> getMixedFraction() const {
    	
        BigInt ret(numer_ / denomin_);
        
        return {ret, *this - ret};
        
    }
    
    // ----------------------------- 流式函数 -----------------------------
    friend std::istream& operator >> (std::istream &Fin, Fraction &t) {
    	
        Fin >> FractionBuf;
        t = Fraction(FractionBuf);
        return Fin;
        
    }
    
    std::string toString() {
    	
        if (denomin_ == BigInt(1)) return numer_.toString();
        
        return numer_.toString() + "/" + denomin_.toString();
        
    }
    
    friend std::ostream& operator << (std::ostream &out, Fraction t) {
    	
    	return out << t.toString();
    	
    }
    
    // ----------------------------- 比较函数 -----------------------------------
    
    bool operator < (const Fraction t) const {
    	
        return numer_ * t.denomin_ < t.numer_ * denomin_;
        
    }
    
    bool operator <= (const Fraction t) const {
    	
        return numer_ * t.denomin_ <= t.numer_ * denomin_;
        
    }
    
    bool operator > (const Fraction t) const {
    	
        return numer_ * t.denomin_ > t.numer_ * denomin_;
    }
    
    
    bool operator >= (const Fraction t) const {
    	
        return numer_ * t.denomin_ >= t.numer_ * denomin_;
    }
    
    
    bool operator == (const Fraction t) const {
    	
        return numer_ * t.denomin_ == t.numer_ * denomin_;
    }
    
    
    bool operator != (const Fraction t) const {
    	
        return numer_ * t.denomin_ != t.numer_ * denomin_;
        
    }
    
    // -------------------------------- 数值运算 -------------------------------------
    
    Fraction operator -() { return Fraction(-numer_, denomin_); }
    
    Fraction operator + (const Fraction t) const {
    	
        Fraction ret(numer_ * t.denomin_ + t.numer_ * denomin_, t.denomin_ * denomin_);
        
        ret.reduce();
        
        return ret;
        
    }
    
    Fraction operator - (const Fraction t) const {
    	
        Fraction ret(numer_ * t.denomin_ - t.numer_ * denomin_, t.denomin_ * denomin_);
        
        ret.reduce();
        
        return ret;
        
    }
    
    Fraction operator * (const Fraction t) const {
    	
        Fraction ret(numer_ * t.numer_, denomin_ * t.denomin_);
        
        ret.reduce();
        
        return ret;
        
    }
    
    Fraction operator / (const Fraction t) const {
    	
        Fraction ret(numer_ * t.denomin_, denomin_ * t.numer_);
        
        ret.reduce();
        
        return ret;
        
    }
    
    
    // ------------------------- 自运算符重载 ------------------------------
    
    
    Fraction& operator += (const Fraction t) { *this = *this + t; return *this; }
    
    Fraction& operator -= (const Fraction t) { *this = *this - t; return *this; }
    
    Fraction& operator *= (const Fraction t) { *this = *this * t; return *this; }
    
    Fraction& operator /= (const Fraction t) { *this = *this / t; return *this; }
    
};

Fraction abs(Fraction a);

#endif