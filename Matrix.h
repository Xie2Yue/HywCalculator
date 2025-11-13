#ifndef _XIE2YUE_MATRIX_H
#define _XIE2YUE_MATRIX_H

#include <vector>

#define ll long long

template<typename _T>
class Matrix {
private:
    std::vector<std::vector<_T> > _data;
    ll _row, _col;
    
public:
    Matrix() {
        _row = _col = 0;
        _data.clear();
    }
    
    Matrix(ll n) : _row(n), _col(n) {
        _data.assign(n, std::vector<_T>(n, _T()));
        for (ll i = 0; i < n; ++i) _data[i][i] = _T(1);
    }
    
    Matrix(ll n, ll m) : _row(n), _col(m) {
        _data.assign(n, std::vector<_T>(m, _T()));
    }
    
    std::vector<_T> solve() {
        if (_col != _row + 1) {
            std::cerr << "No Solotion/I Can't Solve It\n";
            return std::vector<_T>();
        }
        std::vector<_T> ret(_row);
        for (int i = 0; i < _row; ++i) {
            for (int j = i + 1; j < _row; ++j) {
                if (abs(_data[j][i]) > abs(_data[i][i])) {
                    std::swap(_data[j], _data[i]);
                }
            }
            for (int j = i + 1; j < _row; ++j) {
                for (int k = i + 1; k < _col; ++k) {
                    _data[j][k] -= _data[i][k] * _data[j][i] / _data[i][i];
                }
            }
        }
        for (int i = _row - 1; i >= 0; --i) {
            ret[i] = _data[i][_row] / _data[i][i];
            for (int j = i; j >= 0; --j) {
                _data[j][_row] -= _data[j][i] * ret[i];
                _data[j][i] = _T(0);
            }
        }
        return ret;
    }
    
    void Mread() {
        for (int i = 0; i < _row; ++i) {
            for (int j = 0; j < _col; ++j) {
                std::cin >> _data[i][j];
            }
        }
    }
    
    void Mprint() {
        for (int i = 0; i < _row; ++i) {
            for (int j = 0; j < _col; ++j) {
                std::cout << _data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

#undef ll

#endif