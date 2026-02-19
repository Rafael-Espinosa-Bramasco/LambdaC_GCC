#ifndef LDA_C_DATASTRUCTURES_LIST_INCLUDED
#define LDA_C_DATASTRUCTURES_LIST_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

#include <LDA/LDA_StatusCodes.h>

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

LDA_ReturnCodes LDA_CreateSLL(void *state, LDA_SLL **listResult, bool (*OnSLLCreated)(LDA_SLL *sll));
LDA_ReturnCodes LDA_CreateSLLNode(void *state, void *data, LDA_SLLNode **nodeResult, bool (*OnSLLNodeCreated)(LDA_SLLNode *node));
LDA_ReturnCodes LDA_SLLAddAtStart(LDA_SLLNode *node, LDA_SLL *list);
LDA_ReturnCodes LDA_SLLAddAtEnd();
LDA_ReturnCodes LDA_SLLAddAtIndex();
LDA_ReturnCodes LDA_SLLRemoveAtStart();
LDA_ReturnCodes LDA_SLLRemoveAtEnd();
LDA_ReturnCodes LDA_SLLRemoveAtIndex();
LDA_ReturnCodes LDA_SLLPeekStart();
LDA_ReturnCodes LDA_SLLPeekEnd();
LDA_ReturnCodes LDA_SLLPeekIndex();
LDA_ReturnCodes LDA_SLLClear();
LDA_ReturnCodes LDA_SLLDelete();

/* Doubly Linked List Section */

typedef struct __lda_dllnode__
{
    void *_nodeState;
    void *_nodeData;
    struct __lda_dllnode__ *_prevNode;
    struct __lda_dllnode__ *_nextNode;
}LDA_DLLNode;
typedef struct __lda_dll__
{
    void *_dllstate;
    LDA_DLLNode *_firstNode;
    LDA_DLLNode *_lastNode;
}LDA_DLL;

LDA_ReturnCodes LDA_CreateDLL(void *state, LDA_DLL **listResult, bool (*OnSLLCreated)(LDA_DLL *sll));
LDA_ReturnCodes LDA_CreateDLLNode(void *state, void *data, LDA_DLLNode **nodeResult, bool (*OnSLLNodeCreated)(LDA_DLLNode *node));
LDA_ReturnCodes LDA_DLLAddAtStart();
LDA_ReturnCodes LDA_DLLAddAtEnd();
LDA_ReturnCodes LDA_DLLAddAtIndex();
LDA_ReturnCodes LDA_DLLRemoveAtStart();
LDA_ReturnCodes LDA_DLLRemoveAtEnd();
LDA_ReturnCodes LDA_DLLRemoveAtIndex();
LDA_ReturnCodes LDA_DLLPeekStart();
LDA_ReturnCodes LDA_DLLPeekEnd();
LDA_ReturnCodes LDA_DLLPeekIndex();
LDA_ReturnCodes LDA_DLLClear();
LDA_ReturnCodes LDA_DLLDelete();

#endif /* LDA_C_DATASTRUCTURES_LIST_INCLUDED */