#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 


#include <unistd.h>
#include <pthread.h>

//链表节点类型
typedef struct _node_t{
    int data; //数据域
    struct _node_t *next; //指针域
}node_t;


//定义条件变量
pthread_cond_t cond;

//定义互斥锁
pthread_mutex_t mutex;

//指向链表的第一个节点
node_t *head = NULL;


//线程1处理函数  生产者线程
void *producer(void *arg)
{
    node_t *new = NULL;

    while(1)
    {
    
        //加锁
        pthread_mutex_lock(&mutex);    

        //分配空间
        new = malloc(sizeof(node_t));
        if (NULL == new)
        {
            printf("malloc failed..\n"); 
            break;
        }
        memset(new, 0, sizeof(node_t));

        //1 - 100
        new->data = random() % 100 + 1;
        //头插法
        new->next = head;
        head = new;
    
        //\033[31m 设置前景色   \033[0m 取消设置属性
        printf("\033[31m生产者生产了一个产品: %d\033[0m\n", new->data);
        //解锁
        pthread_mutex_unlock(&mutex);

        //唤醒阻塞在条件变量上的线程
        pthread_cond_signal(&cond);

        sleep(random() % 3 + 1); 
    }
    
    pthread_exit(NULL);
}


//线程2处理函数  消费者线程
void *customer(void *arg)
{
    node_t *tmp = NULL;
    while(1)
    {
        //加锁
        pthread_mutex_lock(&mutex);    

        //条件不满足
        if (NULL == head)
        {
            //1. 会阻塞等待
            //2. 解锁
            //3. 当pthread_cond_signal被调用之后加锁
            pthread_cond_wait(&cond, &mutex); 
        }

        //删除链表第一个节点
        tmp = head;
        head = head->next;
        printf("消费者消费了产品%d\n", tmp->data); 

        //释放内存
        free(tmp);    

        //解锁
        pthread_mutex_unlock(&mutex); 

        sleep(random() % 3 + 1); 

    }


    pthread_exit(NULL);
}
int main(void)
{
    int ret = -1;

    pthread_t tid1;
    pthread_t tid2;


    //设置随机种子
    srandom(time(NULL));

    //1. 初始化互斥锁
    ret = pthread_mutex_init(&mutex, NULL);
    if (0 != ret)
    {
        printf("pthread_mutex_init failed...\n"); 
        return 1;
    }

    //2. 初始化条件变量
    ret = pthread_cond_init(&cond, NULL);
    if (0 != ret)
    {
        printf("pthread_cond_init failed...\n"); 
        return 1;
    }

    //3. 创建生产者和消费者线程
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, customer, NULL);


    //4. 等待线程退出
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);


    //5. 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    //6. 销毁条件变量
    pthread_cond_destroy(&cond);

    return 0;
}
