#include <mission.h>

int visualizeDistribution() {
    double _start = -3.0;
    double _end = 3.0;
    int segs = 18;
    double gap = (_end - _start) / segs;
    sail::GaussianDistribution1D gd;
    std::vector<float> data; // = {1.0f, 3.0f, 2.0f, 4.0f, 1.0f};
    for (auto i = 0; i < segs-1; i++) {
        data.push_back(static_cast<float>(gd(_start+i*gap, _start+(i+1)*gap)));
    }    

    int res = drawHistogram(data);
    return res;
}