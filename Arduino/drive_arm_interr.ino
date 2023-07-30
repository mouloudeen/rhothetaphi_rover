#include <Engines.h>
#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Cablages moteurs L298N
#define ENA_G 13
#define IN1_G 12
#define IN2_G 11
#define IN3_G 10
#define IN4_G 9
#define ENB_G 8
#define ENA_D 3
#define IN1_D 2
#define IN2_D 4
#define IN3_D 5
#define IN4_D 7
#define ENB_D 6
#define SERVOMIN 150 // Position minimale
#define SERVOMAX 600 // Position maximale

// Pin Chip Select
#define CS 53

struct can_frame canMsg; // can_frame de réception
// struct can_frame canSnd //can_frame d'envoi
MCP2515 mcp2515(CS);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint8_t servoClaw = 3;
uint8_t servoA = 0;
uint8_t servoB = 1;
uint8_t servoC = 2;
int pulseLen;
int claw = 0;
int motorA = 90;
int motorB = 90;
int motorC = 90;

ENGINES rover(ENA_G, IN1_G, IN2_G, IN3_G, IN4_G, ENB_G, ENA_D, IN1_D, IN2_D, IN3_D, IN4_D, ENB_D);
int time_delay = 100;
int speed = 255;
int speed2 = 75;

int mode;                 // passage entre direction et bras
int config;               // choix de la configuration (marche avant, bras tendu...)
volatile bool received = false; // flag pour éviter une boucle infinie

// Réception informations CAN (2 octets)
int receive_can(int *mode, int *config)
{

    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
    {
        *mode = canMsg.data[0];
        *config = canMsg.data[1];
        received = true;
    }
} //

// envoi informations CAN (2 octets)
void send_can()
{
    mcp2515.sendMessage(&canMsg);

    Serial.println("Messages sent");

    delay(2000);
}

void irqHandler() {
    received = true;
}

void setup()
{

    // Partie Réception
    Serial.begin(115200);

    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp2515.setNormalMode();

    attachInterrupt(0, irqHandler, FALLING);

    Serial.println("------- CAN Read ----------");
    Serial.println("ID  DLC   DATA");

    // Partie Envoi
    /*canSnd.can_id  = 0x0F6;
    canSnd.can_dlc = 2;
    canSnd.data[0] = 0x8E;
    canSnd.data[1] = 0x87;
    canSnd.data[2] = 0x32;
    canSnd.data[3] = 0xFA;
    canSnd.data[4] = 0x26;
    canSnd.data[5] = 0x8E;
    canSnd.data[6] = 0xBE;
    canSnd.data[7] = 0x86;*/

    while (!Serial)
        ;
    Serial.begin(115200);

    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp2515.setNormalMode();

    Serial.println("Example: Write to CAN");

    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);

    pulseLen = map(0, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servoClaw, 0, pulseLen); // Claw
    delay(1000);
    pulseLen = map(90, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servoA, 0, pulseLen); // MotorA
    delay(1500);
    pwm.setPWM(servoB, 0, pulseLen); // MotorB
    delay(1500);
    pwm.setPWM(servoC, 0, pulseLen); // MotorC
    delay(1500);
}

void loop()
{

    // send_can();
    receive_can(&mode, &config);
    if (received)
    {
    uint8_t irq = mcp2515.getInterrupts();
        switch (mode)
        {
        case 0:
            switch (config)
            { // Mode Conduite
            case 0:
                received = false;
                while(!received){
                  rover.full_stop(time_delay);
                  receive_can(&mode, &config);
                }
                break;
            case 1:
                received = false;
                while(!received){
                  rover.rotate_left(speed, time_delay);
                  receive_can(&mode, &config);
                  // rover.full_stop(time_delay);
                }
                break;
            case 2:
                received = false;
                while(!received){
                  rover.forward(speed, time_delay);
                  receive_can(&mode, &config);
                  // rover.full_stop(time_delay);
                }
                break;
            case 3:
                received = false;
                while(!received){
                  rover.rotate_right(speed, time_delay);
                  receive_can(&mode, &config);
                  // rover.full_stop(time_delay);
                }
                break;
            case 4:
                received = false;
                while(!received){
                  rover.lateral_left(speed, time_delay);
                  receive_can(&mode, &config);
                  // rover.full_stop(time_delay);
                }
                break;
            case 5:
                received = false;
                while(!received){
                  rover.lateral_right(speed, time_delay);
                  receive_can(&mode, &config);
                  // rover.full_stop(time_delay);
                }
                break;
            case 6:
                received = false;
                while(!received){
                  rover.backward(speed, time_delay);
                  receive_can(&mode, &config);
                  // rover.full_stop(time_delay);
                }
                break;
            default:
                received = false;
                while(!received){
                  rover.full_stop(time_delay);
                  receive_can(&mode, &config);
                }
                break;
            }
            break;
        case 1:
            switch (config)
            { // Mode Bras
            case 1:
                claw -= 15;
                if (claw >= 0)
                {
                    pulseLen = map(claw, 0, 180, SERVOMIN, SERVOMAX);
                    pwm.setPWM(servoClaw, 0, pulseLen); // claw1
                    delay(1);
                }
                else
                {
                    claw = 0;
                }
                config = 0;
                break;
            case 2:
                claw += 15;
                if (claw <= 75)
                {
                    pulseLen = map(claw, 0, 180, SERVOMIN, SERVOMAX);
                    pwm.setPWM(servoClaw, 0, pulseLen); // claw2
                    delay(1);
                }
                else
                {
                    claw = 180;
                }
                config = 0;
                break;
            case 3:
                motorA -= 5;
                if (motorA >= 60)
                {
                    pulseLen = map(motorA, 0, 180, SERVOMIN, SERVOMAX);
                    pwm.setPWM(servoA, 0, pulseLen); // motorA1
                    delay(1);
                }
                else
                {
                    motorA = 60;
                }
                config = 0;
                break;
            case 4:
                motorA += 5;
                if (motorA <= 100)
                {
                    pulseLen = map(motorA, 0, 180, SERVOMIN, SERVOMAX);
                    pwm.setPWM(servoA, 0, pulseLen); // motorA2
                    delay(1);
                }
                else
                {
                    motorA = 100;
                }
                config = 0;
                break;
            case 5:
                motorB -= 5;
                if (motorB >= 60)
                {
                    pulseLen = map(motorB, 0, 180, SERVOMIN, SERVOMAX);
                    pwm.setPWM(servoB, 0, pulseLen); // motorB1
                    delay(1);
                }
                else
                {
                    motorB = 60;
                }
                config = 0;
                break;
            case 6:
                motorB += 5;
                if (motorB <= 100)
                {
                    pulseLen = map(motorB, 0, 180, SERVOMIN, SERVOMAX);
                    pwm.setPWM(servoB, 0, pulseLen); // motorB2
                    delay(1);
                }
                else
                {
                    motorB = 180;
                }
                config = 0;
                break;
            case 7:
                motorC -= 5;
                if (motorC >= 60)
                {
                    pulseLen = map(motorC, 0, 180, SERVOMIN, SERVOMAX);
                    pwm.setPWM(servoC, 0, pulseLen); // motorC1
                    delay(1);
                }
                else
                {
                    motorC = 60;
                }
                config = 0;
                break;
            case 8:
                motorC += 5;
                if (motorC <= 100)
                {
                    pulseLen = map(motorC, 0, 180, SERVOMIN, SERVOMAX);
                    pwm.setPWM(servoC, 0, pulseLen); // motorC2
                    delay(1);
                }
                else
                {
                    motorB = 100;
                }
                config = 0;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}
