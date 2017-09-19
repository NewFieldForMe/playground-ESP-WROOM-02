#ifndef __MPU6050__
#define __MPU6050__

#include <Wire.h>
#include <math.h>
#include <Arduino.h>
#define DEVICE_ADDR 0x68  // Device Address
#define ACCEL_XOUT  0x3b
#define ACCEL_YOUT  0x3d
#define ACCEL_ZOUT  0x3f
#define GYRO_XOUT   0x43
#define GYRO_YOUT   0x45
#define GYRO_ZOUT   0x47
#define PWR_MGMT_1  0x6b
#define PWR_MGMT_2  0x6c
#define WHO_AM_I    0x75

#define MPU6050_SMPLRT_DIV   0x19 // MPU-6050 register address
#define MPU6050_CONFIG       0x1a
#define MPU6050_GYRO_CONFIG  0x1b
#define MPU6050_ACCEL_CONFIG 0x1c


class MPU6050 {
public:
  MPU6050();
  void setup();
  void loop();
  void printRawSensorData();
  void printCalcSensorData();
  void printAngle();
  String stringAngle();
  void calcRotation();
  bool decideLED();
private:
  void caribrationMPU6050();
  void writeMPU6050(byte addr, byte data);
  byte readByteMPU6050(byte addr);
  int16_t readWordMPU6050(byte addr);
  void readSensorData();

  // private variables 
  float angleX, angleY, angleZ;

  double RawAccelX, RawAccelY, RawAccelZ;
  double RawGyroX, RawGyroY, RawGyroZ;

  double CalcAccelX, CalcAccelY, CalcAccelZ;
  double CalcGyroX, CalcGyroY, CalcGyroZ;

  double BaseAccelX, BaseAccelY, BaseAccelZ;
  double BaseGyroX, BaseGyroY, BaseGyroZ;

  float acc_x, acc_y, acc_z, acc_angle_x, acc_angle_y, acc_angle_z;
  float preInterval, interval;
  double gyro_angle_x = 0, gyro_angle_y = 0, gyro_angle_z = 0;
};

#endif