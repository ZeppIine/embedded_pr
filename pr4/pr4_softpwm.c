#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */


void softpwmControl(int PWM0){
    int duty;

    pinMode(PWM0, OUTPUT);
    softPwmCreate(PWM0, 0, 100);
    softPwmWrite(PWM0, 100);
    delay(1000);   

    while(1){
        // scanf("%d", &duty);
        // softPwmWrite(PWM0, duty);
        for(duty = 100; duty >= 0; duty--){
            softPwmWrite(PWM0, duty);
            delay(10);
        }

        for(duty = 0; duty <= 100; duty++){
            softPwmWrite(PWM0, duty);
            delay(10);
        }
    }
}

int main(int argc, char **argv){
    int gno;
    if(argc < 2){
        printf("Usage : %s GPIO_NO\n", argv[0]);
        return -1;
    }
    gno = atoi(argv[1]);
    printf("PWM Example with wiringPi\n");
    wiringPiSetupGpio();
    softpwmControl(gno);
    return 0;
}