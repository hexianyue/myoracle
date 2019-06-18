#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <pthread.h>

int main(void)
{
    int ret = -1;

#if 0
    //定义一个互斥锁变量
    pthread_mutex_t mutex;

    //1. 初始化互斥锁
    ret = pthread_mutex_init(&mutex, NULL);
    if (0 != ret)
    {
        printf("初始化互斥锁失败...\n"); 
        return 1;
    }
    printf("初始化互斥锁成功...\n");
#else
    //初始化互斥量
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#endif




    //2. 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    return 0;
}
