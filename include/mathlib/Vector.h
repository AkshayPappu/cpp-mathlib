// vector class with dot product, cross product, magnitude, normalization, and scalar multiplication

#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <vector>
#include "Matrix.h"

template <typename T, int N>
class Vector {
    private:
        T* data;
        int size;
    public:
        Vector() {
            size = N;
            data = new T[size];
            for (int i = 0; i < size; i++) {
                data[i] = T();
            }
        }

        Vector(std::initializer_list<T> list) {
            size = N;
            data = new T[size];
            int i = 0;
            for (const auto& element : list) {
                if (i < size) {
                    data[i++] = element;
                }
            }
        }

        Vector(const T arr[]) {
            size = N;
            data = new T[size];
            for (int i = 0; i < size; i++) {
                data[i] = arr[i];
            }
        }

        // Copy constructor
        Vector(const Vector& other) {
            size = other.size;
            data = new T[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }

        // Assignment operator
        Vector& operator=(const Vector& other) {
            if (this != &other) {
                delete[] data;
                size = other.size;
                data = new T[size];
                for (int i = 0; i < size; i++) {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }

        ~Vector() {
            delete[] data;
        }

        T getSize() const {
            return this->size;
        }

        T get(int index) const {
            if (index < 0 || index >= this->getSize()) {
                throw std::runtime_error("Index out of bounds");
            }
            return this->data[index];
        }

        void set(int index, T value) {
            if (index < 0 || index >= this->getSize()) {
                throw std::runtime_error("Index out of bounds");
            }
            this->data[index] = value;
        }

        template <typename U, int M>
        friend std::ostream& operator<<(std::ostream& os, const Vector<T, N>& vec);

        template <typename U>
        auto dotProduct(const Vector<U, N>& other) const {
            if (this->getSize() != other.getSize()) {
                throw std::runtime_error("Vectors must be of the same size");
            }
            auto result = 0;
            for (int i = 0; i < this->getSize(); i++) {
                result += this->get(i) * other.get(i);
            }
            return result;
        }

        template <typename U>
        auto crossProduct(const Vector<U, N>& other) const {
            if (this->getSize() != other.getSize() || this->getSize() != 3) {
                throw std::runtime_error("Vectors must be of the same size");
            }
            auto result = Vector<decltype(this->get(0) * other.get(0)), N>{0, 0, 0};
            result.set(0, this->get(1) * other.get(2) - this->get(2) * other.get(1));
            result.set(1, this->get(2) * other.get(0) - this->get(0) * other.get(2));
            result.set(2, this->get(0) * other.get(1) - this->get(1) * other.get(0));
            return result;
        }

        T magnitude() const {
            T result = 0;
            for (int i = 0; i < this->getSize(); i++) {
                result += this->get(i) * this->get(i);
            }
            return std::sqrt(result);
        }

        auto normalize() const {
            T mag = this->magnitude();
            T new_data[N] = {};
            auto result = Vector<decltype(this->get(0) / mag), N>(new_data);
            for (int i = 0; i < this->getSize(); i++) {
                result.set(i, this->get(i) / mag);
            }
            return result;
        }

        template <typename U>
        Vector<T, N>& scalarMultiply(U scalar) {
            for (int i = 0; i < this->getSize(); i++) {
                this->set(i, this->get(i) * scalar);
            }
            return *this;
        }

        // multiplication of a matrix and a vector
        template <typename U, int P>
        auto multiply(const Matrix<U, N, P>& matrix) const {
            Vector<decltype(this->get(0) * matrix.get(0, 0)), P> result;
            for (int i = 0; i < P; i++) {
                T sum = T();
                for (int j = 0; j < N; j++) {
                    sum += this->get(j) * matrix.get(j, i);
                }
                result.set(i, sum);
            }
            return result;
        }
};

// Implementation of operator<<
template <typename T, int N>
std::ostream& operator<<(std::ostream& os, const Vector<T, N>& vec) {
    os << "[";
    for (int i = 0; i < N; i++) {
        os << vec.get(i);
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif // VECTOR_H