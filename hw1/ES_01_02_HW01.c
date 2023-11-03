#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

#define PWM0 18
#define SCH0 23
#define SCH1 24
//20180147 김민
//20180405 문지혁

void pwmControl(){
    int duty = 0;
    int range = 200;
    int divisor = 96;

    int flag0 = 1, flag1 = 0;

    pinMode(PWM0, PWM_OUTPUT);
    pinMode(SCH0, INPUT);
    pinMode(SCH1, INPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range);
    pwmSetClock(divisor);
    
    pwmWrite(PWM0, range);
    delay(1000);    

    while(1){
        if(!digitalRead(SCH0) && !digitalRead(SCH1) == TRUE){ //두 개의 스위치가 동시에 눌린 경우
            delay(2000);                    //2000ms 기다림
            if(!digitalRead(SCH0) && !digitalRead(SCH1) == TRUE){ //여전히 누르고 있을 경우
                duty = 200;                 
                pwmWrite(PWM0, duty);       //꺼짐
                printf("turn off! %d\n", duty);
            }
        }
        if(digitalRead(SCH0)) flag0 = 1;    //0번 스위치 미입력 상태
        if(digitalRead(SCH1)) flag1 = 1;    //1번 스위치 미입력 상태
        
        if (!digitalRead(SCH0) && flag0 == 1){
            flag0 = 0;                      //0번 스위치 입력 상태
            if(duty == 200) duty = 0;       //작을수록 밝음
            else duty += 50;
            printf("sch0 = %d, duty = %d\n", !digitalRead(SCH0), duty);
            pwmWrite(PWM0, duty);
        }
        
        if (!digitalRead(SCH1) && flag1 == 1){
            flag1 = 0;                      //1번 스위치 입력 상태
            if(duty == 0) duty = 200;       //클수록 어두움
            else duty -= 50;
            printf("sch1 = %d, duty = %d\n", !digitalRead(SCH1), duty);
            pwmWrite(PWM0, duty);
        }
        delay(50);                          //버튼 2개 동시 입력 대기
    }
}

int main(void){
    printf("Embedded Homework 01 PWM Led with Switch\n");
    wiringPiSetupGpio();
    pwmControl();
    return 0;
}