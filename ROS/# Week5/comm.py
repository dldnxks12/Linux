#### keyboard Input -> Publish -> Robot Control  ####

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Image # Camera data ...
from sensor_msgs.msg import Imu   # Imu data ...
from cv_bridge import CvBridge

class ClientPublisher(Node):
    def __init__(self):
        super().__init__('my_controller_pub')

        # Message Type : Twist
        # Message Name : /cmd_vel
        # Buffer size  : 10 
        self.publisher = self.create_publisher(Twist, '/cmd_vel', 10)
        time_period = 0.5        

        # Instance Variable 
        self.__LinearVel = 0.0    # __ means private variable in python ...
        self.__AngularVel = 0.0

        self.timer = self.create_timer(time_period, self.timer_callback)

    # Each set_velocity -> __LinearVel, __AngularVel published by timer_callback function !
    def set_velocity(self, linear_vel, angular_vel):
        self.__LinearVel  = linear_vel
        self.__AngularVel = angular_vel

    def timer_callback(self):

        # Make Message box and put data in it!
        # Input -> linear , angular vel control
        msg = Twist()
        msg.linear.x = self.__LinearVel
        msg.angular.z = self.__AngularVel

        # Publish Message !
        self.publisher.publish(msg)

        # Print Message Log 
        self.get_logger().info("Publishing: %s" % msg)


class ClientSubscriber(Node):
    def __init__(self):
        super().__init__('my_controller_sub')

        # Subscribe Image Type data !
        # Subscrie /camera/image_raw topic !
        self.subscriber_img = self.create_subscription(Image, '/camera/image_raw', self.listener_img_callback, 10)
        
        # Subscrie /imu topic !
        #self.subscriber_imu = self.create_subscription(Imu, '/imu', self.listener_imu_callback, 10)

        self.CV2Image = None 
        self.CvBridge = CvBridge() # ROS Image -> OpenCV Image 

    def listener_img_callback(self, msg):

        # Camera data !
        self.get_logger().info('Subscribed Width : %s' % msg.width)
        self.get_logger().info('Subscribed Height: %s' % msg.height)
        # self.get_logger().info('Subscribed: %s' % msg.data)

        # ROS2 Image Message type -> OpenCV Image Type Conversion with CV Bridge !
        self.CV2Image = self.CvBridge.imgmsg_to_cv2(msg, desired_encoding = 'bgr8') # msg.data XX ! just msg 

    def listener_imu_callback(self, msg):
        self.get_logger().info('Subscribed IMU: %s' % msg.linear_acceleration)


    # Return processed Image 
    def GetImage(self):
        return self.CV2Image 
