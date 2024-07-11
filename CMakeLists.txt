cmake_minimum_required(VERSION 3.0.0)
project(Car VERSION 0.1.0 LANGUAGES C CXX)
set(OPENCV_ENABLE_NONFREE ON CACHE BOOL "Enable non-free algorithms")
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
enable_testing()
include(CTest)
add_executable(Car main.cpp)
target_link_libraries(Car ${OpenCV_LIBS})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



# cmake_minimum_required(VERSION 3.0.0)
# project(prac VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# set(OPENCV_ENABLE_NONFREE ON CACHE BOOL "Enable non-free algorithms")
# find_package(OpenCV)
# include_directories(${OpenCV_INCLUDE_DIRS})
# enable_testing()

# add_executable(prac parallel.cpp)
# target_link_libraries(prac ${OpenCV_LIBS})

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
