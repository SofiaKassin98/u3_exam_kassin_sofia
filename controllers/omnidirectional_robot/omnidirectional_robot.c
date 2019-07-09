/*
 * File:          onmiwheel.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>
#include <webots/keyboard.h>

#include <stdio.h>
#include <math.h>

/*
 * macros
 */
#define TIME_STEP 64
#define PI 3.141592
#define OBSTACLE_DISTANCE 80.0


enum {
  Autonomous,
  Manual,
  Go,
  Turn,
  TurnL,
  TurnR,
  left,
  right,
  FreeWay,
  Obstacle
};

int  A = 65, S = 83, G = 71, W = 87;
int state;
double initial_angle_wheel1;

int checkForObstacles(WbDeviceTag distance_sensor) {
  double distance = wb_distance_sensor_get_value(distance_sensor);

  if (distance > OBSTACLE_DISTANCE)
    return FreeWay;
  else 
    return Obstacle;   
}

void goRobot(WbDeviceTag *wheels, double velocity) {
  wb_motor_set_velocity(wheels[0],0);
  wb_motor_set_velocity(wheels[1], velocity);
  wb_motor_set_velocity(wheels[2], -velocity);

}

void backRobot(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 0);
  wb_motor_set_velocity(wheels[1],-6);
  wb_motor_set_velocity(wheels[2], 6);
}

void leftRobot(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 6);
  wb_motor_set_velocity(wheels[1], 0);
  wb_motor_set_velocity(wheels[2],-6);
}

void rightRobot(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0],-6);
  wb_motor_set_velocity(wheels[1], 0);
  wb_motor_set_velocity(wheels[2], 6);
}

void stopRobot(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 0);
  wb_motor_set_velocity(wheels[1], 0);
  wb_motor_set_velocity(wheels[2], 0);
}

void turnLeft(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 6);
  wb_motor_set_velocity(wheels[1], 6);
  wb_motor_set_velocity(wheels[2], 6);
}

void turnRight(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0],-6);
  wb_motor_set_velocity(wheels[1],-6);
  wb_motor_set_velocity(wheels[2],-6);
}

double getAngleRobot(WbDeviceTag pos_sensor) {
  double angle_wheel1 = wb_position_sensor_get_value(pos_sensor);
  double angle;

  angle = fabs(angle_wheel1 - initial_angle_wheel1);

  return angle;
}

/*
 * main
 */
int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);
  
  int key;
  float velocity;
  short int ds_state, ds_state1, robot_state = Go;
  float angle;
  float dis1, dis2;
   
   WbDeviceTag wheels[2];
     wheels[0] = wb_robot_get_device("wheel1");
     wheels[1] = wb_robot_get_device("wheel2");
     wheels[2] = wb_robot_get_device("wheel3");
     
   wb_motor_set_position (wheels[0], INFINITY);
   wb_motor_set_position (wheels[1], INFINITY);
   wb_motor_set_position (wheels[2], INFINITY);

   WbDeviceTag DSensor[1];
     DSensor[0] = wb_robot_get_device("DSENSOR_F1");
     DSensor[1] = wb_robot_get_device("DSENSOR_F2");
     
   wb_distance_sensor_enable(DSensor[0], TIME_STEP);
   wb_distance_sensor_enable(DSensor[1], TIME_STEP);
   
   WbDeviceTag encoder = wb_robot_get_device("encoder1");
   wb_position_sensor_enable(encoder, TIME_STEP);
   
  /* 
   * main loop
   */
  while (wb_robot_step(TIME_STEP) != -1) {

     key = wb_keyboard_get_key();
     
     if (key == G)
       state = Autonomous;
     else if (key == W)
       state = Manual;
     else if (key == S){
       state = left;
       initial_angle_wheel1 = wb_position_sensor_get_value(encoder);
     } else if (key == A){
         state = right;
         initial_angle_wheel1 = wb_position_sensor_get_value(encoder);
     }
       
       
     if (state == Autonomous){
      if (robot_state == Go) {
        ds_state = checkForObstacles(DSensor[0]);
        ds_state1 = checkForObstacles(DSensor[1]);
        
        dis1 = wb_distance_sensor_get_value(DSensor[0]);
        dis2 = wb_distance_sensor_get_value(DSensor[1]);
        printf ("dis1 : %lf\n",dis1);
        printf ("dis2 : %lf\n",dis2);
        
        if (ds_state == FreeWay && ds_state1 == FreeWay) {
          velocity = 8;
          goRobot(wheels, velocity);
        } else if (ds_state == Obstacle && ds_state1 == FreeWay) {
            robot_state = TurnL;
            stopRobot(wheels);
        } else if (ds_state == FreeWay && ds_state1 == Obstacle) {
            robot_state = TurnR;
            stopRobot(wheels);
        } else if (ds_state == Obstacle && ds_state1 == Obstacle) {
            robot_state = TurnL;
            stopRobot(wheels);
        }
      } else if (robot_state == TurnL) {
          turnLeft(wheels);
          ds_state = checkForObstacles(DSensor[0]);
          ds_state1 = checkForObstacles(DSensor[1]);
          if (ds_state == FreeWay && ds_state1 == FreeWay) {
            robot_state = Go;
            stopRobot(wheels);
          }
      } else if (robot_state == TurnR) {
          turnRight(wheels);
          ds_state = checkForObstacles(DSensor[0]);
          ds_state1 = checkForObstacles(DSensor[1]);
          if (ds_state1 == FreeWay && ds_state == FreeWay) {
            robot_state = Go;
            stopRobot(wheels);
          }
      }     
     } else {
         if (key == WB_KEYBOARD_UP){
           velocity = 6;
           goRobot(wheels, velocity);
           angle = wb_position_sensor_get_value(encoder);
           printf("Angle: %lf\n", angle);
         } else if (key == WB_KEYBOARD_DOWN){
             backRobot(wheels);
             angle = wb_position_sensor_get_value(encoder);
             printf("Angle: %lf\n", angle);
         } else if (key == WB_KEYBOARD_LEFT){
             leftRobot(wheels);
             angle = wb_position_sensor_get_value(encoder);
             printf("Angle: %lf\n", angle);
         } else if (key == WB_KEYBOARD_RIGHT){
             rightRobot(wheels);
             angle = wb_position_sensor_get_value(encoder);
             printf("Angle: %lf\n", angle);
         } else if (state == left){
             turnLeft(wheels);
             angle = getAngleRobot(encoder);
             if (angle >= 0.4*PI) {
               robot_state = Go;
               stopRobot(wheels);
             }
         } else if (state == right){
             turnRight(wheels);
             angle = getAngleRobot(encoder);
             if (angle >= 0.4*PI) {
               robot_state = Go;
               stopRobot(wheels);
             }
         } else {
             stopRobot(wheels);
         }
          dis1 = wb_distance_sensor_get_value(DSensor[0]);
          dis2 = wb_distance_sensor_get_value(DSensor[1]);
          printf ("dis1 : %lf\n",dis1);
          printf ("dis2 : %lf\n",dis2);
       }
  }

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}