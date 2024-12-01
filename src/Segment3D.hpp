#ifndef SEGMENT3D_HPP
#define SEGMENT3D_HPP

#include "Vector3D.hpp"

#include <ostream>

/*!
 * \brief Трёхмерный отрезок
 *
 * Задаётся двумя Vector3D.
 */
class Segment3D {
    Vector3D start_;
    Vector3D end_;
public:
    Segment3D(Vector3D& start, Vector3D& end);
    Segment3D(double sx, double sy, double sz,
              double ex, double ey, double ez);
    Segment3D(const Segment3D& other);
    Segment3D& operator=(const Segment3D& other);
    bool operator==(const Segment3D& other) const;
    bool operator!=(const Segment3D& other) const;
    //! Формат вывода: [start,end]
    friend std::ostream& operator<<(std::ostream& os, Segment3D& s);
    const Vector3D& getStart() const;
    const Vector3D& getEnd() const;
    void setStart(const Vector3D& start);
    void setStart(double x, double y, double z);
    void setEnd(const Vector3D& end);
    void setEnd(double x, double y, double z);
};

/*!
 * \brief Функция поиска точки пересечения отрезков
 * 
 * Если отрезки пересекаются, находит их единственную общую точку,
 * устанавливает её координаты в point и возвращает true. 
 * Если отрезки не пересекаются или имеют более одной общей точки, то
 * возвращает false и не меняет point.
 * 
 * \param[out] point Если отрезки имеют ровно одну общую точку, её координаты
 * записываются сюда
 * \param[in] lhs Первый отрезок
 * \param[in] lhs Второй отрезок
 * \return true, если найдена единственная общая точка отрезков, иначе - false
 */
bool intersect(Vector3D& point, const Segment3D& lhs, const Segment3D& rhs);

#endif