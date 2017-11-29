/*
 * From wiki.ros.org/tf/Tutorials/Adding a frame
 * Version by E. Krupczak - 29 Nov 2017
 */
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_broadcaster");
  ros::NodeHandle node;

  tf::TransformBroadcaster br;
  tf::Transform transform;

  ros::Rate rate(10.0);
  while (node.ok()){
    
    //Constant offset version
    //carrot1 frame is 2m offset to left of turtle1 frame
    // transform.setOrigin( tf::Vector3(0.0, 2.0, 0.0) );
    //transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
    
    //Moving offset version
    transform.setOrigin( tf::Vector3(2.0*sin(ros::Time::now().toSec()), 2.0*cos(ros::Time::now().toSec()), 0.0) );
    transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "turtle1", "carrot1"));
    rate.sleep();
  }
  return 0;
};
