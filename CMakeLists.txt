cmake_minimum_required(VERSION 2.8)
project( Eigenfaces )
find_package(OpenCV REQUIRED)

add_library (eigenfaces src/eigenfaces.cpp)
add_executable(main src/main.cpp)

add_definitions(-Wall)

target_link_libraries(main ${OpenCV_LIBS})
target_link_libraries(main eigenfaces)



add_executable(celeb src/celeb.cpp)

add_definitions(-Wall)
add_definitions(-std=c++11)
target_link_libraries(celeb ${OpenCV_LIBS})
target_link_libraries(celeb eigenfaces)