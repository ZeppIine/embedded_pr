#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CS_GPIO 8 //CS
#define SPI_CH 0
#define SPI_SPEED 1000000 // 1MHz
#define SPI_MODE 3

#define BW_RATE 0x2C //
#define POWER_CTL 0x2D //Power Control Register

#define DATA_FORMAT 0x31
#define DATAX0 0x32 //X-Axis Data 0
#define DATAX1 0x33 //X-Axis Data 1
#define DATAY0 0x34 //Y-Axis Data 0
#define DATAY1 0x35 //Y-Axis Data 1
#define DATAZ0 0x36 //Z-Axis Data 0
#define DATAZ1 0x37 //Z-Axis Data 1

//ADXL345
void readRegister_ADXL345(char registerAddress, int numBytes, char * values){
    //read 1 .
    values[0] = 0x80 | registerAddress;
    // 6 1
    if(numBytes > 1) values[0] = values[0] | 0x40;
    digitalWrite(CS_GPIO, LOW); // Low : CS Active
    // values
    wiringPiSPIDataRW(SPI_CH, values, numBytes + 1);
    digitalWrite(CS_GPIO, HIGH); // High : CS Inactive
}

//ADXL345
void writeRegister_ADXL345(char address, char value){
    unsigned char buff[2];
    buff[0] = address;
    buff[1] = value;
    digitalWrite(CS_GPIO, LOW); // Low : CS Active
    wiringPiSPIDataRW(SPI_CH, buff, 2);
    digitalWrite(CS_GPIO, HIGH); // High : CS Inactive
}

int main (void){
    unsigned char buffer[100];
    short x= 0, y= 0 , z= 0;
    double dx, dy, dz;
    double roll, pitch;
    if(wiringPiSetupGpio() == -1) return 1;
    if(wiringPiSPISetupMode(SPI_CH, SPI_SPEED,SPI_MODE) == -1) return 1;

    pinMode(CS_GPIO, OUTPUT); //Chip Select OUTPUT
    digitalWrite(CS_GPIO, HIGH); //IDLE

    writeRegister_ADXL345(DATA_FORMAT,0x01|0x08); // +- 4G
    writeRegister_ADXL345(BW_RATE,0x0C); //Output Data Rate 400 Hz
    writeRegister_ADXL345(POWER_CTL,0x08); //

    while(1){
        readRegister_ADXL345(DATAX0,6,buffer); //
        x = ((short)buffer[2]<<8)|(short)buffer[1]; //X
        y = ((short)buffer[4]<<8)|(short)buffer[3]; //Y
        z = ((short)buffer[6]<<8)|(short)buffer[5]; //Z
        dx = x*0.0039;
        dy = y*0.0039;
        dz = z*0.0039;
        roll = atan(-dy / sqrt(pow(dz, 2) + pow(dx, 2))) * 180 / M_PI;
        pitch = atan(-dx / sqrt(pow(dz, 2) + pow(dy, 2))) * 180 / M_PI;
        printf("X: %7.2f, Y: %7.2f, Z: %7.2f, Roll: %7.2f, Pitch: %7.2f\n", dx, dy, dz, roll, pitch); //X, Y, Z
        delay(20);
    }
    
    return 0;
}