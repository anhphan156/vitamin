#ifndef IMGUI_INCLUDES_H
#define IMGUI_INCLUDES_H

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define CIMGUI_USE_OPENGL3
#define CIMGUI_USE_GLFW
#include "cimgui.h"
#include "cimgui_impl.h"

#define IMGUI_NEW_FRAME                                                        \
  ImGui_ImplOpenGL3_NewFrame();                                                \
  ImGui_ImplGlfw_NewFrame();                                                   \
  igNewFrame();

#define IMGUI_RENDER                                                           \
  igRender();                                                                  \
  ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());                           \
/*if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) { \*/
/*  GLFWwindow *backup_current_window = glfwGetCurrentContext(); \*/
/*  igUpdatePlatformWindows(); \*/
/*  igRenderPlatformWindowsDefault(NULL, NULL); \*/
/*  glfwMakeContextCurrent(backup_current_window); \*/
/*}*/

#endif
