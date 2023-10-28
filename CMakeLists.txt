cmake_minimum_required(VERSION 3.20.0)
project(scope VERSION 0.1.0 LANGUAGES C)

add_executable(${PROJECT_NAME})
add_subdirectory(source)
add_subdirectory(libs)

target_include_directories(${PROJECT_NAME} PUBLIC source)
target_include_directories(${PROJECT_NAME} PUBLIC libs/SDL/include)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
	SDL2::SDL2main
    ${OPENGL_LIBRARY}
)

if (MSVC)
target_compile_options(${PROJECT_NAME} PUBLIC /Wall)
else()
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Werror -pedantic)
endif()

if(ASAN_ENABLED)
  if(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /fsanitize=address)
  else()
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
    target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
  endif()
endif()
