/*
ENGINES.cpp - Library for ENGINES motor driver
*/

#include "Arduino.h"
#include "Engines.h"

struct Motor {
  int in1;
  int in2;
  int pwn;
};

Motor motors[4];

ENGINES::ENGINES(int ena_g, int in1_g, int in2_g, int in3_g, int in4_g, int enb_g, int ena_d, int in1_d, int in2_d, int in3_d, int in4_d, int enb_d) {
  pinMode (ena_g, OUTPUT);
  pinMode (in1_g, OUTPUT);
  pinMode (in2_g, OUTPUT);
  pinMode (in3_g, OUTPUT);
  pinMode (in4_g, OUTPUT);
  pinMode (enb_g, OUTPUT);

  pinMode (ena_d, OUTPUT);
  pinMode (in1_d, OUTPUT);
  pinMode (in2_d, OUTPUT);
  pinMode (in3_d, OUTPUT);
  pinMode (in4_d, OUTPUT);
  pinMode (enb_d, OUTPUT);

  motors[0].in1 = in1_g;
  motors[0].in2 = in2_g;
  motors[0].pwn = ena_g;

  motors[1].in1 = in3_g;
  motors[1].in2 = in4_g;
  motors[1].pwn = enb_g;

  motors[2].in1 = in1_d;
  motors[2].in2 = in2_d;
  motors[2].pwn = ena_d;

  motors[3].in1 = in3_d;
  motors[3].in2 = in4_d;
  motors[3].pwn = enb_d;
}

void ENGINES::drive_motors(int speed0, int speed1, int speed2, int speed3) {
  this->drive_motor(this->MOTOR_ARG,speed0);
  this->drive_motor(this->MOTOR_AVG,speed1);
  this->drive_motor(this->MOTOR_AVD,speed2-(speed2/50));
  this->drive_motor(this->MOTOR_ARD,speed3-(speed3/100));
}

void ENGINES::drive_motor(int motor_index, int speed) {
  analogWrite(motors[motor_index].pwn,speed);
}

void ENGINES::setup_motors(int state1, int state2, int state3, int state4, int state5, int state6, int state7, int state8) {
  ENGINES::setup_motor(this->MOTOR_ARG,state1,state2);
  ENGINES::setup_motor(this->MOTOR_AVG,state3,state4);
  ENGINES::setup_motor(this->MOTOR_AVD,state5,state6);
  ENGINES::setup_motor(this->MOTOR_ARD,state7,state8);
}

void ENGINES::setup_motor(int motor_index, int state1, int state2) {
  digitalWrite(motors[motor_index].in1, state1);
  digitalWrite(motors[motor_index].in2, state2);
}

void ENGINES::forward(int speed, int delay_time) {
  this->setup_motors(HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW);
  this->drive_motors(speed, speed, speed, speed);
  delay(delay_time);
}

void ENGINES::backward(int speed, int delay_time) {
  this->setup_motors(LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH);
  this->drive_motors(speed, speed, speed, speed);
  delay(delay_time);
}

void ENGINES::full_stop(int delay_time) {
  this->setup_motors(LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW);
  this->drive_motors(0,0,0,0);
  delay(delay_time);
}

void ENGINES::rotate_right(int speed, int delay_time){
  this->setup_motors(HIGH,LOW,HIGH,LOW,LOW,HIGH,LOW,HIGH);
  this->drive_motors(speed, speed, speed, speed);
  delay(delay_time);
}

void ENGINES::rotate_left(int speed, int delay_time){
  this->setup_motors(LOW,HIGH,LOW,HIGH,HIGH,LOW,HIGH,LOW);
  this->drive_motors(speed, speed, speed, speed);
  delay(delay_time);
}

void ENGINES::lateral_right(int speed, int delay_time){
  this->setup_motors(HIGH,LOW,LOW,HIGH,HIGH,LOW,LOW,HIGH);
  this->drive_motors(speed, speed, speed, speed);
  delay(delay_time);
}

void ENGINES::lateral_left(int speed, int delay_time){
  this->setup_motors(LOW,HIGH,HIGH,LOW,LOW,HIGH,HIGH,LOW);
  this->drive_motors(speed, speed, speed, speed);
  delay(delay_time);
}

void ENGINES::forward_rotate_right(int speed1, int speed2, int delay_time){
  this->setup_motors(HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW);
  this->drive_motors(speed1, speed1, speed2, speed2);
  delay(delay_time);
}

void ENGINES::forward_rotate_left(int speed1, int speed2, int delay_time){
  this->setup_motors(HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW);
  this->drive_motors(speed2, speed2, speed1, speed1);
  delay(delay_time);
}

void ENGINES::backward_rotate_right(int speed1, int speed2, int delay_time){
  this->setup_motors(LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH);
  this->drive_motors(speed1, speed1, speed2, speed2);
  delay(delay_time);
}

void ENGINES::backward_rotate_left(int speed1, int speed2, int delay_time){
  this->setup_motors(LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH);
  this->drive_motors(speed2, speed2, speed1, speed1);
  delay(delay_time);
}

void ENGINES::forward_lateral_right(int speed, int delay_time){
  this->setup_motors(LOW,LOW,HIGH,LOW,LOW,LOW,HIGH,LOW);
  this->drive_motors(0, speed, 0, speed);
  delay(delay_time);
}

void ENGINES::forward_lateral_left(int speed, int delay_time){
  this->setup_motors(HIGH,LOW,LOW,LOW,HIGH,LOW,LOW,LOW);
  this->drive_motors(speed, 0, speed, 0);
  delay(delay_time);
}

void ENGINES::backward_lateral_right(int speed, int delay_time){
  this->setup_motors(LOW,LOW,LOW,HIGH,LOW,LOW,LOW,HIGH);
  this->drive_motors(0, speed, 0, speed);
  delay(delay_time);
}

void ENGINES::backward_lateral_left(int speed, int delay_time){
  this->setup_motors(LOW,HIGH,LOW,LOW,LOW,HIGH,LOW,LOW);
  this->drive_motors(speed, 0, speed, 0);
  delay(delay_time);
}

void ENGINES::rotate_right_lateral_right(int speed, int delay_time){
  this->setup_motors(HIGH,LOW,LOW,LOW,LOW,HIGH,HIGH,LOW);
  this->drive_motors(speed, 0, speed, speed);
  delay(delay_time);
}

void ENGINES::rotate_right_lateral_left(int speed, int delay_time){
  this->setup_motors(HIGH,LOW,LOW,HIGH,LOW,LOW,LOW,HIGH);
  this->drive_motors(0, speed, speed, speed);
  delay(delay_time);
}

void ENGINES::rotate_left_lateral_right(int speed, int delay_time){
  this->setup_motors(LOW,HIGH,HIGH,LOW,LOW,HIGH,HIGH,LOW);
  this->drive_motors(speed, speed, speed, 0);
  delay(delay_time);
}

void ENGINES::rotate_left_lateral_left(int speed, int delay_time){
  this->setup_motors(HIGH,LOW,LOW,HIGH,HIGH,LOW,LOW,LOW);
  this->drive_motors(speed, speed, 0, speed);
  delay(delay_time);
}





