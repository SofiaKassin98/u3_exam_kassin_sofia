/*
 * File:          u3_exam_kassin_sofia.c
 * Date:          JUly, 8th, 2019
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include <webots/distance_sensor.h>
#include <webots/keyboard.h>

#include <stdio.h> 

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64
#define PI 3.141592

#define OBSTACLE DISTANCE 17  
/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();

   WbDeviceTag wheel_left= wb_robot_get_device("wheel1");
   WbDeviceTag wheel_right = wb_robot_get_device("wheel2");
   WbDeviceTag wheel_front = wb_robot_get_device("wheel3");
   
   WbDeviceTag distance_sensor = wb_robot_get_device("DSENSOR_F1");
   wb_distance_sensor_enable(distance_sensor, TIME_STEP); 
   WbDeviceTag distance_sensor = wb_robot_get_device("DSENSOR_F2");
   wb_distance_sensor_enable(distance_sensor, TIME_STEP);
    
   
   WbDeviceTag pos_right = wb_robot_get_device("encoder1");
   WbDeviceTag pos_left = wb_robot_get_device("encoder2");
   WbDeviceTag pos_front = wb_robot_get_device("encoder3");
  
   wb_position_sensor_enable(pos_right, TIME_STEP);
   wb_position_sensor_enable(pos_left, TIME_STEP);
  
   wb_motor_set_position(wheel_right, INFINITY);   
   wb_motor_set_position(wheel_left, INFINITY);
   wb_motor_set_position(wheel_front, INFINITY);



  while (wb_robot_step(TIME_STEP) != -1) {

    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */

    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_differential_wheels_set_speed(100.0,100.0);
     */
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}