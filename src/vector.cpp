//
// Created by Conni Bilham on 10/07/2023.
//

#include <cmath>
#include "vector.h"

vector::vector(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

vector::vector(double x, double y) {
    this->x = x;
    this->y = y;
    this->z = 0;
}

vector::vector(double x) {
    this->x = x;
    this->y = 0;
    this->z = 0;
}

vector::vector() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

vector vector::operator+(const vector& other) const {
    return {
        this->x + other.x,
        this->y + other.y,
        this->z + other.z
    };
}

vector vector::operator-(const vector& other) const {
    return {
        this->x - other.x,
        this->y - other.y,
        this->z - other.z
    };
}

vector vector::operator*(const vector& other) const {
    return {
        this->x * other.x,
        this->y * other.y,
        this->z * other.z
    };
}

vector vector::operator/(const vector& other) const {
    return {
        this->x / other.x,
        this->y / other.y,
        this->z / other.z
    };
}

vector vector::operator+(const double& other) {
    return {
        this->x + other,
        this->y + other,
        this->z + other
    };
}

vector vector::operator-(const double& other) {
    return {
        this->x - other,
        this->y - other,
        this->z - other
    };
}

vector vector::operator*(const double& other) {
    return {
        this->x * other,
        this->y * other,
        this->z * other
    };
}

vector vector::operator/(const double& other) {
    return {
        this->x / other,
        this->y / other,
        this->z / other
    };
}

vector vector::operator+=(const vector& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

vector vector::operator-=(const vector& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

vector vector::operator*=(const vector& other) {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

vector vector::operator/=(const vector& other) {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

vector vector::operator+=(const double& other) {
    this->x += other;
    this->y += other;
    this->z += other;
    return *this;
}

vector vector::operator-=(const double& other) {
    this->x -= other;
    this->y -= other;
    this->z -= other;
    return *this;
}

vector vector::operator*=(const double& other) {
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
}

vector vector::operator/=(const double& other) {
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
}

bool vector::operator==(const vector& other) {
    return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool vector::operator!=(const vector& other) {
    return this->x != other.x || this->y != other.y || this->z != other.z;
}

double vector::magnitude() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

vector vector::normalize() {
    double mag = this->magnitude();
    return {
        this->x / mag,
        this->y / mag,
        this->z / mag
    };
}

double vector::dot(const vector& other) {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

vector vector::cross(const vector& other) {
    return {
        this->y * other.z - this->z * other.y,
        this->z * other.x - this->x * other.z,
        this->x * other.y - this->y * other.x
    };
}

vector vector::direction(const vector& other) {
    return (other - *this).normalize();
}