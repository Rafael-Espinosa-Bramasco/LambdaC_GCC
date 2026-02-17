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
LDA_ListCode LDA_ListAddAtStart(LDA_ListNode *node, LDA_List *list, bool (*OnListNodeAdded)(LDA_ListNode *node, LDA_List *list))
{
    if(!node)
    {
        return LDA_ListNodeIsNull;
    }
    if(!list)
    {
        return LDA_ListIsNull;
    }
    if(OnListNodeAdded)
    {
        if(!OnListNodeAdded(node,list))
        {
            return LDA_OnListNodeAddedFailed;
        }
    }
    if(list->_fistElement == NULL && list->_LastElement == NULL)
    {
        list->_fistElement = node;
        list->_LastElement = node;
    }
    else
    {
        list->_fistElement->_prevNode = node;
        node->_nextNode = list->_fistElement;
        list->_fistElement = node;
    }
    return LDA_ListSuccess;
}
LDA_ListCode LDA_ListAddAtEnd(LDA_ListNode *node, LDA_List *list, bool (*OnListNodeAdded)(LDA_ListNode *node, LDA_List *list))
{
    if(!node)
    {
        return LDA_ListNodeIsNull;
    }
    if(!list)
    {
        return LDA_ListIsNull;
    }
    if(OnListNodeAdded)
    {
        if(!OnListNodeAdded(node,list))
        {
            return LDA_OnListNodeAddedFailed;
        }
    }
    if(list->_fistElement == NULL && list->_LastElement == NULL)
    {
        list->_fistElement = node;
        list->_LastElement = node;
    }
    else
    {
        list->_LastElement->_nextNode = node;
        node->_prevNode = list->_LastElement;
        list->_LastElement = node;
    }
    return LDA_ListSuccess;
}
LDA_ListCode LDA_ListAddAtIndex(LDA_ListNode *node, LDA_List *list, size_t index, bool forceInsert, bool (*OnListNodeAdded)(LDA_ListNode *node, LDA_List *list))
{
    if(!node)
    {
        return LDA_ListNodeIsNull;
    }
    if(!list)
    {
        return LDA_ListIsNull;
    }
    LDA_ListNode *aux = list->_fistElement;
    if(!aux)
    {
        if(forceInsert)
        {
            return LDA_ListAddAtStart(node, list, OnListNodeAdded);
        }
        return LDA_ListIndexIsOutOfRange;
    }
    size_t i = 0;
    do
    {
        if(i == index)
        {
            aux->_prevNode = node;
            node->_nextNode = aux;
        }
    } while (aux);
    
    return LDA_ListSuccess;
}
LDA_ListCode LDA_ListRemoveAtStart();
LDA_ListCode LDA_ListRemoveAtEnd();
LDA_ListCode LDA_ListRemoveAtIndex();
LDA_ListCode LDA_ListGetFirstElement();
LDA_ListCode LDA_ListGetLastElement();
LDA_ListCode LDA_ListGetElementAtIndex();
bool LDA_ListIsEmpty(LDA_List *list)
{
    if(!list)
    {
        return false;
    }
    return list->_fistElement == NULL && list->_LastElement == NULL;
}
LDA_ListCode LDA_ListClear();
LDA_ListCode LDA_ListDelete();