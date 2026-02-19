#include <LDA/DataStructures/LDA_Queue.h>

LDA_ReturnCodes LDA_CreateQueue(void *queuestate, LDA_Queue **queueResult, bool (*OnQueueCreated)(LDA_Queue *queue))
{
    if(!queueResult)
    {
        return LDA_MainStructureParameterResultIsNULL;
    }
    LDA_Queue *newqueue = malloc(sizeof(LDA_Queue));
    if(!newqueue)
    {
        return LDA_ItemNotCreated;
    }
    newqueue->_firstElement = NULL;
    newqueue->_lastElement = NULL;
    newqueue->_queuestate = queuestate;
    if(OnQueueCreated)
    {
        if(!OnQueueCreated(newqueue))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    *queueResult = newqueue;
    return LDA_Success;
}
LDA_ReturnCodes LDA_CreateQueueNode(void *nodestate, void *nodedata, LDA_QueueNode **queueNodeResult, bool (*OnQueueNodeCreated)(LDA_QueueNode *node))
{
    if(!queueNodeResult)
    {
        return LDA_NodeStructureParameterResultIsNULL;
    }
    LDA_QueueNode *newnode = malloc(sizeof(LDA_QueueNode));
    if(!newnode)
    {
        return LDA_ItemNotCreated;
    }
    newnode->_nodestate = nodestate;
    newnode->_nodedata = nodedata;
    newnode->_nextnode = NULL;
    if(OnQueueNodeCreated)
    {
        if(!OnQueueNodeCreated(newnode))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    *queueNodeResult = newnode;
    return LDA_Success;
}
LDA_ReturnCodes LDA_QueueEnqueue(LDA_QueueNode *node, LDA_Queue *queue, bool (*ToQueueEnqueue)(LDA_QueueNode *node, LDA_Queue *queue),bool (*OnQueueEnqueue)(LDA_QueueNode *node, LDA_Queue *queue))
{
    if(!node)
    {
        return LDA_NodeStructureParameterIsNULL;
    }
    if(!queue)
    {
        return LDA_MainStructureParameterIsNULL;
    }
    if(ToQueueEnqueue)
    {
        if(!ToQueueEnqueue(node, queue))
        {
            return LDA_PreActionCallbackFunctionFailed;
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
    if(OnQueueEnqueue)
    {
        if(!OnQueueEnqueue(node, queue))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    return LDA_Success;
}
LDA_ReturnCodes LDA_QueueDequeue(LDA_Queue *queue, LDA_QueueNode **nodeResult, bool (*ToQueueDequeue)(LDA_QueueNode *node, LDA_Queue *queue), bool (*OnQueueDequeue)(LDA_QueueNode *node, LDA_Queue *queue))
{
    if(!queue)
    {
        return LDA_MainStructureParameterIsNULL;
    }
    if(!nodeResult)
    {
        return LDA_NodeStructureParameterResultIsNULL;
    }
    LDA_QueueNode *firstElementAux = queue->_firstElement;
    if(ToQueueDequeue)
    {
        if(!ToQueueDequeue(firstElementAux,queue))
        {
            return LDA_PreActionCallbackFunctionFailed;
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
    if(OnQueueDequeue)
    {
        if(!OnQueueDequeue(firstElementAux,queue))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    *nodeResult = firstElementAux;
    return LDA_Success;
}
LDA_ReturnCodes LDA_QueuePeek(LDA_Queue *queue, LDA_QueueNode **nodeResult)
{
    if(!queue)
    {
        return LDA_MainStructureParameterIsNULL;
    }
    if(!nodeResult)
    {
        return LDA_NodeStructureParameterResultIsNULL;
    }
    *nodeResult = queue->_firstElement;
    return LDA_Success;
}
bool LDA_QueueIsEmpty(LDA_Queue *queue)
{
    if(!queue)
    {
        return false;
    }
    return queue->_firstElement == NULL;
}
LDA_ReturnCodes LDA_QueueClear(LDA_Queue *queue, bool (*OnNodeCleared)(LDA_QueueNode *node), bool (*OnQueueClared)(LDA_Queue *queue))
{
    if(!queue)
    {
        return LDA_MainStructureParameterIsNULL;
    }
    LDA_QueueNode *nodeAux;
    LDA_ReturnCodes dequeueResult;
    while(queue->_firstElement != NULL)
    {
        dequeueResult = LDA_QueueDequeue(queue, &nodeAux,NULL,NULL);
        if(dequeueResult != LDA_Success)
        {
            return dequeueResult;
        }
        if(OnNodeCleared)
        {
            if(!OnNodeCleared(nodeAux))
            {
                return LDA_PreActionCallbackFunctionFailed;
            }
        }
        free(nodeAux);
    }
    if(OnQueueClared)
    {
        if(!OnQueueClared(queue))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    return LDA_Success;
}
LDA_ReturnCodes LDA_QueueDelete(LDA_Queue **queue, bool (*OnNodeCleared)(LDA_QueueNode *node), bool (OnQueueCleared)(LDA_Queue *queue))
{
    LDA_ReturnCodes clearResult = LDA_QueueClear(*queue, OnNodeCleared,OnQueueCleared);
    if(clearResult != LDA_Success)
    {
        return clearResult;
    }
    free(*queue);
    return LDA_Success;
}