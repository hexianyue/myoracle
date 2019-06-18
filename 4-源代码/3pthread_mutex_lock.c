#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <pthread.h>

int main(void)
{
    int ret = -1;

    //定义一个互斥锁变量
    pthread_mutex_t mutex;

    //1. 初始化互斥锁 默认是打开
    ret = pthread_mutex_init(&mutex, NULL);
    if (0 != ret)
    {
        printf("初始化互斥锁失败...\n"); 
        return 1;
    }
    printf("初始化互斥锁成功...\n");


    //2. 加锁
    ret = pthread_mutex_lock(&mutex);
    if (0 != ret)
    {
        printf("第一次加锁失败...\n"); 
        return 1;
    }
    printf("第一次加锁成功...\n");

#if 0

    //2. 加锁
    ret = pthread_mutex_lock(&mutex);
    if (0 != ret)
    {
        printf("第一次加锁失败...\n"); 
        return 1;
    }
    printf("第一次加锁成功...\n");
#endif


    //3. 解锁
    ret = pthread_mutex_unlock(&mutex);
    if (0 != ret)
    {
        printf("第一次解锁失败...\n"); 
        return 1;
    }
    printf("第一次解锁成功\n");



    //4. 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    return 0;
}
