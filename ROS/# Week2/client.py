import rclpy
import ros2client.comm as comm

def main(args = None):
    rclpy.init(args = args)
    client_publihser = comm.ClientPublisher()

    # Loop
    rclpy.spin(client_publihser)

    # delete node  
    client_publihser.destroy_node()
    rclpy.shutdown


if __name__ == '__main__':
    main()
