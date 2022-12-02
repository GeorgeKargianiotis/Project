# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.1...3.23)

#project( polygonization )
project( optimal_polygon )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE__CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )

  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()  

endif()


# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )

  message(STATUS "This project requires the Boost library, and will not be compiled.")

  return()  

endif()

# include for local directory
add_subdirectory(sources)
include_directories(headers)
list(APPEND EXTRA_LIBS utils incremental convex_hull local_search simulated_annealing)
# include for local package

# Creating entries for target: polygonization
# ############################

#add_executable( polygonization polygonization.cpp )
add_executable( optimal_polygon optimal_polygon.cpp )

add_to_cached_list( CGAL_EXECUTABLE_TARGETS optimal_polygon )

# Link the executable to CGAL and third-party libraries
target_link_libraries(optimal_polygon PRIVATE CGAL::CGAL ${EXTRA_LIBS})