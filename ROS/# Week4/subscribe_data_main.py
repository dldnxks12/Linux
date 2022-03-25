# publish to Gazebo !
import rclpy
import my_controller2.comm as comm
import cv2 

def main():
    rclpy.init(args = None)

    # Publish !!
    # Make Publisher Object - Activate timer callback function... 
    # my_controller_publisher = comm.ClientPublisher()
    # Keep Acting ... 
    # rclpy.spin(my_controller_publisher)
    # my_controller_publisher.destroy_node()

    # Subscribe !!
    my_controller_subscriber = comm.ClientSubscriber()
    rclpy.spin_once(my_controller_subscriber) # Once ...
    # rclpy.spin(my_controller_subscriber) # Loop ...

    # Get Image
    my_image = my_controller_subscriber.GetImage() # OpenCV type Image 
    cv2.imshow('OpenCV Image', my_image)
    cv2.waitKey(0)

    # Destroy node ...
    my_controller_subscriber.destroy_node()
    rclpy.shutdown

if __name__ == '__main__':
    main()
