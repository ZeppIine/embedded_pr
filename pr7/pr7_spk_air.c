#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

#define PWM0 18

#define TOTAL_NOTES 32

#define DO 262
#define RE 294
#define MI 330

int notes[TOTAL_NOTES] = {
    MI, RE, DO, RE, MI, MI, MI, MI,
    RE, RE, RE, RE, MI, MI, MI, MI,
    MI, RE, DO, RE, MI, MI, MI, MI,
    RE, RE, MI, RE, DO, DO, DO, DO};

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
    for (int i = 0; i < TOTAL_NOTES; i++)
    {
        myTone(PWM0, notes[i]);
        delay(200);
    }
    initMyTone(PWM0, 0);

    return 0;
}