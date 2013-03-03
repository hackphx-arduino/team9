/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
#include <Shieldbot.h>
//#include <Servo.h> 
 
//Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 

Shieldbot shieldbot = Shieldbot();

int sensorPin = 0; //analog 0
int sonarValue;
int sonarTotal = 0;
int sonarAve = 0;
int sensorValue = 0;
int sensorAve = 0;
int sensorAngle = 0;
int shortRotateDelay = 20;

int shortMovAveTotal = 0;
int shortMovAve = 0;
const int shortNumReadings = 10;
int shortReadings[shortNumReadings];      // the readings from the analog input
int shortIndex = 0;

int longMovAveTotal = 0;
int longMovAve = 0;
const int longNumReadings = 20;
int longReadings[longNumReadings];      // the readings from the analog input
int longIndex = 0;

int looking = 0;




unsigned long previousMillis;
long interval = 1000;



// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
      shieldbot.setMaxSpeed(40);//255 is max
      //pinMode(3, OUTPUT);
//    myservo.attach(A3);  // attaches the servo on pin 9 to the servo object
   pinMode(2, OUTPUT);
   
   digitalWrite(2,HIGH); //power for sonar 

    
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue = analogRead(sensorPin);
  delay(1);
  sensorValue = abs(sensorValue - 12);
  sensorAngle = map(sensorValue, 100, 450, 0, 120);
  
  shortMovAveTotal = shortMovAveTotal - shortReadings[shortIndex];
  shortReadings[shortIndex] = sensorAngle;
  shortMovAveTotal = shortMovAveTotal + shortReadings[shortIndex];
  shortIndex++;
  if (shortIndex >= shortNumReadings){
    shortIndex = 0;
  }
  shortMovAve = shortMovAveTotal / shortNumReadings;
 
 
 
  longMovAveTotal = longMovAveTotal - longReadings[longIndex];
  longReadings[longIndex] = sensorAngle;
  longMovAveTotal = longMovAveTotal + longReadings[longIndex];
  longIndex++;
  if (longIndex >= longNumReadings){
    longIndex = 0;
  }
  longMovAve = longMovAveTotal / longNumReadings; 
  
  
  
  /*
  shortMovAve = shortMovAveTotal / 4;
  shortMovAveTotal = shortMovAveTotal - shortMovAve;
  
  
  
  longMovAveTotal = sensorAngle + longMovAveTotal;
  longMovAve = longMovAveTotal / 8;
  longMovAveTotal = longMovAveTotal - shortMovAve;
  */
  
  
  if( shortMovAve < longMovAve ) {
      shieldbot.drive(-128,127);   //turn left on a dime
      delay(shortRotateDelay);
      looking = 0;  
  }
  else if( shortMovAve > longMovAve ) {
      shieldbot.drive(127,-128);   //turn left on a dime
      delay(shortRotateDelay);
      looking = 0;
  }
  else {
      shieldbot.stop();   //turn left on a dime
      previousMillis = millis();
      looking = 1;      
  }
  
  

//  sonarTotal = sonarValue + sonarTotal;
//  sensorAve = sonarTotal / 8;  
//  sonarTotal = sonarTotal - sonarAve;
//  sensorValue = sensorAve;
// print out the value you read:
  Serial.println(sensorValue);
  // delay(1);        // delay in between reads for stability
  

  if(millis() - previousMillis < interval && looking == 1) {
/*      for(pos = 0; pos < 60; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 60; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
   looking = 0;
  */ 
  }

}
