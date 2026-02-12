#include <LDA/DataStructures/LDA_List.h>

LDA_ListCode LDA_CreateList(void *liststate, LDA_List **listResult, bool (*OnListCreated)(LDA_List *list))
{
    if(!listResult)
    {
        return LDA_ListResultIsNull;
    }
    LDA_List *newlist = malloc(sizeof(LDA_List));
    if(!newlist)
    {
        return LDA_ListNotCreated;
    }
    newlist->_fistElement = NULL;
    newlist->_LastElement = NULL;
    newlist->_liststate = liststate;
    if(OnListCreated)
    {
        if(!OnListCreated(newlist))
        {
            return LDA_OnListCreatedFailed;
        }
    }
    *listResult = newlist;
    return LDA_ListSuccess;
}
LDA_ListCode LDA_CreateListNode(void *nodestate, void *nodedata, LDA_ListNode **nodeResult, bool (*OnNodeCreated)(LDA_ListNode *node))
{
    if(!nodeResult)
    {
        return LDA_ListNodeResultIsNull;
    }
    LDA_ListNode *newnode = malloc(sizeof(LDA_ListNode));
    if(!newnode)
    {
        return LDA_ListNodeNotCreated;
    }
    newnode->_prevNode = NULL;
    newnode->_nextNode = NULL;
    newnode->_nodestate = nodestate;
    newnode->_nodedata = nodedata;
    if(OnNodeCreated)
    {
        if(!OnNodeCreated(newnode))
        {
            return LDA_OnListNodeCreatedFailed;
        }
    }
    *nodeResult = newnode;
    return LDA_ListSuccess;
}