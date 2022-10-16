# Install script for directory: /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCGAL_Qt5x" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/CGAL/Qt" TYPE DIRECTORY FILES "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/include/CGAL/Qt/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/CGAL" TYPE FILE FILES
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/AUTHORS"
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/CHANGES.md"
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/LICENSE"
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/LICENSE.GPL"
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/LICENSE.LGPL"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/include/CGAL" REGEX "/\\.svn$" EXCLUDE REGEX "/Qt$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/scripts/cgal_create_CMakeLists"
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/scripts/cgal_create_cmake_script"
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/scripts/cgal_make_macosx_app"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/CGAL" TYPE DIRECTORY FILES "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/cmake/modules/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/CGAL" TYPE FILE FILES "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/cmake/modules/UseCGAL.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/CGAL" TYPE FILE FILES
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/lib/cmake/CGAL/CGALConfig.cmake"
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/lib/cmake/CGAL/CGALConfigBuildVersion.cmake"
    "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/lib/cmake/CGAL/CGALConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/auxiliary/cgal_create_cmake_script.1")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CGAL-5.5/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
