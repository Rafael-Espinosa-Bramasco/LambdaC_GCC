#ifndef LDA_C_DATASTRUCTURES_QUEUE_INCLUDED
#define LDA_C_DATASTRUCTURES_QUEUE_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    LDA_QueueSuccess,

    LDA_QueueResultIsNull,
    LDA_QueueNotCreated,
    LDA_QueueIsNull,

    LDA_OnQueueCreatedFailed,
    LDA_OnQueueNodeCreatedFailed,
    LDA_OnQueueEnqueueFailed,
    LDA_OnQueueDequeueFailed,
    LDA_OnQueueNodeClearedFailed,
    LDA_OnQueueClearedFailed,

    LDA_QueueNodeResultIsNull,
    LDA_QueueNodeNotCreated,
    LDA_QueueNodeIsNull,
}LDA_QueueCode;
typedef struct __lda_queuenode__
{
    void *_nodestate;
    void *_nodedata;
    struct __lda_queuenode__ *_nextnode;
}LDA_QueueNode;
typedef struct
{
    void *_queuestate;
    LDA_QueueNode *_firstElement;
    LDA_QueueNode *_lastElement;
}LDA_Queue;

LDA_QueueCode LDA_CreateQueue(void *queuestate, LDA_Queue **queueResult, bool (*OnQueueCreated)(LDA_Queue *queue));
LDA_QueueCode LDA_CreateQueueNode(void *nodestate, void *nodedata, LDA_QueueNode **queueNodeResult, bool (*OnQueueNodeCreated)(LDA_QueueNode *node));
LDA_QueueCode LDA_QueueEnqueue(LDA_QueueNode *node, LDA_Queue *queue, bool (*OnQueueEnqueue)(LDA_QueueNode *node, LDA_Queue *queue));
LDA_QueueCode LDA_QueueDequeue(LDA_Queue *queue, LDA_QueueNode **nodeResult, bool (*OnQueueDequeue)(LDA_QueueNode *node, LDA_Queue *queue));
LDA_QueueCode LDA_QueuePeek(LDA_Queue *queue, LDA_QueueNode **nodeResult);
bool LDA_QueueIsEmpty(LDA_Queue *queue);
LDA_QueueCode LDA_QueueClear(LDA_Queue *queue, bool (*OnNodeCleared)(LDA_QueueNode *node), bool (*OnQueueClared)(LDA_Queue *queue));
LDA_QueueCode LDA_QueueDelete(LDA_Queue **queue, bool (*OnNodeCleared)(LDA_QueueNode *node), bool (OnQueueCleared)(LDA_Queue *queue));

#endif /* LDA_C_DATASTRUCTURES_QUEUE_INCLUDED */