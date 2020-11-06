cmake_minimum_required(VERSION 2.4)

set(CMAKE_CXX_STANDARD 11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(imagematch)

set( BASE_DIR ${CMAKE_SOURCE_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/bin )
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
  STRING( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
  SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BASE_DIR}/bin )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(TARGET matcher)

find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(${TARGET} src/main.cpp)

target_link_libraries( ${TARGET} ${OpenCV_LIBS} )
install(TARGETS ${TARGET} DESTINATION bin)
