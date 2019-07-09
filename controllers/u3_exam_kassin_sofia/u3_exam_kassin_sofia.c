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

#define OBSTACLE DISTANCE 17 

int vel=3;

int turn_r=0;
int turn_l=0; 

float dis_1=0;
float dis_2=0;
float disl_v=0;

float  m_1=0;
float m_2=0;

float pos1_v=0;
float pos2_v=0;
float pos3_v=0;

float pos_f=0;

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

   wb_motor_set_velocity(wheel_left,-vel);
   wb_motor_set_velocity(wheel_right,vel);
   wb_motor_set_velocity(wheel_front,  0);
   
   
   
   dis_1 = wb_distance_sensor_get_value(distance_sensor1);
   dis_2 = wb_distance_sensor_get_value(distance_sensor2);
   
   pos1_v = wb_position_sensor_get_value(pos_right);
   pos2_v = wb_position_sensor_get_value(pos_left);
   pos3_v = wb_position_sensor_get_value(pos_front);
     
   m_1=((dis_1)*(0.2)/65535);
   m_2=((dis_2)*(0.2)/65535);
   
   
   printf ("pos1 : %f  ",pos1_v);
   
   printf ("dis_1 : %.2f \t ",dis_1);
   printf ("dis_2 : %.2f \t ",dis_2);
   
   printf ("m_1 : %f \t ",m_1);
   printf ("m_2 : %f\n",m_2);
   
    printf ("posfinal : %f \t",pos_f);
    
    printf("The distance value in Left (BITS): %f \t", disl_v);
  
  printf("The distance measure Left  (M): %f \t", dis_1);
  
  printf("The distance measure Right  (M): %f \t", dis_2);
   
  printf("The final position is: %f" , pos_f);
     
   
   
   
  if (m_1 <= 0.17 && dis_1 > dis_2 && turn_r == 0) {
  pos_f = pos1_v + 3.14156;
  turn_r = 1;
  } 
  
   if (turn_r == 1){
     if(pos1_v > pos_f){
       wb_motor_set_velocity(wheel_left, -vel);
       wb_motor_set_velocity(wheel_right, -vel);
       wb_motor_set_velocity(wheel_front, -vel);
   }
   
       else{
       turn_r = 0;
       }
       
   }
   
   if (m_2 <= 0.17 && dis_2 > dis_1 && turn_l == 0){
   pos_f = pos1_v + 4.14156;
   turn_l = 1;
   }    
   
   if(turn_l == 1){
     if(pos1_v < pos_f){
       wb_motor_set_velocity(wheel_left, vel);
       wb_motor_set_velocity(wheel_right, vel);
       wb_motor_set_velocity(wheel_front, vel);   
   }
  else{
  turn_l = 0;
  }
  
  } 
  }
  
  printf("The distance value in Left (BITS): %f ", disl_v);
  
  printf("The distance measure Left  (M): %f \t", dis_1);
  
  printf("The distance measure Right  (M): %f \t", dis_2);
   
  printf("The final position is: %f" , pos_f);
  //};

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
