//#include <moveit/move_group_interface/move_group.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <cmath>




// Main moveit libraries are included
int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(0);
  spinner.start(); // For moveit implementation we need AsyncSpinner, we cant use ros::spinOnce()
  static const std::string PLANNING_GROUP = "arm"; /* Now we specify with what group we want work, here group1 is the name of my group controller*/
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP); // loading move_group

  const robot_state::JointModelGroup *joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP); //For joint control
  geometry_msgs::PoseStamped current_pose;
  geometry_msgs::PoseStamped home_pose;
  geometry_msgs::PoseStamped target_pose; // Pose in ROS is implemented using geometry_msgs::PoseStamped, google what is the type of this msg
  current_pose = move_group.getCurrentPose(); /* Retrieving the information about the current position and orientation of the end effector*/
  target_pose = current_pose;
  home_pose = current_pose;
  
  //except that we want to move it a little bit along x-axis*/
  ros::Rate loop_rate(60); //Frequency
  while (ros::ok()){

	for (double x = -0.2; x >= -1.2; x-=0.1) {
		
		target_pose.pose.position.x = home_pose.pose.position.x + x;

		double y = std::sqrt(0.25 - (x+0.7)*(x+0.7));

		target_pose.pose.position.y = home_pose.pose.position.y - y;
		
		ROS_INFO("%f, %f", x, y);

	    	//move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
		move_group.setJointValueTarget(target_pose);
	    	move_group.move(); // Move the robot
		//ros::Duration(0.1).sleep();
		
		/*while (ros::ok()){
			current_pose = move_group.getCurrentPose();
			if (abs(current_pose.pose.position.x - target_pose.pose.position.x) < 0.05){
				ROS_INFO("Reached1");
			  break; // Basically, check if we reached the desired position
			}
			loop_rate.sleep();
		}*/
	
	}
	

	for (double x = -1.2; x <= -0.2; x+=0.1) {
		
		target_pose.pose.position.x = home_pose.pose.position.x + x;

		double y = std::sqrt(0.25 - (x+0.7)*(x+0.7));

		target_pose.pose.position.y = home_pose.pose.position.y + y;
		
		//ROS_INFO("%f, %f", x, y);


	    	//move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
		move_group.setJointValueTarget(target_pose);
	    	move_group.move(); // Move the robot
		//ros::Duration(0.1).sleep();
		
		/*while (ros::ok()){
			current_pose = move_group.getCurrentPose();
			if (abs(current_pose.pose.position.x - target_pose.pose.position.x) < 0.05){
				ROS_INFO("Reached1");
			  break; // Basically, check if we reached the desired position
			}
			loop_rate.sleep();
		}*/
	
	}
    
  }

  ROS_INFO("Done");
  ros::shutdown();
  return 0;
}
