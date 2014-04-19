project(hosslib)
cmake_minimum_required(VERSION 2.6)

# 
# find boost libraries and headers.
#
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options filesystem system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
message( "BOOST: ${Boost_LIBRARY_DIRS}")

# check for Doxygen to generate doxygen
FIND_PACKAGE(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in 
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} 
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

enable_testing()

include_directories ( include include/os )

add_library(hosslib SHARED 
    src/environment.cpp
    src/posix/backtrace_handler.cpp
    src/posix/libinit.cpp
    )
    
INSTALL_FILES( . .so hosslib )

#add_executable ( launch unittests/launch.cpp )

add_executable ( hosslibtest unittests/cppunit-test-main.cpp
                 unittests/test-environment.cpp
                )
target_link_libraries( hosslibtest hosslib cppunit )
#target_link_libraries( launch hosslib  ${Boost_LIBRARIES})
add_test( hosslibtest hosslibtest)     