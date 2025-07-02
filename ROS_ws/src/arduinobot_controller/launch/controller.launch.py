import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command, PathJoinSubstitution
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    controllers_file = PathJoinSubstitution([get_package_share_directory("arduinobot_controller"), "config", "arduinobot_controllers.yaml"])
    robot_description = ParameterValue(
        Command(
            [
                "xacro ",
                os.path.join(get_package_share_directory("arduinobot_description"), "urdf", "arduinobot.urdf.xacro")
            ]
        ),
        value_type=str
    )

    control_node = Node(
        package='controller_manager',
        executable='ros2_control_node',
        parameters = [controllers_file],
        output='screen'
    )

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{"robot_description": robot_description}]
    )

    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "joint_state_broadcaster",
            "--controller-manager",
            "/controller_manager",
        ]
    )

    arm_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "arm_controller",
            "--param-file",
            controllers_file,
        ]
    )

    # gripper_controller_spawner = Node(
    #     package="controller_manager",
    #     executable="spawner",
    #     arguments=[
    #         "gripper_controller",
    #         "--controller-manager",
    #         "/controller_manager",
    #     ]
    # )

    return LaunchDescription([
        control_node,
        robot_state_publisher,
        joint_state_broadcaster_spawner,
        arm_controller_spawner
        # gripper_controller_spawner
    ])