cmake_minimum_required(VERSION 3.15)

project(CRS_MDrt VERSION 1.0
                 DESCRIPTION "Platform specific window and graphics and audio creation wrapper."
                 LANGUAGES C CXX)
# 针对所有平台都应添加的源文件。
file(GLOB COMMON_SRC     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.*")
file(GLOB COMMON_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.hpp" )
# 针对特定平台添加的源文件。
if    (WIN32)
    message("当前平台为 win32")
    file(GLOB PLAT_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/win32/*.*")
    set(LINK_LIST "OpenGL32")
elseif(UNIX)
    message("当前平台为 unix")
    file(GLOB PLAT_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/unix/*.*")
    set(LINK_LIST "GL")
endif (WIN32)

# CRS_ MDrt 只可以静态链接，因为这个库体量挺小的而且可以避免动态链接的一些问题。
add_library               (CRS_MDrt_lib STATIC ${COMMON_SRC} ${COMMON_HEADERS} ${PLAT_SRC})
target_include_directories(CRS_MDrt_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries     (CRS_MDrt_lib PUBLIC ${LINK_LIST})
target_compile_features   (CRS_MDrt_lib PUBLIC cxx_std_20)

# 测试用来检测库是否能够正常工作。
add_executable            (CRS_MDrt_test "test/window_test.cpp")
target_include_directories(CRS_MDrt_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features   (CRS_MDrt_test PUBLIC cxx_std_20)
target_link_libraries     (CRS_MDrt_test PUBLIC CRS_MDrt_lib)

message("配置完成!")