#include <ros/ros.h>
#include <example_ros_service/PathSrv.h> // this message type is defined in the current package
#include <iostream>
#include <string>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Bool.h>
using namespace std;
bool g_lidar_alarm=false;
void alarmCallback(const std_msgs::Bool& alarm_msg) 
{ 
  g_lidar_alarm = alarm_msg.data; //make the alarm status global, so main() can use it
if (g_lidar_alarm) {
     ROS_INFO("danger robot will halt!");}
else
{ROS_INFO("ROBOT RUNNING");}

}


geometry_msgs::Quaternion convertPlanarPhi2Quaternion(double phi) {
    geometry_msgs::Quaternion quaternion;
    quaternion.x = 0.0;
    quaternion.y = 0.0;
    quaternion.z = sin(phi / 2.0);
    quaternion.w = cos(phi / 2.0);
    return quaternion;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "path_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<example_ros_service::PathSrv>("path_service");
    
    geometry_msgs::Quaternion quat;
    
    while (!client.exists()) {
      ROS_INFO("waiting for service...");
      ros::Duration(1.0).sleep();
    }
    ROS_INFO("connected client to service");
    example_ros_service::PathSrv path_srv;
    ros::Subscriber alarm_subscriber = n.subscribe("lidar_alarm",1,alarmCallback);//subscribed to lidar_alarm
    
    //create some path points...this should be done by some intelligent algorithm, but we'll hard-code it here
    geometry_msgs::PoseStamped pose_stamped;
    geometry_msgs::Pose pose;
while(ros::ok()){
if(!g_lidar_alarm){
    pose_stamped.pose.orientation = quat;
    pose_stamped.pose.position.x=1.0;   
    pose_stamped.pose.position.y=0.0; 
    path_srv.request.nav_path.poses.push_back(pose_stamped);
 client.call(path_srv);
}
else{//If it has come here means lidar_alarm signal is true!!
pose_stamped.pose.orientation = quat;
    pose_stamped.pose.position.x=0.0;//pose to halt the robot.   
    pose_stamped.pose.position.y=0.0; 
ROS_INFO("ROBOT HALTED");
    path_srv.request.nav_path.poses.push_back(pose_stamped);
client.call(path_srv);}
    

}
    

   

    return 0;
}
