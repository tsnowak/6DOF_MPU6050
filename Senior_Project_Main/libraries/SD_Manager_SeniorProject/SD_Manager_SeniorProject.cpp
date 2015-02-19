/*
  SD_Manager_Baja.h Implementation

  Last Edit: Ted Nowak 10/12/2014
*/

#include "Arduino.h"
#include <SD_Manager_SeniorProject.h>


// Initializes the SD card at the chip location
SD_Manager_SeniorProject::SD_Manager_SeniorProject(const int chipSelect):chipSelect(chipSelect) {
	isSD = false;
}

// Begins the SD card session if it can
void SD_Manager_SeniorProject::initializeSDCard() {
	if (!SD.begin(chipSelect)) {
		isSD = false;
		return;
	} 
	else {
		isSD = true;
	}
}

// Ensures that the file location exists
void SD_Manager_SeniorProject::checkStatus() {
	if (SD.exists("IMUData.txt")) {
		isSD = true;
	}
	else {
		isSD = false;
	}
}

// Retrieves isSD for public use
bool SD_Manager_SeniorProject::getStatus() {
	return isSD;
}