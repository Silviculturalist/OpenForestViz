cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(forestviewer)

#Find dependencies using vcpkg.json
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)

#stb is header only.
find_path(STB_INCLUDE_DIRS "stb_image.h")

#add executable
add_executable(main source/main.cpp)
target_include_directories(main
  PRIVATE
    ${STB_INCLUDE_DIRS}
    "${CMAKE_CURRENT_LIST_DIR}/source"
) 

target_link_libraries(
        main
        PRIVATE
          glfw
          glad::glad
          glm::glm
          imgui::imgui
)