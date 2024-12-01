#include "Segment3D.hpp"

#include <ostream>

static bool getDot3DLineParam(double* t,
                              const double* dotCoords, 
                              const double* segStartCoords,
                              const double* segPVecCoords);

bool intersect(Vector3D& point, const Segment3D& lhs, const Segment3D& rhs) {
    /* 
     * Прямую, которой принадлежит отрезок,
     * можно представить в параметрической форме как систему
     *   --
     *  | x == x0 + p0 * t
     * <  y == y0 + p1 * t
     *  | z == z0 + p2 * t
     *   --
     * , где p - направляющий вектор.
     */
    
    const Vector3D& lhsStart = lhs.getStart();
    const Vector3D& lhsEnd = lhs.getEnd();
    const Vector3D& rhsStart = rhs.getStart();
    const Vector3D& rhsEnd = rhs.getEnd();
    constexpr size_t dims = 3;
    const double lhsStartC[dims] = {lhsStart.getX(), 
                                    lhsStart.getY(),
                                    lhsStart.getZ()};
    const double lhsEndC[dims] = {lhsEnd.getX(), 
                                  lhsEnd.getY(), 
                                  lhsEnd.getZ()};
    const double rhsStartC[dims] = {rhsStart.getX(), 
                                    rhsStart.getY(), 
                                    rhsStart.getZ()};
    const double rhsEndC[dims] = {rhsEnd.getX(), 
                                  rhsEnd.getY(), 
                                  rhsEnd.getZ()};

    double p0[dims] = {lhsEndC[0] - lhsStartC[0], 
                       lhsEndC[1] - lhsStartC[1], 
                       lhsEndC[2] - lhsStartC[2]};
    double p1[dims] = {rhsEndC[0] - rhsStartC[0], 
                       rhsEndC[1] - rhsStartC[1], 
                       rhsEndC[2] - rhsStartC[2]};

    /* 
     * Начнём с того, что, т.к в условии не сказано, что у Segment3D 
     * не могут совпадать начало и конец, отсеем случаи, когда это так.
     */
    const Vector3D* onlyDot = nullptr;
    const double* onlyDotC = nullptr;
    const double* onlySegmentStartC = nullptr;
    const double* onlySegmentPC = nullptr;

    if (rhsStart == rhsEnd) {
        if (lhsStart == lhsEnd) {
            if (rhsStart == lhsStart) {
                point = rhsStart;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            onlyDot = &rhsStart;
            onlyDotC = rhsStartC;
            onlySegmentStartC = lhsStartC;
            onlySegmentPC = p0;
        }
    }
    else if (lhsStart == lhsEnd) {
        onlyDot = &lhsStart;
        onlyDotC = lhsStartC;
        onlySegmentStartC = rhsStartC;
        onlySegmentPC = p1;
    }

    if (nullptr != onlyDotC) {
        double t;
        if (getDot3DLineParam(&t, onlyDotC, onlySegmentStartC, onlySegmentPC)) {
            if ((t > 0) && (t < 1)) {
                // Попадает именно на отрезок
                point = *onlyDot;
                return true;
            }
        }
        return false;
    }

    /* 
     * Приравняв x, y и z из систем, представляющих две прямых, 
     * и перенеся слагаемые между правыми и левыми частями, получим систему
     *   --
     *  | p00 * t - p10 * s == x10 - x00
     * <  p01 * t - p11 * s == y10 - y00
     *  | p02 * t - p12 * s == z10 - z00
     *   -- 
     * из трёх уравнений с двумя неизвестными.
     * 
     * Проверим существование решения. Прямые должны лежать 
     * в одной плоскости и при этом не быть параллельными или совпадающими.
     * 
     * При этом мы ищем пересечение отрезков, а не прямых, из-за чего 
     * существует краевой случай: совпадение концов отрезков, 
     * лежащих на одной прямой.
     */

    if ((p0[0] * p1[1] == p0[1] * p1[0]) &&
        (p0[1] * p1[2] == p0[2] * p1[1]) &&
        (p0[0] * p1[2] == p0[2] * p1[0])) {
        /*
         * Направляющие векторы коллинеарны. Проверим краевой случай.
         */
        if ((lhsStart == rhsStart)) {
            double t;
            if (getDot3DLineParam(&t, lhsEndC, rhsStartC, p1)) {
                if (t < 0) {
                    // Отрезки направлены в разные стороны
                    point = lhsStart;
                    return true;
                }
            }
            return false;
        }
        if ((lhsStart == rhsEnd)) {
            double t;
            if (getDot3DLineParam(&t, lhsEndC, rhsStartC, p1)) {
                if (t > 1) {
                    // Отрезки направлены в одну сторону
                    point = lhsStart;
                    return true;
                }
            }
            return false;
        }
        if ((lhsEnd == rhsStart)) {
            double t;
            if (getDot3DLineParam(&t, lhsStartC, rhsStartC, p1)) {
                if (t < 0) {
                    // Отрезки направлены в одну сторону
                    point = lhsEnd;
                    return true;
                }
            }
            return false;
        }
        if ((lhsEnd == rhsEnd)) {
            double t;
            if (getDot3DLineParam(&t, lhsStartC, rhsStartC, p1)) {
                if (t > 1) {
                    // Отрезки направлены в разные стороны
                    point = lhsEnd;
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    /*
     * Проверить нахождение в одной плоскости можно, 
     * вычислив смешанное произведение вектора, соединяющего две известные 
     * точки на разных прямых, и направляющих векторов.
     * | (x10 - x00)    (y10 - y00)     (z10 - z00) |
     * |    p00             p01             p02     |
     * |    p10             p11             p12     |
     */

    // b[] будет и вектором правых частей системы.
    double b[dims] = {rhsStartC[0] - lhsStartC[0], 
                      rhsStartC[1] - lhsStartC[1], 
                      rhsStartC[2] - lhsStartC[2]};

    double prod = b[0] * (p0[1] * p1[2] - p0[2] * p1[1]) +
                  b[1] * (p0[2] * p1[0] - p0[0] * p1[2]) +
                  b[2] * (p0[0] * p1[1] - p0[1] * p1[0]);
    
    if (0 != prod) {
        return false;
    }

    /* 
     * Т.о., решение существует и единственно. 
     * Осталось решить систему.
     * Можно обойти её расширенную матрицу методом Гаусса, но более эффективно
     * будет воспользоваться методом Крамера, убрав одно из уравнений.
     * Однако придётся учесть, что пересекающиеся прямые не обязаны
     * иметь пересекающиеся проекции на все координатные плоскости,
     * проекции на одну или даже две могут совпадать. 
     * Тем не менее, не на все три. По крайней мере один из трёх определителей
     * не будет нулевым.
     */
    
    const double sysExtendedMatrix[dims][dims] = {
        {p0[0], -p1[0], b[0]},
        {p0[1], -p1[1], b[1]},
        {p0[2], -p1[2], b[2]}
    };

    size_t excludedIdx;
    double det = 0;
    for (size_t i = 0; i < dims; ++i) {
        det = sysExtendedMatrix[(i + 1) % dims][0] *
              sysExtendedMatrix[(i + 2) % dims][1] -
              sysExtendedMatrix[(i + 1) % dims][1] *
              sysExtendedMatrix[(i + 2) % dims][0];
        if (0 != det) {
            excludedIdx = i;
            break;
        }
    }

    double coeff = 1 / det;
    double t = coeff * (sysExtendedMatrix[(excludedIdx + 1) % dims][2] *
                        sysExtendedMatrix[(excludedIdx + 2) % dims][1] -
                        sysExtendedMatrix[(excludedIdx + 1) % dims][1] *
                        sysExtendedMatrix[(excludedIdx + 2) % dims][2]);

    double s = coeff * (sysExtendedMatrix[(excludedIdx + 1) % dims][0] *
                        sysExtendedMatrix[(excludedIdx + 2) % dims][2] -
                        sysExtendedMatrix[(excludedIdx + 1) % dims][2] *
                        sysExtendedMatrix[(excludedIdx + 2) % dims][0]);

    // Проверим, что пересечение прямых принадлежит отрезкам
    if ((0 > t) || (1 < t) || (0 > s) || (1 < s)) {
        return false;
    }

    point.setCoords(lhsStartC[0] + p0[0] * t, lhsStartC[1] + p0[1] * t, lhsStartC[2] + p0[2] * t);

    return true;
}

static bool getDot3DLineParam(double* t,
                              const double* dotCoords, 
                              const double* segStartCoords,
                              const double* segPVecCoords) {
    double tFound;
    bool tIsFound = false;
    bool dotIsOnSegment = true;
    for (size_t i = 0; i < 3; ++i) {
        if (0 == segPVecCoords[i]) {
            if (segStartCoords[i] != dotCoords[i]) {
                dotIsOnSegment = false;
                break;
            }
        }
        else {
            double curT = (dotCoords[i] - segStartCoords[i]) / segPVecCoords[i];
            if (!tIsFound) {
                tFound = curT;
                tIsFound = true;
            }
            else {
                if (tFound != curT) {
                    dotIsOnSegment = false;
                    break;
                }
            }
        }
    }
    *t = tFound;
    return dotIsOnSegment;
}

std::ostream& operator<<(std::ostream& os, Segment3D& s) {
    os << "[" << s.start_ << ", " << s.end_ << "]";
    return os;
}

Segment3D::Segment3D(Vector3D& start, Vector3D& end) 
    : start_(start)
    , end_(end)
    {}

Segment3D::Segment3D(double sx, double sy, double sz, 
                     double ex, double ey, double ez) 
    : start_(sx, sy, sz)
    , end_(ex, ey, ez)
    {}

Segment3D::Segment3D(const Segment3D& other)
    : start_(other.start_)
    , end_(other.end_)
    {}

Segment3D& Segment3D::operator=(const Segment3D& other) {
    if (this == &other) {
        return *this;
    }
    start_ = other.start_;
    end_ = other.end_;
    return *this;
}

bool Segment3D::operator==(const Segment3D& other) const {
    if (this == &other) {
        return true;
    }
    return ((start_ == other.start_) && (end_ == other.end_));
}

bool Segment3D::operator!=(const Segment3D& other) const {
    return !(*this == other);
}

const Vector3D& Segment3D::getStart() const {
    return start_;
}

const Vector3D& Segment3D::getEnd() const {
    return end_;
}

void Segment3D::setStart(const Vector3D& start) {
    start_ = start;
}

void Segment3D::setStart(double x, double y, double z) {
    start_.setCoords(x, y, z);
}

void Segment3D::setEnd(const Vector3D& end) {
    end_ = end;
}

void Segment3D::setEnd(double x, double y, double z) {
    end_.setCoords(x, y, z);
}
