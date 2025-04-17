# C++ Math Library

A templated C++ library for matrix and vector operations, providing efficient and type-safe mathematical computations.

## Features

- Matrix operations:
  - Addition and subtraction
  - Matrix multiplication
  - Transpose
  - Determinant (for 1x1, 2x2, and 3x3 matrices)
  - Inverse (for 2x2 and 3x3 matrices)
  - Scalar multiplication

- Vector operations:
  - Dot product
  - Cross product (for 3D vectors)
  - Magnitude calculation
  - Normalization
  - Scalar multiplication
  - Matrix-vector multiplication

## Installation

```bash
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
```

## Usage

### Including Headers

```cpp
#include <mathlib/Matrix.h>
#include <mathlib/Vector.h>
```

### Matrix Operations

```cpp
// Matrix initialization
Matrix<int, 2, 2> A{{1, 2}, {3, 4}};
Matrix<int, 2, 2> B{{5, 6}, {7, 8}};

// Matrix addition
Matrix<int, 2, 2> C = A + B;  // Result: [[6, 8], [10, 12]]

// Matrix subtraction
Matrix<int, 2, 2> D = A - B;  // Result: [[-4, -4], [-4, -4]]

// Matrix multiplication
Matrix<int, 2, 2> E = A * B;  // Result: [[19, 22], [43, 50]]

// Matrix transpose
Matrix<int, 2, 2> F = A.transpose();  // Result: [[1, 3], [2, 4]]

// Matrix determinant
int det = A.determinant();  // Result: -2

// Matrix inverse (returns float matrix)
Matrix<float, 2, 2> G{{1.0f, 2.0f}, {3.0f, 4.0f}};
Matrix<float, 2, 2> H = G.inverse();  // Result: [[-2, 1], [1.5, -0.5]]
```

### Vector Operations

```cpp
// Vector initialization
Vector<int, 3> v1{1, 2, 3};
Vector<int, 3> v2{4, 5, 6};

// Scalar multiplication
v1.scalarMultiply(2);  // Result: [2, 4, 6]

// Dot product
auto dot = v1.dotProduct(v2);  // Result: 32

// Cross product (3D only)
auto cross = v1.crossProduct(v2);  // Result: [-3, 6, -3]

// Vector magnitude
auto mag = v1.magnitude();  // Result: 3

// Vector normalization
Vector<double, 3> v3{1.0, 2.0, 3.0};
auto normalized = v3.normalize();  // Result: [0.267261, 0.534522, 0.801784]

// Matrix-vector multiplication
Vector<int, 2> v4{1, 2};
Matrix<int, 2, 2> M{{1, 2}, {3, 4}};
auto result = v4.multiply(M);  // Result: [7, 10]
```

### Template Parameters

- Matrix template parameters:
  - `T`: Data type (int, float, double, etc.)
  - `M`: Number of rows
  - `N`: Number of columns

- Vector template parameters:
  - `T`: Data type (int, float, double, etc.)
  - `N`: Vector dimension

## CMake Integration

To use this library in your CMake project:

```cmake
find_package(mathlib REQUIRED)
target_link_libraries(your_target PRIVATE mathlib::mathlib)
```

## Error Handling

The library includes error checking for:
- Matrix dimensions in operations
- Vector dimensions in operations
- Index bounds checking
- Matrix invertibility
- Vector cross product dimensions

## Notes

- The library uses dynamic memory allocation for vectors
- Matrix storage is stack-based using fixed-size arrays
- Matrix inverse operations return float matrices for numerical stability
- Determinant and inverse operations are supported for matrices up to 3x3

## Contributing

Feel free to submit issues and enhancement requests!
