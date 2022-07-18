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
        void scale(double k);
        bool operator==(const Vector& other) const;
        bool operator!=(const Vector& other) const;
        Vector& operator+=(const Vector& other);
        Vector& operator-=(const Vector& other);
        Vector& operator*=(const Vector& other);
        Vector& operator/=(const Vector& other);
        Vector operator+(const Vector& other);
        Vector operator-(const Vector& other);
        Vector operator*(const Vector& other);
        Vector operator/(const Vector& other);
};

std::ostream& operator<<(std::ostream& out, const Vector& vector);

#endif //VECTOR_H