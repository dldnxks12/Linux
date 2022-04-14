### 2022-4-15 Check

- `Goal`

        1. Check Lidar data with ROS2 topic - ok
        2. Process lidar data and toss it to GAZEBO world -> make some controller -ok

<br>

### Lidar data type

       sensor_msgs/LaserScan 
       
       
### Practice Setup

- Terminal Setup

      source ~/ros2_foxy/ros2-linux/setup.bash
      source /opt/ros/foxy/setup.bash
      . install/setup.bash

<br>

- Terminal 1

      turtlebot_ws / ...
      
      export TURTLEBOT3_MODEL=burger      
      ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
       
<br>

- Terminal 2

      Capston / ...
      
      ros2 run capston lidar_topic_check

<br>

- Terminal 3

      ros2 topic list 
      ros2 topic echo /scan 




