/*
	SD_Manager_SeniorProject.h

	SD class for IMU Data Transmission

	Last Edit: Theodore Nowak 10/12/2014
*/

#ifndef SD_Manager_SeniorProject_h
#define SD_Manager_SeniorProject_h

#include "Arduino.h"
#include "SD.h"
#include "SPI.h"

class SD_Manager_SeniorProject {

public:

SD_Manager_SeniorProject(const int chipSelect);

void initializeSDCard();
bool getStatus();
void checkStatus();

private:

const int chipSelect;
bool isSD;

};
#endif