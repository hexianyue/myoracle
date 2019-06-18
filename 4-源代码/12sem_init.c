#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


//信号量相关操作
int main(void)
{
    int ret = -1;
    int val = 0;

    sem_t sem;
    
    //1. 初始化
    ret = sem_init(&sem, 0, 1); 
    if (0 != ret)
    {
        printf("sem_init failed...\n"); 
        return 1;
    }


    //获取信号量的值
    sem_getvalue(&sem, &val);
    printf("当前信号量: %d\n", val);

    //v操作 释放资源  +1
    sem_post(&sem);
    //获取信号量的值
    sem_getvalue(&sem, &val);
    printf("当前信号量: %d\n", val);

    //p操作 申请资源 -1
    sem_wait(&sem);
    //获取信号量的值
    sem_getvalue(&sem, &val);
    printf("当前信号量: %d\n", val);


    //销毁
   ret = sem_destroy(&sem); 
   if (0 != ret)
   {
        printf("sem_destroy failed...\n"); 
        return 1;
   }

    return 0;
}
