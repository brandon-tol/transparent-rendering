cmake_minimum_required(VERSION 3.12)
project(transparent-rendering LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

# Setup the macro for build path
add_compile_definitions(FILE_ROOT="${PROJECT_SOURCE_DIR}/")

# Add the subdirectories
add_subdirectory(lib/glfw)
add_subdirectory(lib/glew/build/cmake)
add_subdirectory(lib/glm)

# Add your source files here
file (GLOB SOURCES
    src/*.cpp
    src/*.h
)

# Add any additional libraries or dependencies here
set(LIBRARIES
    ${OPENGL_gl_LIBRARIES}
    glfw
    glew_s
    glm
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add the include directories
target_include_directories(${PROJECT_NAME} PRIVATE src ${LIBRARIES} lib/glew/include/)

# Link the libraries
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
