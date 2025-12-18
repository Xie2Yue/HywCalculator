#ifndef _XIE2YUE_MATRIX_H
#define _XIE2YUE_MATRIX_H

#include <vector>

#define ll long long

template<typename _T>
class Matrix {
private:
    std::vector<std::vector<_T> > data_;
    ll _row, _col;
    
public:
    Matrix() {
        _row = _col = 0;
        data_.clear();
    }
    
    Matrix(ll n) : _row(n), _col(n) {
        data_.assign(n, std::vector<_T>(n, _T()));
        for (ll i = 0; i < n; ++i) data_[i][i] = _T(1);
    }
    
    Matrix(ll n, ll m) : _row(n), _col(m) {
        data_.assign(n, std::vector<_T>(m, _T()));
    }
    
    std::vector<_T> solve() {
        if (_col != _row + 1) {
            std::cerr << "No Solotion/I Can't Solve It\n";
            return std::vector<_T>();
        }
        std::vector<_T> ret(_row);
        for (int i = 0; i < _row; ++i) {
            for (int j = i + 1; j < _row; ++j) {
                if (abs(data_[j][i]) > abs(data_[i][i])) {
                    std::swap(data_[j], data_[i]);
                }
            }
            for (int j = i + 1; j < _row; ++j) {
                for (int k = i + 1; k < _col; ++k) {
                    data_[j][k] -= data_[i][k] * data_[j][i] / data_[i][i];
                }
            }
        }
        for (int i = _row - 1; i >= 0; --i) {
            ret[i] = data_[i][_row] / data_[i][i];
            for (int j = i; j >= 0; --j) {
                data_[j][_row] -= data_[j][i] * ret[i];
                data_[j][i] = _T(0);
            }
        }
        return ret;
    }
    
    void Mread() {
        for (int i = 0; i < _row; ++i) {
            for (int j = 0; j < _col; ++j) {
                std::cin >> data_[i][j];
            }
        }
    }
    
    void Mprint() {
        for (int i = 0; i < _row; ++i) {
            for (int j = 0; j < _col; ++j) {
                std::cout << data_[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

#undef ll

#endif