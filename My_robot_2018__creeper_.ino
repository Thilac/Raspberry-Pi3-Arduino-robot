#include <Servo.h>

Servo myservo;
Servo myservo1;
Servo turn_servo;

float x;
float y;
float radius;
float area;

int vcc = 13;
int red_led = 12;
int blue_led = 11;
int green_led = 10;

int mid_pos = 90;
int vertical_possition = 90;

int destiation_angle;
int destiation_angle1;

int pos = 0;
int pos1 = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode (vcc, OUTPUT);
  pinMode (red_led, OUTPUT);
  pinMode (blue_led, OUTPUT);
  pinMode (green_led, OUTPUT);

  digitalWrite (vcc, HIGH);
  digitalWrite (green_led, LOW);
  digitalWrite (blue_led, HIGH);
  digitalWrite (red_led, HIGH);

  myservo.attach(9);  // for pan
  myservo.write(90);
  myservo1.attach(8); // for tilting
  myservo1.write(90);
  turn_servo.attach(7); // controll direction of front wheel
  turn_servo.write(90);

}

void loop() {
  /*---- Read the data using UART ---------------------------------------*/
  if (Serial1.available () > 0) {

    Serial.flush();
    String incomingByte = Serial1.readStringUntil('/;');  // Read the string unting there is semicolm

    /*---- Seperate the string by comma and store their values -----------*/
    int commaIndex = incomingByte.indexOf(',');
    int secondCommaIndex = incomingByte.indexOf(',', commaIndex + 1);
    String firstValue = incomingByte.substring(0, commaIndex);
    String secondValue = incomingByte.substring(commaIndex + 1, secondCommaIndex);
    String thirdValue = incomingByte.substring(secondCommaIndex + 1);

    /*---- Convert string to int -----------------------------------------*/
    x = firstValue.toFloat();
    y = secondValue.toFloat();
    radius = thirdValue.toFloat();

    area = (2 * PI * radius);

    /*---- For debucking purpose -----------------------------------------*/
    //Serial.print ("X = ");
    //Serial.println(x);
    Serial.print ("Y = ");
    Serial.println (y);
    //Serial.print ("radius = ");
    //Serial.println (radius);
    /*
        if (!Serial.available () || x == 0 || y == 0 || radius == 0) {
          x = 0;
          y = 0;
          area = 0;
          myservo.write(90);
          turn_servo.write(90);
          myservo1.write(90);
        }

    */
    /*---- For horizontal Servo ---------------------------------------------*/
    if (x > 360) {  // 250
      destiation_angle = 1;
    }

    else if (x < 40 && x > 1) { // 150

      destiation_angle = 2;

    }

    else if (x <= 0 || x <= 250 || x >= 150) {
      destiation_angle1 = 3;
    }


    /*---- For vertical Servo -----------------------------------------------*/

    if (y > 260) {   // 180
      destiation_angle1 = 4;
    }

    else if (y < 40 && y > 1) { // (y < 120 && y > 1)

      destiation_angle1 = 5;

    }

    else if (y <= 0 || y <= 180 || y >= 120) {
      destiation_angle1 = 6;
    }

    /*---- Motor and direction controll -----------------------------------*/
    /*
        if (area >= 71) {

          // Reverse the car functions (controll Motor)
        }

        else if (area < 10) {
          // Go forward function (controll Motor)
        }

    */



    /*---- Deside whether to turn left or right ---------------------------*/
    switch (destiation_angle) {


      case 2:
        mid_pos += 2;
        

        if (mid_pos > 170) {

          mid_pos = 180;
        }

        break;


      case 1:
        mid_pos -= 2;
     
        
        if (mid_pos < 10) {

          mid_pos = 10;
        }

        break;


      case 3:

        pos = myservo.read ();
        myservo.write (pos);

        break;
    }


    switch (destiation_angle1) {

      case 4:
        vertical_possition += 2;

        if (vertical_possition > 170) {

          vertical_possition = 170;
        }

        break;


      case 5:
        vertical_possition -= 2;

        if (vertical_possition < 10) {

          vertical_possition = 10;
        }

        break;

      case 6:

        pos1 = myservo1.read ();
        myservo1.write (pos1);

        break;
    }

    myservo.write(mid_pos);
    turn_servo.write(mid_pos);
    myservo1.write(vertical_possition);
    //Serial.flush();

    //delay(20);
  }
}



