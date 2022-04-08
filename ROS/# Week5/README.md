### Week4 `Cartographer`


- `Goal`

      1. Use Cartographer
      2. Robot Control 

<br>	

- Follow up 

```python

cd turtlebot_ws

sudo apt install ros-foxy-cartographer

sudo apt install ros-foxy-cartographer-fos

sudo apt install ros-foxy-navigation2

sudo apt install ros-foxy-nav2-bringup

```


`Use terminal x 3`

Num 1 terminal : Cartographer

Num 2 terminal : Gazebo Simulation 

Num 3 terminal : Robot Control 


`Terminal1 - Cartographer`

```python

source ~/ros2_foxy/ros2-linux/setup.bash
source /opt/ros/foxy/setup.bash
. install/setup.bash

export TURTLEBOT3_MODEL=burger - terminal 1 (Cartographer)
ros2 launch turtlebot3_cartographer cartographer.launch.py -> rviz On!

```
export ?	assign some value to variable 
		
<br>

`Terminal2 - Gazebo simulation`

```python 

cd turtlebot_ws

source ~/ros2_foxy/ros2-linux/setup.bash
source /opt/ros/foxy/setup.bash
. install/setup.bash

export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py

or ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py -> for lower complexity 

```

<br>

`Terminal3 - Robot Control`

```python 

cd turblebot_ws
source ~/ros2_foxy/ros2-linux/setup.bash
source /opt/ros/foxy/setup.bash
. install/setup.bash
export TURTLEBOT3_MODEL=burger

ros2 run turtlebot3_teleop teleop_keyboard

```

<br>

`Save Map data`

```python 

cd turtlebot3_ws

mkdir map 

cd map

ros2 run nav2_map_server map_saver_cli -f ~/turtlebot3_ws/map/test

	-f : file path
	test : file name 

```

<br>

`Bring up Map data`

```python

cd turtlebot3_ws

export GAZEBO_MODEL_PATH=`ros2 pkg prefix turtlebot3_gazebo`/share/turtlebot3_gazebo/models/

export TURTLEBOT3_MODEL=waffle

ros2 launch turtlebot3_navigation2 navigation2.launch.py map:=./map/test.yaml

```





