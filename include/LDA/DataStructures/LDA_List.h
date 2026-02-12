#ifndef LDA_C_DATASTRUCTURES_LIST_INCLUDED
#define LDA_C_DATASTRUCTURES_LIST_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    LDA_ListSuccess,

    LDA_ListResultIsNull,
    LDA_ListNodeResultIsNull,

    LDA_ListNotCreated,
    LDA_ListNodeNotCreated,

    LDA_OnListCreatedFailed,
    LDA_OnListNodeCreatedFailed,
}LDA_ListCode;
typedef struct __lda_listnode__
{
    void *_nodestate;
    void *_nodedata;
    struct __lda_listnode__ *_prevNode;
    struct __lda_listnode__ *_nextNode;
}LDA_ListNode;
typedef struct
{
    void *_liststate;
    LDA_ListNode *_fistElement;
    LDA_ListNode *_LastElement;
}LDA_List;

LDA_ListCode LDA_CreateList(void *liststate, LDA_List **listResult, bool (*OnListCreated)(LDA_List *list));
LDA_ListCode LDA_CreateListNode(void *nodestate, void *nodedata, LDA_ListNode **nodeResult, bool (*OnNodeCreated)(LDA_ListNode *node));
LDA_ListCode LDA_ListAddAtStart();
LDA_ListCode LDA_ListAddAtEnd();
LDA_ListCode LDA_ListAddAtIndex();
LDA_ListCode LDA_ListRemoveAtStart();
LDA_ListCode LDA_ListRemoveAtEnd();
LDA_ListCode LDA_ListRemoveAtIndex();
LDA_ListCode LDA_ListGetFirstElement();
LDA_ListCode LDA_ListGetLastElement();
LDA_ListCode LDA_ListGetElementAtIndex();
bool LDA_ListIsEmpty();
LDA_ListCode LDA_ListClear();
LDA_ListCode LDA_ListDelete();

#endif /* LDA_C_DATASTRUCTURES_LIST_INCLUDED */