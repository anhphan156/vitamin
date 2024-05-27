#ifndef IMGUI_INIT_H
#define IMGUI_INIT_H

struct GLFWwindow;
struct ImGuiContext;
struct ImGuiIO;

void gui_init(struct GLFWwindow *win, struct ImGuiContext **ctx,
              struct ImGuiIO **io);

#endif
