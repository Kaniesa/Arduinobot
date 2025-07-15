import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from arduinobot_msgs.action import Fibonacci




class SimpleActionClient(Node):
    def __init__(self):
        super().__init__("simple_action_client")
        self.action_client = ActionClient(self, Fibonacci, "fibonacci")


        self.action_client.wait_for_server()


        self.goal = Fibonacci.Goal()
        self.goal.order = 10
        self.future = self.action_client.send_goal_async(self.goal, feedback_callback=self.feedbackCallback)
        self.future.add_done_callback(self.responseCallback)


    # Executed after we send goal to action server, checks whether goal is accepted
    def responseCallback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info("Goal Rejected :(")
            return
       
        self.get_logger().info("Goal Accepted :)")
        self.future = goal_handle.get_result_async()
        self.future.add_done_callback(self.resultCallback)


    # Executed at end of action server execution so after server has completed action/callback
    def resultCallback(self, future):
        result = future.result().result
        self.get_logger().info("Result: {0}".format(result.sequence))
        rclpy.shutdown()


    # Executed repeatedly so each time a new feedback message is received from action server
    def feedbackCallback(self, feedback_msg):
        self.get_logger().info("Received Feedback: {0}".format(feedback_msg.feedback.partial_sequence))




def main():
    rclpy.init()
    action_client = SimpleActionClient()
    rclpy.spin(action_client)




if __name__ == '__main__':
    main()
#under arduinobot_py_examples arduinobot_py_examples create 'simple_action_client.py'
# continue V68 at 15:10

