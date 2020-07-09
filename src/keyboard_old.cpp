#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"

#include "std_msgs/Int64.h"
#include <ros/package.h>

#include <sstream>


void key_callback(const std_msgs::Int64::ConstPtr& k){
    ROS_INFO("key: %ld",k->data);
    ros::NodeHandle n;

  ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

  ros::Rate loop_rate(10);

 int count = 0;
  while (ros::ok())
  {

      geometry_msgs::Twist msg;
      int c = k->data;
     
      msg.linear.x = (double)(c%10 +2)/4.0;
      msg.linear.y = (double)(c%10 +2)/4.0;
      msg.linear.z = 0;

      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = (double) (c%3);

  
   if(c >= 49 && c <= 57){
       msg.linear.x = double((c-49)/2.0);
      msg.linear.y = 0;
      msg.linear.z = 0;

      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = 0;

   }
   // -stop
   if(c == 32){
       msg.linear.x = 0;
      msg.linear.y = 0;
      msg.linear.z = 0;

      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = 0;
   }
//119 -w
    if(c == 119){
       msg.linear.x =double((c%8)/2.0);
      msg.linear.y = 0;
      msg.linear.z = 0;

      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = 0;
   }
   //100 -d
 if(c == 115){
       msg.linear.x = -2.0;
      msg.linear.y = 0;
      msg.linear.z = 0;

      msg.angular.x =0;
      msg.angular.y = 0;
      msg.angular.z = 0;
   }

   //97 -a
    if(c == 119){
       msg.linear.x = 0;
      msg.linear.y = 0;
      msg.linear.z = 2.0;

      msg.angular.x =0;
      msg.angular.y = 0;
      msg.angular.z = 0;
   }
 //100 -d
    if(c == 119){
       msg.linear.x = 0;
      msg.linear.y = -2.0;
      msg.linear.z = 0;

      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = 0;
   }
    vel_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

}



int main(int argc, char **argv){
      ros::init(argc, argv, "turtleKey");
      ros::NodeHandle node;

      ros::Subscriber sub_key = node.subscribe("/key_pressed", 1000,key_callback);

      ros::spin();
}