cmake_minimum_required(VERSION 2.8.3)
project(my_action_server)

find_package(catkin_simple REQUIRED)
# example boost usage
find_package(Boost REQUIRED COMPONENTS system thread)
catkin_simple()

# Executables
cs_add_executable(my_action_server src/my_action_server.cpp)
cs_add_executable(my_action_client src/my_action_client.cpp)
cs_install()
cs_export()
    
