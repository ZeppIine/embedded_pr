#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiSPI.h>

#define BAUD_RATE 115200

#define CS_GPIO 8 // CS
#define SPI_CH 0
#define SPI_SPEED 1000000 // 1MHz
#define SPI_MODE 3

#define BW_RATE 0x2C   //
#define POWER_CTL 0x2D // Power Control Register

#define DATA_FORMAT 0x31
#define DATAX0 0x32 // X-Axis Data 0
#define DATAX1 0x33 // X-Axis Data 1
#define DATAY0 0x34 // Y-Axis Data 0
#define DATAY1 0x35 // Y-Axis Data 1
#define DATAZ0 0x36 // Z-Axis Data 0
#define DATAZ1 0x37 // Z-Axis Data 1

// ADXL345
void readRegister_ADXL345(char registerAddress, int numBytes, char *values)
{
    // read 1 .
    values[0] = 0x80 | registerAddress;
    // 6 1
    if (numBytes > 1)
        values[0] = values[0] | 0x40;
    digitalWrite(CS_GPIO, LOW); // Low : CS Active
    // values
    wiringPiSPIDataRW(SPI_CH, values, numBytes + 1);
    digitalWrite(CS_GPIO, HIGH); // High : CS Inactive
}

// ADXL345
void writeRegister_ADXL345(char address, char value)
{
    unsigned char buff[2];
    buff[0] = address;
    buff[1] = value;
    digitalWrite(CS_GPIO, LOW); // Low : CS Active
    wiringPiSPIDataRW(SPI_CH, buff, 2);
    digitalWrite(CS_GPIO, HIGH); // High : CS Inactive
}

static const char *UART2_DEV = "/dev/ttyAMA1"; // UART2 연결을 위한 장치 파일

unsigned char serialRead(const int fd);                // 1Byte 데이터를 수신하는 함수
void serialWrite(const int fd, const unsigned char c); // 1Byte 데이터를 송신하는 함수
// 1Byte 데이터를 수신하는 함수
unsigned char serialRead(const int fd)
{
    unsigned char x;
    if (read(fd, &x, 1) != 1) // read 함수를 통해 1바이트 읽어옴
        return -1;
    return x; // 읽어온 데이터 반환
}

// 1Byte 데이터를 송신하는 함수
void serialWrite(const int fd, const unsigned char c)
{
    write(fd, &c, 1); // write 함수를 통해 1바이트 씀
}

int main()
{
    int fd_serial;     // UART2 파일 서술자
    unsigned char dat; // 데이터 임시 저장 변수
    if (wiringPiSetup() < 0)
        return 1;
    if ((fd_serial = serialOpen(UART2_DEV, BAUD_RATE)) < 0)
    { // UART2 포트 오픈
        printf("Unable to open serial device.\n");
        return 1;
    }

    unsigned char buffer[100];
    short x = 0, y = 0, z = 0;
    double dx, dy, dz;
    double roll, pitch;
    if (wiringPiSetupGpio() == -1)
        return 1;
    if (wiringPiSPISetupMode(SPI_CH, SPI_SPEED, SPI_MODE) == -1)
        return 1;

    pinMode(CS_GPIO, OUTPUT);    // Chip Select OUTPUT
    digitalWrite(CS_GPIO, HIGH); // IDLE

    writeRegister_ADXL345(DATA_FORMAT, 0x01 | 0x08); // +- 4G
    writeRegister_ADXL345(BW_RATE, 0x0C);            // Output Data Rate 400 Hz
    writeRegister_ADXL345(POWER_CTL, 0x08);          //

    while (1)
    {
        readRegister_ADXL345(DATAX0, 6, buffer);        //
        x = ((short)buffer[2] << 8) | (short)buffer[1]; // X
        y = ((short)buffer[4] << 8) | (short)buffer[3]; // Y
        z = ((short)buffer[6] << 8) | (short)buffer[5]; // Z
        dx = x * 0.0039;
        dy = y * 0.0039;
        dz = z * 0.0039;
        roll = atan(-dy / sqrt(pow(dz, 2) + pow(dx, 2))) * 180 / M_PI;
        pitch = atan(-dx / sqrt(pow(dz, 2) + pow(dy, 2))) * 180 / M_PI;
        printf("X: %7.2f, Y: %7.2f, Z: %7.2f, Roll: %7.2f, Pitch: %7.2f\n", dx, dy, dz, roll, pitch); // X, Y, Z
        fflush(stdout);
        serialWrite(fd_serial, roll); // 입력 받은 데이터를 다시 보냄 (Echo)
        serialWrite(fd_serial, pitch);
        delay(20);
    }
}