#include "Vector3D.hpp"

Vector3D::Vector3D() 
    : x_(0)
    , y_(0)
    , z_(0)
    {}

Vector3D::Vector3D(double x, double y, double z) 
    : x_(x)
    , y_(y)
    , z_(z)
    {}

Vector3D::Vector3D(const Vector3D& other)
    : x_(other.x_)
    , y_(other.y_)
    , z_(other.z_)
    {}

Vector3D& Vector3D::operator=(const Vector3D& other) {
    if (this == &other) {
        return *this;
    }
    x_ = other.x_;
    y_ = other.y_;
    z_ = other.z_;
    return *this;
}

bool Vector3D::operator==(const Vector3D& other) const {
    if (this == &other) {
        return true;
    }
    return ((x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_));
}

bool Vector3D::operator!=(const Vector3D& other) const {
    return !(*this == other);
}

double Vector3D::getX() const {
    return x_;
}

double Vector3D::getY() const {
    return y_;
}

double Vector3D::getZ() const { 
    return z_; 
}

void Vector3D::setX(double x) {
    x_ = x;
}

void Vector3D::setY(double y) {
    y_ = y;
}

void Vector3D::setZ(double z) {
    z_ = z;
}

void Vector3D::setCoords(double x, double y, double z) {
    x_ = x;
    y_ = y;
    z_ = z;
}

std::ostream& operator<<(std::ostream& os, Vector3D& v) {
    os << "<" << v.x_ << ", " << v.y_ << ", " << v.z_ << ">";
    return os;
}
