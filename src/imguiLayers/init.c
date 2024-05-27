#include "init.h"
#include "../renderer/stdinc.h"
#include "includes.h"

void gui_init(struct GLFWwindow *win, struct ImGuiContext **ctx,
              struct ImGuiIO **io) {
  // IMGUI_CHECKVERSION();
  *ctx = igCreateContext(NULL);
  *io = igGetIO();
  (*io)->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
  (*io)->ConfigFlags |=
      ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport
                                        // / Platform Windows

  const char *glsl_version = "#version 460 core";
  ImGui_ImplGlfw_InitForOpenGL(win, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Setup style
  igStyleColorsDark(NULL);
  GLCall();
}
