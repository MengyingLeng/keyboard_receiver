#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"

#include "std_msgs/Int64.h"
#include <ros/package.h>

#include <sstream>

class TurtleController{
   public:
   TurtleController(){
      // ROS_INFO("pub");
      vel_pub = node1.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 2);
      // ROS_INFO("sub");
      sub_key = node2.subscribe("/key_pressed", 2,&TurtleController::callback, this);
      // ROS_INFO("end");

   }
   void callback(const std_msgs::Int64::ConstPtr& k){
      // ROS_INFO("callback_function");
      ROS_INFO("key: %ld",k->data);
      //ros::NodeHandle n;


       ros::Rate loop_rate(10);

       int count = 0;
       geometry_msgs::Twist msg;
      int c = k->data;
     
      msg.linear.x = (double)(c%10 +2)/4.0;
      msg.linear.y = (double)(c%10 +2)/4.0;
      msg.linear.z = 0;

      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = (double) (c%3);

// using 1-9 to control the speed 
   if(c >= 49 && c <= 57){
       msg.linear.x = double((c-49)/2.0);
      msg.linear.y = 0;
      msg.linear.z = 0;

      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = 0;

   }
   // using space to stop
   if(c == 32){
       msg.linear.x = 0;
      msg.linear.y = 0;
      msg.linear.z = 0;

      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = 0;
   }
//using w to moving forward
    if(c == 119){
       msg.linear.x =double((c%8)/2.0);
      msg.linear.y = 0;
      msg.linear.z = 0;

      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = 0;
   }
   //using d to moving backward
 if(c == 115){
       msg.linear.x = -double((c%8)/2.0);
      msg.linear.y = 0;
      msg.linear.z = 0;

      msg.angular.x =0;
      msg.angular.y = 0;
      msg.angular.z = 0;
   }


      vel_pub.publish(msg);
      // ros::spinOnce();
      // loop_rate.sleep();

}
protected:
      ros::NodeHandle node1;
      ros::NodeHandle node2;
      ros::Subscriber sub_key;
      ros::Publisher vel_pub;


};




int main(int argc, char **argv){
      ros::init(argc, argv, "turtleKey");
      // ROS_INFO("Start");
      TurtleController t;

      ros::spin();
      return 0;
}