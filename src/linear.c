#include "math/linear.h"
#include <math.h>

static inline int mat2_idx(int i, int j);
static inline int mat4_idx(int i, int j);

Mat2 mat2_identity(void) {
  return (Mat2){
      .m = {
            1.0f, 0.0f,
            0.0f, 1.0f}
  };
}

Mat2 mat2_mul(Mat2 a, Mat2 b) {
  Mat2 result = {0};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      result.m[mat2_idx(i, j)] =
          a.m[mat2_idx(i, 0)] * b.m[mat2_idx(0, j)] +
          a.m[mat2_idx(i, 1)] * b.m[mat2_idx(1, j)];
    }
  }
  return result;
}

Mat4 mat4_ortho(double left, double right, double bottom, double top, double near, double far) {
  float width = (float)right - left;
  float height = (float)top - bottom;
  float depth = (float)far - near;
  return (Mat4){
      .m = {
            2.f / width, 0.f, 0.f, -(right + left) / width,
            0.f, 2.f / height, 0.f, -(top + bottom) / height,
            0.f, 0.f, -2.f / depth, -(far + near) / depth,
            0.f, 0.f, 0.f, 1.f}
  };
}

Mat4 mat4_frustum(double left, double right, double bottom, double top, double near, double far) {
  float rl = (float)(right - left);
  float tb = (float)(top - bottom);
  float fn = (float)(far - near);

  return (Mat4){
      .m = {((float)near * 2.0f) / rl, 0.0f, ((float)right + (float)left) / rl, 0.0f,
            0.0f, ((float)near * 2.0f) / tb, ((float)top + (float)bottom) / tb, 0.0f,
            0.0f, 0.0f, -((float)far + (float)near) / fn, -((float)far * (float)near * 2.0f) / fn,
            0.0f, 0.0f, -1.0f, 0.0f}
  };
}

// fov in radians
Mat4 mat4_perspective(double fov, double aspect, double near, double far) {
  double top = near * tan(fov * 0.5);
  double bottom = -top;
  double right = top * aspect;
  double left = -right;
  return mat4_frustum(left, right, bottom, top, near, far);

  // float tangent = tan(fov / 2);
  // float top = near * tangent;
  // float right = top * aspect;
  //
  // return (Mat4){
  //     .m = {near / right, 0.0f, 0.0f, 0.0f,
  //           0.0f, near / top, 0.0f, 0.0f,
  //           0.0f, 0.0f, -(far + near) / far - near, -(2 * far * near) / (far - near),
  //           0.0f, 0.0f, -1.0f, 0.0f}
  // };
}

Mat4 mat4_lookat(Vec3 eye, Vec3 target, Vec3 up) {
  float length = 0.0f;
  float ilength = 0.0f;

  // Vector3Subtract(eye, target)
  Vec3 vz = {eye.x - target.x, eye.y - target.y, eye.z - target.z};

  // Vector3Normalize(vz)
  Vec3 v = vz;
  length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  if (length == 0.0f)
    length = 1.0f;
  ilength = 1.0f / length;
  vz.x *= ilength;
  vz.y *= ilength;
  vz.z *= ilength;

  // Vector3CrossProduct(up, vz)
  Vec3 vx = {up.y * vz.z - up.z * vz.y, up.z * vz.x - up.x * vz.z, up.x * vz.y - up.y * vz.x};

  // Vector3Normalize(x)
  v = vx;
  length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  if (length == 0.0f)
    length = 1.0f;
  ilength = 1.0f / length;
  vx.x *= ilength;
  vx.y *= ilength;
  vx.z *= ilength;

  // Vector3CrossProduct(vz, vx)
  Vec3 vy = {vz.y * vx.z - vz.z * vx.y, vz.z * vx.x - vz.x * vx.z, vz.x * vx.y - vz.y * vx.x};

  float vxdoteye = -(vx.x * eye.x + vx.y * eye.y + vx.z * eye.z); // Vector3DotProduct(vx, eye)
  float vydoteye = -(vy.x * eye.x + vy.y * eye.y + vy.z * eye.z); // Vector3DotProduct(vy, eye)
  float vzdoteye = -(vz.x * eye.x + vz.y * eye.y + vz.z * eye.z); // Vector3DotProduct(vz, eye)

  return (Mat4){
      .m = {
            vx.x, vx.y, vx.z, vxdoteye,
            vy.x, vy.y, vy.z, vydoteye,
            vz.x, vz.y, vz.z, vzdoteye,
            0.0f, 0.0f, 0.0f, 1.0f}
  };
}

Mat4 mat4_identity(void) {
  return (Mat4){
      .m = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f}
  };
}

Mat4 mat4_mul(Mat4 a, Mat4 b) {
  Mat4 result = {0};
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result.m[mat4_idx(i, j)] =
          a.m[mat4_idx(i, 0)] * b.m[mat4_idx(0, j)] +
          a.m[mat4_idx(i, 1)] * b.m[mat4_idx(1, j)] +
          a.m[mat4_idx(i, 2)] * b.m[mat4_idx(2, j)] +
          a.m[mat4_idx(i, 3)] * b.m[mat4_idx(3, j)];
    }
  }
  return result;
}

Mat4 mat4_translate(Vec3 v) {
  return (Mat4){
      .m = {
            1.f, 0.f, 0.f, v.x,
            0.f, 1.f, 0.f, v.y,
            0.f, 0.f, 1.f, v.z,
            0.f, 0.f, 0.f, 1.f}
  };
}

Mat4 mat4_scale(Vec3 v) {
  return (Mat4){
      .m = {
            v.x, 0.f, 0.f, 0.f,
            0.f, v.y, 0.f, 0.f,
            0.f, 0.f, v.z, 0.f,
            0.f, 0.f, 0.f, 1.f}
  };
}

Mat4 mat4_rotate(float angle, Vec3 axis) {
  float x = axis.x, y = axis.y, z = axis.z;

  float lengthSquared = x * x + y * y + z * z;

  if ((lengthSquared != 1.0f) && (lengthSquared != 0.0f)) {
    float ilength = 1.0f / sqrtf(lengthSquared);
    x *= ilength;
    y *= ilength;
    z *= ilength;
  }

  float sinres = sinf(angle);
  float cosres = cosf(angle);
  float t = 1.0f - cosres;

  return (Mat4){
      .m = {
            x * x * t + cosres, x * y * t - z * sinres, x * z * t + y * sinres, 0.f,
            y * x * t + z * sinres, y * y * t + cosres, y * z * t - x * sinres, 0.f,
            z * x * t - y * sinres, z * y * t + x * sinres, z * z * t + cosres, 0.f,
            0.0f, 0.0f, 0.0f, 1.0f}
  };
}

Vec2 vec2(float x, float y) {
  return (Vec2){x, y};
}

Vec2 vec2_add(Vec2 a, Vec2 b) {
  return (Vec2){a.x + b.x, a.y + b.y};
}

Vec2 vec2_sub(Vec2 a, Vec2 b) {
  return (Vec2){a.x - b.x, a.y - b.y};
}

Vec2 vec2_scale(Vec2 a, float scale) {
  return (Vec2){scale * a.x, scale * a.y};
}

float vec2_length(Vec2 v) {
  return sqrtf((v.x * v.x) + (v.y * v.y));
}

float vec2_length_sqr(Vec2 v) {
  return (v.x * v.x) + (v.y * v.y);
}

float vec2_det(Vec2 a, Vec2 b) {
  return (a.x * b.y) - (a.y * b.x);
}

float vec2_dot_product(Vec2 a, Vec2 b) {
  return a.x * b.x + a.y + b.y;
}

Vec2 vec2_lerp(Vec2 start, Vec2 end, float t) {
  return (Vec2){start.x + t * (end.x - start.x),
                start.y + t * (end.y - start.y)};
}

float vec2_angle(Vec2 v1, Vec2 v2) {
  return atan2f(vec2_det(v1, v2), vec2_dot_product(v1, v2));
}

Vec2 vec2_angle_to_direction(float angle) {
  return (Vec2){cosf(angle), sinf(angle)};
}

float vec2_direction_to_angle(Vec2 v) {
  return atan2f(v.y, v.x);
}

Vec2 vec2_transform2x2(Vec2 v, Mat2 mat) {
  return (Vec2){
      mat.m[mat2_idx(0, 0)] * v.x + mat.m[mat2_idx(0, 1)] * v.y,
      mat.m[mat2_idx(1, 0)] * v.x + mat.m[mat2_idx(1, 1)] * v.y};
}

// Mat4 * (Vec2.x, Vec2.y, 0.f, 1.f)
Vec2 vec2_transform4x4(Vec2 v, Mat4 mat) {
  return (Vec2){
      mat.m[mat4_idx(0, 0)] * v.x + mat.m[mat4_idx(0, 1)] * v.y + mat.m[mat4_idx(0, 3)],
      mat.m[mat4_idx(1, 0)] * v.x + mat.m[mat4_idx(1, 1)] * v.y + mat.m[mat4_idx(1, 3)]};
}

Vec3 vec3(float x, float y, float z) {
  return (Vec3){x, y, z};
}

Vec3 vec3_cross(Vec3 v1, Vec3 v2) {
  return vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

Vec3 vec3_normalize(Vec3 v) {
  Vec3 result = v;

  float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  if (length != 0.0f) {
    float ilength = 1.0f / length;

    result.x *= ilength;
    result.y *= ilength;
    result.z *= ilength;
  }

  return result;
}

Vec3 vec3_scale(Vec3 v, float scalar) {
  Vec3 result = {v.x * scalar, v.y * scalar, v.z * scalar};
  return result;
}

Vec3 vec3_add(Vec3 v1, Vec3 v2) {
  Vec3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
  return result;
}
Vec3 vec3_sub(Vec3 v1, Vec3 v2) {
  Vec3 result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
  return result;
}

Vec3 vec3_mul(Vec3 v1, Vec3 v2) {
  Vec3 result = {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
  return result;
}

Vec4 vec4(float x, float y, float z, float w) {
  return (Vec4){x, y, z, w};
}

Vec2i vec2i_add(Vec2i a, Vec2i b) {
  return (Vec2i){a.x + b.x, a.y + b.y};
}

Vec2i vec2i_sub(Vec2i a, Vec2i b) {
  return (Vec2i){a.x - b.x, a.y - b.y};
}

Vec2i vec2i_scale(Vec2i a, int scale) {
  return (Vec2i){a.x * scale, a.y * scale};
}

Vec2i vec2i_clamp(Vec2i x, Vec2i a, Vec2i b) {
  return (Vec2i){clampi(x.x, a.x, b.x), clampi(x.y, a.y, b.y)};
}

bool vec2i_eq(Vec2i a, Vec2i b) {
  return a.x == b.x && a.y == b.y;
}

float clampf(float x, float a, float b) {
  return fminf(fmaxf(a, x), b);
}

int mini(int a, int b) {
  return a < b ? a : b;
}

int maxi(int a, int b) {
  return a < b ? b : a;
}

int clampi(int x, int a, int b) {
  return mini(maxi(a, x), b);
}

static inline int mat2_idx(int i, int j) {
  return 2 * i + j;
}

static inline int mat4_idx(int i, int j) {
  return 4 * i + j;
}
