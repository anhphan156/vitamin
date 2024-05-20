#ifndef MATH_H
#define MATH_H
#include <string.h>
#include <math.h>

void mkRotation2x2(float a, float* result){
    float s = sin(a);    
    float c = cos(a);
    float n[4] = { c, s, -s, c };
    memcpy(result, n, 4 * sizeof(float));
}

#endif
