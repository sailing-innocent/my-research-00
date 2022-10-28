/**
 * @file: src/plane-draw
 * For this project I am going to 
 * initialize the model using sail
 * output the visualization info (vertices & indecies)
 * show the visualization info on ing window (vulkan backend)
 * @advance: uniform update call by sail solver ( input dt, output new)
*/

#include <iostream>
#include <sail/math/geometry.h>
#include <ing/app/vk_canvas.hpp>

const std::string vertShaderPath = "E:/assets/shaders/canvas/vert.spv";
const std::string fragShaderPath = "E:/assets/shaders/canvas/frag.spv";

int main() { 
    sail::point p1(-0.5, 0.0, 0.0, 1.0);
    sail::point p2(0.5, 0.0, 0.0, 1.0);
    sail::point p3(0.0, 0.5, 0.0, 1.0);
    sail::Triangle tri(p1, p2, p3);
    sail::VTriangle vtri;
    tri.visualize(vtri);

    std::vector<float> vf;
    std::vector<uint16_t> iu;
    vtri.genING(vf, iu);
/*
    for (auto f: vf) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
    for (auto i: iu) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
*/

    ing::CanvasApp app(vertShaderPath, fragShaderPath);

    if (!app.setVertex(vf, vf.size())) {
        std::cout << "Init Vertices Failed~" << std::endl;
    }
    if (!app.setIndex(iu, iu.size())) {
        std::cout << "Init Indices Failed" << std::endl;
    }

    
    try {
        app.init();
        app.run();
        app.terminate();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return 0;
}

