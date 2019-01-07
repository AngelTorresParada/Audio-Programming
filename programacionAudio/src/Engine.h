#pragma once
#ifndef LGFX_INCLUDED
#define LGFX_INCLUDED
#include "litegfx.h"
#endif
#include "stb_image.h"

ltex_t *loadTexture(const char *);
bool valInInterval(float value, float a, float b);
float clamp(float value, float low, float high);
float fract(float);
