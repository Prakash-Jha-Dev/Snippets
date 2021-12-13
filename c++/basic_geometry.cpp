/// Name: BasicGeometry
/// Description: Implementation of Point, Line and basic geometrical operations
/// Detail: Maths, Geometry
/// Guarantee: } // BasicGeometry


// structure of Point and basic operations like +,-,*,/
template <class F>
struct Point
{
    F x, y;
    Point() : x(0), y(0) {}
    Point(const F &x, const F &y) : x(x), y(y) {}

    void swap(Point &other)
    {
        using std::swap;
        swap(x, other.x);
        swap(y, other.y);
    }

    template <class F1>
    explicit operator Point<F1>() const
    {
        return Point<F1>(static_cast<F1>(x), static_cast<F1>(y));
    }

    template <class F1>
    Point &operator=(const Point<F1> &other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    template <class F1>
    Point &operator+=(const Point<F1> &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    template <class F1>
    Point &operator-=(const Point<F1> &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    template <class F1>
    Point &operator*=(const F1 &factor)
    {
        x *= factor;
        y *= factor;
        return *this;
    }

    template <class F1>
    Point &operator/=(const F1 &factor)
    {
        x /= factor;
        y /= factor;
        return *this;
    }
};

// input for point
template <class F>
istream &operator>>(istream &is, Point<F> &point)
{
    return is >> point.x >> point.y;
}

// output for point
template <class F>
ostream &operator<<(ostream &os, const Point<F> &point)
{
    return os << point.x << ' ' << point.y;
}

template <class F>
inline Point<F> makePoint(const F &x, const F &y) { return Point<F>(x, y); }

template <class F>
void swap(Point<F> &lhs, Point<F> &rhs) { lhs.swap(rhs); }

#define FUNC1(name, arg, expr) \
    template <class F>         \
    inline auto name(const arg)->decltype(expr) { return expr; }
#define FUNC2(name, arg1, arg2, expr) \
    template <class F1, class F2>     \
    inline auto name(const arg1, const arg2)->decltype(expr) { return expr; }
#define FUNC3(name, arg1, arg2, arg3, expr) \
    template <class F1, class F2, class F3> \
    inline auto name(const arg1, const arg2, const arg3)->decltype(expr) { return expr; }

FUNC1(operator-, Point<F> &point, makePoint(-point.x, -point.y))
FUNC2(operator+, Point<F1> &lhs, Point<F2> &rhs, makePoint(lhs.x + rhs.x, lhs.y + rhs.y))
FUNC2(operator-, Point<F1> &lhs, Point<F2> &rhs, makePoint(lhs.x - rhs.x, lhs.y - rhs.y))
FUNC2(operator*, F1 &factor, Point<F2> &rhs, makePoint(factor *rhs.x, factor *rhs.y))
FUNC2(operator*, Point<F1> &lhs, F2 &factor, makePoint(lhs.x *factor, lhs.y *factor))
FUNC2(operator/, Point<F1> &lhs, F2 &factor, makePoint(lhs.x / factor, lhs.y / factor))

FUNC2(operator*, Point<F1> &lhs, Point<F2> &rhs, lhs.x *rhs.x + lhs.y *rhs.y)
FUNC2(operator^, Point<F1> &lhs, Point<F2> &rhs, lhs.x *rhs.y - lhs.y *rhs.x)

// < 0 if clockwise, 0 if collinear, > 0 if counter-clockwise.
FUNC2(ccw, Point<F1> &lhs, Point<F2> &rhs, lhs ^ rhs)
FUNC3(ccw, Point<F1> &lhs, Point<F2> &rhs, Point<F3> &origin, ccw(lhs - origin, rhs - origin))

FUNC2(operator==, Point<F1> &lhs, Point<F2> &rhs, lhs.x == rhs.x &&lhs.y == rhs.y)
FUNC2(operator!=, Point<F1> &lhs, Point<F2> &rhs, !(lhs == rhs))

FUNC2(operator<, Point<F1> &lhs, Point<F2> &rhs,
      lhs.y<rhs.y ||(lhs.y == rhs.y && lhs.x < rhs.x))
FUNC2(operator>, Point<F1> &lhs, Point<F2> &rhs, rhs<lhs)
FUNC2(operator<=, Point<F1> &lhs, Point<F2> &rhs, !(lhs > rhs))
FUNC2(operator>=, Point<F1> &lhs, Point<F2> &rhs, !(lhs < rhs))

// Angles and rotations (counter-clockwise).
// NOTE: Returns an angle in (-PI,PI]
FUNC1(angle, Point<F> &point, atan2(point.y, point.x))
FUNC2(angle, Point<F1> &lhs, Point<F2> &rhs, atan2(lhs ^ rhs, lhs *rhs))
FUNC3(angle, Point<F1> &lhs, Point<F2> &rhs, Point<F3> &origin,
      angle(lhs - origin, rhs - origin))
FUNC3(rotate, Point<F1> &point, F2 &angleSin, F3 &angleCos,
      makePoint(angleCos *point.x - angleSin * point.y,
                angleSin *point.x + angleCos * point.y))
FUNC2(rotate, Point<F1> &point, F2 &angle, rotate(point, sin(angle), cos(angle)))
FUNC3(rotate, Point<F1> &point, F2 &angle, Point<F3> &origin,
      origin + rotate(point - origin, angle))
FUNC1(perp, Point<F> &point, makePoint(-point.y, point.x))

// Distances.
FUNC1(abs, Point<F> &point, point *point)
FUNC1(norm, Point<F> &point, sqrt(abs(point)))
FUNC2(dist, Point<F1> &lhs, Point<F2> &rhs, norm(lhs - rhs))
FUNC2(dist2, Point<F1> &lhs, Point<F2> &rhs, abs(lhs - rhs))
// Point(Vector) at equal angle from other two point(vector). Paralellogram technique.
FUNC2(bisector, Point<F1> &lhs, Point<F2> &rhs, lhs *norm(rhs) + rhs * norm(lhs))

#undef FUNC1
#undef FUNC2
#undef FUNC3

// stores line equation in parametric form: a + t*vector(ab)
// a() and b() defines end-point of segment
template <class F>
struct Line
{
    Point<F> a, ab;
    Line() : a(), ab() {}
    Line(const Point<F> &a, const Point<F> &b, bool twoPoints = true)
        : a(a), ab(twoPoints ? b - a : b) {}
    Line(const F &xa, const F &ya, const F &xb, const F &yb)
        : a(xa, ya), ab(xb - xa, yb - ya) {}

    void swap(Line &other)
    {
        using std::swap;
        swap(a, other.a);
        swap(ab, other.ab);
    }
    template <class F1>
    explicit operator Line<F1>() const
    {
        return Line<F1>(Point<F1>(a), Point<F1>(ab), false);
    }
    template <class F1>
    Line &operator=(const Line<F1> &other)
    {
        a = other.a;
        ab = other.ab;
        return *this;
    }

    Point<F> b() const { return a + ab; }
    operator bool() const { return ab != Point<F>(); }

    template <typename T>
    long double get_y(T x)
    {
        if (abs(ab.x) < 1e-6)
            return INFINITY;
        long double t = (x - a.x) / ab.x;
        return (ab.y * t + a.y);
    }

    template <typename T>
    long double get_x(T y)
    {
        if (abs(ab.y) < 1e-6)
            return INFINITY;
        long double t = (y - a.y) / ab.y;
        return (ab.x * t + a.x);
    }
};

// input for line
template <class F>
istream &operator>>(istream &is, Line<F> &line)
{
    Point<F> p1, p2;
    is >> p1 >> p2;
    line = Line<F>(p1, p2);
}

// output for line
template <class F>
ostream &operator<<(ostream &os, const Line<F> &line)
{
    return os << line.a << ' ' << line.ab;
}

template <class F>
inline Line<F> makeLine(const Point<F> &a, const Point<F> &b, bool twoPoints = true)
{
    return Line<F>(a, b, twoPoints);
}

template <class F>
void swap(Line<F> &lhs, Line<F> &rhs) { lhs.swap(rhs); }

// checks if given point lies on given line
template <class F1, class F2>
bool onLine(const Point<F1> &point, const Line<F2> &line)
{
    if (!line)
        return point == line.a;
    return ((point - line.a) ^ line.ab) == 0;
}

template <class F1, class F2>
using distF = decltype(sqrt(F1() + F2()));

// minimum distance of point from line
template <class F1, class F2>
distF<F1, F2> distLine(const Point<F1> &point, const Line<F2> &line)
{
    if (!line)
        return dist(point, line.a);
    return abs((point - line.a) ^ line.ab) / norm(line.ab);
}

// minimum distance of point from line-segment [a,b]
template <class F1, class F2>
distF<F1, F2> distSegment(const Point<F1> &point, const Line<F2> &seg)
{
    if (((point - seg.a) * seg.ab) <= 0)
        return dist(point, seg.a);
    if (((point - seg.b()) * seg.ab) >= 0)
        return dist(point, seg.b());
    return distLine(point, seg);
}

// point on line obtained by projection of given point on given line
// also the closest point on line from given point
template <class F1, class F2, class F3>
void projection(const Point<F1> &point, const Line<F2> &line, Point<F3> &res)
{
    res = line.a;
    if (line)
        res += line.ab * static_cast<F3>((point - line.a) * line.ab) / abs(line.ab);
}

// point obtained by reflecting given point across given line
template <class F1, class F2, class F3>
void reflection(const Point<F1> &point, const Line<F2> &line, Point<F3> &res)
{
    projection(point, line, res);
    res = 2 * res - point;
}

// closest point on line-segement [a,b] from given point
template <class F1, class F2, class F3>
void closest(const Point<F1> &point, const Line<F2> &seg, Point<F3> &res)
{
    if (((point - seg.a) * seg.ab) <= 0)
        res = seg.a;
    else if (((point - seg.b()) * seg.ab) >= 0)
        res = seg.b();
    else
        projection(point, seg, res);
}

template <int TYPE>
struct EndpointChecker
{
};

// no endpoint (ray)
template <>
struct EndpointChecker<0>
{
    template <class F>
    bool operator()(const F &a, const F &b) const { return true; }
};

// closed endpoint
template <>
struct EndpointChecker<1>
{
    template <class F>
    bool operator()(const F &a, const F &b) const { return a <= b; }
};

// open endpoint
template <>
struct EndpointChecker<2>
{
    template <class F>
    bool operator()(const F &a, const F &b) const { return a < b; }
};

// gives the point of intersection of two lines
// let p be point of intesection, then <c1,c2,c3,c4>
// c1 : is p bounded by l1.a
// c2 : is p bounded by l1.b
// c3 : is p bounded by l2.a
// c4 : is p bounded by l2.b
// to intersect lines : <0,0,0,0>
// to intersect line-segment : <1,1,1,1>
// to intersect rays [a1,inf) [a2,inf) : <1,0,1,0>
// to intersect rays (a1,inf) (a2,inf) : <2,0,2,0>
template <int LA, int LB, int RA, int RB, class F1, class F2, class F3>
bool intersectLines(const Line<F1> &lhs, const Line<F2> &rhs, Point<F3> &res)
{
    assert(lhs && rhs);
    auto s = lhs.ab ^ rhs.ab;
    if (s == 0)
        return false;
    auto ls = (rhs.a - lhs.a) ^ rhs.ab;
    auto rs = (rhs.a - lhs.a) ^ lhs.ab;
    if (s < 0)
        s = -s, ls = -ls, rs = -rs;
    bool intersect =
        EndpointChecker<LA>()(decltype(ls)(0), ls) && EndpointChecker<LB>()(ls, s) &&
        EndpointChecker<RA>()(decltype(rs)(0), rs) && EndpointChecker<RB>()(rs, s);
    if (intersect)
        res = lhs.a + lhs.ab * static_cast<F3>(ls) / s;
    return intersect;
}

// gives the point of intersection of two line-segment
template <class F1, class F2, class F3>
bool intersectClosedSegments(const Line<F1> &lhs, const Line<F2> &rhs, Point<F3> &res)
{
    return intersectLines<1, 1, 1, 1>(lhs, rhs, res);
}

// intersecting line-segement between two line-segment
template <class F1, class F2, class F3>
bool intersectSegments(const Line<F1> &lhs, const Line<F2> &rhs, Line<F3> &res)
{
    auto s = lhs.ab ^ rhs.ab;
    auto ls = (rhs.a - lhs.a) ^ rhs.ab;
    if (s == 0)
    {
        if (ls != 0)
            return false;
        auto lhsa = lhs.a, lhsb = lhs.b();
        auto rhsa = rhs.a, rhsb = rhs.b();
        if (lhsa > lhsb)
            swap(lhsa, lhsb);
        if (rhsa > rhsb)
            swap(rhsa, rhsb);
        res = Line<F3>(max(lhsa, rhsa), min(lhsb, rhsb));
        return res.ab >= Point<F3>();
    }
    auto rs = (rhs.a - lhs.a) ^ lhs.ab;
    if (s < 0)
        s = -s, ls = -ls, rs = -rs;
    bool intersect = 0 <= ls && ls <= s && 0 <= rs && rs <= s;
    if (intersect)
        res = Line<F3>(lhs.a + lhs.ab * static_cast<F3>(ls) / s, Point<F3>());
    return intersect;
}

// struct for comparison of angles between points w.r.t. origin
template <class F>
struct AngleCompare
{
    const Point<F> origin;
    const bool zero;

    AngleCompare(const Point<F> &origin = Point<F>())
        : origin(origin), zero(origin == Point<F>()) {}

    template <class F1, class F2>
    bool operator()(const Point<F1> &lhs, const Point<F2> &rhs) const
    {
        return zero ? ccw(lhs, rhs) > 0 : ccw(lhs, rhs, origin) > 0;
    }
};

// sorts a range according to polar angle w.r.t origin
template <class Iterator, class F>
void sortByAngle(Iterator first, Iterator last, const Point<F> &origin)
{
    first = partition(first, last, [&origin](const decltype(*first) &point) { return point == origin; });
    auto pivot = partition(first, last, [&origin](const decltype(*first) &point) { return point > origin; });
    AngleCompare<F> acmp(origin);
    sort(first, pivot, acmp);
    sort(pivot, last, acmp);
}

template <class Iterator>
double get_area(Iterator first, Iterator last)
{
    // empty container
    if (first == last)
        return 0;
    auto p1 = first;
    auto p2 = p1;
    p2++;
    // only one point
    if (p2 == last)
        return 0;

    double ans = 0;
    while (p2 != last)
    {
        ans += (*p1) ^ (*p2);
        p1++;
        p2++;
    }
    ans += (*p1) ^ (*first);
    return abs(ans) / 2;
} // BasicGeometry