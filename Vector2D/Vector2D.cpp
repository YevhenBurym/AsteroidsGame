#include <iostream>
#include <cmath>
#include "Vector2D.h"

Vector2D::Vector2D() {
    this->x = 0;
    this->y = 0;
}

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

double Vector2D::getX() const {
    return this->x;
}

double Vector2D::getY() const {
    return this->y;
}

void Vector2D::setX(double value) {
    this->x = value;
}
void Vector2D::setY(double value) {
    this->y = value;
}

double Vector2D::len() const {
    return hypot(this->x, this->y);
}

bool Vector2D::operator==(const Vector2D& other) const {
    bool isEqual = this->x == other.getX() && this->y == other.getY();

    return isEqual; 
}

bool Vector2D::operator!=(const Vector2D& other) const {
    bool isNotEqual = this->x != other.getX() && this->y != other.getY();

    return isNotEqual; 
}

void Vector2D::operator+=(const Vector2D& other) {
    this->x += other.getX();
    this->y += other.getY();
}

void Vector2D::operator-=(const Vector2D& other) {
    this->x -= other.getX();
    this->y -= other.getY();
}

void Vector2D::operator*=(const Vector2D& other) {
    this->x *= other.getX();
    this->y *= other.getY();
}

void Vector2D::operator*=(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
}

void Vector2D::operator/=(const Vector2D& other) {
    this->x /= other.getX();
    this->y /= other.getY();
}

Vector2D Vector2D::operator+(const Vector2D& other) {
    Vector2D sum = *this;
    sum += other;

    return sum;
}

Vector2D Vector2D::operator-(const Vector2D& other) {
    Vector2D diff = *this;
    diff -= other;

    return diff;
}

Vector2D Vector2D::operator*(const Vector2D& other) {
    Vector2D mult = *this;
    mult *= other;

    return mult;
}

Vector2D Vector2D::operator/(const Vector2D& other) {
    Vector2D div = *this;
    div /= other;

    return div;
}

Vector2D Vector2D::operator*(double scalar) const {
    return {this->x * scalar, this->y * scalar};
}

void Vector2D::normalize() {
    double l = this->len();
    if ( l > 0) {
        (*this) *= (1 / l);
    }
}

std::ostream& operator<<(std::ostream& out, const Vector2D& vector) {
    out << "(" << vector.getX() << ", " << vector.getY() << ")";
    
    return out;
}