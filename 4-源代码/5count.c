#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 


#include <unistd.h>
#include <pthread.h>


//全局变量
int num = 0;

//互斥量
pthread_mutex_t mutex;

void *fun1(void *arg)
{
    int i = 0;

    for (i = 0; i < 1000000; i++)
    {
        //加锁
        pthread_mutex_lock(&mutex);
        num++; 

        //解锁
        pthread_mutex_unlock(&mutex);
    }


    pthread_exit(NULL);
}

void *fun2(void *arg)
{
    int i = 0;

    for (i = 0; i < 1000000; i++)
    {
        //加锁
        pthread_mutex_lock(&mutex);

        num ++; 

        //解锁
        pthread_mutex_unlock(&mutex);

    }
        
    pthread_exit(NULL);
}


int main(void)
{
    int ret = -1;

    pthread_t tid1;
    pthread_t tid2;


    //初始化互斥量
    ret = pthread_mutex_init(&mutex, NULL);
    if (0 != ret)
    {
        printf("pthread_mutex_init failed..\n"); 
        return 1;
    }

    //创建两个线程
    ret = pthread_create(&tid1, NULL, fun1, NULL);
    if (0 != ret)
    {
        printf("pthread_create failed...\n"); 
        return 1;
    }

    ret = pthread_create(&tid2, NULL, fun2, NULL);
    if (0 != ret)
    {
        printf("pthread_create failed..\n"); 
        return 1;
    }


    //回收线程资源
    ret = pthread_join(tid1, NULL);
    if (0 != ret)
    {
        printf("pthread_join failed..\n"); 
        return 1;
    }

    ret = pthread_join(tid2, NULL);
    if (0 != ret)
    {
        printf("pthread_join failed..\n"); 
        return 1;
    }

    printf("main num: %d\n", num);

    //销毁互斥量
    pthread_mutex_destroy(&mutex);

    return 0;
}
