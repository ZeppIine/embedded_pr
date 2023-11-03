#include <stdio.h>
#include <stdlib.h> /* atoi( ) */
#include <string.h>
#include <fcntl.h>
#include <unistd.h> /* close( ) */
#include <wiringPi.h>

void ledControlwithSwitch(int gpioOut, int gpioIn){
    pinMode(gpioOut, OUTPUT); /* Pin */
    pinMode(gpioIn, INPUT);
    while(1) digitalWrite(gpioOut, digitalRead(gpioIn));
}

int main(int argc, char **argv){
    int led, swch;
    if (argc < 3){
        printf("Usage : %s GPIO_NO\n", argv[0]);
        return -1;
    }

    led = atoi(argv[1]);
    swch = atoi(argv[2]);
    wiringPiSetupGpio(); /* wiringPi */
    ledControlwithSwitch(led, swch);
    return 0;
}
