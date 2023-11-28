#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int share_var = 15;
pthread_mutex_t mid;        // 뮤텍스 오브젝트
void *producerFunc(void *); // 생산자 쓰레드 실행 함수
void *consumerFunc(void *); // 소비자 쓰레드 실행 함수
int main()
{
    pthread_t ptProduc, ptConsum;
    pthread_mutex_init(&mid, NULL);                      // 뮤텍스 초기화
    pthread_create(&ptProduc, NULL, producerFunc, NULL); // 생산자 쓰레드 생성
    pthread_create(&ptConsum, NULL, consumerFunc, NULL); // 소비자 쓰레드 생성
    pthread_join(ptProduc, NULL);                        // 생산자 쓰레드 종료 대기
    pthread_join(ptConsum, NULL);                        // 소비자 쓰레드 종료 대기
    pthread_mutex_destroy(&mid);                         // 뮤텍스 제거
    return 0;
}
void *producerFunc(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mid); // 뮤텍스 잠금
        printf("[%d] Producer : %d -> ", i, share_var);
        share_var++;
        printf(" %d \n", share_var);
        pthread_mutex_unlock(&mid); // 뮤텍스 잠금 해제
        sleep(2);
    }
    return NULL;
}
void *consumerFunc(void *arg)
{
    for (int i = 0; i < 15; i++)
    {
        pthread_mutex_lock(&mid); // 뮤텍스 잠금
        printf("[%d] Consumer : %d -> ", i, share_var);
        share_var--;
        printf(" %d \n", share_var);
        pthread_mutex_unlock(&mid); // 뮤텍스 잠금 해제
        sleep(1);
    }
    return NULL;
}