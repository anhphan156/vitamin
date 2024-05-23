#include "math/math.h"
#include "renderer/mesh.h"
#include "renderer/stdinc.h"
#include "renderer/window.h"

int main() {
  GLFWwindow *window = GetWindow();
  if (window == NULL) {
    return 1;
  }

  glewInit();

  float positions[] = {-.5f,  -.5f,  1.0f, 0.0f, 0.0f, 0.0, 0.0,
                       .5f,   .5f,   0.0f, 0.0f, 1.0f, 1.0, 1.0,
                       -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 0.0, 1.0,
                       0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0, 0.0};

  unsigned int indices[6] = {0, 1, 2, 0, 3, 1};

  struct Mesh *mesh = CreateMesh(positions, 28, indices, 6);

  float rotation[4];

  while (!glfwWindowShouldClose(window)) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    GLCall(glBindVertexArray(mesh->vao));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo));
    GLCall(glUseProgram(mesh->shader_program));

    GLCall(int loc = glGetUniformLocation(mesh->shader_program, "u_r"));
    if (loc != -1) {
      double t = glfwGetTime();
      mkRotation2x2(t, rotation);
      GLCall(glUniformMatrix2fv(loc, 1, GL_FALSE, rotation));
    }

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  ClearMesh(mesh);
  glfwTerminate();

  return 0;
}
