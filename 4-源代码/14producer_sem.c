#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 


#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

//链表节点类型
typedef struct _node_t{
    int data; //数据域
    struct _node_t *next; //指针域
}node_t;


//指向链表的第一个节点
node_t *head = NULL;

//用于存储商品容器个数
sem_t sem_producer;
//用于消费商品的个数
sem_t sem_customer;


//线程1处理函数  生产者线程
void *producer(void *arg)
{
    node_t *new = NULL;

    while(1)
    {
        
        //申请生产者资源 
        sem_wait(&sem_producer);    

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
    
        //释放消费者资源
        sem_post(&sem_customer);

        //\033[31m 设置前景色   \033[0m 取消设置属性
        printf("\033[31m生产者生产了一个产品: %d\033[0m\n", new->data);

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
        
        //申请消费者资源
        sem_wait(&sem_customer);

        //删除链表第一个节点
        tmp = head;
        head = head->next;
        printf("消费者消费了产品%d\n", tmp->data); 

        //释放内存
        free(tmp);    

        //释放生产者资源
        sem_post(&sem_producer);

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

    //1. 初始化生产者信号量 表示存储商品容器个数
    ret = sem_init(&sem_producer, 0, 4);
    if (0 != ret)
    {
        printf("sem_init failed...\n"); 
        return 1;
    }

    //2. 初始化消费者信号量 表示可以卖的商品个数
    ret = sem_init(&sem_customer, 0, 0);
    if (0 != ret)
    {
        printf("sem_init failed...\n"); 
        return 1;
    }


    //3. 创建生产者和消费者线程
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, customer, NULL);


    //4. 等待线程退出
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);


    //5. 销毁生产者信号量
    ret = sem_destroy(&sem_producer);
    if (0 != ret)
    {
        printf("sem_destroy failed..\n"); 
        return 1;
    }

    //6. 销毁消费者信号量
    ret = sem_destroy(&sem_customer);
    if (0 != ret)
    {
        printf("sem_destroy\n"); 
        return 1;
    }

    return 0;
}
