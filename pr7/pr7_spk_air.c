#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

#define PWM0 18

#define TOTAL_NOTES 64

#define U_PA 174
#define U_SOL 196
#define U_RA 220
#define U_SI 246
#define DO 262
#define RE 294
#define MI 330
#define PA 350
#define SOL 392
#define RA 440
#define SI 494

int notes[TOTAL_NOTES] = {
    SOL, SOL, SOL, SOL, RE, RE, SOL, SOL,
    PA, PA, MI, RE, MI, MI, RE, DO,
    SOL, SOL, SOL, SOL, RE, RE, SOL, SOL,
    PA, PA, MI, RE, MI, MI, RE, DO,
    SOL, SOL, SOL, SOL, RE, RE, SOL, SOL,
    PA, PA, MI, RE, MI, MI, RE, DO,
    U_SI, DO, RE, RE, DO, DO, U_SI, U_RA,
    U_SOL, U_SOL, U_SOL, U_SOL, U_SOL, U_SOL, U_SOL, U_SOL};

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
        delay(100);
    }
    initMyTone(PWM0, 0);

    return 0;
}