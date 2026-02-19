#include <LDA/DataStructures/LDA_List.h>

LDA_ReturnCodes LDA_CreateSLL(void *state, LDA_SLL **listResult, bool (*OnSLLCreated)(LDA_SLL *sll))
{
    if(!listResult)
    {
        return LDA_MainStructureParameterResultIsNULL;
    }
    LDA_SLL *newsll = malloc(sizeof(LDA_SLL));
    if(!newsll)
    {
        return LDA_ItemNotCreated;
    }
    newsll->_sllstate = state;
    newsll->_firstNode = NULL;
    newsll->_lastNode = NULL;
    if(OnSLLCreated)
    {
        if(!OnSLLCreated(newsll))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    *listResult = newsll;
    return LDA_Success;
}
LDA_ReturnCodes LDA_CreateSLLNode(void *state, void *data, LDA_SLLNode **nodeResult, bool (*OnSLLNodeCreated)(LDA_SLLNode *node))
{
    if(!nodeResult)
    {
        return LDA_NodeStructureParameterResultIsNULL;
    }
    LDA_SLLNode *newsllnode = malloc(sizeof(LDA_SLLNode));
    if(!newsllnode)
    {
        return LDA_ItemNotCreated;
    }
    newsllnode->_nodeState = state;
    newsllnode->_nodeData = data;
    newsllnode->_nextNode = NULL;
    if(OnSLLNodeCreated)
    {
        if(!OnSLLNodeCreated(newsllnode))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    *nodeResult = newsllnode;
    return LDA_Success;
}
LDA_ReturnCodes LDA_SLLAddAtStart(LDA_SLLNode *node, LDA_SLL *list)
{
    return LDA_Success;
}