/*
  ENGINES.h - Library for ENGINES motor driver
*/
#ifndef ENGINES_h
#define ENGINES_h

#include "Arduino.h"

class ENGINES
{
  public:
    static const int MOTOR_ARG = 0;
    static const int MOTOR_AVG = 1;
    static const int MOTOR_AVD = 2;
    static const int MOTOR_ARD = 3;

    //Constructeur
    ENGINES(int ena_g, int in1_g, int in2_g, int in3_g, int in4_g, int enb_g, int ena_d, int in1_d, int in2_d, int in3_d, int in4_d, int enb_d);
    void drive_motors(int speed0, int speed1, int speed2, int speed3);
    void drive_motor(int motor_index, int speed);

    //Setters
    void setup_motors(int state1, int state2, int state3, int state4, int state5, int state6, int state7, int state8);
    void setup_motor(int motor_index, int state1, int state2);

    //Méthodes
    void forward(int speed, int delay_time);
    void backward(int speed, int delay_time);
    void full_stop(int delay_time);

    void rotate_right(int speed, int delay_time);
    void rotate_left(int speed, int delay_time);
 
    void lateral_right(int speed, int delay_time);
    void lateral_left(int speed, int delay_time);

    void forward_rotate_right(int speed1, int speed2, int delay_time);
    void forward_rotate_left(int speed1, int speed2, int delay_time);

    void backward_rotate_right(int speed1, int speed2, int delay_time);
    void backward_rotate_left(int speed1, int speed2, int delay_time);

    void forward_lateral_right(int speed, int delay_time);
    void forward_lateral_left(int speed, int delay_time);

    void backward_lateral_right(int speed, int delay_time);
    void backward_lateral_left(int speed, int delay_time);

    void rotate_right_lateral_right(int speed, int delay_time);
    void rotate_right_lateral_left(int speed, int delay_time);
    void rotate_left_lateral_right(int speed, int delay_time);
    void rotate_left_lateral_left(int speed, int delay_time);

  private:
    struct Motor;
    int _ena_g;
    int _in1_g;
    int _in2_g;
    int _in3_g;
    int _in4_g;
    int _enb_g;
    int _ena_d;
    int _in1_d;
    int _in2_d;
    int _in3_d;
    int _in4_d;
    int _enb_d;
};

#endif
