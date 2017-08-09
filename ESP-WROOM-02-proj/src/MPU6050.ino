#include <Wire.h>
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

double AccelX;
double AccelY;
double AccelZ;
double GyroX;
double GyroY;
double GyroZ;

double BaseAccelX;
double BaseAccelY;
double BaseAccelZ;

void initializeMPU6050(){
  Wire.begin();
  writeMPU6050(PWR_MGMT_1, 0);
  delay(1000);
  caribration();
}

void caribration(){
  int i;
  BaseAccelX = 0.0;
  BaseAccelY = 0.0;
  BaseAccelZ = 0.0;
  for(i = 0; i < 20; i++){
    readSensorData();
    BaseAccelX += AccelX;
    BaseAccelY += AccelY;
    BaseAccelZ += AccelZ;
    delay(100);
  }
  BaseAccelX /= 20.0;
  BaseAccelY /= 20.0;
  BaseAccelZ /= 20.0;
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
  if (ret >= 0x8000) {
    ret = -((65535 - ret) + 1);
  }
  return ret;
}

void readSensorData() {
  AccelX = readWordMPU6050(ACCEL_XOUT) / 16384.0;
  AccelY = readWordMPU6050(ACCEL_YOUT) / 16384.0;
  AccelZ = readWordMPU6050(ACCEL_ZOUT) / 16384.0;
  GyroX = readWordMPU6050(GYRO_XOUT) / 131.0;
  GyroY = readWordMPU6050(GYRO_YOUT) / 131.0;
  GyroZ = readWordMPU6050(GYRO_ZOUT) / 131.0;
}

void printSensorData() {
  Serial.println("--------------");
  Serial.print("Accel X:" + String(AccelX));
  Serial.print(" Y:" + String(AccelY));
  Serial.println(" Z:" + String(AccelZ));
  Serial.print("Gyro X:" + String(GyroX));
  Serial.print(" Y:" + String(GyroY));
  Serial.println(" Z:" + String(GyroZ));
  Serial.println("-----END-----");
}

void sendSensorDataForMovingMouse() {
  Serial.println("Accel:" + String(AccelX - BaseAccelX) + ":" + String(AccelY - BaseAccelY) + ":dummy");
}

bool decideLED() {
    if (AccelX > 0.5 ){
        return true;
    }
    return false;
}