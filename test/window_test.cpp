#include <plat/window.hpp>
#include <plat/functions.hpp>
#include <plat/gfx_context.hpp>
#include <iostream>

int main(int argc, char* argv[]) {

    crs::plat::wndconfig cfg = crs::plat::window::get_best_config();
    cfg.title = "Hello!";
    crs::plat::window win(cfg);
    crs::plat::opengl_config GLcfg{ 3, 3 };

    crs::plat::gl_context ctx(GLcfg);
    ctx.init_on_handle(win.native_handle());
    win.show();

    crs::plat::wevent E;
    while (!win.close()) {
        // 事件处理
        while (win.poll_event(E)) {
            if (E.type == crs::plat::wevent::closed) win.close(true);
            if (E.type == crs::plat::wevent::kyprsd) {
                if (E.key.code == crs::plat::kybd::escape) win.close(true);
                if (E.key.code == crs::plat::kybd::Q) {
                    win.size({ 800, 600 });
                    win.style(crs::plat::styles::initsetting);
                }
                if (E.key.code == crs::plat::kybd::E) {
                    win.size({ 1366, 768 });
                    win.style(crs::plat::styles::fullscreen);
                }
                if (E.key.code == crs::plat::kybd::W) {
                    // 如果调用了该函数，务必在程序结束后将分辨率更改回去，否则就要手动调整。
                    crs::plat::resolution({ 640,480 });
                }
            }
        }

        ctx.clear_color(0.5f, 0.5f, 1.f);
        ctx.swap_buffers();
    }
    crs::plat::resolution({ cfg.width, cfg.height });
}