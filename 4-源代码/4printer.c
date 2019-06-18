#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <unistd.h>
#include <pthread.h>


//定义一个互斥锁变量
pthread_mutex_t mutex;

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

    //加锁
    pthread_mutex_lock(&mutex);  

    print(str);

    //解锁
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

//输出小写字母
void *printB(void *arg)
{
    char *str = "abcdefghijklmnopq";

    //加锁
    pthread_mutex_lock(&mutex); 

    print(str);

    //解锁
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}


int main(void)
{
    int ret = -1;

    pthread_t tid1;
    pthread_t tid2;

    //互斥量初始化
    ret = pthread_mutex_init(&mutex, NULL);
    if (0 != ret)
    {
        printf("初始化互斥量失败...\n"); 
        return 1;
    }

    //创建两个线程
    pthread_create(&tid1, NULL, printA, NULL);
    pthread_create(&tid2, NULL, printB, NULL);


    //等待线程退出
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    //互斥量销毁
    ret = pthread_mutex_destroy(&mutex);
    if (0 != ret)
    {
        printf("互斥量销毁失败...\n"); 
        return 1;
    }

    return 0;
}
