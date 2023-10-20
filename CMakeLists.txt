cmake_minimum_required(VERSION 3.25)

project("3D-Engine")
set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

set(SOURCE_FILES
        main.cpp

        external/glad/src/glad.c
        external/glm/glm/glm.hpp

        src/window.cpp
        include/Window.h
        src/Shader.cpp   include/Shader.h
        src/logging.cpp  include/logging.h
        src/vector.cpp   include/vector.h
        src/Entity_t.cpp include/Entity_t.h
        src/Camera.cpp   include/Camera.h
        src/Storage.cpp  include/Storage.h
        src/Scene.cpp    include/Scene.h

        src/PhysicsEngine.cpp  include/PhysicsEngine.h
        Scenes/main_scene.cpp  Scenes/main_scene.h

        Scenes/orth_scene.cpp Scenes/orth_scene.h

        src/CollisionEngine.cpp include/CollisionEngine.h

        include/DebugRendering/DebugBox.h
        src/DebugRendering/DebugBox.cpp

        include/DebugRendering/DebugEntry.h
        src/DebugRendering/DebugEntry.cpp
        src/DebugRendering/DebugLine.cpp
        include/DebugRendering/DebugLine.h
        Scenes/star_viewer.cpp
        Scenes/star_viewer.h
)


# add includes
include_directories(${PROJECT_SOURCE_DIR}/external/glad/include ${PROJECT_SOURCE_DIR}/external/glfw/include ${PROJECT_SOURCE_DIR}/external/glm/glm ${PROJECT_SOURCE_DIR}/include)

# add subdirectories with params
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/glfw)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(2D-Engine ${SOURCE_FILES})
target_include_directories(2D-Engine PUBLIC ${PROJECT_SOURCE_DIR}/external/glfw/include ${PROJECT_SOURCE_DIR}/external/glad/include ${OPENGL_INCLUDE_DIR})
target_link_libraries(2D-Engine ${OPENGL_gl_LIBRARY} ${GLFW3_LIBRARY} glfw)
