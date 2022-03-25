# publish to Gazebo !
import rclpy
import my_controller.comm as comm


def main():
    rclpy.init(args = None)

    # Make Publisher Object - Activate timer callback function... 
    my_controller_publisher = comm.ClientPublisher()

    # Keep Acting ... 
    rclpy.spin(my_controller_publisher)

    my_controller_publisher.destroy_node()
    rclpy.shutdown


if __name__ == '__main__':
    main()
