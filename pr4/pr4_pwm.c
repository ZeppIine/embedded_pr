#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

#define PWM0 18
#define PWM1 19

void pwmControl(){
    int duty = 0;
    int range = 200;
    int divisor = 96;

    pinMode(PWM0, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range);
    pwmSetClock(divisor);
    
    // pwmWrite(PWM0, range-1);
    // delay(1000);    

    while(1){
        scanf("%d", &duty);
        pwmWrite(PWM0, duty);
        // for(duty = range-1; duty > 0; duty--){
        //     pwmWrite(PWM0, duty);
        //     delay(2);
        // }

        // for(duty = 0; duty < range; duty++){
        //     pwmWrite(PWM0, duty);
        //     delay(2);
        // }
    }
}

int main(){
    printf("PWM Example with wiringPi\n");
    wiringPiSetupGpio();
    pwmControl();
    return 0;
}