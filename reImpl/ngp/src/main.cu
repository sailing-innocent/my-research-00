#include <neural-graphics-primitives/common.h>
#include <neural-graphics-primitives/testbed.h>

#include <tiny-cuda-nn/common.h>

// #include <args/args.hxx>
// #include <filesystem/path.h>

// using namespace args;
using namespace ngp;
using namespace std;
using namespace tcnn;

// namespace fs = ::filesystem;

int main(int argc, char** argv) {
    // parsers
    try {
        // mode
        ETestbedMode mode;
        // switch mode flag 
        mode = ETestbedMode::Nerf;

        // testbed
        Testbed testbed{mode};
        // testbed.load_traning_data()

        std::string mode_str;
        // switch mode str
        mode_str = "nerf";

        // snapshot?

        // gui?
        bool gui = true;
#ifndef NGP_GUI
    gui = false
#endif
        if (gui) {
            testbed.init_window(1920, 1080, false, false);
        }

        // Render/Training Loop
        //  while (testbed.frame()) {
            // if no gui, log
        // }
    } catch (const exception& e) {
        // error log
        return 1;
    }
}