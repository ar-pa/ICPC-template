const double EPS = 1e-12;
struct P {
    double x, y;
    P operator+(const P &p) const { return {x + p.x, y + p.y}; }
    P operator-(const P &p) const { return {x - p.x, y - p.y}; }
    P operator*(double c) const { return {x * c, y * c}; }
    double operator*(P q) const { return x * q.y - y * q.x; }
    P operator/(double c) const { return {x / c, y / c}; }
    double angle() const {
        return atan2(y, x);
    }
    P RotateCCW90() const { return {-y, x}; }
    P RotateCW90() const { return {y, -x}; }
    P RotateCCW(double t) const {
        return {x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
    }
    double size2() const {
        return x * x + y * y;
    }
    double size() const {
        return sqrt(size2());
    }
};
double dot(P p, P q) { return p.x * q.x + p.y * q.y; }
double dist2(P p, P q) { return (p - q).size2(); }
double dist(P p, P q) { return (p - q).size(); }
ostream &operator<<(ostream &os, const P &p) {
    return os << "(" << p.x << "," << p.y << ")";
}
// project point c onto line through a and b
// assuming a != b
P project_point_line(P a, P b, P c) {
    return a + (b - a) * dot(c - a, b - a) / (b - a).size2();
}
// project point c onto line segment through a and b
P project_point_segment(P a, P b, P c) {
    double r = dot(b - a, b - a);
    if (abs(r) < EPS) return a;
    r = dot(c - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a) * r;
}
// compute distance from c to segment between a and b
double distance_point_segment(P a, P b, P c) {
    return sqrt(dist2(c, project_point_segment(a, b, c)));
}
// compute distance between point (x,y,z) and plane ax+by+cz=d
double distance_point_plane(double x, double y, double z,
                            double a, double b, double c, double d) {
    return abs(a * x + b * y + c * z - d) / sqrt(a * a + b * b + c * c);
}
// determine if lines from a to b and c to d are parallel or collinear
bool lines_parallel(P a, P b, P c, P d) {
    return abs((b - a) * (c - d)) < EPS;
}
bool lines_collinear(P a, P b, P c, P d) {
    return lines_parallel(a, b, c, d)
           && abs((a - b) * (a - c)) < EPS
           && abs((c - d) * (c - a)) < EPS;
}
// determine if line segment from a to b intersects with
// line segment from c to d
bool segments_intersect(P a, P b, P c, P d) {
    if (lines_collinear(a, b, c, d)) {
        if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
            dist2(b, c) < EPS || dist2(b, d) < EPS)
            return true;
        if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0)
            return false;
        return true;
    }
    if (((d - a) * (b - a)) * ((c - a) * (b - a)) > 0 || ((a - c) * (d - c)) * ((b - c) * (d - c)) > 0)
        return false;
    return true;
}
// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
P line_intersection(P a, P b, P c, P d) {
    b = b - a;
    d = c - d;
    c = c - a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b * (c * d) / (b * d);
}
// compute center of circle given three points
P circle_center(P a, P b, P c) {
    b = (a + b) / 2;
    c = (a + c) / 2;
    return line_intersection(b, b + (a - b).RotateCW90(), c, c + (a - c).RotateCW90());
}
// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool point_in_polygon(const vector<P> &p, P q) {
    bool c = false;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        if ((p[i].y <= q.y && q.y < p[j].y ||
             p[j].y <= q.y && q.y < p[i].y) &&
            q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
            c = !c;
    }
    return c;
}
// determine if point is on the boundary of a polygon
bool point_on_polygon(const vector<P> &p, P q) {
    for (int i = 0; i < p.size(); i++)
        if (dist2(project_point_segment(p[i], p[(i + 1) % p.size()], q), q) < EPS)
            return true;
    return false;
}
// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
// going from a to b, t[1] is the first intersection and t[0] is the second
vector<P> circle_line_intersection(P a, P b, P c, double r) {
    vector<P> ret;
    b = b - a;
    a = a - c;
    double A = dot(b, b);
    double B = dot(a, b);
    double C = dot(a, a) - r * r;
    double D = B * B - A * C;
    if (D < -EPS) return ret;
    ret.push_back(c + a + b * (-B + sqrt(D + EPS)) / A);
    if (D > EPS)
        ret.push_back(c + a + b * (-B - sqrt(D)) / A);
    return ret;
}
// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
// order is counter clock wise
vector<P> circle_circle_intersection(P a, P b, double r, double R) {
    vector<P> ret;
    double d = sqrt(dist2(a, b));
    if (d > r + R || d + min(r, R) < max(r, R)) return ret;
    double x = (d * d - R * R + r * r) / (2 * d);
    double y = sqrt(r * r - x * x);
    P v = (b - a) / d;
    ret.push_back(a + v * x + v.RotateCCW90() * y);
    if (y > 0)
        ret.push_back(a + v * x - v.RotateCCW90() * y);
    return ret;
}
// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
double signed_area(const vector<P> &p) {
    double area = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        area += p[i].x * p[j].y - p[j].x * p[i].y; // TODO
    }
    return area / 2.0;
}
double area(const vector<P> &p) {
    return abs(signed_area(p));
}
P centroid(const vector<P> &p) {
    P c{0, 0};
    double scale = 6.0 * signed_area(p);
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
    }
    return c / scale;
}
// tests whether or not a given polygon (in CW or CCW order) is simple
bool is_simple(const vector<P> &p) {
    for (int i = 0; i < p.size(); i++) {
        for (int k = i + 1; k < p.size(); k++) {
            int j = (i + 1) % p.size();
            int l = (k + 1) % p.size();
            if (i == l || j == k) continue;
            if (segments_intersect(p[i], p[j], p[k], p[l]))
                return false;
        }
    }
    return true;
}
double coef_on_line(P a, P b, P c) {
    if (abs(a.x - c.x) < EPS)
        return (b.y - a.y) / (c.y - a.y);
    return (b.x - a.x) / (c.x - a.x);
}
void seg_union(vector<pair<double, double >> &segs) {
    sort(segs.begin(), segs.end());
    int sz = 0;
    for (auto[l, r] : segs)
        if (l <= r)
            if (!sz || l > segs[sz - 1].second + EPS)
                segs[sz++] = {l, r};
            else
                segs[sz - 1].second = max(segs[sz - 1].second, r);
    segs.resize(sz);
}
vector<pair<double, double> > polygon_segment_intersection(vector<P> &pol, P a, P b) {
    vector<pair<double, double> > segs;
    vector<P> impos({a, b});
    for (int k = 0; k < pol.size(); k++)
        if (segments_intersect(a, b, pol[k], pol[(k + 1) % pol.size()]))
            impos.push_back(line_intersection(a, b, pol[k], pol[(k + 1) % pol.size()]));
    sort(impos.begin(), impos.end(), [&](P x, P y) {
        return coef_on_line(a, x, b) < coef_on_line(a, y, b);
    });
    for (int k = 0; k < impos.size() - 1; k++) {
        P mid = (impos[k] + impos[k + 1]) / 2;
        if (point_in_polygon(pol, mid))
            segs.emplace_back(coef_on_line(a, impos[k], b), coef_on_line(a, impos[k + 1], b));
    }
    return segs;
}
pair<double, double> circle_segment_intersection(P a, P b, P c, double r) {
    vector<P> ret = circle_line_intersection(a, b, c, r);
    if (ret.size() < 2)
        return {0, 0};
    return {max<double>(0, min(coef_on_line(a, ret[0], b), coef_on_line(a, ret[1], b))),
            min<double>(1, max(coef_on_line(a, ret[0], b), coef_on_line(a, ret[1], b)))};
}
bool cmp_angle(const P &a, const P &b) {
    if (a.y * b.y < 0)
        return a.y < b.y;
    return a * b > 0;
}
