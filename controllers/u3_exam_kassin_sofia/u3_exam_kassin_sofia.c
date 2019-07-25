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
#include <stdlib.h> 
#include <math.h> 

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64
#define PI 3.141592

#define OBSTACLE_DISTANCE 55704.75 

int vel=3;
int turn_r=0;
int turn_l=0; 

float dis_1=0;
float dis_2=0;
float m_1=0;
float m_2=0;

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
   
  WbDeviceTag pos_right = wb_robot_get_device("enco_1");
  WbDeviceTag pos_left = wb_robot_get_device("enco_2");
  WbDeviceTag pos_front = wb_robot_get_device("enco_3");
  
  wb_position_sensor_enable(pos_right, TIME_STEP);
  wb_position_sensor_enable(pos_left, TIME_STEP);
  wb_position_sensor_enable(pos_front, TIME_STEP);
  
  

  while (wb_robot_step(TIME_STEP) != -1) {
  
  wb_motor_set_position(wheel_right, INFINITY);   
  wb_motor_set_position(wheel_left, INFINITY);
  wb_motor_set_position(wheel_front, INFINITY);
    
    dis_1 = wb_distance_sensor_get_value(distance_sensor1);
    dis_2 = wb_distance_sensor_get_value(distance_sensor2);
    
    m_1 = dis_1*.2/65535;
    m_2 = dis_2*.2/65535;
     
    if (dis_1 <= OBSTACLE_DISTANCE && dis_2 > OBSTACLE_DISTANCE){
      wb_motor_set_velocity(wheel_left, vel);
      wb_motor_set_velocity(wheel_right, vel);
      wb_motor_set_velocity(wheel_front, vel);
    }
    
    if (dis_1 >= OBSTACLE_DISTANCE && dis_2 < OBSTACLE_DISTANCE){
      wb_motor_set_velocity(wheel_left, -vel);
      wb_motor_set_velocity(wheel_right, -vel);
      wb_motor_set_velocity(wheel_front, -vel);
    }
     
    if (dis_1 <= OBSTACLE_DISTANCE && dis_2 <= OBSTACLE_DISTANCE){
      wb_motor_set_velocity(wheel_left, -vel);
      wb_motor_set_velocity(wheel_right, -vel);
      wb_motor_set_velocity(wheel_front, -vel);
    }
     
    if (dis_1 > OBSTACLE_DISTANCE && dis_2 > OBSTACLE_DISTANCE){
      wb_motor_set_velocity(wheel_left, 0);
      wb_motor_set_velocity(wheel_right,vel);
      wb_motor_set_velocity(wheel_front,-vel);
    }
    
    
    printf("The distance measure Left  (M): %f \t", dis_1);
    
    printf("The distance measure Right  (M): %f \t", dis_2);
  
   
    printf ("m_1 : %f \t ",m_1);
    printf ("m_2 : %f\n",m_2);

  }
  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}


