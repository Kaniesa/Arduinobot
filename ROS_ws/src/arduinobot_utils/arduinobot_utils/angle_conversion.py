#!/usr/bin/env python3 
import rclpy
from rclpy.node import Node
from arduinobot_msgs.srv import EulerToQuaternion, QuaternionToEuler
from tf_transformations import quaternion_from_euler, euler_from_quaternion

class AnglesConverter(Node):
    def __init__(self):
        super().__init__("angle_conversion_service_server")

        self.euler_to_quaternion = self.create_service(EulerToQuaternion, "euler_to_quaternion", self.eulerToQuaternionCallback)
        self.quaternion_to_euler = self.create_service(QuaternionToEuler, "quaternion_to_euler", self.quaternionToEulerCallback)
        self.get_logger().info("Angle Conversion Services Ready")

    def eulerToQuaternionCallback(self, req, res):
        self.get_logger().info("Requested to convert euler angles roll: %f, pitch: %f, yaw: %f, into a quaternion." % (req.roll, req.pitch, req.yaw) )
        (res.x, res.y, res.z, res.w) = quaternion_from_euler(req.roll, req.pitch, req.yaw)
        self.get_logger().info("Corresponding quaternion x: %f, y: %f, z: %f, w: %f" % (res.x, res.y, res.z, res.w))
        return res

    def quaternionToEulerCallback(self, req, res):
        self.get_logger().info("Requested to convert quaternion x: %f, y: %f, z: %f, w: %f, into euler angles." % (req.x, req.y, req.z, req.w) )
        (res.roll, res.pitch, res.yaw) = euler_from_quaternion([req.x, req.y, req.z, req.w])
        self.get_logger().info("Corresponding euler angles roll: %f, pitch: %f, yaw: %f," % (res.roll, res.pitch, res.yaw) )
        return res
    
def main():
    rclpy.init()
    angles_converter = AnglesConverter()
    rclpy.spin(angles_converter)
    angles_converter.destroy_node()
    rclpy.shutdown

if __name__ == '__main__':
    main()

# did need to downlaod: 
# sudo apt-get install ros-humble-tf-transformations 
# sudo pip3 install transforms3d
# sudo apt install python3-ament-package

# note: the very first line is to:
# Declare Python Interpreter Directory on line below (since ament_cmake build type we used cannot auto locate it)
