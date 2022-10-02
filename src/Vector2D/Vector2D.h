#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector2D {
    private:
        double x;
        double y;
    public:
        Vector2D();
        Vector2D(double x, double y);

        double getX() const;
        double getY() const;

        void setX(double value);
        void setY(double value);

        double len() const;
        void normalize();
        bool operator==(const Vector2D& other) const;
        bool operator!=(const Vector2D& other) const;
        void operator+=(const Vector2D& other);
        void operator-=(const Vector2D& other);
        void operator*=(const Vector2D& other);
        void operator*=(double scalar);
        void operator/=(const Vector2D& other);
        Vector2D operator+(const Vector2D& other);
        Vector2D operator-(const Vector2D& other);
        Vector2D operator*(const Vector2D& other);
        Vector2D operator*(double scalar) const;
        Vector2D operator/(const Vector2D& other);
};

std::ostream& operator<<(std::ostream& out, const Vector2D& vector);

#endif //VECTOR_H