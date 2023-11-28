#include <stdio.h>
#include <unistd.h>
#include <mqueue.h>
#include <string.h>
int main(int argc, char **argv)
{
    mqd_t mq;
    struct mq_attr attr;
    const char *name = "/posix_mq"; // 메시지 큐끼리 공유할 이름
    char buf[BUFSIZ];               // 메시지를 저장할 공간
    int n;                          // 읽은 메시지의 길이
    int bQuit = 0;                  // 종료 여부를 저장할 변수
    // 메시지 큐 속성의 초기화
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = BUFSIZ;
    attr.mq_curmsgs = 0;
    mq = mq_open(name, O_CREAT | O_RDONLY, 0644, &attr);
    while (!bQuit)
    {
        n = mq_receive(mq, buf, sizeof(buf), NULL); // 메시지 큐에서 데이터를 읽음
        switch (buf[0])
        {
        case 'q': // 메시지가 'q' 이면 while 문 종료
            bQuit = 1;
            break;
        default: // 다른 메시지이면 화면에 가져온 데이터를 출력
            printf("Server: %s\n", buf);
            break;
        }
        memset(buf, 0, sizeof(buf)); // buf 초기화
    }
    // 메시지 큐를 닫은 후 정리하고 프로그램을 종료
    mq_close(mq);
    mq_unlink(name);
    return 0;
}