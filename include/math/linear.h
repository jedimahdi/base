#ifndef LINEAR_H_
#define LINEAR_H_

#include <stdbool.h>

#ifndef PI
#define PI 3.14159265358979323846f
#endif

#ifndef TAU
#define TAU (PI * 2)
#endif

#ifndef DEG2RAD
#define DEG2RAD (PI / 180.0f)
#endif

#ifndef RAD2DEG
#define RAD2DEG (180.0f / PI)
#endif

#define SPREAD_XY(v) (v).x, (v).y
#define SPREAD_XYZ(v) (v).x, (v).y, (v).z

typedef struct {
  float x, y;
} Vec2;

typedef struct {
  int x, y;
} Vec2i;

typedef struct {
  float x, y, z;
} Vec3;

typedef struct {
  unsigned int x, y;
} Vec2u;

typedef struct {
  unsigned int x, y, z;
} Vec3u;

typedef struct {
  float x, y, z, w;
} Vec4;

typedef struct {
  float m[2 * 2];
} Mat2;

typedef struct {
  float m[4 * 4];
} Mat4;

// Right to left, T * R * S
Mat4 mat4_mul(Mat4 a, Mat4 b);
Mat4 mat4_identity(void);
Mat4 mat4_translate(Vec3 v);
Mat4 mat4_scale(Vec3 v);
Mat4 mat4_rotate(float angle, Vec3 axis);
Mat4 mat4_ortho(double left, double right, double bottom, double top, double near, double far);
Mat4 mat4_perspective(double fov, double aspect, double near, double far);
Mat4 mat4_frustum(double left, double right, double bottom, double top, double near, double far);
Mat4 mat4_lookat(Vec3 eye, Vec3 target, Vec3 up);

Mat2 mat2_identity(void);
Mat2 mat2_mul(Mat2 a, Mat2 b);

Vec2 vec2(float x, float y);
Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_scale(Vec2 a, float scale);
float vec2_length(Vec2 v);
float vec2_length_sqr(Vec2 v);
float vec2_det(Vec2 a, Vec2 b);
float vec2_dot_product(Vec2 a, Vec2 b);
Vec2 vec2_cross_product(Vec2 a, Vec2 b);
Vec2 vec2_lerp(Vec2 start, Vec2 end, float t);
float vec2_angle(Vec2 v1, Vec2 v2);
Vec2 vec2_angle_to_direction(float angle);
float vec2_direction_to_angle(Vec2 v);
Vec2 vec2_transform2x2(Vec2 v, Mat2 mat);
Vec2 vec2_transform4x4(Vec2 v, Mat4 mat);

Vec3 vec3(float x, float y, float z);
Vec3 vec3_cross(Vec3 v1, Vec3 v2);
Vec3 vec3_normalize(Vec3 v);
Vec3 vec3_scale(Vec3 v, float scalar);
Vec3 vec3_add(Vec3 v1, Vec3 v2);
Vec3 vec3_sub(Vec3 v1, Vec3 v2);
Vec3 vec3_mul(Vec3 v1, Vec3 v2);

Vec4 vec4(float x, float y, float z, float w);

float clampf(float x, float a, float b);

int mini(int a, int b);
int maxi(int a, int b);
int clampi(int x, int a, int b);

Vec2i vec2i_add(Vec2i a, Vec2i b);
Vec2i vec2i_sub(Vec2i a, Vec2i b);
Vec2i vec2i_scale(Vec2i a, int scale);
Vec2i vec2i_clamp(Vec2i x, Vec2i a, Vec2i b);
bool vec2i_eq(Vec2i a, Vec2i b);

#endif // LINEAR_H_
