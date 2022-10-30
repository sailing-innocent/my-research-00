#include <mission.h>

int drawTriangle() {
    sail::point p1(-0.5, 0.0, 0.0, 1.0);
    sail::point p2(0.5, 0.0, 0.0, 1.0);
    sail::point p3(0.0, 0.5, 0.0, 1.0);
    sail::Triangle tri(p1, p2, p3);
    sail::VTriangle vtri;
    tri.visualize(vtri);

    std::vector<float> vf;
    std::vector<uint16_t> iu;
    vtri.genING(vf, iu);

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
int drawRect2D() {
    sail::point lb(-0.5f, -0.5f, 0.0f, 1.0f);
    float width = 1.0f;
    float height = 1.0f;
    sail::Rect2D rec(lb, width, height);
    sail::VisNode vn;
    rec.visualize(vn);
    std::vector<float> vf;
    std::vector<uint16_t> iu;
    vn.genING(vf, iu);

    std::cout << "["; 
    for (auto i: iu) {
        std::cout << i << ",";
    }
    std::cout << "]" << std::endl;
    // iu[5] = 3;
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