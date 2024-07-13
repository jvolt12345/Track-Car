#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <Servo.h>
Servo myservo;

int angle = 90;
int angleStep = 5;

char t;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);      //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
  myservo.attach(11);
  myservo.write(angle);
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
 // Serial.print("KeyPressed: ");

  if (GamePad.isUpPressed())   // FORWARD
  {
    Serial.print("UP");
    digitalWrite(8, HIGH);    // 8 = left     forward
    digitalWrite(10, HIGH);    // 10 = right    forward
  }
  else if (GamePad.isDownPressed())    // REVERSE
  {
    Serial.print("DOWN");
    digitalWrite(9, HIGH);    // 9 = right    reverse
    digitalWrite(7, HIGH);    // 7 = left     reverse
  }
  else if (GamePad.isLeftPressed())    // TURN LEFT
  {
    Serial.print("Left");
    digitalWrite(10, HIGH);    // right forward 
    digitalWrite(7, HIGH);    // left  reverse
  }
  else if (GamePad.isRightPressed())   // TURN RIGHT
  {
    Serial.print("Right");
    digitalWrite(8, HIGH);    // left  forward
    digitalWrite(9, HIGH);    // fight reverse
  }
    else 
    {
      digitalWrite(8, LOW);     // stops the motor
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(7, LOW);
    }
  

  if (angle > 0 && angle <= 180 && GamePad.isSquarePressed()) {
    angle = angle - angleStep;
    if (angle < 0) {
      angle = 0;
    } else {
      myservo.write(angle);
      Serial.print("Moved to: ");
      Serial.print(angle);
      Serial.println("degree");
    }
  }

  delay(20);

  if (angle >= 0 && angle < 180 && GamePad.isCirclePressed()) {
    angle = angle + angleStep;
    if (angle < 0) {
      angle = 0;
    } else {
      myservo.write(angle);
      Serial.print("Moved to: ");
      Serial.print(angle);
      Serial.println("degree");
    }
  }
  delay(20);
}
