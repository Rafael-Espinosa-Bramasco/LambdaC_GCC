#include <LDA/DataStructures/LDA_List.h>

#include <stdlib.h>

LDA_ListCodes LDA_CreateSLL(void *state, LDA_SLL **listResult, bool (*OnSLLCreated)(LDA_SLL *sll))
{
    if(!listResult)
    {
        return LDA_ListResultIsNull;
    }
    LDA_SLL *newsll = malloc(sizeof(LDA_SLL));
    if(!newsll)
    {
        return LDA_ListNotCreated;
    }
    newsll->_sllstate = state;
    newsll->_firstNode = NULL;
    newsll->_lastNode = NULL;
    if(OnSLLCreated)
    {
        if(!OnSLLCreated(newsll))
        {
            return LDA_OnSLLCreatedFailed;
        }
    }
    *listResult = newsll;
    return LDA_ListSuccess;
}
LDA_ListCodes LDA_CreateSLLNode(void *state, void *data, LDA_SLLNode **nodeResult, bool (*OnSLLNodeCreated)(LDA_SLLNode *node))
{
    if(!nodeResult)
    {
        return LDA_ListNodeResultIsNull;
    }
    LDA_SLLNode *newsllnode = malloc(sizeof(LDA_SLLNode));
    if(!newsllnode)
    {
        return LDA_ListNodeNotCreated;
    }
    newsllnode->_nodeState = state;
    newsllnode->_nodeData = data;
    newsllnode->_nextNode = NULL;
    if(OnSLLNodeCreated)
    {
        if(!OnSLLNodeCreated(newsllnode))
        {
            return LDA_OnSLLNodeCreatedFailed;
        }
    }
    *nodeResult = newsllnode;
    return LDA_ListSuccess;
}