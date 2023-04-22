-- MIT License
-- 
-- Copyright (c) 2022 luckydu-henry
-- 
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
-- 
-- The above copyright notice and this permission notice shall be included in all
-- copies or substantial portions of the Software.
-- 
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
-- SOFTWARE.

add_rules("mode.debug", "mode.release")

g_yan_pltut_libtype = "shared"

target("libypltut")
    set_kind(g_yan_pltut_libtype)
    set_languages("c++20")

    add_includedirs("./include/")
    add_headerfiles("./include/pltut/*.h")    

    -- lib type switch
    if g_yan_pltut_libtype == "static"     then 
        add_defines("YAN_LIB_SHARED")
    elseif g_yan_pltut_libtype == "shared" then 
        add_defines("YAN_LIB_STATIC")
    end

    add_files("src/*.cpp")
    add_headerfiles("src/*.h")

    if is_plat("windows")   then
        add_headerfiles("src/win32/*.h")
        add_files("src/win32/*.cpp", "src/win32/*.c")
	    -- user32.lib is for Windows API functions.
	    -- like CreateWindowClass.
	    -- d3d11.lib is for Direct3D 11 stuff.
	    -- gdi32.lib is neccesarry when youu are creating wgl context.
	    -- OpenGL32.lib is for your OpenGL stuffs.
        add_links("user32", "d3d11", "gdi32", "OpenGL32")
    elseif is_plat("linux") then
        add_headerfiles("src/linux/*.h")
        add_files("src/linux/*.cpp", "src/linux/*.c")
        add_links("X11", "xcb", "GL", "Xfixes")
    end

    --[[
    after_build(function (target)
        os.cp("$(scriptdir)/res", "$(buildir)/$(plat)/$(arch)/$(mode)/")
    end)
    ]]--
target_end()

target("pltut-window-example")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("./include/")
    add_files("./example/*.cpp")
    add_deps("libypltut")
target_end()