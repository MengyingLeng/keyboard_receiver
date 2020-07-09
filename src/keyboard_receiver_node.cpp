/*=======================================================
created by Hui Xiao - University of Washington - 2018
hui.xiao@uw.edu
========================================================*/
#include <iostream>
#include "ros/ros.h"
#include "opencv2/highgui/highgui.hpp"
#include "std_msgs/Int64.h"
#include <ros/package.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "keyboard_receiver");
    ros::NodeHandle nh;
    ros::Publisher msg_pub = nh.advertise<std_msgs::Int64>("key_pressed",3);

    cv::namedWindow("keyboard capturing window",1);
    std::string package_path = ros::package::getPath("keyboard_receiver");
    cv::Mat image = cv::imread(package_path + "/pictures/JonathanStill.jpg");
    std_msgs::Int64 key_msg;
    while(ros::ok())
    {
        cv::imshow("keyboard capturing window",image);
        int key = cv::waitKey(1000) & 0xFF;
        if (key != -1 and key != 255)
        {
            key_msg.data = key;
            msg_pub.publish(key_msg);
        }
        ros::spinOnce();
    }
}
