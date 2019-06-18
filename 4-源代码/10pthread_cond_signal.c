#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 


#include <unistd.h>
#include <pthread.h>


//定义条件变量
pthread_cond_t cond;

//定义互斥锁
pthread_mutex_t mutex;

int num = 0;


//线程1处理函数
void *fun1(void *arg)
{
    while(1)
    {
        //加锁
        pthread_mutex_lock(&mutex);    

        //条件不满足
        if (0 == num)
        {
            //1. 会阻塞等待
            //2. 解锁
            //3. 当pthread_cond_signal被调用之后加锁
            pthread_cond_wait(&cond, &mutex); 
        }
        
        printf("条件已经满足\n");

        num = 0;
    
        //解锁
        pthread_mutex_unlock(&mutex); 

    }


    pthread_exit(NULL);
}

//线程2处理函数
void *fun2(void *arg)
{
    while(1)
    {
    
        //加锁
        pthread_mutex_lock(&mutex);    

        num = 1;
    
        //解锁
        pthread_mutex_unlock(&mutex);

        //唤醒阻塞在条件变量上的线程
        pthread_cond_signal(&cond);

        sleep(1); 
    }
    
    pthread_exit(NULL);
}

int main(void)
{
    int ret = -1;

    pthread_t tid1;
    pthread_t tid2;

    //初始化互斥锁
    ret = pthread_mutex_init(&mutex, NULL);
    if (0 != ret)
    {
        printf("pthread_mutex_init failed...\n"); 
        return 1;
    }

    //初始化条件变量
    ret = pthread_cond_init(&cond, NULL);
    if (0 != ret)
    {
        printf("pthread_cond_init failed...\n"); 
        return 1;
    }

    pthread_create(&tid1, NULL, fun1, NULL);
    pthread_create(&tid2, NULL, fun2, NULL);


    //等待线程退出
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);


    //销毁互斥锁
    pthread_mutex_destroy(&mutex);

    //销毁条件变量
    pthread_cond_destroy(&cond);

    return 0;
}
