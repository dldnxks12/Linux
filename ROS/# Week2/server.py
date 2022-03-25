import rclpy
import ros2server.comm as comm


def main(args = None):
    rclpy.init(args = args) # initialize
    print("Server Run!")

    server_subscriber = comm.ServerSubscriber()

    # Keep doing 
    rclpy.spin(server_subscriber)

    # Delete used ones
    server_subscriber.destroy_node()
    rclpy.shutdown


if __name__ == '__main__':
    main()



