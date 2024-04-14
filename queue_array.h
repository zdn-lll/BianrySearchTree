#if !defined(__QUEUE_ARRAY_H)
#define __QUEUE_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#if !defined(QUEUE_ARRAY_USER_DATATYPE)

typedef int datatype;

#endif // QUEUE_ARRAY_USER_DATATYPE

#if defined(QUEUE_ARRAY_USER_DATATYPE)

typedef QUEUE_ARRAY_USER_DATATYPE datatype;

#endif // QUEUE_ARRAY_USER_DATATYPE


// 链式队列节点
typedef struct node
{
    datatype data;
    struct node *next;
} node;

// 链式队列管理结构体
typedef struct
{
    node *front; // 队头指针
    node *rear;  // 队尾指针

    int size; // 队列当前元素个数
} linkQueue;

// 初始化空队列
static inline linkQueue *initQueue()
{
    linkQueue *q = (linkQueue *)malloc(sizeof(linkQueue));
    if (q != NULL)
    {
        q->front = NULL;
        q->rear = NULL;

        q->size = 0;
    }

    return q;
}

// 判断队列是否为空
static inline bool isEmpty(linkQueue *q)
{
    return q->size == 0;
}

// 入队
static inline bool enQueue(linkQueue *q, datatype data)
{
    // 创建新节点
    node *new = malloc(sizeof(node));
    if (new == NULL)
        return false;

    new->data = data;
    new->next = NULL;

    // 入队分两种情况：
    // 1. 当前队列为空，则新节点是队列的唯一节点
    if (isEmpty(q))
        q->front = q->rear = new;

    // 2. 否则队列不为空，将新节点拼接到队尾之后
    else
    {
        q->rear->next = new;
        q->rear = new;
    }

    q->size++;
    return true;
}

// 出队
static inline bool outQueue(linkQueue *q, datatype *pm)
{
    if (isEmpty(q))
        return false;

    // 返回用户数据
    *pm = q->front->data;

    // 更新队头队尾指针，分两种情况：
    // 1. 当前队列只有一个元素，出队后队列为空，此时队头队尾指针都必须更新
    if (q->size == 1)
    {
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
    }

    // 2. 否则，只需更新队头指针即可
    else
    {
        node *tmp = q->front;
        q->front = q->front->next;

        tmp->next = NULL;
        free(tmp);
    }

    q->size--;
    return true;
}

// 取队头元素
static inline bool front(linkQueue *q, datatype *pm)
{
    if (isEmpty(q))
        return false;

    *pm = q->front->data;
    return true;
}

#endif // __QUEUE_ARRAY_H
