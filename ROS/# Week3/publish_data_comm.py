'''

publish /cmd_vel data to gazebo simulation

geometry_msgs/Twist

1. Vector3 linear
2. vector3 angular 

'''

import rclpy
from rclpy.node import Node
#from std_msgs.std_msgs import String
from geometry_msgs.msg import Twist

class ClientPublisher(Node):
    def __init__(self):
        super().__init__('my_controller_pub')

        # Message Type : Twist
        # Message Name : /cmd_vel
        # Buffer size  : 10 
        self.publisher = self.create_publisher(Twist, '/cmd_vel', 10)
        time_period = 0.5
        self.timer = self.create_timer(time_period, self.timer_callback)

    def timer_callback(self):

        # Make Message box and put data in it!
        msg = Twist()
        msg.linear.x = 1.0
        msg.angular.z = 1.0

        # Publish Message !
        self.publisher.publish(msg)

        # Print Message Log 
        self.get_logger().info("Publishing: %s" % msg)


'''
class ClientSubscriber(Node):
    def __init__(self):
        super().__init__('client_subscriber')
        self.subscriber = self.create_subscription(String, 'server2client', self.listener_callback, 10)

    def listener_callback(self, msg):
        self.get_logger().info()('Subscribed: %s', % msg.data)
'''
