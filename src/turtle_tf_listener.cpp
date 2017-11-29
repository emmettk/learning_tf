/*
 * From wiki.ros.org/tf/Tutorials/Writing a tf broascaster
 * Version by E. Krupczak - 29 Nov 2017
 */
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;

  ros::service::waitForService("spawn");
  ros::ServiceClient add_turtle =
    node.serviceClient<turtlesim::Spawn>("spawn");
  turtlesim::Spawn srv;
  add_turtle.call(srv);

  ros::Publisher turtle_vel =
    node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

  tf::TransformListener listener;

  ros::Rate rate(10.0);
  while (node.ok()){
    tf::StampedTransform transform;
    // original version of code to call listener
    /*  try{
     listener.lookupTransform("/turtle2", "/turtle1",
                               ros::Time(0), transform);
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }
    */
    //Better version using waitForTransform
    //Can be modified to have turtle2 chase carrot1 rather than turtle1
    try {
      //set "now" to be a specific "now" so we can use the same value twice
      ros::Time now = ros::Time::now();
      //Set a time in the past (duration takes seconds as arg)
      ros::Time past = ros::Time::now() - ros::Duration(5.0);
      listener.waitForTransform("/turtle2", "/turtle1", past, ros::Duration(10.0) );
      listener.lookupTransform("/turtle2", "/turtle1",past, transform);
    } catch (tf::TransformException ex) {
      ROS_ERROR("%s",ex.what());
    }
    
    geometry_msgs::Twist vel_msg;
    vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(),
                                    transform.getOrigin().x());
    vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) +
                                  pow(transform.getOrigin().y(), 2));
    turtle_vel.publish(vel_msg);

    rate.sleep();
  }
  return 0;
};
