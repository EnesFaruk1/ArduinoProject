#include <SPI.h> //SD Card Library
#include <SD.h> //SD Card Library
#include <LiquidCrystal.h> //LCD Display library
#include <Servo.h> //Servo library
#include <virtuabotixRTC.h> //RTC library

int CS_PIN = 10; // Digital Pin for SD Card CS pin 
File test; // File to write data for SD 
LiquidCrystal lcd(12,11,5,4,3,2); //Initializing the LCD
int clk_pin = 6;
int data_pin = 7; // 6,7,8 Pins for the RTC Module
int rst_pin = 8;

virtuabotixRTC myRTC(clk_pin,data_pin,rst_pin); //Initializing the RTC

Servo myservo;  // create servo object to control a servo
int deger; // For fetching the angle
int derece; // For fetching the angle

const int servoAnalogOut=A1; //The new Servo Pin
unsigned int servoValue0Deg, servoValue180Deg; // Variables to store min and max values of servo's pot
int pos = 0;    // variable to store the servo position

void setup() {
 lcd.begin(16,2);
 lcd.print("hello!");
 myservo.attach(13);
 Serial.begin(9600);
 //initializeSD();
 //createFile(test.txt);
 //writeToFile("This is sample text!");
 //closeFile();
 //openFile("test.txt");
 //Serial.println(readLine());
 //Serial.println(readLine());
 //closeFile();
 calibration(); // Calling the function to calibrate Servo
}

void loop() {
 myRTC.updateTime();
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(myRTC.dayofmonth);
 lcd.print("/");
 lcd.print(myRTC.month);
 lcd.print("/");
 lcd.print(myRTC.year);   // Writing the initial time to LCD Display with RTC
 lcd.print("/");
 lcd.setCursor(0,1);
 lcd.print(myRTC.hours);
 lcd.print("/");
 lcd.print(myRTC.minutes);
 lcd.print("/");
 lcd.print(myRTC.seconds);
 lcd.print("   ");

 Serial.print(myRTC.dayofmonth);
 Serial.print("/");
 Serial.print(myRTC.month);
 Serial.print("/");
 Serial.print(myRTC.year);
 Serial.print("/");
 Serial.print(myRTC.hours);   // Writing the initial time to Serial with RTC
 Serial.print("/");
 Serial.print(myRTC.minutes);
 Serial.print("/");
 Serial.print(myRTC.seconds);
 Serial.print("   ");
 Serial.println(map(analogRead(servoAnalogOut),servoValue0Deg,servoValue180Deg, 0, 180)); // Writing the Servo angles to Serial with RTC

 lcd.print(map(analogRead(servoAnalogOut),servoValue0Deg,servoValue180Deg, 0, 180)); // Writing the Servo angles to LCD Display with RTC
 delay(500); // This delay is for avoiding the blinking of the new angle on the LCD
 deger = analogRead(A0); // Analog pin for the Potentiometer of the Servo
 derece = map(deger, 0,1023,0,180); // Initializing the Servo angles
 myservo.write(derece);
}

void calibration(){
  myservo.write(0); //set the servo to 0 position
  delay(2000); //wait for the servo to reach there
  servoValue0Deg= analogRead(servoAnalogOut); // Pot value at 0 degrees
  Serial.println("Pot value for 0 deg is " + String(servoValue0Deg)); // Print it!
  delay(500); //fancy delay
  myservo.write(180); //go to 180 degrees
  delay(2000); //wait for the servo to reach there
  servoValue180Deg= analogRead(servoAnalogOut); //pot value at 180 deg
  Serial.println("Pot value for 180 deg is " + String(servoValue0Deg));
  delay(500); //fancy delay 
  Serial.println("Now going to 90 Degrees"); //It does what it says
  myservo.write(90);// going to 90 degrees
  delay(2000);// wait for it to reach there
  //myservo.detach(); // stop the PWM so that we can freely move the servo
  delay(1000);
  Serial.println(derece);
  
}
