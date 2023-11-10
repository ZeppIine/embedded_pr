#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>
#include <stdlib.h> //atoi

#define TOTAL_NOTES 32

#define DO 262
#define RE 294
#define MI 330
#define PA 350
#define SOL 392
#define RA 440
#define SI 494

int notes[TOTAL_NOTES] = {
    SOL, SOL, SOL, SOL, RE, RE, SOL, SOL,
    PA, PA, MI, RE, MI, MI, DO, DO,
    SOL, SOL, SOL, SOL, RE, RE, SOL, SOL,
    PA, PA, MI, RE, MI, MI, DO, DO};

void musicPlay(int gpio)
{
    int i;
    softToneCreate(gpio);

    for (i = 0; i < TOTAL_NOTES; i++)
    {
        softToneWrite(gpio, notes[i]); //
        delay(250);                    //
    }
}

int main(int argc, char **argv)
{
    int gno;
    if (argc < 2)
    {
        printf("Usage : %s Enter the duty\n", argv[0]);
        return -1;
    }
    wiringPiSetupGpio();
    gno = atoi(argv[1]);
    musicPlay(gno);

    return 0;
}
