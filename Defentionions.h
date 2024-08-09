#include "imgui/imgui.h"



float ViewportWidth;
float ViewportHeight;
float ScreenCenterX;
float ScreenCenterY;
float AimFOV;
bool outlines = false;
ImDrawList* draw;
int red = 0;
int green = 255;
int blue = 255;
int segments = 50;
bool invisible = false;
int
g_width,
g_height,
g_pid
;
bool particles = false;
ImFont* m_pFont;
int tabb = 1;
bool showmenu = false;
bool initonce = false;
int outlinebit = 0;