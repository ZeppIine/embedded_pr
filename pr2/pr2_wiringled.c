#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

int ledControl(int gpio1, int gpio2, int gpio3, int ms){
    int i;
    pinMode(gpio1, OUTPUT); /* Pin */
    pinMode(gpio2, OUTPUT); /* Pin */
    pinMode(gpio3, OUTPUT); /* Pin */

    for (i = 0; i < 10; i++){
        digitalWrite(gpio1, LOW); /* HIGH(1) : LED */
        digitalWrite(gpio2, LOW); /* LOW(0) : LED */
        digitalWrite(gpio3, HIGH); /* LOW(0) : LED */
        delay(ms); /* 1 (1000 ) */

        digitalWrite(gpio2, LOW); /* HIGH(1) : LED */
        digitalWrite(gpio3, LOW); /* LOW(0) : LED */
        digitalWrite(gpio1, HIGH); /* LOW(0) : LED */
        delay(ms); /* 1 (1000 ) */

        digitalWrite(gpio3, LOW); /* HIGH(1) : LED */
        digitalWrite(gpio1, LOW); /* LOW(0) : LED */
        digitalWrite(gpio2, HIGH); /* LOW(0) : LED */
        delay(ms); /* 1 (1000 ) */
    }

    digitalWrite(gpio1, LOW); /* LOW(0) : LED */
    digitalWrite(gpio2, LOW); /* LOW(0) : LED */
    digitalWrite(gpio3, LOW); /* LOW(0) : LED */

    return 0;
}

int main(int argc, char **argv){
    int gno1, gno2, gno3, ms;
    if (argc < 5){
        printf("Usage : %s GPIO_NO\n", argv[0]);
        return -1;
    }

    gno1 = atoi(argv[1]);
    gno2 = atoi(argv[2]);
    gno3 = atoi(argv[3]);
    ms = atoi(argv[4]);
    wiringPiSetupGpio(); /* wiringPi */
    ledControl(gno1, gno2, gno3, ms);

    return 0;
}