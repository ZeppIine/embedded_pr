#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

#define PWM1 19
#define SCH0 20
#define SCH1 21
//20180147 김민
//20180405 문지혁

#define MAX_DEGREE 120
#define NEUTRAL_DEGREE 75
#define MIN_DEGREE 30

void pwmControl(){
    int range = 1000;
    int divisor = 384;
    int degree = NEUTRAL_DEGREE;

    int flag0 = 1, flag1 = 0;

    pinMode(PWM1, PWM_OUTPUT);
    pinMode(SCH0, INPUT);
    pinMode(SCH1, INPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range);
    pwmSetClock(divisor);
    
    pwmWrite(PWM1, NEUTRAL_DEGREE);
    delay(1000);    

    while(1){
        if(!digitalRead(SCH0) && !digitalRead(SCH1) == TRUE){ //두 개의 스위치가 동시에 눌릴 경우
            delay(2000);                    //2000ms 기다림
            if(!digitalRead(SCH0) && !digitalRead(SCH1) == TRUE){ //여전히 누르고 있을 경우
                degree = NEUTRAL_DEGREE;    
                pwmWrite(PWM1, degree);       //중앙 정렬
                delay(NEUTRAL_DEGREE);
                printf("NEUTRAL! degree = %d\n", degree);
            }
        }
        if(digitalRead(SCH0)) flag0 = 1;    //0번 스위치 미입력 상태
        if(digitalRead(SCH1)) flag1 = 1;    //1번 스위치 미입력 상태
        
        if (!digitalRead(SCH0) && flag0 == 1){
            flag0 = 0;                      //0번 스위치 입력 상태
            if(degree == MIN_DEGREE);       //최소 각도일 때 더이상 동작하지 않음
            else {
                degree -= 15;
                printf("sch0 = %d, degree = %d\n", !digitalRead(SCH0), degree);
                pwmWrite(PWM1, degree);
                delay(range * 30 / MAX_DEGREE);
            }
        }
        
        if (!digitalRead(SCH1) && flag1 == 1){
            flag1 = 0;                      //1번 스위치 입력 상태
            if(degree == MAX_DEGREE);       //최대 각도일 때 더이상 동작하지 않음
            else{
                degree += 15;
                printf("sch1 = %d, degree = %d\n", !digitalRead(SCH1), degree);
                pwmWrite(PWM1, degree);
                delay(range * 30 / MAX_DEGREE);
            }
        }
        delay(50);                          //버튼 2개 동시 입력 대기
    }
}

int main(void){
    printf("Embedded Homework 02 PWM Servo with Switch\n");
    wiringPiSetupGpio();
    pwmControl();
    return 0;
}