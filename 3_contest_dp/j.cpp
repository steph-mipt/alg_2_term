#include <iostream>
#include <vector>

template<unsigned M, unsigned N = M>
class Matrix {
public:
    std::vector<std::vector<long long>> table;

    Matrix(void) {
        std::vector<long long> row(N, 0);

        for (unsigned i = 0; i < M; ++i) {
            row[i] = (1);
            table.push_back(row);
            row[i] = (0);
        }
    }

    template<class t>
    Matrix(std::vector<std::vector<t>> tab) {
        std::vector<long long> row(N);
        table.resize(M);
        for (unsigned i = 0; i < M; ++i) {
            for (unsigned j = 0; j < N; ++j) {
                row[j] = tab[i][j];
            }
            table[i] = row;
        }
    }

    void swap(unsigned long i, unsigned long k) {
        for (unsigned long j = 0; j < table.size(); ++j) {
            std::swap(table[j][i], table[j][k]);
        }
    }

    std::vector<long long> &operator[](const int i) {
        return table[i];
    }
};

template<unsigned N>
class SquareMatrix : public Matrix<N, N> {
public:
    SquareMatrix<N>() : Matrix<N, N>() {}

    SquareMatrix<N>(std::vector<std::vector<long long>> c) : Matrix<N, N>(c) {}
};

template<unsigned M, unsigned N>
Matrix<M, N> &operator*=(Matrix<M, N> &matrix, const long long a) {
    for (unsigned i = 0; i < matrix.table.size(); ++i) {
        for (unsigned j = 0; j < matrix.table[0].size(); ++j) {
            matrix.table[i][j] *= a;
        }
    }
    return matrix;
};

template<unsigned M, unsigned N, unsigned K>
Matrix<M, K> operator*(const Matrix<M, N> first, const Matrix<N, K> &another) {
    long long sum = 0;
    Matrix<M, K> mat;
    for (unsigned i = 0; i < first.table.size(); ++i) {
        for (unsigned j = 0; j < another.table[0].size(); ++j) {
            for (unsigned k = 0; k < first.table[0].size(); ++k) {
                sum += first.table[i][k] * another.table[k][j] ;
            }
            mat[i][j] = sum % 999999937;
            sum = 0;
        }
    }
    return mat;
}

template<unsigned M, unsigned N, unsigned K>
Matrix<M, K> &operator*=(Matrix<M, N> &first, const Matrix<N, K> &another) {
    first = first * another;
    return first;
}


class solution {
private:
    SquareMatrix<5> matrix;
public:
    long long ans = 0;

    Matrix<5> power(Matrix<5> &a, long long n ) {
        if (n == 1) {
            return a;
        }
        else if (n == 2) {
            return a * a;
        }
        else if (n % 2 == 0) {
            Matrix<5> tmp = power(a, n / 2);
            return tmp * tmp;
        }
        else {
            Matrix<5> tmp = power(a, n / 2);
            tmp = tmp * tmp;
            return tmp * a;
        }

    }
    solution(SquareMatrix<5> &a, long long n) {
        std::vector<std::vector<long long>> tmp(5, std::vector<long long> (5, 0));
        Matrix<5> res(tmp);
        res = power(a, n);
        long long sum = 0;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j) {
                sum += res[i][j];
            }
        ans = sum % 999999937;
    }
};

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::vector<std::vector<long long>> start(5, std::vector<long long> (5, 1));
    start[2][3] = start[2][4] = start[4][3] = start[4][4] = 0;
    long long n;
    SquareMatrix<5> m(start);

    std::cin >> n;
    while (n != 0) {
        if (n == 1) {
            std::cout << 5 << "\n";
        } else{
            solution sol(m, n - 1);
            std::cout << sol.ans << "\n";
        }

        std::cin >> n;
    }
    return 0;
}
