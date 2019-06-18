#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <unistd.h>
#include <pthread.h>


//互斥量
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;


void *fun1(void *arg)
{
    //先加锁互斥量1 然后加锁互斥量2

    pthread_mutex_lock(&mutex1);
    usleep(1);
    pthread_mutex_lock(&mutex2);

    printf("线程1执行程序...\n");
    
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    
    pthread_exit(NULL);
}


void *fun2(void *arg)
{
    //先加锁互斥量2 然后加锁互斥量1

    pthread_mutex_lock(&mutex2);
    usleep(1);
    pthread_mutex_lock(&mutex1);

    printf("线程2执行程序...\n");
    
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    
    pthread_exit(NULL);
}



int main(void)
{
    int ret = -1;

    pthread_t tid1;
    pthread_t tid2;

    //创建线程
    ret = pthread_create(&tid1, NULL, fun1, NULL);
    if (0 != ret)
    {
        printf("pthread_create failed...\n"); 
        return 1;
    }

    ret = pthread_create(&tid2, NULL, fun2, NULL);
    if (0 != ret)
    {
        printf("pthread_create failed...\n"); 
        return 1;
    }


    //等待线程退出
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


    return 0;
}
