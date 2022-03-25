### Publisher and Subscriber 



Lecture 1 

### Error 1 ros2 : command not found 

. ~/ros2_foxy/ros2-linux/setup.bash  

or source ~/ros2_foxy/ros2-linux/setup.bash  # to every terminal  

source /opt/ros/foxy/setup.bash  

.install/setup.bash  


### 2 workspace folder : dev_ws
### 3 package build : colcon 

### 4 Package example

cd dev_ws
cd src
mkdir ros2comm
cd ros2comm/
source ~/ros2_foxy/ros2-linux/setup.bash

`server package build -> build type -> node name -> package name`  
ros2 pkg create --build-type ament_python --node serverRun ros2server  # if i want c -> build type : cmake 

`client package build -> build type -> node name -> package name`  
ros2 pkg create --build-type ament_python --node clientRun ros2client  # if i want c -> build type : cmake 

`specific package build`
colcon build --packages-select ros2server # (package name .. )

`all package build`
colcon build  # build, install, log ...

. install/setup.bash # execute setup.bash 
