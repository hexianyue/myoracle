#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <unistd.h>
#include <pthread.h>

int main(void)
{
    int ret = -1;

#if 0
    pthread_cond_t cond;

    //初始化条件变量
    ret = pthread_cond_init(&cond, NULL);
    if (0 != ret)
    {
        printf("pthread_cond_init failed...\n"); 
        return 1;
    }
    printf("条件变量初始化成功\n");

#else
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
#endif



    //销毁
    ret = pthread_cond_destroy(&cond);

    return 0;
}
