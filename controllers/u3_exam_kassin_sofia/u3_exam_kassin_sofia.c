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

int dis1;
int  dis2;
int m1;
int m2;

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
   
   WbDeviceTag distance_sensor1 = wb_robot_get_device("DSENSOR_1");
   wb_distance_sensor_enable(distance_sensor1, TIME_STEP); 
   WbDeviceTag distance_sensor2 = wb_robot_get_device("DSENSOR_2");
   wb_distance_sensor_enable(distance_sensor2, TIME_STEP);
    
   
   WbDeviceTag pos_right = wb_robot_get_device("enco1");
   WbDeviceTag pos_left = wb_robot_get_device("enco2");
   WbDeviceTag pos_front = wb_robot_get_device("encoder3");
  
   wb_position_sensor_enable(pos_right, TIME_STEP);
   wb_position_sensor_enable(pos_left, TIME_STEP);
   wb_position_sensor_enable(pos_front, TIME_STEP);
  
   wb_motor_set_position(wheel_right, INFINITY);   
   wb_motor_set_position(wheel_left, INFINITY);
   wb_motor_set_position(wheel_front, INFINITY);



  while (wb_robot_step(TIME_STEP) != -1) {

   wb_motor_set_velocity(wheel_left,0);
   wb_motor_set_velocity(wheel_right, 10);
   wb_motor_set_velocity(wheel_front, -10);
   
   
   
   dis1 = wb_distance_sensor_get_value(distance_sensor1);
   dis2 = wb_distance_sensor_get_value(distance_sensor2);
   
   m1=((dis1)*(0.2)/65000);
   m2=((dis2)*(0.2)/65000);
   
   
   
   
   printf ("dis1 : %d\n",dis1);
   printf ("dis2 : %d\n",dis2);
   
   printf ("m1 : %d\n",m1);
   printf ("m2 : %d\n",m2);
     
   
   
   
   
   
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}