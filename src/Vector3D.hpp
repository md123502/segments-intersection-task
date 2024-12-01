#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <ostream>

/*!
 * \brief Трёхмерный вектор
 *
 * Определяется тремя координатами: x, y, z.
 */
class Vector3D {
    double x_;
    double y_;
    double z_;
public:
    Vector3D();
    Vector3D(double x, double y, double z);
    Vector3D(const Vector3D& other);
    Vector3D& operator=(const Vector3D& other);
    bool operator==(const Vector3D& other) const;
    bool operator!=(const Vector3D& other) const;
    //! Формат вывода: <x, y, z>
    friend std::ostream& operator<<(std::ostream& os, Vector3D& v);
    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setCoords(double x, double y, double z);
};

#endif
