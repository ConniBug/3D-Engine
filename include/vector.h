//
// Created by Conni Bilham on 10/07/2023.
//

#ifndef INC_2D_ENGINE_VECTOR_H
#define INC_2D_ENGINE_VECTOR_H

class vector {

public:
    double x, y, z;

    vector(double x, double y, double z);
    vector(double x, double y);
    vector(double x);
    vector();

    vector operator+(const vector& other) const;
    vector operator-(const vector& other) const;
    vector operator*(const vector& other) const;
    vector operator/(const vector& other) const;

    vector operator+(const double& other);
    vector operator-(const double& other);
    vector operator*(const double& other);
    vector operator/(const double& other);

    vector operator+=(const vector& other);
    vector operator-=(const vector& other);
    vector operator*=(const vector& other);
    vector operator/=(const vector& other);

    vector operator+=(const double& other);
    vector operator-=(const double& other);
    vector operator*=(const double& other);
    vector operator/=(const double& other);

    bool operator==(const vector& other);
    bool operator!=(const vector& other);

    double magnitude();
    vector normalize();
    double dot(const vector& other);
    vector cross(const vector& other);

    vector direction(const vector& other);
};


#endif //INC_2D_ENGINE_VECTOR_H
