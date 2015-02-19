/*
	Implementation of the IMU_SeniorProject.h file

	Last Edit: Theodore Nowak 11/20/2014
*/


#include "Arduino.h"
#include "Wire.h"
#include <IMU_SeniorProject.h>

// Sets the address, initializes to default parameters and sets the clockSpeed
IMU_SeniorProject::IMU_SeniorProject(uint8_t address, SD_Manager_SeniorProject *ptrSDObject) {	
	_SDObject = ptrSDObject;
	
	// Set IMU to specified address
	if (address == 0x69||address == 0x68) {
		MPU6050 imu(address);
	}
	
	// If address is not specified, change the address to the default
	else {
		MPU6050 imu;
	}
	
	// Initialize the data count to 0
	dataCounter = 0;
}

/** Initialize IMU with default parameters
 *  (+/-2g, +/- 250 deg/sec, CLK Source References X-Gyro)
 */
void IMU_SeniorProject::initializeIMU() {
	Serial.println("Initializing I2C devices.....");
	imu.initialize();
}

/** Sets the Masters Clock Speed 4-bit binary 0-15 where all 
 *  values are dividends of 8MHz
 */
void IMU_SeniorProject::masterClock(int8_t clockSpeed) {
	imu.setMasterClockSpeed(clockSpeed);
}

// Determines if IMU is connected or not
bool IMU_SeniorProject::testIMUConnection() {
	return imu.testConnection();
}

// Outputs to Serial whether IMU(s) are connected or not
void IMU_SeniorProject::verifyConnection() {
	if (testIMUConnection()){
		Serial.println("MPU6050 connection successful!");
	}
	else if (!testIMUConnection()){
		Serial.println("All is lost.... Abandon Ship.");
	}
}

// Records the accel/gyro measurements
void IMU_SeniorProject::takeMeasurements() {
	imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
}

/*
 * Functions to return individual IMU magnitude values
 */
int16_t IMU_SeniorProject::getAX() {
	return ax;
}

int16_t IMU_SeniorProject::getAY() {
	return ay;
}

int16_t IMU_SeniorProject::getAZ() {
	return az;
}

int16_t IMU_SeniorProject::getGX() {
	return gx;
}

int16_t IMU_SeniorProject::getGY() {
	return gy;
}

int16_t IMU_SeniorProject::getGZ() {
	return gz;
}

// Retrieve the status of the SD card
bool IMU_SeniorProject::sdStatus() {
	return _SDObject -> getStatus();
}

// Output in Decimal format
void IMU_SeniorProject::printDecimal() {
	
	int dif = millis()-lastmil;
	lastmil = millis();

	Serial.print(dif); Serial.print("\t");
    Serial.print(((double)ax/32767)*2, 8); Serial.print("\t");
    Serial.print(((double)ay/32767)*2, 8); Serial.print("\t");
    Serial.print(((double)az/32767)*2, 8); Serial.print("\t");
    Serial.print(((double)gx/32767)*250, 8); Serial.print("\t");
    Serial.print(((double)gy/32767)*250, 8); Serial.print("\t");
    Serial.println(((double)gz/32767)*250, 8);

    if (sdStatus()) {

		imuFile = SD.open("IMUData.txt", FILE_WRITE);

		imuFile.print(dataCounter);
		imuFile.print("\t");
		imuFile.print(((double)ax/32767)*2, 8);
		imuFile.print("\t");
		imuFile.print(((double)ay/32767)*2, 8);
		imuFile.print("\t");
		imuFile.print(((double)az/32767)*2, 8);
		imuFile.print("\t");
		imuFile.print(((double)gx/32767)*250, 8);
		imuFile.print("\t");
		imuFile.print(((double)gy/32767)*250, 8);
		imuFile.print("\t");
		imuFile.print(((double)gz/32767)*250, 8);
		imuFile.println("");
		imuFile.close();

		dataCounter++;
	}
}

// Output in Binary 
void IMU_SeniorProject::printBinary() {

	Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
    Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
    Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
    Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
    Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
    Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
		
	if (sdStatus()) {

		imuFile = SD.open("IMUData.txt", FILE_WRITE);

		imuFile.print(dataCounter);
		imuFile.print("\t");
		imuFile.print((uint8_t)(ax >> 8));
		imuFile.print((uint8_t)(ax & 0xFF));
		imuFile.print("\t");
		imuFile.print((uint8_t)(ay >> 8));
		imuFile.print((uint8_t)(ay & 0xFF));
		imuFile.print("\t");
		imuFile.print((uint8_t)(az >> 8));
		imuFile.print((uint8_t)(az & 0xFF));
		imuFile.print("\t");
		imuFile.print((uint8_t)(gx >> 8));
		imuFile.print((uint8_t)(gx & 0xFF));
		imuFile.print("\t");
		imuFile.print((uint8_t)(gy >> 8));
		imuFile.print((uint8_t)(gy & 0xFF));
		imuFile.print("\t");
		imuFile.print((uint8_t)(gz >> 8));
		imuFile.print((uint8_t)(gz & 0xFF));
		imuFile.println("");
		imuFile.close();

		dataCounter ++;
	}
}

/** Output of all values, and option to selects Decimal or
 *  Binary output and outputs to Serial and SD Card
 */
void IMU_SeniorProject::outputToFormat(int format) {

	_SDObject -> checkStatus();

	if (format == 1) {
		printBinary();
	}

	else {
		printDecimal();
	}
}