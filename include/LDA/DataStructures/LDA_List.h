#ifndef LDA_C_DATASTRUCTURES_LIST_INCLUDED
#define LDA_C_DATASTRUCTURES_LIST_INCLUDED

#include <stdbool.h>

typedef enum __lda_listcodes__
{
    LDA_ListSuccess,
    LDA_ListResultIsNull,
    LDA_ListNodeResultIsNull,
    LDA_ListNotCreated,
    LDA_ListNodeNotCreated,
    LDA_OnSLLCreatedFailed,
    LDA_OnSLLNodeCreatedFailed,
}LDA_ListCodes;

/* Simply Linked List Section */

typedef struct __lda_sllnode__
{
    void *_nodeState;
    void *_nodeData;
    struct __lda_sllnode__ *_nextNode;
}LDA_SLLNode;
typedef struct __lda_sll__
{
    void *_sllstate;
    LDA_SLLNode *_firstNode;
    LDA_SLLNode *_lastNode;
}LDA_SLL;

LDA_ListCodes LDA_CreateSLL(void *state, LDA_SLL **listResult, bool (*OnSLLCreated)(LDA_SLL *sll));
LDA_ListCodes LDA_CreateSLLNode(void *state, void *data, LDA_SLLNode **nodeResult, bool (*OnSLLNodeCreated)(LDA_SLLNode *node));

#endif /* LDA_C_DATASTRUCTURES_LIST_INCLUDED */