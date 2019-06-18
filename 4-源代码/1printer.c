#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <unistd.h>
#include <pthread.h>



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

    print(str);

    pthread_exit(NULL);
}

//输出小写字母
void *printB(void *arg)
{
    char *str = "abcdefghijklmnopq";

    print(str);

    pthread_exit(NULL);
}


int main(void)
{
    pthread_t tid1;
    pthread_t tid2;

    //创建两个线程
    pthread_create(&tid1, NULL, printA, NULL);
    pthread_create(&tid2, NULL, printB, NULL);


    //等待线程退出
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
