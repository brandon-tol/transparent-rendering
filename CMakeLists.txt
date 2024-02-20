cmake_minimum_required(VERSION 3.12)
project(transparent-rendering LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

# Add the subdirectories
add_subdirectory(lib/glfw)
add_subdirectory(lib/glew/build/cmake)

# Add your source files here
file (GLOB SOURCES
    src/*.cpp
)

# Add any additional libraries or dependencies here
set(LIBRARIES
    OpenGL::GL
    glfw
    glew
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add the include directories
target_include_directories(${PROJECT_NAME} PRIVATE src ${LIBRARIES} lib/glew/include/)

# Link the libraries
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
