### Gazebo


Lecture 2

# source [-h] filename : execute commands in filename

# Robotis link 
https://emanual.robotis.com/docs/en/platform/turtlebot3/overview/

1. Quick Start Guide Menu -> foxy -> install ... 
2. Simulation Menu

### For each terminal 
source ~/ros2_foxy/ros2-linux/setup.bash  
source /opt/ros/foxy/setup.bash  

colcon build --symlink-install  # In turtlebot_ws directory   


### make turtlebot in Gazebo
. install/setup.bash  
ros2 launch turtlebot3_gazebo empty_world.launch.py

### Topic
ros2 topic list  
ros2 topic echo /camera/image_raw # See topic data

### Topic publish in command  
ros2 topic echo /cmd_vel # Nothing appears...

# publish - twist type data - geometry_msgs/Twist Search
ros2 topic pub /cmd_vel geometry_msgs/Twist '{angular: {z: 1.0}, linear : {x : 0.5}}'

	# geometry_msgs/Twist
	Vector3 linear
	Vector3 angular
	
### Control Package ..
ros2 pkg create --build-type ament_python --node-name my_controller my_controller  

colcon build --packages-select my_controller # at turtlebot3_ws directory  	
. install/setup.bash  
ros2 run my_controller my_controller # hi from my controller print!  

### Coding vscode 

