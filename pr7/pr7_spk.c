#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>
#include <stdlib.h> //atoi

#define TOTAL_NOTES 32

#define DO 262
#define RE 294
#define MI 330

int notes[TOTAL_NOTES] = {
    MI, RE, DO, RE, MI, MI, MI, MI,
    RE, RE, RE, RE, MI, MI, MI, MI,
    MI, RE, DO, RE, MI, MI, MI, MI,
    RE, RE, MI, RE, DO, DO, DO, DO};

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
