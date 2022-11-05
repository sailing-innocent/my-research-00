#ifndef MISSION_H_
#define MISSION_H_

#include <iostream>
#include <sail/math.h>
#include <sail/ui/figure.h>
#include <ing/app/vk_canvas.hpp>

const std::string vertShaderPath = "E:/assets/shaders/canvas/vert.spv";
const std::string fragShaderPath = "E:/assets/shaders/canvas/frag.spv";

int drawRect2D();
int drawTriangle();
int drawHistogram(std::vector<float>& data);
int visualizeDistribution();

#endif // MISSION_H_