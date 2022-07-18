#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    private:
        double x;
        double y;
    public:
        Vector();
        Vector(double x, double y);

        double getX() const;
        double getY() const;

        void setX(double value);
        void setY(double value);

        double len() const;
        void normalize();
        bool operator==(const Vector& other) const;
        bool operator!=(const Vector& other) const;
        void operator+=(const Vector& other);
        void operator-=(const Vector& other);
        void operator*=(const Vector& other);
        void operator*=(double scalar);
        void operator/=(const Vector& other);
        Vector operator+(const Vector& other);
        Vector operator-(const Vector& other);
        Vector operator*(const Vector& other);
        Vector operator*(double scalar) const;
        Vector operator/(const Vector& other);
};

std::ostream& operator<<(std::ostream& out, const Vector& vector);

#endif //VECTOR_H