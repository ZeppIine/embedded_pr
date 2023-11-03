#include <stdio.h>
#include <stdlib.h> /* atoi( ) */
#include <string.h>
#include <fcntl.h>
#include <unistd.h> /* close( ) */
int ledControl(int gpio){
    int fd;
    char buf[BUFSIZ]; //512
    
    fd = open("/sys/class/gpio/export", O_WRONLY); /* 해당 GPIO 디바이스 사용 준비 */
    sprintf(buf, "%d", gpio);
    write(fd, buf, strlen(buf));
    
    close(fd);
    sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio); /* 해당 GPIO 디바이스의 방향 설정 */
    fd = open(buf, O_WRONLY);
    write(fd, "out", 4);
    close(fd);
    
    sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio); /* 디바이스에 '1'값 출력 */
    fd = open(buf, O_WRONLY);
    write(fd, "1", 2);
    close(fd);
    
    getchar(); /* LED 확인을 위한 대기 */

    sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio); /* 디바이스에 '0'값 출력 */
    fd = open(buf, O_WRONLY);
    write(fd, "0", 2);
    close(fd);
    
    fd = open("/sys/class/gpio/unexport", O_WRONLY); /* 사용한 GPIO 디바이스 해제하기 */
    sprintf(buf, "%d", gpio);
    write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}

int main(int argc, char **argv){
    int gno;
    if (argc < 2){
        printf("Usage : %s GPIO_NO\n", argv[0]);
        return -1;
    }

    gno = atoi(argv[1]);
    ledControl(gno);
    return 0;
}