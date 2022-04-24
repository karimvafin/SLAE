cmake_minimum_required(VERSION 3.17)
project(my_project)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE MY_PROJECT_SOURCES *.h *.cpp *.hpp)

#find_package(eigen3 REQUIRED)
## ... и подключим её со всеми её компонентами её нативными средствами
#include(${eigen_USE_FILE})

#add_library(gmsh SHARED IMPORTED)
#set_target_properties(gmsh PROPERTIES
#        IMPORTED_LOCATION "/Users/karimvafin/opt/anaconda3/envs/python006/lib/libgmsh.4.9.dylib"
#        INTERFACE_INCLUDE_DIRECTORIES "/Users/karimvafin/opt/anaconda3/envs/python006/include"
#        )
#set(GMSH_LIBRARY gmsh)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
if (WIN32)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -lrt ${CMAKE_CXX_STANDARD_LIBRARIES}")
endif (WIN32)

add_library(my_project ${MY_PROJECT_SOURCES})
target_link_libraries(my_project PUBLIC )

target_include_directories(my_project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
