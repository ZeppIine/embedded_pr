#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

#define PWM0 18
#define PWM1 19

void motorControl(int speed, int dir)
{
    if (dir)
    {
        pwmWrite(PWM1, 0);
        pwmWrite(PWM0, speed);
    }
    else
    {
        pwmWrite(PWM0, 0);
        pwmWrite(PWM1, speed);
    }
}

int main(void)
{
    printf("DC Motor PWM Example with wiringPi\n");
    wiringPiSetupGpio();
    int speed = 0;
    int dir = 0;
    int range = 100;
    int divisor = 192;

    pinMode(PWM0, PWM_OUTPUT);
    pinMode(PWM1, PWM_OUTPUT);

    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range);
    pwmSetClock(divisor);
    pwmWrite(PWM1, 0);
    pwmWrite(PWM0, 0);
    while (1)
    {
        scanf("%d %d", &speed, &dir);
        motorControl(speed, dir);
    }
    return 0;
}