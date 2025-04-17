// matrix class with addition, subtraction, multiplication, determinant, and inverse, transpose, and scalar multiplication

#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>

template <typename T, int M, int N>
class Matrix {
    private:
        T data[M][N];
    public:
        Matrix() {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    data[i][j] = T();
                }
            }
        }

        Matrix(std::initializer_list<std::initializer_list<T>> list) {
            int i = 0;
            for (const auto& row : list) {
                int j = 0;
                for (const auto& elem : row) {
                    data[i][j++] = elem;
                }
                i++;
            }
        }

        T get(int row, int col) const {
            return data[row][col];
        }

        void set(int row, int col, T value) {
            data[row][col] = value;
        }

        template <typename U>
        friend Matrix<T, M, N> operator+(const Matrix<T, M, N>& mat1, const Matrix<U, M, N>& mat2) {
            Matrix<T, M, N> result;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    result.set(i, j, mat1.get(i, j) + mat2.get(i, j));
                }
            }
            return result;
        }

        template <typename U>
        friend Matrix<T, M, N> operator-(const Matrix<T, M, N>& mat1, const Matrix<U, M, N>& mat2) {
            Matrix<T, M, N> result;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    result.set(i, j, mat1.get(i, j) - mat2.get(i, j));
                }
            }
            return result;
        }

        template <typename U, int P>
        friend Matrix<T, M, P> operator*(const Matrix<T, M, N>& mat1, const Matrix<U, N, P>& mat2) {
            Matrix<T, M, P> result;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < P; j++) {
                    T sum = T();
                    for (int k = 0; k < N; k++) {
                        sum += mat1.get(i, k) * mat2.get(k, j);
                    }
                    result.set(i, j, sum);
                }
            }
            return result;
        }

        T determinant() const {
            if (M != N) {
                throw std::invalid_argument("Matrix is not square");
            }
            if (M == 1) {
                return get(0, 0);
            }
            if (M == 2) {
                return get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0);
            }
            if (M == 3) {
                return get(0, 0) * get(1, 1) * get(2, 2) + get(0, 1) * get(1, 2) * get(2, 0) + get(0, 2) * get(1, 0) * get(2, 1) - get(0, 2) * get(1, 1) * get(2, 0) - get(0, 1) * get(1, 0) * get(2, 2) - get(0, 0) * get(1, 2) * get(2, 1);
            }
            else {
                throw std::invalid_argument("Matrix is not 1x1, 2x2, or 3x3");
            }
        }

        Matrix<float, N, M> inverse() const {
            if (M != N) {
                throw std::invalid_argument("Matrix is not square");
            }
            float det = static_cast<float>(determinant());
            if (det == 0) {
                throw std::invalid_argument("Matrix is not invertible");
            }

            Matrix<float, N, M> result;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    // Calculate minor
                    float minor = 0.0f;
                    if (M == 2) {
                        minor = static_cast<float>(get((i + 1) % 2, (j + 1) % 2));
                    } else if (M == 3) {
                        // For 3x3, calculate the 2x2 minor
                        int rows[2], cols[2];
                        int r = 0, c = 0;
                        for (int k = 0; k < 3; k++) {
                            if (k != i) rows[r++] = k;
                            if (k != j) cols[c++] = k;
                        }
                        minor = static_cast<float>(get(rows[0], cols[0]) * get(rows[1], cols[1]) - 
                                get(rows[0], cols[1]) * get(rows[1], cols[0]));
                    }
                    
                    // Calculate cofactor with sign
                    float cofactor = minor;
                    if ((i + j) % 2 == 1) {
                        cofactor = -cofactor;
                    }
                    
                    // Set the transposed cofactor divided by determinant
                    result.set(j, i, cofactor / det);
                }
            }
            return result;
        }

        Matrix<T, N, M> transpose() const { 
            Matrix<T, N, M> result;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    result.set(j, i, get(i, j));
                }
            }
            return result;
        }

        Matrix<T, M, N> scalarMultiply(T scalar) const {
            Matrix<T, M, N> result;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    result.set(i, j, get(i, j) * scalar);
                }  
            }
            return result;
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix<T, M, N>& mat) {
            os << '[';
            for (int i = 0; i < M; i++) {
                os << '[';
                for (int j = 0; j < N; j++) {
                    os << mat.get(i, j);
                    if (j < N - 1) {
                        os << ", ";
                    }
                }
                os << ']';
                if (i < M - 1) {
                    os << ", ";
                }
            }
            os << ']';
            return os;
        }
};

#endif // MATRIX_H