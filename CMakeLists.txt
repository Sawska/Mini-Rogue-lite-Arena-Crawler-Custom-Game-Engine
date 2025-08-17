cmake_minimum_required(VERSION 3.16)
project(MiniRogueLiteArenaCrawler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Your source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Renderer2D.cpp
    src/ScriptManager.cpp
    src/AudioManager.cpp
    src/UIManager.cpp
    # Add other .cpp files as needed
)

add_executable(${PROJECT_NAME} ${SOURCES})

# SFML
find_package(SFML 3 REQUIRED COMPONENTS graphics window system)


# OpenGL
find_package(OpenGL REQUIRED)

# ImGui-SFML (manually cloned or added via submodule)
add_subdirectory(deps/imgui-sfml)

# Lua (installed via Homebrew)
find_package(PkgConfig REQUIRED)
pkg_search_module(LUA REQUIRED lua5.4)

# Includes
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${LUA_INCLUDE_DIRS}
)

# Linking
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    OpenGL::GL
    imgui-sfml
    ${LUA_LIBRARIES}
)

# ImGui requires this for proper icon support
if (APPLE)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourdomain.MiniRogueLiteArenaCrawler")
    set(CMAKE_MACOSX_BUNDLE TRUE)
endif()
