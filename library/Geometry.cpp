// arg(x) : argment,[-PI,PI]
using CP = complex<long double>;
#define X real()
#define Y imag()
const long double PI = acos(-1.0L);
const long double EPS = 1e-10;
bool operator==(const CP &l, const CP &r) { return norm(l - r) <= EPS; }
struct Circle {
  CP o;
  long double r;
  Circle(long double _x = 0.0L, long double _y = 0.0L, long double _r = 0.0L)
      : o(CP(_x, _y)), r(_r) {}
  Circle(CP _o, long double _r = 0.0) : o(_o), r(_r) {}
  bool operator<(const Circle &cr) const { return r < cr.r; }
};

struct Line {
  CP s, t;
  Line(long double sx = 0.0L, long double sy = 0.0L, long double tx = 0.0L,
       long double ty = 0.0L)
      : s(CP(sx, sy)), t(CP(tx, ty)) {}
  Line(CP _s, CP _t) : s(_s), t(_t) {}
};

// cos a
long double costh(const long double &a, const long double &b,
                  const long double &c) {
  return (b * b - a * a + c * c) / (2.0L * b * c);
}

// dot(a,b) = |a||b|cos x
long double dot(const CP &a, const CP &b) { return (conj(a) * b).X; }
// cross(a,b) : area of parallelogram
// sign : a-> b ,counter clockwise? + : -
long double cross(const CP &a, const CP &b) { return (conj(a) * b).Y; }
long double corner(const CP &a, const CP &b) {
  //[0,PI]
  return acos(dot(a, b) / (abs(a) * abs(b)));
}

CP projectionLP(const CP &s, const CP &t, const CP &p) {
  if (s == t) return s;
  CP base = t - s;
  long double r = dot(p - s, base) / norm(base);
  return s + base * r;
}
CP projectionLP(const Line &l, const CP &p) {
  return projectionLP(l.s, l.t, p);
}

CP reflectionLP(const CP &s, const CP &t, const CP &p) {
  CP tmp = (projectionLP(s, t, p) - p);
  tmp *= 2;
  return p + tmp;
}
CP reflectionLP(const Line &l, const CP &p) {
  return reflectionLP(l.s, l.t, p);
}

int calc_clockwiseSP(const CP &s, CP t, CP p) {
  t -= s;
  p -= s;
  if (cross(t, p) > EPS) return 1;    // "COUNTER_CLOCKWISE"
  if (cross(t, p) < -EPS) return -1;  //"CLOCK_WISE"
  if (dot(t, p) < 0) return 2;        // "ONLINE_BACK"
  if (norm(t) < norm(p)) return -2;   // "ONLINE_FRONT"
  return 0;                           // "ON_SEGMENT"
}
int calc_clockwiseSP(const Line &l, const CP &p) {
  return calc_clockwiseSP(l.s, l.t, p);
}

int parallel_orthogonalLL(const CP &s, CP t, const CP &a, CP b) {
  t -= s;
  b -= a;
  if (abs(cross(t, b)) <= EPS) return 2;  // "parallel"
  if (abs(dot(t, b)) <= EPS) return 1;    // "orthogonal"
  return 0;
}
int parallel_orthogonalLL(const Line &ll, const Line &lr) {
  return parallel_orthogonalLL(ll.s, ll.t, lr.s, lr.t);
}

CP intersectionLL(const CP &a, const CP &b, const CP &c, const CP &d) {
  return a + (b - a) * (cross(d - c, c - a) / cross(d - c, b - a));
}
CP intersectionLL(const Line &ll, const Line &lr) {
  return intersectionLL(ll.s, ll.t, lr.s, lr.t);
}

bool on_segSP(const CP &s, const CP &t, const CP &p) {
  // if not use end point, dot(s - p, t - p) < 0
  return abs(cross(s - p, t - p)) <= EPS && dot(s - p, t - p) <= 0;
}
bool on_segSP(const Line &l, const CP &p) { return on_segSP(l.s, l.t, p); }

// crossing segments? (a,b) and (c,d)
bool iscrossSS(const CP &a, const CP &b, const CP &c, const CP &d) {
  // parallel
  if (abs(cross(a - b, c - d)) <= EPS) {
    return on_segSP(a, b, c) || on_segSP(a, b, d) || on_segSP(c, d, a) ||
           on_segSP(c, d, b);
  }
  CP isp = intersectionLL(a, b, c, d);
  return on_segSP(a, b, isp) && on_segSP(c, d, isp);
}
bool iscrossSS(const Line &ll, const Line &lr) {
  return iscrossSS(ll.s, ll.t, lr.s, lr.t);
}

long double distLP(const CP &s, const CP &t, const CP &p) {
  return abs(cross(t - s, p - s) / abs(t - s));
}
long double distLP(const Line &l, const CP &p) { return distLP(l.s, l.t, p); }

long double distSP(const CP &s, const CP &t, const CP &p) {
  if (dot(t - s, p - s) < 0) return abs(p - s);
  if (dot(s - t, p - t) < 0) return abs(p - t);
  return distLP(s, t, p);
}
long double distSP(const Line &l, const CP &p) { return distSP(l.s, l.t, p); }

long double distSS(const CP &a, const CP &b, const CP &c, const CP &d) {
  long double res = 1e18;
  if (iscrossSS(a, b, c, d)) return 0.0L;
  res = min(res, distSP(a, b, c));
  res = min(res, distSP(a, b, d));
  res = min(res, distSP(c, d, a));
  res = min(res, distSP(c, d, b));
  return res;
}
long double distSS(const Line &ll, const Line &lr) {
  return distSS(ll.s, ll.t, lr.s, lr.t);
}

// counter clockwise
bool is_convex(const vector<CP> &pol) {
  int n = pol.size();
  for (int i = 0; i < n; ++i)
    if (cross(pol[(i + 1) % n] - pol[i], pol[(i + 2) % n] - pol[(i + 1) % n]) <
        -EPS)
      return 0;
  return 1;
}

vector<CP> convex_hull(vector<CP> &ps) {
  auto lmd = [&](const CP &l, const CP &r) {
    if (l.X != r.X) return l.X < r.X;
    return l.Y < r.Y;
  };
  vector<CP> res;
  int psize = ps.size();
  sort(ps.begin(), ps.end(), lmd);
  int k = 0;
  res.resize(psize * 2);
  for (int i = 0; i < psize; ++i) {
    while (k > 1 && cross(res[k - 1] - res[k - 2], ps[i] - res[k - 1]) <= 0)
      --k;
    res[k++] = ps[i];
  }
  for (int i = psize - 2, t = k; i >= 0; --i) {
    while (k > t && cross(res[k - 1] - res[k - 2], ps[i] - res[k - 1]) <= 0)
      --k;
    res[k++] = ps[i];
  }
  res.resize(k - 1);
  return res;
}

long double convex_diameter(const vector<CP> &pol) {
  vector<CP> ps = pol;
  ps = convex_hull(ps);
  int n = ps.size(), i = 0, j = 0;
  if (n < 2) return 0.0L;
  if (n == 2) return abs(ps[0] - ps[1]);
  for (int k = 0; k < n; ++k) {
    if (ps[k].X < ps[i].X) i = k;
    if (ps[k].X > ps[j].X) j = k;
  }
  long double res = 0;
  int si = i, sj = j;
  while (i != sj || j != si) {
    res = max(res, abs(ps[i] - ps[j]));
    if (cross(ps[(i + 1) % n] - ps[i], ps[(j + 1) % n] - ps[j]) < 0)
      (++i) %= n;
    else
      (++j) %= n;
  }
  return res;
}

vector<CP> convex_cut(const vector<CP> &pol, const CP &s, const CP &t) {
  vector<CP> res;
  int n = pol.size();
  for (int i = 0; i < n; ++i) {
    CP nows = pol[i], nowt = pol[(i + 1) % n];
    if (cross(t - s, nows - s) >= -EPS) res.push_back(nows);
    if (cross(t - s, nows - s) * cross(t - s, nowt - s) < 0)
      res.push_back(intersectionLL(s, t, nows, nowt));
  }
  return res;
}
vector<CP> convex_cut(const vector<CP> &pol, const Line &l) {
  return convex_cut(pol, l.s, l.t);
}

// number of tangents
int iscrossCC(Circle l, Circle r) {
  if (l.r < r.r) swap(l, r);
  long double distlr = abs(l.o - r.o);
  if (l.r + r.r < distlr)
    return 4;  // not touch
  else if (abs(distlr - l.r - r.r) <= EPS)
    return 3;  // circumscription
  else if (l.r - r.r < distlr)
    return 2;  // cross
  else if (abs(distlr - l.r + r.r) <= EPS)
    return 1;  // inscribed
  else         // contain
    return 0;
}

vector<CP> intersectionCC(const Circle &c1, const Circle &c2) {
  vector<CP> res;
  if (iscrossCC(c1, c2) == 4) return res;

  long double d = abs(c1.o - c2.o);
  long double a = acos(costh(c2.r, c1.r, d));
  long double t = atan2(c2.o.imag() - c1.o.imag(), c2.o.real() - c1.o.real());
  res.push_back(c1.o + CP(cos(t + a) * c1.r, sin(t + a) * c1.r));
  res.push_back(c1.o + CP(cos(t - a) * c1.r, sin(t - a) * c1.r));
  if (res[0].X > res[1].X || (res[0].X == res[1].X && res[0].Y > res[1].Y))
    swap(res[0], res[1]);
  return res;
}

vector<CP> intersectionCL(const Circle &ci, const CP &s, CP t) {
  vector<CP> res(2, projectionLP(s, t, ci.o));
  long double r = ci.r * ci.r - norm(res[0] - ci.o);
  if (r <= EPS || t == s) return res;
  t -= s;
  t *= r / abs(t);
  res[0] += t;
  res[1] -= t;
  if (res[0].X > res[1].X || (res[0].X == res[1].X && res[0].Y > res[1].Y))
    swap(res[0], res[1]);
  return res;
}
vector<CP> intersectionCL(const Circle &ci, const Line &l) {
  return intersectionCL(ci, l.s, l.t);
}

vector<CP> contactCP(const Circle &ci, const CP &p) {
  vector<CP> res;
  long double d = abs(ci.o - p);
  if (abs(d - ci.r) <= EPS) {
    res.push_back(p);
    return res;
  } else if (d < ci.r)
    return res;
  long double arg = asin(ci.r / d);
  res.push_back((ci.o - p) * CP(cos(arg), sin(arg)));
  res[0] *= (d * cos(arg)) / abs(res[0]);
  res[0] += p;
  res.push_back(reflectionLP(p, ci.o, res[0]));
  if (res[0].X > res[1].X || (res[0].X == res[1].X && res[0].Y > res[1].Y))
    swap(res[0], res[1]);
  return res;
}

vector<Line> tangentCC(Circle cl, Circle cr) {
  vector<Line> res;
  if (cl.r < cr.r) swap(cl, cr);
  long double g = abs(cl.o - cr.o);
  if (abs(g - 0.0L) <= EPS) return res;
  CP hor = (cr.o - cl.o) / g, ver;
  ver = hor * (CP(cos(PI * 0.5L), sin(PI * 0.5L)));
  for (int s : {-1, 1}) {
    long double h = (cl.r + s * cr.r) / g;
    if (abs(1 - h * h) <= EPS) {
      res.emplace_back(cl.o + hor * cl.r, cl.o + (hor + ver) * cl.r);
    } else if (1 - h * h > 0) {
      CP nhor = hor * h, nver = ver * sqrtl(1 - h * h);
      res.emplace_back(cl.o + (nhor + nver) * cl.r,
                       cr.o - (nhor + nver) * (cr.r * s));
      res.emplace_back(cl.o + (nhor - nver) * cl.r,
                       cr.o - (nhor - nver) * (cr.r * s));
    }
  }
  return res;
}

long double areaPol(const vector<CP> &pol) {
  int n = pol.size();
  long double res = 0;
  for (int i = 0; i < n; ++i)
    res += (pol[(i - 1 + n) % n].X - pol[(i + 1) % n].X) * pol[i].Y;
  return res / 2.0L;
}

int containPolP(const vector<CP> &pol, CP p) {
  bool con = 0, onseg = 0;
  int n = pol.size();
  for (int i = 0; i < n; ++i) {
    onseg |= on_segSP(pol[i], pol[(i + 1) % n], p);
    CP s = pol[i] - p, t = pol[(i + 1) % n] - p;
    if (s.Y > t.Y) swap(s, t);
    if (s.Y * t.Y <= 0 && t.Y > 0 && cross(s, t) < 0) con = !con;
  }
  if (onseg) return 1;
  if (con) return 2;
  return 0;
}

long double closest_pair(vector<CP> &ps, int l = -1, int r = -1,
                         bool reqsqrt = 0) {
  if (l == r && l == -1) {
    l = 0;
    r = ps.size();
    reqsqrt = 1;
    auto lmd = [&](const CP &l, const CP &r) {
      if (l.X != r.X) return l.X < r.X;
      return l.Y < r.Y;
    };
    sort(ps.begin(), ps.end(), lmd);
  }
  if (r - l < 2) return 1e18;
  if (r - l == 2) {
    if (ps[l].Y > ps[l + 1].Y) swap(ps[l], ps[l + 1]);
    if (reqsqrt) return abs(ps[l] - ps[l + 1]);
    return norm(ps[l] - ps[l + 1]);
  }
  int mid = (l + r) / 2;
  long double x = ps[mid].X,
              res = min(closest_pair(ps, l, mid), closest_pair(ps, mid, r));
  auto f = [](CP pl, CP pr) { return pl.Y < pr.Y; };
  inplace_merge(ps.begin() + l, ps.begin() + mid, ps.begin() + r, f);
  vector<CP> tmp;
  for (int i = l; i < r; ++i) {
    long double dx = abs(ps[i].X - x);
    int tsize = tmp.size();
    if (dx * dx >= res) continue;
    for (int j = 0; j < tsize; ++j) {
      CP delta = ps[i] - tmp[tsize - 1 - j];
      if (delta.Y * delta.Y >= res) break;
      res = min(res, norm(delta));
    }
    tmp.push_back(ps[i]);
  }
  if (reqsqrt) res = sqrtl(res);
  return res;
}

Circle min_ball(vector<CP> ps) {
  int n = ps.size();
  if (n == 1) return Circle(ps[0], 0.0L);
  mt19937 mt(int(time(0)));
  shuffle(ps.begin(), ps.end(), mt);
  auto make3 = [](const CP &a, const CP &b, const CP &c) {
    long double A = norm(b - c), B = norm(c - a), C = norm(a - b),
                S = cross(b - a, c - a);
    CP p = (A * (B + C - A) * a + B * (C + A - B) * b + C * (A + B - C) * c) /
           (4 * S * S);
    long double nowr = norm(p - a);
    return Circle(p, nowr);
  };
  auto make2 = [](const CP &a, const CP &b) {
    CP c = (a + b) / 2.0L;
    long double nowr = norm(a - c);
    return Circle(c, nowr);
  };
  auto in_circle = [](const CP &a, const Circle &c) {
    return norm(a - c.o) <= c.r + EPS;
  };
  Circle res = make2(ps[0], ps[1]);
  for (int i = 2; i < n; ++i)
    if (!in_circle(ps[i], res)) {
      res = make2(ps[0], ps[i]);
      for (int j = 1; j < i; ++j)
        if (!in_circle(ps[j], res)) {
          res = make2(ps[i], ps[j]);
          for (int k = 0; k < j; ++k)
            if (!in_circle(ps[k], res)) res = make3(ps[i], ps[j], ps[k]);
        }
    }
  res.r = sqrtl(res.r);
  return res;
}

bool arg_comp(CP a, CP b) {
  int up_down_a = a.Y > 0 || (abs(a.Y) <= EPS && a.X >= 0);
  int up_down_b = b.Y > 0 || (abs(b.Y) <= EPS && b.X >= 0);
  if (up_down_a != up_down_b) return up_down_a < up_down_b;
  if (a.X * b.Y == a.Y * b.X) return norm(a) < norm(b);
  return calc_clockwiseSP(CP(0, 0), a, b) == 1;
}
bool operator<(const Line &l, const Line &r) {
  CP lp = l.t - l.s, rp = r.t - r.s;
  return arg_comp(lp, rp);
}