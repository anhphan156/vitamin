#ifndef MATH_H
#define MATH_H
#include <math.h>
#include <string.h>

void matrixMul(float *A, float *B, float *result) {
  int i, j;
  float r[16];
  for (i = 0; i < 4; i++) {
    float ax = A[i + 0];
    float ay = A[i + 4];
    float az = A[i + 8];
    float aw = A[i + 12];

    for (j = 0; j < 4; j++) {
      float bx = B[j * 4 + 0];
      float by = B[j * 4 + 1];
      float bz = B[j * 4 + 2];
      float bw = B[j * 4 + 3];

      r[i + j * 4] = ax * bx + ay * by + az * bz + aw * bw;
    }
  }
  memcpy(result, r, 16 * sizeof(float));
}

void mkPerspective4x4(float fov, float aspect, float znear, float zfar,
                      float *result) {
  float lambda = zfar / (zfar - znear);
  float f = 1 / tan(fov / 2.0);

  float n[16] = {
      aspect * f, 0.0f, 0.0f,
      0.0f, // 1
      0.0f,       f,    0.0f,
      0.0f, // 2
      0.0f,       0.0f, lambda,
      1.0f, // 3
      0.0f,       0.0f, lambda * znear * -1.0f,
      1.0f // 4
  };

  memcpy(result, n, 16 * sizeof(float));
}

void mkTranslation4x4(float *translation, float *result) {
  float n[16] = {
      1.0f,           0.0f,           0.0f,           0.0f, // 1
      0.0f,           1.0f,           0.0f,           0.0f, // 2
      0.0f,           0.0f,           1.0f,           0.0f, // 3
      translation[0], translation[1], translation[2], 1.0f, // 4
  };
  memcpy(result, n, 16 * sizeof(float));
}

void mkRotationZ4x4(float a, float *result) {
  float s = sin(a);
  float c = cos(a);
  float n[16] = {c,    s,    0.0f, 0.0f, -s,   c,    0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  memcpy(result, n, 16 * sizeof(float));
}

void mkRotationY4x4(float a, float *result) {
  float s = sin(a);
  float c = cos(a);
  float n[16] = {
      c,    0.0f, s,    0.0f, // 1
      0.0f, 1.0f, 0.0f, 0.0f, // 2
      -s,   0.0f, c,    0.0f, // 3
      0.0f, 0.0f, 0.0f, 1.0f  // 4
  };
  memcpy(result, n, 16 * sizeof(float));
}

void mkRotation2x2(float a, float *result) {
  float s = sin(a);
  float c = cos(a);
  float n[4] = {c, s, -s, c};
  memcpy(result, n, 4 * sizeof(float));
}

#endif
