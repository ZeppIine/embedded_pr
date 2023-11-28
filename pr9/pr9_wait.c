#include <stdio.h>
#include <unistd.h> //fork() 함수를 사용하기 위한 헤더 파일
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{
    int status; // 상태 저장 변수
    pid_t pid;  // process id 를 저장하기 위한 변수
    pid_t r_pid;
    if ((pid = fork()) < 0)
    { // fork( ) 함수의 에러 시 처리
        perror("fork() error");
    }
    else if (pid == 0)
    {                                                           // 자식 프로세스에 대한 처리
        execl("/home/pi/Desktop/code/pr8/pr8_acdc", (char *)0); //(char*) 0는 NULL 포인터
        printf("exec() error!!\n");                             // 이 코드가 실행될 경우 execl() 함수에서 에러 발생
    }
    else
    { // 부모 프로세스에 대한 처리
        printf("Parent pid: %d, Child pid: %d\n", getpid(), pid);
        if ((r_pid = waitpid(pid, &status, 0)) < 0)
        { // 자식 프로세스의 종료 대기
            printf("waitpid() error\n");
        }
        printf("Child pid: %d, status: %d\n", r_pid, status);
    }
    return 0;
}