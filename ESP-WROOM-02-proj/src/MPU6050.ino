#include <Wire.h>
#include <math.h>
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

float angleX, angleY, angleZ;

double RawAccelX;
double RawAccelY;
double RawAccelZ;
double RawGyroX;
double RawGyroY;
double RawGyroZ;

double CalcAccelX;
double CalcAccelY;
double CalcAccelZ;
double CalcGyroX;
double CalcGyroY;
double CalcGyroZ;

double BaseAccelX;
double BaseAccelY;
double BaseAccelZ;
double BaseGyroX;
double BaseGyroY;
double BaseGyroZ;

void initializeMPU6050(){
  Wire.begin();
  writeMPU6050(PWR_MGMT_1, 0);
  delay(1000);
  caribrationMPU6050();
}

void caribrationMPU6050(){
  int i;
  BaseAccelX = 0.0;
  BaseAccelY = 0.0;
  BaseAccelZ = 0.0;
  for(i = 0; i < 3000; i++){
    readSensorData();
    BaseAccelX += RawAccelX;
    BaseAccelY += RawAccelY;
    BaseAccelZ += RawAccelZ;
    BaseGyroX += RawGyroX;
    BaseGyroY += RawGyroY;
    BaseGyroZ += RawGyroZ;
    delay(1);
  }
  BaseAccelX /= 3000.0;
  BaseAccelY /= 3000.0;
  BaseAccelZ /= 3000.0;
  BaseGyroX /= 3000.0;
  BaseGyroY /= 3000.0;
  BaseGyroZ /= 3000.0;
}

void writeMPU6050(byte addr, byte data) {
  Wire.beginTransmission(DEVICE_ADDR);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission(true);
}

byte readByteMPU6050(byte addr) {
  Wire.beginTransmission(DEVICE_ADDR);
  Wire.write(addr);
  Wire.endTransmission(true);
  Wire.requestFrom(DEVICE_ADDR, 1);
  return Wire.read();
}

int16_t readWordMPU6050(byte addr) {
  int8_t high;
  int8_t low;
  int16_t ret;
  high = readByteMPU6050(addr);
  low = readByteMPU6050(low);
  ret = (high << 8) + low;
  // if (ret >= 0x8000) {
  //   ret = -((65535 - ret) + 1);
  // }
  return ret;
}

void readSensorData() {
  RawAccelX = readWordMPU6050(ACCEL_XOUT) / 16384.0;
  RawAccelY = readWordMPU6050(ACCEL_YOUT) / 16384.0;
  RawAccelZ = readWordMPU6050(ACCEL_ZOUT) / 16384.0;
  RawGyroX = readWordMPU6050(GYRO_XOUT) / 131.0;
  RawGyroY = readWordMPU6050(GYRO_YOUT) / 131.0;
  RawGyroZ = readWordMPU6050(GYRO_ZOUT) / 131.0;
}

void printRawSensorData() {
  Serial.println("--------------");
  Serial.print("Raw Accel X:" + String(RawAccelX));
  Serial.print(" Y:" + String(RawAccelY));
  Serial.println(" Z:" + String(RawAccelZ));
  Serial.print("Raw Gyro X:" + String(RawGyroX));
  Serial.print(" Y:" + String(RawGyroY));
  Serial.println(" Z:" + String(RawGyroZ));
  Serial.println("-----END-----");
}

void printCalcSensorData() {
  Serial.println("--------------");
  Serial.print("Calc Accel X:" + String(CalcAccelX));
  Serial.print(" Y:" + String(CalcAccelY));
  Serial.println(" Z:" + String(CalcAccelZ));
  Serial.print("Calc Gyro X:" + String(CalcGyroX));
  Serial.print(" Y:" + String(CalcGyroY));
  Serial.println(" Z:" + String(CalcGyroZ));
  Serial.println("-----END-----");
}

void printAngle() {
  Serial.print("Angle X:" + String(angleX));
  Serial.print(" Y:" + String(angleY));
  Serial.println(" Z:" + String(angleZ));
}

String stringAngle() {
  String ret;
  ret = "X:" + String(angleX) + "\nY:" + String(angleY) + "\nZ:" + String(angleZ);
  return ret;
}

void sendSensorDataForMovingMouse() {
  // Serial.println("Accel:" + String(AccelX - BaseAccelX) + ":" + String(AccelY - BaseAccelY) + ":dummy");
}

float acc_x, acc_y, acc_z, acc_angle_x, acc_angle_y, acc_angle_z;
float preInterval, interval;
double gyro_angle_x = 0, gyro_angle_y = 0, gyro_angle_z = 0;
void calcRotation() {
  float acc_angle_x, acc_angle_y;
  CalcAccelX = RawAccelX - BaseAccelX;
  CalcAccelY = RawAccelY - BaseAccelY;
  CalcAccelZ = RawAccelZ - BaseAccelZ;
  CalcGyroX = RawGyroX - BaseGyroX;
  CalcGyroY = RawGyroY - BaseGyroY;
  CalcGyroZ = RawGyroZ - BaseGyroZ;
  
  acc_angle_x = atan2(RawAccelX, RawAccelZ + abs(RawAccelY)) * 360.0 / 2.0 / PI;
  acc_angle_y = atan2(RawAccelY, RawAccelZ + abs(RawAccelX)) * 360.0 / 2.0  / PI;
  acc_angle_z = atan2(RawAccelZ, abs(RawAccelY) + abs(RawAccelX)) * 360.0 / 2.0  / PI;

  interval = millis() - preInterval;
  preInterval = millis();

  gyro_angle_x += CalcGyroX * (interval * 0.001);
  gyro_angle_y += CalcGyroY * (interval * 0.001);
  gyro_angle_z += CalcGyroZ * (interval * 0.001);

  // filter
  angleX = (0.2 * gyro_angle_x) + (0.8 * acc_angle_x);
  angleY = (0.2 * gyro_angle_y) + (0.8 * acc_angle_y);
  angleZ = (0.2 * gyro_angle_z) + (0.8 * acc_angle_z);

  gyro_angle_x = angleX;
  gyro_angle_y = angleY;
  gyro_angle_z = angleZ;
}

bool decideLED() {
    if (RawAccelX > 0.5 ){
        return true;
    }
    return false;
}