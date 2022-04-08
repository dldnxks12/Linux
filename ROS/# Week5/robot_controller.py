# publish to Gazebo !
import rclpy
import my_controller3.comm as comm
import cv2 

def main():
    rclpy.init(args = None)

    # Create Publish, Subscribe Object !!    
    my_controller_subscriber = comm.ClientSubscriber()
    my_controller_publisher = comm.ClientPublisher()  

    while(1):

        rclpy.spin_once(my_controller_publisher)  # Once in a while loop    
        rclpy.spin_once(my_controller_subscriber) # Once in a while loop

        # Get Image
        my_image = my_controller_subscriber.GetImage() # OpenCV type Image (Internally ROS type -> OpenCV type Conversion)
        cv2.imshow('OpenCV Image', my_image)

        # wait key input ....
        # keyin = cv2.waitKey(0)  # Check Keyboard Input 

        # per 1 second
        keyin = cv2.waitKey(1)  # Check Keyboard Input 

        if (keyin == ord('w')): # ord : string into number
            my_controller_publisher.set_velocity(0.1, 0.0)   # Forward 
        elif (keyin == ord('a')):
            my_controller_publisher.set_velocity(0.0, 0.1)   # Turn Left
        elif (keyin == ord('s')):
            my_controller_publisher.set_velocity(-0.1, 0.0)  # Backward
        elif (keyin == ord('d')):
            my_controller_publisher.set_velocity(0.0, -0.1)  # Turn Right
        elif (keyin == ord('q')): 
            my_controller_publisher.set_velocity(0.1, 0.1)   # Forward + Turn Left
        elif (keyin == ord('e')): 
            my_controller_publisher.set_velocity(0.1, -0.1)  # Forward + Turn Right
        elif (keyin == ord('z')): 
            my_controller_publisher.set_velocity(-0.1, 0.1)  # Backward + Turn Left
        elif (keyin == ord('c')): 
            my_controller_publisher.set_velocity(-0.1, -0.1) # Backward + Turn Right

        elif (keyin == 32): # 32 : Space Bar            
            my_controller_publisher.set_velocity(0.0, 0.0)  # Stop            

        elif (keyin == ord('f')): # Quit while loop
            break
        
    # Destroy nodes ...
    my_controller_publisher.destroy_node()
    my_controller_subscriber.destroy_node()
    rclpy.shutdown
    
if __name__ == '__main__':
    main()
    
