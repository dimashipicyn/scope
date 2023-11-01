cmake_minimum_required(VERSION 3.20.0)
project(scope VERSION 0.1.0 LANGUAGES C)

add_subdirectory(libs)
add_executable(${PROJECT_NAME})
add_subdirectory(source)

target_include_directories(${PROJECT_NAME} PRIVATE
    source
    libs/SDL/include
    libs/glew-cmake/include
    #libs/cglm/include
)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
	SDL2::SDL2main
    ${OPENGL_LIBRARY}
    glew_s
    cglm
)

if (MSVC)
target_compile_options(${PROJECT_NAME} PUBLIC /Wall)
else()
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Werror -pedantic -Wno-language-extension-token -Wno-static-in-inline)
endif()

if(ASAN_ENABLED)
  if(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /fsanitize=address)
  else()
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
    target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
  endif()
endif()
