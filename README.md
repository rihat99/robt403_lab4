# robt403_lab4
Source code for the laboratory session 4 of the ROBT403 course

This code has been tested on ROS Melodic

## Install dependicies
  1) git clone https://github.com/arebgun/dynamixel_motor
  2) git clone https://github.com/KNurlanZ/snake-noetic.git
  
## Compile
  1) source /opt/ros/melodic/setup.bash
  2) source ~/CATKIN_WORKSPACE/devel/setup.bash
  3) catkin_make
  
## Run
  1) roslaunch my_dynamixel_tutorial controller_manager.launch
  2) roslaunch snake_moveit_config start_moveit_arm_controllers.launch
  3) roslaunch snake_moveit_config moveit_planning_execution.launch 
  
  4) rosrun snake_move test_moveit
