#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


//信号量变量
sem_t sem;

//打印机资源
int print(char *str)
{
    while(*str)
    {
        putchar(*str); 
        str++; 
        //刷新标准输出
        fflush(stdout); 

        //100毫秒
        usleep(100000); 
    }

    return 0;
}


//输出大写字母
void *printA(void *arg)
{
    char *str = "ABCDEFGHIJKLMNOPQ";

    //申请资源 P操作 -1
    sem_wait(&sem);

    print(str);

    //释放资源 V操作 +1
    sem_post(&sem);

    pthread_exit(NULL);
}

//输出小写字母
void *printB(void *arg)
{
    char *str = "abcdefghijklmnopq";

    //申请资源 P操作 -1
    sem_wait(&sem);

    print(str);

    //释放资源 V操作 +1
    sem_post(&sem);

    pthread_exit(NULL);
}


int main(void)
{
    int ret = -1;

    pthread_t tid1;
    pthread_t tid2;

    //初始化信号量
    ret = sem_init(&sem, 0, 1);
    if (0 != ret)
    {
        printf("sem_init failed..\n"); 
        return 1;
    }

    //创建两个线程
    pthread_create(&tid1, NULL, printA, NULL);
    pthread_create(&tid2, NULL, printB, NULL);


    //等待线程退出
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    //销毁信号量
    ret = sem_destroy(&sem);
    if (0 != ret)
    {
        printf("sem_destroy failed...\n"); 
        return 1;
    }

    return 0;
}
