/* This node reads a parameter from the launch file
 * and prints it continuously to the console
 * This is just an example of how to get  a parameter from the launch file
 * Emmett Krupczak - 29 Nov 2017
 * WHOI ROS Short Course Assignment 2
 */

#include <ros/ros.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_node");
  ros::NodeHandle n;
  std::string s;
  while (n.ok()){
  if (n.getParam("param1", s))
    {
      ROS_INFO("Got param: %s", s.c_str());
    }
  else
    {
      ROS_ERROR("Failed to get param 'param1'");
    }
  }
  return 0;
};

//Reminder: rqt_console so you can see the exciting output!
