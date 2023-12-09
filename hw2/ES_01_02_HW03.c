#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define CLK 20                              // gpio 20, 21번을 clk, dt로 정의
#define DT 21                               //

int main(){

    int clkState, clkLastState, dtState;    // 상태 변수 선언

    wiringPiSetupGpio();                    // gpio 셋

    pinMode(CLK, INPUT);                    // clk핀과 dt핀을 입력으로 설정
    pinMode(DT, INPUT);                     //

    clkLastState = digitalRead(CLK);        // clk값 저장 후 초기/이전상태로 설정
    int cnt = 0;                            // 카운트 변수 선언 및 0으로 초기화
    
    printf("cnt = %d\n", cnt);

    while(1) {
        clkState = digitalRead(CLK);        // clk와 dt의 현재상태 설정
        dtState = digitalRead(DT);          // 

        if (clkState != clkLastState && clkState == 1) {        // clk가 초기상태와 다르고 clk의 값이 1일 때에
            
            if (dtState != clkState) {      // dt와 clk가 다를 때에 cnt 변경
                cnt++;
            }
            else {
                cnt--;
            }

            printf("cnt = %d\n", cnt);
        }
        
        clkLastState = clkState;            // clk의 현재상태를 초기상태로 저장

        delay(1);
    }
    return 0;
}