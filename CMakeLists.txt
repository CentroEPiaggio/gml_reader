cmake_minimum_required(VERSION 2.8)

project(gmlreader)

ENABLE_LANGUAGE(CXX)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


find_package(catkin REQUIRED COMPONENTS
  roslib
  roscpp
  rospy
  lemon_ros
  graph_msgs
#   rviz_visual_tools
#   eigen_conversions
)

# find_package(Eigen3 REQUIRED)

# add_message_files(
#   FILES
# 
# )
# 
# add_service_files(
#   FILES
# )


catkin_package(
  INCLUDE_DIRS include/
  LIBRARIES ${PROJECT_NAME}
#  CATKIN_DEPENDS roscpp
   #DEPENDS
   )
include_directories(include ${catkin_INCLUDE_DIRS})

link_directories(${catkin_LIBRARY_DIRS})

add_executable(gml_to_lgf src/utils.cpp src/main.cpp src/node.cpp src/graph.cpp src/arc.cpp)
add_executable(test_gml src/utils.cpp src/testgml.cpp src/node.cpp src/graph.cpp src/arc.cpp)

add_library(${PROJECT_NAME} SHARED src/utils.cpp src/node.cpp src/graph.cpp src/arc.cpp)

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} lemon)
target_link_libraries(test_gml ${catkin_LIBRARIES} lemon)
target_link_libraries(gml_to_lgf ${catkin_LIBRARIES})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME} gml_to_lgf
         EXPORT ${PROJECT_NAME}
#         ARCHIVE DESTINATION "${CATKIN_PACKAGE_BIN_DESTINATION}" COMPONENT lib
         RUNTIME DESTINATION "${CATKIN_PACKAGE_BIN_DESTINATION}" COMPONENT bin
         LIBRARY DESTINATION "${CATKIN_PACKAGE_LIB_DESTINATION}" COMPONENT shlib
)


