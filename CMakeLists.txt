cmake_minimum_required(VERSION 3.5)

project(clicker)

set(Header_Files
    "Dependencies/imgui/imgui/imconfig.h"
    "Dependencies/imgui/imgui/imgui.h"
    "Dependencies/imgui/imgui/imgui_impl_glfw.h"
    "Dependencies/imgui/imgui/imgui_impl_opengl3.h"
    "Dependencies/imgui/imgui/imgui_impl_opengl3_loader.h"
    "Dependencies/imgui/imgui/imgui_internal.h"
    "Dependencies/imgui/imgui/imstb_rectpack.h"
    "Dependencies/imgui/imgui/imstb_textedit.h"
    "Dependencies/imgui/imgui/imstb_truetype.h"
    "src/application.h"
    "src/clicker/clicker.h"
    "src/ui/ui.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Dependencies/imgui/imgui/imgui.cpp"
    "Dependencies/imgui/imgui/imgui_demo.cpp"
    "Dependencies/imgui/imgui/imgui_draw.cpp"
    "Dependencies/imgui/imgui/imgui_impl_glfw.cpp"
    "Dependencies/imgui/imgui/imgui_impl_opengl3.cpp"
    "Dependencies/imgui/imgui/imgui_tables.cpp"
    "Dependencies/imgui/imgui/imgui_widgets.cpp"
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

target_include_directories(clicker PUBLIC
    "Dependencies/imgui"
    "Dependencies/GLEW/include"
    "Dependencies/glfw/include"
)

target_link_directories(clicker PRIVATE
    "Dependencies/glfw/lib-vc2022"
    "Dependencies/GLEW/lib/Release/x64"
)

target_link_libraries(clicker PRIVATE
    "glfw3"
    "glfw3_mt"
    "opengl32"
    "glew32s"
)