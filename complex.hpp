#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }

    void setReal(double real) { this->real = real; }
    void setImag(double imag) { this->imag = imag; }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    bool operator<(const Complex& other) const {
        return (real < other.real) || (real == other.real && imag < other.imag);
    }
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }
};

#endif // COMPLEX_HPP

