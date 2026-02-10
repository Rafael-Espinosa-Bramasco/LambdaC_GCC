#ifndef LDA_C_DATASTRUCTURES_STACK_INCLUDED
#define LDA_C_DATASTRUCTURES_STACK_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

/*
    @brief Stack return codes for functions. The values may vary but LDA_StackSuccess will be 0 always.
*/
typedef enum
{
    LDA_StackSuccess,

    LDA_StackNotCreated,
    LDA_StackResultIsNull,

    LDA_StackNodeNotCreated,
    LDA_StackNodeResultIsNull,
    LDA_StackNodePoppedIsNull,

    LDA_StackNodeIsNull,
    LDA_StackIsNull,

    LDA_OnStackNodeCreatedFailed,
    LDA_OnStackCreatedFailed,
    LDA_OnStackPushFailed,
    LDA_OnStackPopFailed,
    LDA_OnNodeCleanedFailed,
    LDA_OnStackCleanedFailed,
}LDA_StackCode;
/*
    @brief Stack node type, this structure holds the main data/information.
*/
typedef struct __lda_stacknode__
{
    void *_nodestate;
    void *_nodedata;
    struct __lda_stacknode__ *_nextnode;
}LDA_StackNode;
/*
    @brief Stack type, this structure hols the stack top and general information for the stack.
*/
typedef struct
{
    void *_stackstate;
    LDA_StackNode *_stacktop;
}LDA_Stack;
/*
    @brief Creates a Stack

    @param stackstate void * type. This can be anything you want to save. This could be a struct, union, integer, bool, etc.
    @param stackResult LDA_Stack ** type. This pointer will save the created stack, you need to pass the address of the pointer, for example LDA_CreateStack(NULL, &myPointerToStack, NULL).
    @param OnStackCreated Callback function. This function is called once the stack is created and initialized.

    @retval LDA_StackSuccess if all the process went as planned
    @retval LDA_StackResultIsNull if the pointer where the stack is supposed to be saved is NULL.
    @retval LDA_StackNotCreated if the system memory allocation function failed.
    @retval LDA_OnStackCreatedFailed if the OnStackCreated callback function returned false (user defined). This return value just means that the callback function failed, but the stack is still created.

    All the return values aside of LDA_StackSuccess means the stack creation failed, however the LDA_OnStackCreatedFailed return value actually means the stack is created but the callback function returned false due to user defined behavior
*/
LDA_StackCode LDA_CreateStack(void *stackstate, LDA_Stack **stackResult, bool (*OnStackCreated)(LDA_Stack *stack));
/*
    @brief Creates a Stack Node

    @param nodestate void * type - Pointer to anything you want to save as a state in the node.
    @param nodedata void * type - Pointer to anything you want to save as the data in the node.
    @param nodeResult LDA_StackNode ** type. This pointer will save the created node, you need to pass the address of the pointer.
    @param OnStackNodeCreated Callback function. This function is called once the node is created and initialized.

    @retval LDA_StackSuccess if all the process went as planned.
    @retval LDA_StackNodeResultIsNull if the pointer where the node is supposed to be saved is NULL.
    @retval LDA_StackNodeNotCreated if the system memory allocation function failed.
    @retval LDA_OnStackNodeCreatedFailed if the OnStackNodeCreated callback function returned false (user defined).
*/
LDA_StackCode LDA_CreateStackNode(void *nodestate, void *nodedata, LDA_StackNode **nodeResult, bool (*OnStackNodeCreated)(LDA_StackNode *node));
/*
    @brief Pushes a node to a stack

    @param node LDA_StackNode * type. The stack node about to get pushed into some stack.
    @param stack LDA_Stack * type. The stack where the node is going to be pushed.
    @param OnStackPush Callback function. This function is called before the pushing the node. If the return value of this function is false, the push function is skipped.

    @retval LDA_StackSuccess if all went as planned.
    @retval LDA_StackIsNull if the stack passed as parameter is NULL.
    @retval LDA_StackNodeIsNull if the stack node passed as parameter is NULL.
    @retval LDA_OnStackPushFailed if the OnStackPush callback function failed (returned false). This is user defined behavior.
*/
LDA_StackCode LDA_StackPush(LDA_StackNode *node, LDA_Stack *stack, bool (*OnStackPush)(LDA_StackNode *node, LDA_Stack *stack));
/*
    @brief Pop the node at the top of the stack

    @param stack LDA_Stack * type. The stack where the node is going to be popped.
    @param stackNodePopped LDA_StackNode ** type. The pointer to a pointer where the popped node is going to be saved.
    @param OnStackPop Callback function. This function is called before popping the node.

    @retval LDA_StackSuccess if all went as planned.
    @retval LDA_StackIsNull if the stack parameter is NULL.
    @retval LDA_StackNodePoppedIsNull if the pointer to a pointer where the popped node is going to be saved is NULL.
    @retval LDA_OnStackPopFailed if the OnStackPop callback function returned false. User defined behavior.
*/
LDA_StackCode LDA_StackPop(LDA_Stack *stack, LDA_StackNode **stackNodePopped, bool (*OnStackPop)(LDA_StackNode *node, LDA_Stack *stack));
/*
    @brief Peek the top of the stack

    @param stack LDA_Stack * type. The stack to peek.
    @param nodeResult LDA_StackNode ** type. Pointer to a pointer where the peeked node is going to be saved.

    @retval LDA_StackSuccess if all went as planned.
    @retval LDA_StackIsNull if the stack parameter is NULL.
    @retval LDA_StackNodeResultIsNull if the pointer to a pointer is NULL.
*/
LDA_StackCode LDA_StackPeek(LDA_Stack *stack, LDA_StackNode **nodeResult);
/*
    @brief Check if the stack is empty

    @param stack LDA_Stack * type. The stack to verify.

    @return true if the stack is empty, false otherwise.
*/
bool LDA_StackIsEmpty(LDA_Stack *stack);
/*
    @brief Clear the stack

    @param stack LDA_Stack * type. The stack to be cleaned.
    @param OnNodeCleaned Callback function. This function is called before freeing the memory for the node.
    @param OnStackCleaned Callback function. This function is called once the stack is empty again.

    @retval LDA_StackSuccess if all went as planned.
    @retval LDA_StackIsNull if the stack parameter is NULL.
    @retval LDA_OnNodeCleanedFailed if the OnNodeCleaned callback function returned false. User defined behavior.
    @retval LDA_OnStackCleanedFailed if the OnStackCleaned callback function returned false. User defined behavior.

    This function removes all the stack nodes but the stack head remains
*/
LDA_StackCode LDA_StackClear(LDA_Stack *stack, bool (*OnNodeCleaned)(LDA_StackNode *node), bool (OnStackCleaned)(LDA_Stack *stack));
/*
    @brief Delete the stack

    This function implements LDA_StackClear to clear all the nodes, and the free function to delete the Stack itself.

    @param stack Pointer to a pointer where the stack to be deleted (by free(stack)) is stored.
    @param OnNodeCleaned Callback function. This function is passed to LDA_StackClear.
    @param OnStackCleaned Callback function. This function is passed to LDA_StackClear. This is the last callback function called. Use this to free memory before the lambda library release the memory of the stack.

    @retval LDA_StackSuccess if all went as planned.
    @retval (Other code) this error is the return code returned by LDA_StackClear function.
*/
LDA_StackCode LDA_StackDelete(LDA_Stack **stack, bool (*OnNodeCleaned)(LDA_StackNode *node), bool (OnStackCleaned)(LDA_Stack *stack));

#endif /* LDA_C_DATASTRUCTURES_STACK_INCLUDED */