#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <sys/ioctl.h>

#define SLAVE_ADDR_01 0x68 //슬레이브 주소

static const char* I2C_DEV = "/dev/i2c-1"; //I2C 연결을 위한 장치 파일

int main(){
    int i2c_fd;

    if(wiringPiSetup() < 0 ){
        printf("wiringPiSetup() is failed\n");
        return 1;
    }

    i2c_fd = wiringPiI2CSetupInterface (I2C_DEV, SLAVE_ADDR_01); //i2C 연결 시도
    printf("I2C start....\n");
    int sec, min, hour, day, date, month, year;
    wiringPiI2CWriteReg8 (i2c_fd, 0x00, 0x13);
    wiringPiI2CWriteReg8 (i2c_fd, 0x01, 0x25);
    wiringPiI2CWriteReg8 (i2c_fd, 0x02, 0x13);
    wiringPiI2CWriteReg8 (i2c_fd, 0x03, 0x05);
    wiringPiI2CWriteReg8 (i2c_fd, 0x04, 0x19);
    wiringPiI2CWriteReg8 (i2c_fd, 0x05, 0x10);
    wiringPiI2CWriteReg8 (i2c_fd, 0x06, 0x20 | 0x23);
    while(1){
        system("clear");
        sec = wiringPiI2CReadReg8 (i2c_fd, 0x00);
        min = wiringPiI2CReadReg8 (i2c_fd, 0x01);
        hour = wiringPiI2CReadReg8 (i2c_fd, 0x02);
        day = wiringPiI2CReadReg8 (i2c_fd, 0x03);
        date = wiringPiI2CReadReg8 (i2c_fd, 0x04);
        month = wiringPiI2CReadReg8 (i2c_fd, 0x05);
        year = wiringPiI2CReadReg8 (i2c_fd, 0x06);
        printf("20%x년 %x월 %x일 ", year, month, date);
        switch (day){
            case 0x01:
                printf("월요일");
                break;
            case 0x02:
                printf("화요일");
                break;
            case 0x03:
                printf("수요일");
                break;
            case 0x04:
                printf("목요일");
                break;
            case 0x05:
                printf("금요일");
                break;
            case 0x06:
                printf("토요일");
                break;
            case 0x07:
                printf("일요일");
                break;
            
            default:
                break;
        }
        printf(" %x시 %x분 %x초\n", hour, min, sec);
        delay(1000);
    }

    return 0;
}