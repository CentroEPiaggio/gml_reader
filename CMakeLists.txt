cmake_minimum_required(VERSION 2.8)

project(gmlreader)

ENABLE_LANGUAGE(CXX)
set(CMAKE_BUILD_TYPE "Debug")

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
#   rviz_visual_tools
#   eigen_conversions
)

find_package(catkin COMPONENTS lemon_ros QUIET)

find_package(catkin COMPONENTS graph_msgs QUIET)

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

list(APPEND MY_SRCS src/utils.cpp src/node.cpp src/graph.cpp src/arc.cpp)

# if(lemon_ros_FOUND)
# 
#    MESSAGE("found lemon, linking additional wrapper")
#    list(APPEND MY_SRCS src/optional_dep1_code.cpp)
#    list(APPEND MY_LINK_INCLUDE_DIRS ${optional_dep1_INCLUDE_DIRS})
#    list(APPEND MY_LINK_LIBRARIES ${optional_dep1_LIBRARIES})
    # Anything else you need to do to enable use of the optional dep, like add definitions
#    add_definitions("-DUSE_OPTIONAL_DEP1=1")
# endif()

# if(graph_msgs_FOUND)
# 
#    MESSAGE("found graph_msgs, linking additional wrapper")
#    list(APPEND MY_SRCS src/optional_dep1_code.cpp)
#    list(APPEND MY_LINK_INCLUDE_DIRS ${optional_dep1_INCLUDE_DIRS})
#    list(APPEND MY_LINK_LIBRARIES ${optional_dep1_LIBRARIES})
    # Anything else you need to do to enable use of the optional dep, like add definitions
#    add_definitions("-DUSE_OPTIONAL_DEP1=1")
# endif()

add_library(${PROJECT_NAME} SHARED ${MY_SRCS})


target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
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


