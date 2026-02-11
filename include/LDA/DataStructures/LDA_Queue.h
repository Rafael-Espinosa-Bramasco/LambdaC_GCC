#ifndef LDA_C_DATASTRUCTURES_QUEUE_INCLUDED
#define LDA_C_DATASTRUCTURES_QUEUE_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

/*
    @brief Enumeration representing the return codes for the Queue functions
*/
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
/*
    @brief Queue node to store data inside the queue
*/
typedef struct __lda_queuenode__
{
    void *_nodestate;
    void *_nodedata;
    struct __lda_queuenode__ *_nextnode;
}LDA_QueueNode;
/*
    @brief Queue structure, the main head of the queue
*/
typedef struct
{
    void *_queuestate;
    LDA_QueueNode *_firstElement;
    LDA_QueueNode *_lastElement;
}LDA_Queue;
/*
    @brief Creates a Queue

    @param queuestate void * type. A pointer to anything you want to save as a state.
    @param queueResult LDA_Queue ** type. A pointer to a pointer where the created queue is going to be saved.
    @param OnQueueCreated Callback function. This function is called once the Queue is created.

    @retval LDA_QueueSuccess if all went as planned.
    @retval LDA_QueueResultIsNull if the pointer to a pointer is NULL.
    @retval LDA_QueueNotCreated if the system memory allocation function failed.
    @retval LDA_OnQueueCreatedFailed if the OnQueueCreated callback function returned false. User defined behavior.
*/
LDA_QueueCode LDA_CreateQueue(void *queuestate, LDA_Queue **queueResult, bool (*OnQueueCreated)(LDA_Queue *queue));
/*
    @brief Creates a Queue node

    @param nodestate void * type. Pointer to anything you want.
    @param nodedata void * type. Pointer to the data you want to store.
    @param queueNodeResult LDA_QueueNode ** type. Pointer to pointer where the new node is going to be saved.
    @param OnQueueNodeCreated Callback function. This function is called once the node is created.

    @retval LDA_QueueSuccess if all went as planned.
    @retval LDA_QueueNodeResultIsNull if the pointer to a pointer is NULL.
    @retval LDA_QueueNodeNotCreated if the system memory allocation function failed.
    @retval LDA_OnQueueNodeCreatedFailed if the OnQueueNodeCreated callback function returned false. User defined behavior.
*/
LDA_QueueCode LDA_CreateQueueNode(void *nodestate, void *nodedata, LDA_QueueNode **queueNodeResult, bool (*OnQueueNodeCreated)(LDA_QueueNode *node));
/**/
LDA_QueueCode LDA_QueueEnqueue(LDA_QueueNode *node, LDA_Queue *queue, bool (*OnQueueEnqueue)(LDA_QueueNode *node, LDA_Queue *queue));
/**/
LDA_QueueCode LDA_QueueDequeue(LDA_Queue *queue, LDA_QueueNode **nodeResult, bool (*OnQueueDequeue)(LDA_QueueNode *node, LDA_Queue *queue));
/**/
LDA_QueueCode LDA_QueuePeek(LDA_Queue *queue, LDA_QueueNode **nodeResult);
/**/
bool LDA_QueueIsEmpty(LDA_Queue *queue);
/*
    @brief Clears all nodes from a Queue

    @param queue LDA_Queue * type. Pouinter to the queue you want to clear.
    @param OnNodeCleared Callback function. This function is called before using free on the dequeued node.
    @param OnQueueCleared Callback function. This function is called once all nodes have been dequeued.

    @retval LDA_QueueSuccess if all went as planned.
    @retval LDA_QueueIsNull if the queue passed as parameter is NULL.
    @retval LDA_QueueDequeue. This means that this function will return anything of the values LDA_QueuDequeue could return as error.
    @retval LDA_OnQueueNodeClearedFailed if the user defined function failed (returned false).
    @retval LDA_OnQueueClearedFailed if the user defined function failed (returned false).
*/
LDA_QueueCode LDA_QueueClear(LDA_Queue *queue, bool (*OnNodeCleared)(LDA_QueueNode *node), bool (*OnQueueClared)(LDA_Queue *queue));
/*
    @brief Clears the Queue and uses free() function on queue at finish

    @param queue LDA_Queue ** type. Pointer to a pointer for the queue you want to Delete.
    @param OnNodeCleared Callback function. This pointer to a function is sent as parameter to LDA_QueueClear.
    @param OnQueueCleared Callback function. This pointer to a function is sent as parameter to LDA_QueueClear.

    @retval LDA_QueueSuccess if all went as planned.
    @retval (Other code) this error is the return code returned by LDA_QueueClear function.
*/
LDA_QueueCode LDA_QueueDelete(LDA_Queue **queue, bool (*OnNodeCleared)(LDA_QueueNode *node), bool (OnQueueCleared)(LDA_Queue *queue));

#endif /* LDA_C_DATASTRUCTURES_QUEUE_INCLUDED */