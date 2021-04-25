#include <Arduino.h>
#include <AFMotor.h>

#define trigPin1 A0
#define echoPin1 A1
#define trigPin2 A2
#define echoPin2 A3
#define trigPin3 A4
#define echoPin3 A5

long duration, distance, FIRSTSensor, SECONDSensor, THIRDSensor;
char command;
bool ultraOn = false;

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);

long SonarSensor(int trigPin, int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    return distance = (duration / 2) / 29.1;
}
void forward()
{
  motor1.setSpeed(240);
  motor1.run(FORWARD);
  motor2.setSpeed(240);
  motor2.run(BACKWARD);
  motor3.setSpeed(0);
  motor3.run(FORWARD);
}
void backward()
{
  motor1.setSpeed(240);
  motor1.run(BACKWARD);
  motor2.setSpeed(240);
  motor2.run(FORWARD);
  motor3.setSpeed(0);
  motor3.run(BACKWARD);
}
void right()
{
  motor1.setSpeed(90);
  motor1.run(FORWARD);
  motor2.setSpeed(90);
  motor2.run(FORWARD);
  motor3.setSpeed(180);
  motor3.run(BACKWARD);
}
void obliqueLeft()
{
  motor1.setSpeed(70);
  motor1.run(FORWARD);
  motor2.setSpeed(235);
  motor2.run(BACKWARD);
  motor3.setSpeed(187);
  motor3.run(FORWARD);
}
void left()
{
  motor1.setSpeed(90);
  motor1.run(BACKWARD);
  motor2.setSpeed(90);
  motor2.run(BACKWARD);
  motor3.setSpeed(180);
  motor3.run(FORWARD);
}
void obliqueRight()
{
  motor1.setSpeed(235);
  motor1.run(FORWARD);
  motor2.setSpeed(70);
  motor2.run(BACKWARD);
  motor3.setSpeed(187);
  motor3.run(BACKWARD);
}
void spin()
{
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
}
void backspin()
{
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
}

void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
}

void setup()
{
    Serial.begin(9600);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);
    Stop();
}

void loop()
{
    if (Serial.available() > 0)
    {
        command = Serial.read();
        Serial.print(command);
        if (ultraOn == false)
        {
            switch (command)
            {
            case 'F':
                forward();
                break;
            case 'L':
                left();
                break;
            case 'R':
                right();
                break;
            case 'B':
                backward();
                break;
            case 'I':
                obliqueRight();
                break;
            case 'G':
                obliqueLeft();
                break;
            case 'H':
                backspin();
                break;
            case 'J':
                spin();
                break;
            case 'V':
                ultraOn = true;
                break;
            case 'v':
                ultraOn = false;
                break;
            default:
                Stop();
                break;
            }
        }
    }

    if (ultraOn == true)
    {
        SonarSensor(trigPin1, echoPin1);
        FIRSTSensor = distance;
        SonarSensor(trigPin2, echoPin2);
        SECONDSensor = distance;
        SonarSensor(trigPin3, echoPin3);
        THIRDSensor = distance;
        if (THIRDSensor > 14)
        {
            if (SECONDSensor<8 & SECONDSensor> 0)
            {
                left();
                delay(150);
            }
            else if ((FIRSTSensor<8 & FIRSTSensor> 0) && (SECONDSensor<8 & SECONDSensor> 0))
            {
                right();
                delay(150);
            }
            forward();
        }
        else if (THIRDSensor < 14)
        {
            Stop();
        }
    }
    if (command == 'v')
        ultraOn = false;
}
