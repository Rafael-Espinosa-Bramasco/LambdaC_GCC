#ifndef LDA_C_DATASTRUCTURES_STACK_INCLUDED
#define LDA_C_DATASTRUCTURES_STACK_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

#include <LDA/LDA_StatusCodes.h>

typedef struct __lda_stacknode__
{
    void *_nodestate;
    void *_nodedata;
    struct __lda_stacknode__ *_nextnode;
}LDA_StackNode;
typedef struct
{
    void *_stackstate;
    LDA_StackNode *_stacktop;
}LDA_Stack;

LDA_ReturnCodes LDA_CreateStack(void *stackstate, LDA_Stack **stackResult, bool (*OnStackCreated)(LDA_Stack *stack));
LDA_ReturnCodes LDA_CreateStackNode(void *nodestate, void *nodedata, LDA_StackNode **nodeResult, bool (*OnStackNodeCreated)(LDA_StackNode *node));
LDA_ReturnCodes LDA_StackPush(LDA_StackNode *node, LDA_Stack *stack, bool (*ToStackPush)(LDA_StackNode *node, LDA_Stack *stack), bool (*OnStackPush)(LDA_StackNode *node, LDA_Stack *stack));
LDA_ReturnCodes LDA_StackPop(LDA_Stack *stack, LDA_StackNode **stackNodePopped, bool (*ToStackPop)(LDA_StackNode *node, LDA_Stack *stack), bool (*OnStackPop)(LDA_StackNode *node, LDA_Stack *stack));
LDA_ReturnCodes LDA_StackPeek(LDA_Stack *stack, LDA_StackNode **nodeResult);
bool LDA_StackIsEmpty(LDA_Stack *stack);
LDA_ReturnCodes LDA_StackClear(LDA_Stack *stack, bool (*OnNodeCleared)(LDA_StackNode *node), bool (OnStackCleared)(LDA_Stack *stack));
LDA_ReturnCodes LDA_StackDelete(LDA_Stack **stack, bool (*OnNodeCleared)(LDA_StackNode *node), bool (OnStackCleared)(LDA_Stack *stack));

#endif /* LDA_C_DATASTRUCTURES_STACK_INCLUDED */