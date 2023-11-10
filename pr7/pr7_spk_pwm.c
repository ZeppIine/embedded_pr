#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

#define PWM0 18

#define DO 262
#define RE 294
#define MI 330

void initMyTone(int gpio, int freq)
{
    int duty = 0;
    int range = 200;
    int divisor = 96;

    pinMode(gpio, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range);
    pwmSetClock(divisor);
    pwmWrite(PWM0, duty);
}

void myTone(int gpio, int freq)
{
    int duty = 50;
    int divisor = 96000 / freq;
    pwmSetClock(divisor);
    pwmWrite(PWM0, duty);
}

int main(void)
{
    printf("Speaker PWM Example with wiringPi\n");
    wiringPiSetupGpio();
    initMyTone(PWM0, 0);
    int freq = 0;
    while (1)
    {
        scanf("%d", &freq);
        myTone(PWM0, freq);
    }
    return 0;
}