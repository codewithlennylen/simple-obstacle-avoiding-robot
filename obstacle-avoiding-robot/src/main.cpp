#include <Arduino.h>
#include <Servo.h>

float get_distance();

void move_forward();
void move_backward();
void turn_left();
void turn_right();
void stop();

void look_forward();
void look_left();
void look_right();

int servoPin = 8;

int TRIG_PIN = 10;
int ECHO_PIN = 11;

int ENA = 2;
int IN1 = 3;
int IN2 = 4;
int IN3 = 5;
int IN4 = 6;
int ENB = 7;

int full_speed = 255;
int half_speed = 127;
int quarter_speed = 72;

Servo servo;

void setup()
{
  // begin serial port
  Serial.begin(9600);

  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  servo.attach(servoPin);

  delay(3000);
}

void loop()
{

  float distance = get_distance();
  float distance_left;
  float distance_right;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 15)
  {
    stop();

    delay(300);
    look_left();
    delay(200);
    distance_left = get_distance();
    delay(1000);
    look_right();
    delay(200);
    distance_right = get_distance();
    delay(1000);

    if (distance_left > distance_right)
    {
      look_forward();
      turn_left();
      delay(1000);
      distance = distance_left;
    }
    else
    {
      look_forward();
      turn_right();
      delay(1000);
      distance = distance_right;
    }
  }
  else
  {
    move_forward();
  }

  delay(300);
}

float get_distance()
{
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  float duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  float distance_cm = 0.017 * duration_us;

  return distance_cm;
}

void look_forward()
{
  servo.write(90);
}

void look_left()
{
  servo.write(180);
}

void look_right()
{
  servo.write(0);
}

void move_forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, half_speed);
  analogWrite(ENB, half_speed);
}

void move_backward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, half_speed);
  analogWrite(ENB, half_speed);
}

void turn_right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, quarter_speed);
  analogWrite(ENB, quarter_speed);
}

void turn_left()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, quarter_speed);
  analogWrite(ENB, quarter_speed);
}

void stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
