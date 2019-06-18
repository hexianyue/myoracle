#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <pthread.h>


//定义变量
pthread_rwlock_t rwlock;


//读写锁
int main(void)
{
    int ret = -1;


#if 1
    //初始化
    ret = pthread_rwlock_init(&rwlock,  NULL);
    if (0 != ret)
    {
        printf("pthread_rwlock_init failed..\n"); 
        return 1;
    }
    printf("初始化读写锁ok....\n");

#else

    //静态初始化一个读写锁
    pthread_rwlock_t rwlock1 = PTHREAD_RWLOCK_INITIALIZER;

#endif

    //加写锁
    ret = pthread_rwlock_wrlock(&rwlock);
    if (0 != ret)
    {
        printf("pthread_rwlock_wrlock failed...\n"); 
        return 1;
    }
    printf("线程加写锁成功....\n");

    //加读锁
    ret = pthread_rwlock_rdlock(&rwlock);
    if (0 != ret)
    {
        printf("pthread_rwlock_rdlock failed...\n"); 
        return 1;
    }
    printf("第一次加读锁成功...\n");


    //加读锁
    ret = pthread_rwlock_rdlock(&rwlock);
    if (0 != ret)
    {
        printf("pthread_rwlock_rdlock failed...\n"); 
        return 1;
    }
    printf("第二次加读锁成功...\n");



    //销毁读写锁
    ret = pthread_rwlock_destroy(&rwlock);
    if (0 != ret)
    {
        printf("pthread_rwlock_destroy failed...\n"); 
        return 1;
    }

    return 0;
}
