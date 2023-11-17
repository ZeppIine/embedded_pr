#include <wiringPi.h>
#include <stdio.h>
// Step GPIO
// IN1(12) ~ IN4(21)
int pin_arr[4] = {12, 16, 20, 21};
int one_two_phase[8][4] = {{1, 0, 0, 0},
                           {1, 1, 0, 0},
                           {0, 1, 0, 0},
                           {0, 1, 1, 0},
                           {0, 0, 1, 0},
                           {0, 0, 1, 1},
                           {0, 0, 0, 1},
                           {1, 0, 0, 1}};

int one_two_Phase_CW(int steps)
{
    for (int i = 0; i < steps; i++)
    {
        digitalWrite(pin_arr[0], one_two_phase[i % 8][0]);
        digitalWrite(pin_arr[1], one_two_phase[i % 8][1]);
        digitalWrite(pin_arr[2], one_two_phase[i % 8][2]);
        digitalWrite(pin_arr[3], one_two_phase[i % 8][3]);
        delay(5);
    }
    return 0;
}

int one_two_Phase_CCW(int steps)
{
    for (int i = steps; i > 0; i--)
    {
        digitalWrite(pin_arr[0], one_two_phase[i % 8][0]);
        digitalWrite(pin_arr[1], one_two_phase[i % 8][1]);
        digitalWrite(pin_arr[2], one_two_phase[i % 8][2]);
        digitalWrite(pin_arr[3], one_two_phase[i % 8][3]);
        delay(5);
    }
    return 0;
}

void init_Step()
{
    // 4
    for (int i = 0; i < 4; i++)
    {
        pinMode(pin_arr[i], OUTPUT);
    }
}
int main()
{
    printf("Stepping motor example\n");
    wiringPiSetupGpio(); /* wiringPi */
    init_Step();

    int dir;
    int steps;

    while (TRUE)
    {
        printf("Step Motor Example with wiringPi\n");
        scanf("%d %d", &steps, &dir);
        if (dir)
            one_two_Phase_CW(steps);
        else
            one_two_Phase_CCW(steps);
        printf("Motor end\n");
    }

    return 0;
}