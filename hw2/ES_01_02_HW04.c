#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define LED 14                              // gpio 14, 15, 18번을 led, trig, echo로 정의
#define TRIG 15                             //
#define ECHO 18                             //

int main()
{
    wiringPiSetupGpio();                    // gpio 셋
    pinMode(LED, OUTPUT);                   // led핀과 trig핀을 출력으로 설정
    pinMode(TRIG, OUTPUT);                  //
    pinMode(ECHO, INPUT);                   // echo핀을 출력으로 설정

    int dist;                               // 거리 기록용 변수 선언
    long first, second;                     // 거리 측정용 변수 선언

    digitalWrite(TRIG, LOW);                // 기본 상태 LOW로 설정

    while(1)
    {
        digitalWrite(TRIG, HIGH);           // 상태를 HIGH로 설정
        delayMicroseconds(20);              // 20ms간 측정
        digitalWrite(TRIG, LOW);            // 상태를 LOW로 설정

        while(digitalRead(ECHO) == LOW);    // echo가 low상태일때 고정, 해제 시에 first에 기록
        first = micros();                   // 
        while(digitalRead(ECHO) == HIGH);   // echo가 high상태일떄 고정, 해제 시에 second에 기록
        second = micros() - first;          // second에 기록시 first의 기록값 만큼 제외함

        dist = second / 58 * 10;            // 반향 시간을 거리로 변환

        printf("dist = %d\n", dist);

        if(dist >= 20 && dist <= 100)       // 거리가 20 이상 100 이하일 때
        {
            digitalWrite(LED, LOW);
            delay(100);                     // 1초에 10번 점멸 
            digitalWrite(LED, HIGH);
        }
        else if(dist > 100 && dist <= 300)  // 거리가 100 초과 300 이하일 때
        {
            digitalWrite(LED, LOW);
            delay(200);                     // 1초에 5번 점멸 
            digitalWrite(LED, HIGH);
        }
        else                                // 그 이상 거리일 때
        {
            digitalWrite(LED, LOW);
            delay(1000);                    // 1초에 1번 점멸 
            digitalWrite(LED, HIGH);
        }

        delay(200);                         // 1초에 5번 수행
    }

    return 0;
}