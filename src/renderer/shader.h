#ifndef SHADER_H
#define SHADER_H
unsigned int create_shader_program(char *, char *);
unsigned int create_compute_shader_program(char *);

void uniform1f(unsigned int, char *, float);
void uniform1i(unsigned int, char *, int);
void uniformm4f(unsigned int, char *, float *);
void uniform3fv(unsigned int, char *, float *);
#endif
