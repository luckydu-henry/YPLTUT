#include <pltut/window.h>
#include <pltut/context.h>
#include <pltut/except.h>
#include <iostream>

#if defined _WIN32
#pragma comment (linker, "/subsystem:console")
#pragma comment (lib, "OpenGL32.lib")
#include <Windows.h>
#endif //! _WIN32

#include <GL/gl.h>
#include <cmath>

float angle2redian(float angle)
{
    return angle * 3.1415926f / 180.f;
}

int main(int argc, char* argv[])
{
    //! Error handling.
    try
    {
        yan::wndconfig cfg;

        cfg.width = yan::window::get_screenprop(yan::scrwidth);
        cfg.height = yan::window::get_screenprop(yan::scrheight);
        cfg.title = "AWindow";
        cfg.is_fullscreen = false;

        yan::window wnd(cfg);
        yan::gl_rndr_context ctx(2, 1);

        ctx.init_on_handle(wnd.native_handle());
        wnd.show();

        std::cout << glGetString(GL_VERSION) << std::endl;

        float c = 0.0f;

        //! This line of code can set the repeat state.
        //! If you want to loop input a key by pressing it
        //! you might want to set this to true - however
        //! if you prefer to press a key only for once, you
        //! should set this to false or just by default.
        wnd.kmhandle().set_autorepeat(true);
        
        float ratio = 0.64f;

        while (!wnd.close())
        {
            auto delta = std::sin(c) / 2.0f + 0.5f;
            //! Update events.
            //! Do your things here.

            
            if (wnd.kmhandle().get_key(yan::scancode_e::Q).is_pressed)
                wnd.full_screen(true);
            if (wnd.kmhandle().get_key(yan::scancode_e::M).is_pressed)
                wnd.full_screen(false);
            if (wnd.kmhandle().get_key(yan::scancode_e::M).is_pressed)
                wnd.cursor_display(false);
            if (wnd.kmhandle().get_key(yan::scancode_e::H).is_pressed &&
                wnd.kmhandle().get_mod(yan::mod_e::lshift))
                wnd.cursor_display(true);
            if (wnd.kmhandle().get_key(yan::scancode_e::escape).is_pressed)
                wnd.close();

            //! This line of code is neccesarry!
            wnd.kmhandle().flush();

            glViewport(0, 0, wnd.get_size(yan::scrwidth),
             wnd.get_size(yan::scrheight));

            
            glLoadIdentity();
            glDisable(GL_BLEND);

            glClearColor(delta, 0.3f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Draw one circle and its out square with OpenGL.
            glBegin(GL_POLYGON);
                // Full circle.
                glColor3f(1.0f, 0.0f, 0.0f);
                for (std::size_t i = 0; i < 360; ++i)
                {
                    // Need to do this cast because std::sin/cos uses redian
                    // instead of angle.
                    float redian = angle2redian(float(i));

                    float x = std::cos(redian);
                    float y = std::sin(redian);

                    glVertex2f(ratio * x, y);
                }
                glColor3f(0.f, 1.f, 0.f);
                for (std::size_t j = 0; j < 4; ++j)
                {
                    float redian = angle2redian(float(j * 90));

                    float x = std::cos(redian);
                    float y = std::sin(redian);

                    glVertex2f(ratio * x, y);
                }
            glEnd();

            //! Your own drawing up.
            ctx.swap_frame();
            wnd.poll_events();
            c += 0.01f;
        }
        return 0;
    }
    //! Error Handling functions.
    //! Catch three kinds of errors.
    catch (const yan::except& e)
    {
        std::cerr << '[' << e.err_type() << ']' << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "[STD EXCEPTION]" << e.what() << std::endl;
    }
    return 0;
}