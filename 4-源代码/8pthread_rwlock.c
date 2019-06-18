#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 


#include <unistd.h>
#include <pthread.h>

//定义读写锁变量
pthread_rwlock_t rwlock;

int num = 0;

//读
void *funRead(void *arg)
{
    while(1)
    {
        //申请加读锁
        pthread_rwlock_rdlock(&rwlock);

        printf("线程%ld读操作 num = %d\n", (long)arg, num);

        //解锁
        pthread_rwlock_unlock(&rwlock);
        usleep(500000);
    }
}


//写
void *funWrite(void *arg)
{
    while(1)
    {
        //申请加写锁
        pthread_rwlock_wrlock(&rwlock);

        num++;

        printf("线程%ld写操作\n", (long)arg);

        //解锁
        pthread_rwlock_unlock(&rwlock);
        usleep(500000);
    }
}


//创建八个线程  5个读线程  3个写线程
int main(void)
{
    int i = 0;
    int ret = -1;

    pthread_t tid[8];

    //初始化
    ret = pthread_rwlock_init(&rwlock, NULL);
    if (0 != ret)
    {
        printf("pthread_rwlock_init failed...\n"); 
        return 1;
    }

    //创建线程
    for (i = 0; i < 8; i++)
    {
        if (i < 5)
        {
            pthread_create(&tid[i], NULL, funRead, (void*)(long)i); 
        }
        else
        {
            pthread_create(&tid[i], NULL, funWrite, (void*)(long)i); 
        }
    }


    //回收资源
    for (i = 0; i < 8; i++)
    {
        pthread_join(tid[i], NULL); 
    }

    //销毁读写锁
    pthread_rwlock_destroy(&rwlock);    

    return 0;
}
