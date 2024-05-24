#include "assimp/mesh.h"
#include "math/math.h"
#include "renderer/mesh.h"
#include "renderer/stdinc.h"
#include "renderer/window.h"

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

int main() {
  GLFWwindow *window = GetWindow();
  if (window == NULL) {
    return 1;
  }

  glewInit();

  /*const char model_path[52] =*/
  /*    "/home/backspace/data/dev/miso/resources/teapot.obj";*/
  const char model_path[54] =
      "/home/backspace/data/dev/miso/resources/WusonOBJ.obj";
  /*const char model_path[54] =*/
  /*    "/home/backspace/data/dev/miso/resources/huesitos.fbx";*/
  const struct aiScene *scene = aiImportFile(
      model_path, aiProcess_CalcTangentSpace | aiProcess_Triangulate);
  if (NULL == scene) {
    printf("%s\n", aiGetErrorString());
    return -1;
  }

  unsigned int vert_count = 8 * scene->mMeshes[0]->mNumVertices;
  float *vertices = (float *)malloc(sizeof(float) * vert_count);

  int i;
  for (i = 0; i < scene->mMeshes[0]->mNumVertices; i++) {
    float pos_x = scene->mMeshes[0]->mVertices[i].x;
    float pos_y = scene->mMeshes[0]->mVertices[i].y;
    float pos_z = scene->mMeshes[0]->mVertices[i].z;
    float normal_x = scene->mMeshes[0]->mNormals[i].x;
    float normal_y = scene->mMeshes[0]->mNormals[i].y;
    float normal_z = scene->mMeshes[0]->mNormals[i].z;

    float uv_x;
    float uv_y;
    if (scene->mMeshes[0]->mTextureCoords[0]) {
      uv_x = scene->mMeshes[0]->mTextureCoords[0][i].x;
      uv_y = scene->mMeshes[0]->mTextureCoords[0][i].y;
    } else {
      uv_x = 0.0f;
      uv_y = 0.0f;
    }

    vertices[i * 8 + 0] = pos_x;
    vertices[i * 8 + 1] = pos_y;
    vertices[i * 8 + 2] = pos_z;
    vertices[i * 8 + 3] = normal_x;
    vertices[i * 8 + 4] = normal_y;
    vertices[i * 8 + 5] = normal_z;
    vertices[i * 8 + 6] = uv_x;
    vertices[i * 8 + 7] = uv_y;
  }

  unsigned int indices_count = scene->mMeshes[0]->mNumFaces * 3;
  unsigned int *indices =
      (unsigned int *)malloc(sizeof(unsigned int) * indices_count);
  for (i = 0; i < scene->mMeshes[0]->mNumFaces; i++) {
    struct aiFace face = scene->mMeshes[0]->mFaces[i];
    for (unsigned int j = 0; j < 3; j++) {
      indices[i * 3 + j] = face.mIndices[j];
    }
  }

  /*float positions[] = {*/
  /*    -.5f,  -.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 0.0, 0.0, // 0*/
  /*    .5f,   .5f,   -0.5f, 0.0f, 0.0f, 1.0f, 1.0, 1.0, // 1*/
  /*    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0, 1.0, // 2*/
  /*    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0, 0.0, // 3*/
  /**/
  /*    -.5f,  -.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0, 0.0, // 4*/
  /*    .5f,   .5f,   0.5f,  0.0f, 0.0f, 1.0f, 1.0, 1.0, // 5*/
  /*    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0, 1.0, // 6*/
  /*    0.5f,  -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 1.0, 0.0  // 7*/
  /*};*/

  /*unsigned int indices[24] = {*/
  /*    0, 1, 2, // 1 front*/
  /*    0, 3, 1, // 2*/
  /*    4, 6, 5, // 3 back*/
  /*    4, 5, 7, // 4*/
  /*    3, 5, 1, // 5 side*/
  /*    3, 7, 5, // 6*/
  /*    0, 6, 4, // 7*/
  /*    0, 2, 6  // 8*/
  /*};*/

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);

  struct Mesh *mesh = CreateMesh(vertices, vert_count, indices, indices_count);

  float translation[16];
  float rotation[16];
  float perspective[16];
  float r[16];

  mkPerspective4x4(3.14f / 4.0f, GetAspectRatio(), 1.0f, 100.0f, perspective);

  while (!glfwWindowShouldClose(window)) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GLCall(glBindVertexArray(mesh->vao));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo));
    GLCall(glUseProgram(mesh->shader_program));

    GLCall(int loc = glGetUniformLocation(mesh->shader_program, "u_mvp"));
    if (loc != -1) {
      double t = glfwGetTime();
      float trans[3] = {0.0f, -0.5f, 5.0f};
      mkTranslation4x4(trans, translation);
      mkRotationY4x4(t, rotation);
      matrixMul(translation, rotation, r);
      matrixMul(perspective, r, r);
      GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, r));
    }

    GLCall(glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, NULL));

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  ClearMesh(mesh);
  aiReleaseImport(scene);
  free(vertices);
  free(indices);
  glfwTerminate();

  return 0;
}
