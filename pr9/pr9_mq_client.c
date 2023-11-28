#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mqueue.h>
int main(int argc, char **argv)
{
    mqd_t mq;
    const char *name = "/posix_mq";
    char buf[BUFSIZ];
    mq = mq_open(name, O_WRONLY);     // 읽기 모드로 메시지 큐 오픈
    sprintf(buf, "Hello, World!\n");  //"Hello, World!"라는 문자열 생성
    mq_send(mq, buf, strlen(buf), 0); // 생성한 문자열을 메시지 큐로 송신
    while (1)
    {
        scanf("%s", buf);
        mq_send(mq, buf, strlen(buf), 0); // 생성한 문자열을 메시지 큐로 송신
        if (buf[0] == 'q')
            break;
        printf("client: %s\n", buf);
    }
    mq_close(mq); // 메시지 큐를 닫는다.
    return 0;
}