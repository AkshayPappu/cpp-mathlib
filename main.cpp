#include <iostream>
#include "mathlib/Matrix.h"
#include "mathlib/Vector.h"
#include "mathlib/Arithmetic.h"

int main() {
    std::cout << "=== Matrix Examples ===\n\n";

    // Matrix initialization
    std::cout << "1. Matrix Initialization:\n";
    Matrix<int, 2, 2> A{{1, 2}, {3, 4}};
    Matrix<int, 2, 2> B{{5, 6}, {7, 8}};
    std::cout << "Matrix A:\n" << A << "\n";
    std::cout << "Matrix B:\n" << B << "\n\n";

    // Matrix addition
    std::cout << "2. Matrix Addition:\n";
    Matrix<int, 2, 2> C = A + B;
    std::cout << "A + B:\n" << C << "\n\n";

    // Matrix subtraction
    std::cout << "3. Matrix Subtraction:\n";
    Matrix<int, 2, 2> D = A - B;
    std::cout << "A - B:\n" << D << "\n\n";

    // Matrix multiplication
    std::cout << "4. Matrix Multiplication:\n";
    Matrix<int, 2, 2> E = A * B;
    std::cout << "A * B:\n" << E << "\n\n";

    // Matrix transpose
    std::cout << "5. Matrix Transpose:\n";
    Matrix<int, 2, 2> F = A.transpose();
    std::cout << "A^T:\n" << F << "\n\n";

    // Matrix determinant
    std::cout << "6. Matrix Determinant:\n";
    std::cout << "det(A) = " << A.determinant() << "\n\n";

    // Matrix inverse
    std::cout << "7. Matrix Inverse:\n";
    Matrix<float, 2, 2> G{{1.0f, 2.0f}, {3.0f, 4.0f}};
    try {
        Matrix<float, 2, 2> H = G.inverse();
        std::cout << "G^-1:\n" << H << "\n\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n\n";
    }

    std::cout << "=== Vector Examples ===\n\n";

    // Vector initialization
    std::cout << "1. Vector Initialization:\n";
    Vector<int, 3> v1{1, 2, 3};
    Vector<int, 3> v2{4, 5, 6};
    std::cout << "Vector v1: " << v1 << "\n";
    std::cout << "Vector v2: " << v2 << "\n\n";

    // Vector scalar multiplication
    std::cout << "2. Vector Scalar Multiplication:\n";
    Vector<int, 3> v3 = v1;
    v3.scalarMultiply(2);
    std::cout << "v1 * 2: " << v3 << "\n\n";

    // Vector dot product
    std::cout << "3. Dot Product:\n";
    auto dot = v1.dotProduct(v2);
    std::cout << "v1 · v2 = " << dot << "\n\n";

    // Cross product (3D only)
    std::cout << "4. Cross Product (3D):\n";
    auto v4 = v1.crossProduct(v2);
    std::cout << "v1 × v2: " << v4 << "\n\n";

    // Vector magnitude
    std::cout << "5. Vector Magnitude:\n";
    std::cout << "|v1| = " << v1.magnitude() << "\n\n";

    // Vector normalization
    std::cout << "6. Vector Normalization:\n";
    Vector<double, 3> v5{1.0, 2.0, 3.0};
    auto v6 = v5.normalize();
    std::cout << "v5 normalized: " << v6 << "\n";
    std::cout << "Magnitude of normalized vector: " << v6.magnitude() << "\n\n";

    // Matrix-Vector multiplication
    std::cout << "7. Matrix-Vector Multiplication:\n";
    Vector<int, 2> v7{1, 2};
    Matrix<int, 2, 2> M{{1, 2}, {3, 4}};
    auto v8 = v7.multiply(M);
    std::cout << "v7 * M: " << v8 << "\n";

    return 0;
}