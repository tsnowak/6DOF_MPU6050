/*
    Last Edited 12/01/2014 by: Theodore Nowak
*/

#include "I2Cdev.h"
#include "MPU6050.h"
#include "SD.h"
#include "SPI.h"
#include "IMU_SeniorProject.h"
#include "SD_Manager_SeniorProject.h"

// Initialize and assign library classes
SD_Manager_SeniorProject sdObject(52);
IMU_SeniorProject imuObject(0, &sdObject);

// Include dependent on whether we are using wire or fastwire
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

#define LED_PIN 13
bool blinkState = false;

void setup(){
  
  // Sets wire or fastwire measurement method
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400,true);
  #endif
 
  Serial.begin(9600);
  
  // Starts up the IMU and initializes parameters to default values
  imuObject.initializeIMU();
  
  // Ensures that we have successfully connected to the IMU
  imuObject.verifyConnection();
  
  // Ensures that an SD card is connected [Currently SD recording is not completed or necessary]
  sdObject.initializeSDCard();
  
  // Ensures the SD card is properly connected
  sdObject.checkStatus();

  pinMode(LED_PIN, OUTPUT);  
}

void loop(){
  
  // Gets the accel/gyro values from the IMU
  imuObject.takeMeasurements();
  
  // Outputs previously collected values
  imuObject.outputToFormat(0);
  
  
 // Blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

