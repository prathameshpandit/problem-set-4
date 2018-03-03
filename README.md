This problem illustrates how robot stops after receiving signal from lidar alarm.

First run the stdr simulator:
"roslaunch stdr_launchers server_with_map_and_gui_plus_robot.launch"

Then run the following:
rosrun my_action_server my_action_server
rosrun my_action_server my_action_server
rosrun my_lidar_alarm my_lidar_alarm
