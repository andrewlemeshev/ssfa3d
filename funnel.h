/*
The Simple Stupid Funnel Algorithm (SSFA) for 3d.
Everything are belongs to Mikko Mononen (http://digestingduck.blogspot.ru/2010/03/simple-stupid-funnel-algorithm.html)
I just implement the 3-rd dimension for the algorithm
No roots, only one divisions it can be avoided if you know your polygon order
*/

#define EPSILON 0.00001f

float fast_fabsf(const float &f) {
  int i=((*(int*)&f)&0x7fffffff);

  return (*(float*)&i);
}

// simple vector struct just for more readable code
struct vec_t {
    float x, y, z;

    vec_t() {}
    vec_t(const float &_x, const float &_y, const float &_z) {
        x = _x;
        y = _y;
        z = _z;
    }

    vec_t operator-(const vec_t &b) const {
        return {this->x - b.x,
                this->y - b.y,
                this->z - b.z};
    }

    vec_t operator*(const float &scalar) const {
        return {scalar * this->x,
                scalar * this->y,
                scalar * this->z};
    }

    vec_t operator+(const vec_t &b) const {
        return {this->x + b.x,
                this->y + b.y,
                this->z + b.z};
    }

    bool operator==(const vec_t &other) const {
        return fast_fabsf(this->x - other.x) < EPSILON && fast_fabsf(this->y - other.y) < EPSILON && fast_fabsf(this->z - other.z) < EPSILON;
    }
};

// line segment as portal for the SSFA
struct segment_t {
    vec_t a, b;

    segment_t() {}
    segment_t(const vec_t &_a, const vec_t &_b) {
        a = _a;
        b = _b;
    }
};

// input for the SSFA
struct funnel_in_t {
    segment_t portal; // portal is just two points
    vec_t normal; // normal of a poly
    vec_t point; // usualy center of poly
};

// helper functions {
vec_t operator*(const float &scalar, const vec_t &vec) {
    return {scalar * vec.x,
            scalar * vec.y,
            scalar * vec.z};
}

vec_t cross(const vec_t &a, const vec_t &b) {
    return {a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
}

float dot(const vec_t &a, const vec_t &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float min(const float &a, const float &b) {
    return a > b ? b : a;
}

float max(const float &a, const float &b) {
    return a > b ? a : b;
}

float clamp(const float &value, const float &minV, const float &maxV) {
    return min(max(value, minV), maxV);
}

vec_t closestPoint(const segment_t &line, const vec_t &p) {
  vec_t vec = line.b - line.a;

  float t = dot(p - line.a, vec) / dot(vec, vec); // it can be avoided
  t = clamp(t, 0.0f, 1.0f);

  return line.a + t * vec;
}
// } // helper functions

// where is point concerning the line ab
float sideOf(const vec_t &a, const vec_t &b, const vec_t &point, const vec_t &normal) {
  vec_t vec = b - a;
  vec = cross(vec, normal);
  return dot(vec, point - a);
}

// get left, right relative to the point
void leftRight(const segment_t &line, const vec_t &point, const vec_t &normal, vec_t &left, vec_t &right) {
  vec_t vec = closestPoint(line, point) - point;
  vec = cross(vec, normal);

  float sign = dot(vec, line.b - line.a);

  if (sign >= 0.0f) {
    left = line.a;
    right = line.b;
  } else {
    left = line.b;
    right = line.a;
  }
}

// please consult http://digestingduck.blogspot.ru/2010/03/simple-stupid-funnel-algorithm.html
int funnelAlgorithm(const funnel_in_t* in, const int &count, vec_t* pts, const int &maxCount) {
    if (count < 2) return 0;
    if (maxCount < 1) return 0;

    int npts = 0;

    vec_t apex = in[0].portal.a, portalLeft = in[0].portal.a, portalRight = in[0].portal.b, left, right;
    int apexIndex = 0, leftIndex = 0, rightIndex = 0;

    pts[0] = apex;
    npts++;

    for (int i = 1; i < count; i++) {
        leftRight(in[i].portal, in[i].point, in[i].normal, left, right);

        if (sideOf(apex, portalRight, right, in[i].normal) <= 0.0f) {
            if (apex == portalRight || sideOf(apex, portalLeft, right, in[i].normal) > 0.0f) {
                portalRight = right;
                rightIndex = i;
            } else {
                pts[npts] = portalLeft;
                npts++;

                apex = portalLeft;
                apexIndex = leftIndex;

                portalLeft = apex;
                portalRight = apex;
                leftIndex = apexIndex;
                rightIndex = apexIndex;

                i = apexIndex;
                continue;
            }
        }

        if (sideOf(apex, portalLeft, left, in[i].normal) >= 0.0f) {
            if (apex == portalLeft || sideOf(apex, portalRight, left, in[i].normal) < 0.0f) {
                portalLeft = left;
                leftIndex = i;
            } else {
                pts[npts] = portalRight;
                npts++;

                apex = portalRight;
                apexIndex = rightIndex;

                portalLeft = apex;
                portalRight = apex;
                leftIndex = apexIndex;
                rightIndex = apexIndex;

                i = apexIndex;
                continue;
            }
        }
    }

    // I no need this for the tests, but you may need it
    //if (npts < maxCount) {
    //    pts[npts] = in[count-1].portal.a;
    //    npts++;
    //}

 return npts;
}
