#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/hdbhead_all.h"

struct yc_period_seg_z
{
	POINTER point;
	int id;					/* added by yyp 07.12.27 for hdb */
	char logicalname[50];
	unsigned char period;
	float realvalue;
	struct yc_period_data data_cur;
	//	struct yc_period_data data_last;
};

typedef struct hdb_yc_period_z
{
	int num;
	int flag;
	struct yc_period_seg_z seg[MAX_YC_NUM];
} HDB_YC_PERIOD_Z;


typedef HDB_YC_PERIOD_Z elemType;


struct sNode{
    elemType data;            /* 值域 */
    struct sNode *next;       /* 链接指针 */
};

struct queueLK{
    struct sNode *front;    /* 队首指针 */
    struct sNode *rear;        /* 队尾指针 */
};

/* 1.初始化链队 */
void initQueue(struct queueLK *hq)
{
    hq->front = hq->rear = NULL;        /* 把队首和队尾指针置空 */
    return;
}

/* 2.向链队中插入一个元素x */
void enQueue(struct queueLK *hq, elemType *x)
{
    /* 得到一个由newP指针所指向的新结点 */
    struct sNode *newP;
    newP = malloc(sizeof(struct sNode));
    if(newP == NULL){
        printf("内存空间分配失败！ ");
        exit(1);
    }
    /* 把x的值赋给新结点的值域，把新结点的指针域置空 */
    //newP->data = x;
	memcpy(&(newP->data),x,sizeof(elemType));
    newP->next = NULL;
    /* 若链队为空，则新结点即是队首结点又是队尾结点 */
    if(hq->rear == NULL){
        hq->front = hq->rear = newP;
    }else{    /* 若链队非空，则依次修改队尾结点的指针域和队尾指针，使之指向新的队尾结点 */
        hq->rear = hq->rear->next = newP;        /* 注重赋值顺序哦 */
    }
    return;
}

/* 3.从队列中删除一个元素 */
void outQueue(struct queueLK *hq, elemType *outdata)
{
    struct sNode *p;
   // elemType temp;
    /* 若链队为空则停止运行 */
    if(hq->front == NULL){
        printf("队列为空，无法删除！ ");
        exit(1);
    }
    memcpy(outdata ,&(hq->front->data),sizeof(elemType));        /* 暂存队尾元素以便返回 */
    p = hq->front;                /* 暂存队尾指针以便回收队尾结点 */
    hq->front = p->next;        /* 使队首指针指向下一个结点 */
    /* 若删除后链队为空，则需同时使队尾指针为空 */
    if(hq->front == NULL){
        hq->rear = NULL;
    }
    free(p);        /* 回收原队首结点 */
    return;    /* 返回被删除的队首元素值 */
}

/* 4.读取队首元素 */
elemType peekQueue(struct queueLK *hq)
{
    /* 若链队为空则停止运行 */
    if(hq->front == NULL){
        printf("队列为空，无法删除！ ");
        exit(1);
    }
    return hq->front->data;        /* 返回队首元素 */
}

/* 5.检查链队是否为空，若为空则返回1, 否则返回0 */
int emptyQueue(struct queueLK *hq)
{
    /* 判定队首或队尾任一个指针是否为空即可 */
    if(hq->front == NULL){
        return 1;
    }else{
        return 0;
    }
}

/* 6.清除链队中的所有元素 */
void clearQueue(struct queueLK *hq)
{
    struct sNode *p = hq->front;        /* 队首指针赋给p */
    /* 依次删除队列中的每一个结点，最后使队首指针为空 */
    while(p != NULL){
        hq->front = hq->front->next;
        free(p);
        p = hq->front;
    }    /* 循环结束后队首指针已经为空 */
    hq->rear = NULL;        /* 置队尾指针为空 */
    return;
}

/************************************************************************/
// int main(int argc, char* argv[])
// {
//     struct queueLK q;
//     int a[8] = {3, 8, 5, 17, 9, 30, 15, 22};
//     int i;
//     initQueue(&q);
//     for(i = 0; i < 8; i++){
//         enQueue(&q, &a[i]);
//     }
//     printf("%d ", outQueue(&q));
//     printf("%d  ", outQueue(&q));
//  //   enQueue(&q, 68);
//     printf("%d ", peekQueue(&q));
//     printf("%d  ", outQueue(&q));
//     while(!emptyQueue(&q)){
//         printf("%d ", outQueue(&q));
//     }
//     printf(" ");
//     clearQueue(&q);
//     system("pause");
// }
