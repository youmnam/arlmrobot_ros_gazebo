cmake_minimum_required(VERSION 2.8.3)
project(arlmrobot_description)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs tf pcl_ros)
find_package( PCL REQUIRED )

catkin_package()

 
install(DIRECTORY launch meshes rviz urdf world
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)


include_directories(include ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pointcloudTransform src/pointcloudTransform.cpp)
target_link_libraries(pointcloudTransform ${PCL_LIBRARIES} ${catkin_LIBRARIES} )
