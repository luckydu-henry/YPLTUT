#include <MDrt/window.hpp>
#include <MDrt/functions.hpp>
#include <MDrt/gfx_context.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    using namespace CRS;

    try {
        MDrt::wndconfig cfg = CRS::MDrt::window::get_best_config();
        cfg.title = "Hello!";
        MDrt::window win(cfg);
        MDrt::OpenGL_config GLcfg{};
        GLcfg.major = 4;
        GLcfg.minor = 0;
        GLcfg.flags = MDrt::OpenGL_config::DEBUG_BIT_ARB;
        GLcfg.mask  = MDrt::OpenGL_config::CORE_PROFILE_BIT_ARB;

        MDrt::GL_context ctx(GLcfg);
        ctx.init_on_handle(win.native_handle());
        std::cout << ctx.version() << std::endl;
        win.show();

        MDrt::wevent E;
        while (!win.close()) {
            // 事件处理
            while (win.poll_event(E)) {
                if (E.type == MDrt::wevent::closed) win.close(true);
                if (E.type == MDrt::wevent::kyprsd) {
                    if (E.key.code == MDrt::kybd::escape) win.close(true);
                    if (E.key.code == MDrt::kybd::Q) {
                        win.size({ 800, 600 });
                        win.style(MDrt::styles::initsetting);
                    }
                    if (E.key.code == MDrt::kybd::E) {
                        win.size({ 1366, 768 });
                        win.style(MDrt::styles::fullscreen);
                    }
                    if (E.key.code == MDrt::kybd::W) {
                        // 如果调用了该函数，务必在程序结束后将分辨率更改回去，否则就要手动调整。
                        MDrt::resolution({ 640,480 });
                    }
                }
            }

            ctx.clear_color(0.5f, 0.5f, 1.f);
            ctx.swap_buffers();
        }
        MDrt::resolution({ cfg.width, cfg.height });
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}