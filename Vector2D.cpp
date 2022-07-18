#include <iostream>
#include <cmath>
#include "Vector2D.h"

Vector::Vector() {
    this->x = 0;
    this->y = 0;
}

Vector::Vector(double x, double y) {
    this->x = x;
    this->y = y;
}

double Vector::getX() const {
    return this->x;
}

double Vector::getY() const {
    return this->y;
}

void Vector::setX(double value) {
    this->x = value;
}
void Vector::setY(double value) {
    this->y = value;
}

double Vector::len() const {
    return hypot(this->x, this->y);
}

bool Vector::operator==(const Vector& other) const {
    bool isEqual = this->x == other.getX() && this->y == other.getY();

    return isEqual; 
}

bool Vector::operator!=(const Vector& other) const {
    bool isNotEqual = this->x != other.getX() && this->y != other.getY();

    return isNotEqual; 
}

void Vector::operator+=(const Vector& other) {
    this->x += other.getX();
    this->y += other.getY();
}

void Vector::operator-=(const Vector& other) {
    this->x -= other.getX();
    this->y -= other.getY();
}

void Vector::operator*=(const Vector& other) {
    this->x *= other.getX();
    this->y *= other.getY();
}

void Vector::operator*=(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
}

void Vector::operator/=(const Vector& other) {
    this->x /= other.getX();
    this->y /= other.getY();
}

Vector Vector::operator+(const Vector& other) {
    Vector sum = *this;
    sum += other;

    return sum;
}

Vector Vector::operator-(const Vector& other) {
    Vector diff = *this;
    diff -= other;

    return diff;
}

Vector Vector::operator*(const Vector& other) {
    Vector mult = *this;
    mult *= other;

    return mult;
}

Vector Vector::operator/(const Vector& other) {
    Vector div = *this;
    div /= other;

    return div;
}

Vector Vector::operator*(double scalar) const {
    return {this->x * scalar, this->y * scalar};
}

void Vector::normalize() {
    double l = this->len();
    if ( l > 0) {
        (*this) *= (1 / l);
    }
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
    out << "(" << vector.getX() << ", " << vector.getY() << ")";
    
    return out;
}