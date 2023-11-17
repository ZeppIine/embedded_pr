#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define SLAVE_ADDR_01 0x48                 //
static const char *I2C_DEV = "/dev/i2c-1"; // I2C
int main()
{
    int i2c_fd;                    // i2c
    int cnt = 0;                   //
    int preVal = 0;                //
    int curVal = 0;                //
    int threshold = 150;           //
    int adcChannel[3] = {0, 1, 3}; //
    // wiringPi
    if (wiringPiSetupGpio() < 0)
    {
        printf("wiringPiSetup() is failed\n");
        return 1;
    }
    // i2C
    if ((i2c_fd = wiringPiI2CSetupInterface(I2C_DEV, SLAVE_ADDR_01)) < 0)
    {
        printf("wiringPi2CSetup Failed: \n");
        return 1;
    }
    printf("I2C start....\n");
    while (1)
    {
        // Analog Input Programming: 00 (4 single ended inputs),
        // A/D Channel Number: 00(AIN0 )
        for (int i = 0; i < 3; i++)
        {
            wiringPiI2CWrite(i2c_fd, 0x40 | adcChannel[i]);
            curVal = wiringPiI2CRead(i2c_fd);               // ADC
            printf("[%d] Current value = %d", cnt, curVal); //
            //     // threshold , Bright
            //     if (curVal < threshold)
            //         printf("Bright!\n");
            //     else
            //         printf("Dark!\n");
            printf("\n");
        }
        printf("\n");
        delay(500);
        cnt++;
    }
    return 0;
}