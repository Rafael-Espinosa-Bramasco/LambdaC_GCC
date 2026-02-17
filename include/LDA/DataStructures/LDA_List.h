#ifndef LDA_C_DATASTRUCTURES_LIST_INCLUDED
#define LDA_C_DATASTRUCTURES_LIST_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    LDA_ListSuccess,
    LDA_ListNodeIsNull,
    LDA_ListIsNull,

    LDA_ListResultIsNull,
    LDA_ListNodeResultIsNull,

    LDA_ListNotCreated,
    LDA_ListNodeNotCreated,
    LDA_ListIndexIsOutOfRange,

    LDA_OnListCreatedFailed,
    LDA_OnListNodeCreatedFailed,
    LDA_OnListNodeAddedFailed,
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

//

#endif /* LDA_C_DATASTRUCTURES_LIST_INCLUDED */