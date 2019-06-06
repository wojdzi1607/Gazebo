#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <ncurses.h>
#include <stdio.h>

/**
 * Sterowanie Husky
 */


int main(int argc, char **argv)
{

	int w;
	double x;
	double y;
	double z;

	double fi;
	double omega;
	double teta;	

	x=y=z=teta=fi=omega=0.0;

 	ros::init(argc, argv, "sterowanie_husky_node");

 	ros::NodeHandle n;

 	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);

	ros::Rate loop_rate(1000);

 while (ros::ok())
 {
	geometry_msgs::Twist msg;

	system ("/bin/stty raw");
	w=getchar();
	system ("/bin/stty cooked");

	std::system("clear");
	printf("Sterowanie WASD \n");

	if(w == 'w')
	{
 		x = 0.4;
		teta = 0.0;
	}
	if(w == 's')
	{
 		x = -0.4;
		teta = 0.0;
	}
	if(w == 'a')
	{
 		x = 0.0;
		teta = 0.5;
	}
	if(w == 'd')
	{
 		x = 0.0;
		teta = -0.5;
	}
	msg.linear.x = x;
	msg.linear.y = y;
	msg.linear.z = z;

	msg.angular.x = fi;
	msg.angular.y = omega;
	msg.angular.z = teta; 


    //ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
 }

  return 0;
}
