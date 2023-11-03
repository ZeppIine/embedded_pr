#include <stdio.h>
#include <stdlib.h> /* atoi( ) */
#include <string.h>
#include <fcntl.h>
#include <unistd.h> /* close( ) */

void ledControlwithSwitch(int gpioOut, int gpioIn){
    initGPIO(gpioOut, 0);
    initGPIO(gpioIn, 1);
    while(1) digitalWrite(gpioOut, !digitalRead(gpioIn));
    unexportGPIO(gpioOut);
    unexportGPIO(gpioIn);
}

void initGPIO(int gno, int dir){
    int fd;
    char buf[BUFSIZ]; //512

    fd = open("/sys/class/gpio/export", O_WRONLY); /* 해당 GPIO 디바이스 사용 준비 */
    sprintf(buf, "%d", gno);
    write(fd, buf, strlen(buf));
    close(fd);

    sprintf(buf, "/sys/class/gpio/gpio%d/direction", gno); /* 해당 GPIO 디바이스의 방향 설정 */
    fd = open(buf, O_WRONLY);
    if(dir == 0) write(fd, "out", 4);
    else write(fd, "in", 3);
    close(fd);
}

void unexportGPIO(int gno){
    int fd;
    char buf[BUFSIZ]; //512

    fd = open("/sys/class/gpio/unexport", O_WRONLY); /* 사용한 GPIO 디바이스 해제하기 */
    sprintf(buf, "%d", gno);
    write(fd, buf, strlen(buf));
    close(fd);
}

void digitalWrite(int gno, int value){
    int fd;
    char buf[BUFSIZ]; //512
    sprintf(buf, "/sys/class/gpio/gpio%d/value", gno); /* 디바이스에 '1'값 출력 */
    fd = open(buf, O_WRONLY);
    if(value == 0) write(fd, "0", 2);
    else write(fd, "1", 2);
    close(fd);
}

int digitalRead(int gno){
    int fd;
    char buf[BUFSIZ]; //512
    char value;

    sprintf(buf, "/sys/class/gpio/gpio%d/value", gno); /* 디바이스에 '1'값 출력 */
    fd = open(buf, O_RDONLY);
    read(fd, &value, 1);
    // printf("%d", value);
    if(value == '1'){
        close(fd);
        return 1;
    }
    else{
        close(fd);
        return 0;
    }
}

int main(int argc, char **argv){
    int led, swch;
    if (argc < 3){
        printf("Usage : %s GPIO_NO\n", argv[0]);
        return -1;
    }

    led = atoi(argv[1]);
    swch = atoi(argv[2]);
    ledControlwithSwitch(led, swch);
    return 0;
}