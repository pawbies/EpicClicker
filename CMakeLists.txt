cmake_minimum_required(VERSION 3.5)

project(clicker)

set(Header_Files
    "Dependencies/imgui/imconfig.h"
    "Dependencies/imgui/imgui.h"
    "Dependencies/imgui/backends/imgui_impl_glfw.h"
    "Dependencies/imgui/backends/imgui_impl_opengl3.h"
    "Dependencies/imgui/backends/imgui_impl_opengl3_loader.h"
    "Dependencies/imgui/imgui_internal.h"
    "Dependencies/imgui/imstb_rectpack.h"
    "Dependencies/imgui/imstb_textedit.h"
    "Dependencies/imgui/imstb_truetype.h"
    "src/application.h"
    "src/clicker/clicker.h"
    "src/ui/ui.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Dependencies/imgui/imgui.cpp"
    "Dependencies/imgui/imgui_demo.cpp"
    "Dependencies/imgui/imgui_draw.cpp"
    "Dependencies/imgui/backends/imgui_impl_glfw.cpp"
    "Dependencies/imgui/backends/imgui_impl_opengl3.cpp"
    "Dependencies/imgui/imgui_tables.cpp"
    "Dependencies/imgui/imgui_widgets.cpp"
    "src/application.cpp"
    "src/clicker/clicker.cpp"
    "src/main.cpp"
    "src/ui/ui.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

add_executable(clicker ${ALL_FILES})
add_subdirectory(Dependencies/glfw)
add_subdirectory(Dependencies/glew-cmake)

target_include_directories(clicker PUBLIC
    "Dependencies/imgui"
    "Dependencies/glew-cmake/include"
    "Dependencies/glfw/include"
)

target_link_libraries(clicker PRIVATE
    "glfw"
    "opengl32"
    "libglew_static"
)