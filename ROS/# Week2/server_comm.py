import rclpy                        # Header for Ros2 Python 
from rclpy.node import Node         # Node Header for Ros2 Python
from std_msgs.msg import String     # Message Header for Ros2 Python 

class ServerPublisher(Node):
    def __init__(self):
        super().__init__('server_publisher')  

        # Message type : String
        # Name         : server2client
        # BufferSize   : 10
        self.publisher = self.create_publisher(String, 'server2client', 10) # Create Publisher 

    def MessagePublish(self, sendMsg):
        msg = String()      # String type 
        msg.data = sendMsg  # Put data in msg structure 
        self.publisher.publish(msg)  # Message Publish Function 

        # Notify 
        self.get_logger().info("Publishing : %s" % msg.data)

class ServerSubscriber(Node):
    def __init__(self):
        super().__init__('server_subscriber')

        # Message type : String
        # Name         : client2server
        # Callback     : Get Message 
        # BufferSize   : 10
        self.subscriber = self.create_subscription(String, 'client2server', self.callback_subscribe, 10)

    def callback_subscribe(self, msg): 
        # Notify
        self.get_logger().info('Received Message : %s' % msg.data)




 
