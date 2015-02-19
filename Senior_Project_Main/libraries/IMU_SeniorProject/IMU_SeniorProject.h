#ifndef IMU_SeniorProject_h
#define IMU_SeniorProject_h

#include "Arduino.h"
#include "MPU6050.h"
#include "SD_Manager_SeniorProject.h"

class IMU_SeniorProject {

public:

	IMU_SeniorProject(uint8_t address, SD_Manager_SeniorProject *ptrSDObject);
	
	void initializeIMU();
	void masterClock(int8_t clockSpeed);
	void verifyConnection();
	bool testIMUConnection();

	void takeMeasurements();

	int16_t getAX();
	int16_t getAY();
	int16_t getAZ();
	int16_t getGX();
	int16_t getGY();
	int16_t getGZ();

	bool sdStatus();

	void outputToFormat(int format);

	MPU6050 imu;

private:

	int16_t ax;
	int16_t ay;
	int16_t az;
	int16_t gx;
	int16_t gy;
	int16_t gz;

	int dataCounter;

	SD_Manager_SeniorProject *_SDObject;

	File imuFile;  

	int lastmil = 0;

	void printBinary();
	void printDecimal();
};
#endif

