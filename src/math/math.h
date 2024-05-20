#include <string.h>

struct mat2 {
    float n[4];
};

struct mat2 mkMat2(float n[4]){
    struct mat2 m;
    memcpy(m.n, n, 4);
    return m;
}
