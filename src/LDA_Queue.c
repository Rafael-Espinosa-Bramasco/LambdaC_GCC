#include <LDA/DataStructures/LDA_Queue.h>

LDA_QueueCode LDA_CreateQueue(void *queuestate, LDA_Queue **queueResult, bool (*OnQueueCreated)(LDA_Queue *queue))
{
    if(!queueResult)
    {
        return LDA_QueueResultIsNull;
    }
    LDA_Queue *newqueue = malloc(sizeof(LDA_Queue));
    if(!newqueue)
    {
        return LDA_QueueNotCreated;
    }
    newqueue->_firstElement = NULL;
    newqueue->_lastElement = NULL;
    newqueue->_queuestate = queuestate;
    if(OnQueueCreated)
    {
        if(!OnQueueCreated(newqueue))
        {
            return LDA_OnQueueCreatedFailed;
        }
    }
    *queueResult = newqueue;
    return LDA_QueueSuccess;
}
LDA_QueueCode LDA_CreateQueueNode(void *nodestate, void *nodedata, LDA_QueueNode **queueNodeResult, bool (*OnQueueNodeCreated)(LDA_QueueNode *node))
{
    if(!queueNodeResult)
    {
        return LDA_QueueNodeResultIsNull;
    }
    LDA_QueueNode *newnode = malloc(sizeof(LDA_QueueNode));
    if(!newnode)
    {
        return LDA_QueueNodeNotCreated;
    }
    newnode->_nodestate = nodestate;
    newnode->_nodedata = nodedata;
    newnode->_nextnode = NULL;
    if(OnQueueNodeCreated)
    {
        if(!OnQueueNodeCreated(newnode))
        {
            return LDA_OnQueueNodeCreatedFailed;
        }
    }
    *queueNodeResult = newnode;
    return LDA_QueueSuccess;
}
LDA_QueueCode LDA_QueueEnqueue(LDA_QueueNode *node, LDA_Queue *queue, bool (*OnQueueEnqueue)(LDA_QueueNode *node, LDA_Queue *queue))
{
    if(!node)
    {
        return LDA_QueueNodeIsNull;
    }
    if(!queue)
    {
        return LDA_QueueIsNull;
    }
    if(OnQueueEnqueue)
    {
        if(!OnQueueEnqueue(node, queue))
        {
            return LDA_OnQueueEnqueueFailed;
        }
    }
    if(queue->_firstElement == NULL)
    {
        queue->_firstElement = node;
        queue->_lastElement = node;
    }else
    {
        queue->_lastElement->_nextnode = node;
        queue->_lastElement = node;
    }
    return LDA_QueueSuccess;
}
LDA_QueueCode LDA_QueueDequeue(LDA_Queue *queue, LDA_QueueNode **nodeResult, bool (*OnQueueDequeue)(LDA_QueueNode *node, LDA_Queue *queue))
{
    if(!queue)
    {
        return LDA_QueueIsNull;
    }
    if(!nodeResult)
    {
        return LDA_QueueNodeResultIsNull;
    }
    LDA_QueueNode *firstElementAux = queue->_firstElement;
    if(OnQueueDequeue)
    {
        if(!OnQueueDequeue(firstElementAux,queue))
        {
            return LDA_OnQueueDequeueFailed;
        }
    }
    if(queue->_firstElement == queue->_lastElement)
    {
        queue->_firstElement = NULL;
        queue->_lastElement = NULL;
    }else
    {
        queue->_firstElement = firstElementAux->_nextnode;
    }
    firstElementAux->_nextnode = NULL;
    *nodeResult = firstElementAux;
    return LDA_QueueSuccess;
}
LDA_QueueCode LDA_QueuePeek(LDA_Queue *queue, LDA_QueueNode **nodeResult)
{
    if(!queue)
    {
        return LDA_QueueIsNull;
    }
    if(!nodeResult)
    {
        return LDA_QueueNodeResultIsNull;
    }
    *nodeResult = queue->_firstElement;
    return LDA_QueueSuccess;
}
bool LDA_QueueIsEmpty(LDA_Queue *queue)
{
    if(!queue)
    {
        return false;
    }
    return queue->_firstElement == NULL;
}
LDA_QueueCode LDA_QueueClear(LDA_Queue *queue, bool (*OnNodeCleared)(LDA_QueueNode *node), bool (*OnQueueClared)(LDA_Queue *queue))
{
    if(!queue)
    {
        return LDA_QueueIsNull;
    }
    LDA_QueueNode *nodeAux;
    LDA_QueueCode dequeueResult;
    while(queue->_firstElement != NULL)
    {
        dequeueResult = LDA_QueueDequeue(queue, &nodeAux,NULL);
        if(dequeueResult != LDA_QueueSuccess)
        {
            return dequeueResult;
        }
        if(OnNodeCleared)
        {
            if(!OnQueueNodeCleared(nodeAux))
            {
                return LDA_OnQueueNodeClearedFailed;
            }
        }
        free(nodeAux);
    }
    if(OnQueueClared)
    {
        if(!OnQueueClared(queue))
        {
            return LDA_OnQueueClearedFailed;
        }
    }
    return LDA_QueueSuccess;
}
LDA_QueueCode LDA_QueueDelete(LDA_Queue **queue, bool (*OnNodeCleared)(LDA_QueueNode *node), bool (OnQueueCleared)(LDA_Queue *queue))
{
    LDA_QueueCode clearResult = LDA_QueueClear(*queue, OnNodeCleared,OnQueueCleared);
    if(clearResult != LDA_QueueSuccess)
    {
        return clearResult;
    }
    free(*queue);
    return LDA_QueueSuccess;
}