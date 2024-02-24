#include <MPU6050.h>
#include <helper_3dmath.h>
#include <I2Cdev.h>

// Modified version of (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include "Wire.h" // This library allows you to communicate with I2C devices.



const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data



void setup() {
	Serial.begin(9600);
	Wire.begin();
	Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
	Wire.write(0x6B); // PWR_MGMT_1 register
	Wire.write(0); // set to zero (wakes up the MPU-6050)
	Wire.endTransmission(true);
}
void loop() {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
	Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
	Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

	// "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
	accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
	accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
	accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
	temperature = Wire.read() << 8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
	gyro_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
	gyro_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
	gyro_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

	//TODO: Your code goes here
	float acc_x = accelerometer_x;
	float acc_y = accelerometer_y;
	float acc_z = accelerometer_z;
	float norm = sqrt(acc_x * acc_x + acc_y * acc_y + acc_z * acc_z);


	float x_angle = acos((float)accelerometer_x / norm) * (180 / M_PI);
	float y_angle = acos((float)accelerometer_y / norm) * (180 / M_PI);
	float z_angle = acos((float)accelerometer_z / norm) * (180 / M_PI);

	Serial.print(x_angle);
	Serial.print(",");
	y_angle = 400 + y_angle + x_angle;
	Serial.print(y_angle);
	Serial.print(",");
	z_angle = 400 + z_angle + y_angle;
	Serial.print(z_angle);
	Serial.print(",");
	// here we subtract 1600 from z_accelerometer
	acc_z = accelerometer_z - 1600;
	norm = sqrt(acc_x * acc_x + acc_y * acc_y + acc_z * acc_z);
	accelerometer_z = accelerometer_z - 1600;
	norm = map(norm, 0, 113510, 0, 360);
	norm = 400 + norm + z_angle;
	Serial.println(norm);

	delay(2);
}
