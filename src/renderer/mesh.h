#ifndef MESH_H
#define MESH_H

struct Mesh {
  unsigned int vao;
  unsigned int ibo;
  unsigned int vbo;
  unsigned int shader_program;
};

struct Mesh *CreateMesh(float *positions, unsigned int position_count,
                        unsigned int *indices, unsigned int index_count);

void ClearMesh(struct Mesh *);

#endif
