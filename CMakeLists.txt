cmake_minimum_required(VERSION 3.16)
project(GrafikaLabor LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- GLFW (system package) ---
find_package(glfw3 3.3 REQUIRED)

# --- OpenGL ---
find_package(OpenGL REQUIRED)

# --- GLAD (bundled) ---
add_library(glad STATIC
    ${CMAKE_SOURCE_DIR}/Libraries/Glad/src/glad.c
)
target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/Libraries/Glad/include
)

# --- GLM (header-only, bundled) ---
set(GLM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Libraries/glm/include)

# --- Source files (framework + lodepng, always compiled) ---
set(FRAMEWORK_SOURCES
    glProgram/sources/framework.cpp
    glProgram/sources/framework.h
    glProgram/sources/glad.c
    glProgram/sources/lodepng.cpp
    glProgram/sources/lodepng.h
)

# --- Skeleton.cpp is always the main application entry ---
set(APP_SOURCES
    glProgram/sources/GreenTriangle/Skeleton.cpp
)

add_executable(${PROJECT_NAME}
    ${FRAMEWORK_SOURCES}
    ${APP_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/glProgram/sources
    ${CMAKE_SOURCE_DIR}/Libraries/Glad/include
    ${CMAKE_SOURCE_DIR}/Libraries/glfw-3.4.bin.WIN64/include
    ${GLM_INCLUDE_DIR}
)

# _HAS_CXX17 is MSVC-specific; define it so framework.h picks std::filesystem
target_compile_definitions(${PROJECT_NAME} PRIVATE _HAS_CXX17=1)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::GL
    glad
    ${CMAKE_DL_LIBS}
)
