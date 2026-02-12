#include <LDA/DataStructures/LDA_Stack.h>

LDA_StackCode LDA_CreateStack(void *stackstate, LDA_Stack **stackResult, bool (*OnStackCreated)(LDA_Stack *stack))
{
    if(!stackResult)
    {
        return LDA_StackResultIsNull;
    }
    LDA_Stack *newstack = malloc(sizeof(LDA_Stack));
    if(!newstack)
    {
        return LDA_StackNotCreated;
    }
    newstack->_stackstate = stackstate;
    newstack->_stacktop = NULL;
    if(OnStackCreated)
    {
        if(!OnStackCreated(newstack))
        {
            return LDA_OnStackCreatedFailed;
        }
    }
    *stackResult = newstack;
    return LDA_StackSuccess;
}
LDA_StackCode LDA_CreateStackNode(void *nodestate, void *nodedata, LDA_StackNode **nodeResult, bool (*OnStackNodeCreated)(LDA_StackNode *node))
{
    if(!nodeResult)
    {
        return LDA_StackNodeResultIsNull;
    }
    LDA_StackNode *newnode = malloc(sizeof(LDA_StackNode));
    if(!newnode)
    {
        return LDA_StackNodeNotCreated;
    }
    newnode->_nodestate = nodestate;
    newnode->_nodedata = nodedata;
    newnode->_nextnode = NULL;
    if(OnStackNodeCreated)
    {
        if(!OnStackNodeCreated(newnode))
        {
            return LDA_OnStackNodeCreatedFailed;
        }
    }
    *nodeResult = newnode;
    return LDA_StackSuccess;
}
LDA_StackCode LDA_StackPush(LDA_StackNode *node, LDA_Stack *stack, bool (*OnStackPush)(LDA_StackNode *node, LDA_Stack *stack))
{
    if(!stack)
    {
        return LDA_StackIsNull;
    }
    if(!node)
    {
        return LDA_StackNodeIsNull;
    }
    if(OnStackPush)
    {
        if(!OnStackPush(node,stack))
        {
            return LDA_OnStackPushFailed;
        }
    }
    if(stack->_stacktop == NULL)
    {
        stack->_stacktop = node;
    }else
    {
        node->_nextnode = stack->_stacktop;
        stack->_stacktop = node;
    }
    return LDA_StackSuccess;
}
LDA_StackCode LDA_StackPop(LDA_Stack *stack, LDA_StackNode **stackNodePopped, bool (*OnStackPop)(LDA_StackNode *node, LDA_Stack *stack))
{
    if(!stack)
    {
        return LDA_StackIsNull;
    }
    if(!stackNodePopped)
    {
        return LDA_StackNodePoppedIsNull;
    }
    LDA_StackNode *auxnode = stack->_stacktop;
    if(OnStackPop)
    {
        if(!OnStackPop(stack,auxnode))
        {
            return LDA_OnStackPopFailed;
        }
    }
    if(!stack->_stacktop == NULL)
    {
        stack->_stacktop = auxnode->_nextnode;
        auxnode->_nextnode = NULL;
    }
    *stackNodePopped = auxnode;
    return LDA_StackSuccess;
}
LDA_StackCode LDA_StackPeek(LDA_Stack *stack, LDA_StackNode **nodeResult)
{
    if(!stack)
    {
        return LDA_StackIsNull;
    }
    if(!nodeResult)
    {
        return LDA_StackNodeResultIsNull;
    }
    *nodeResult = stack->_stacktop;
    return LDA_StackSuccess;
}
bool LDA_StackIsEmpty(LDA_Stack *stack)
{
    if(!stack)
    {
        return false;
    }
    return stack->_stacktop == NULL;
}
LDA_StackCode LDA_StackClear(LDA_Stack *stack, bool (*OnNodeCleared)(LDA_StackNode *node), bool (OnStackCleared)(LDA_Stack *stack))
{
    if(!stack)
    {
        return LDA_StackIsNull;
    }
    LDA_StackNode *aux;
    LDA_StackCode popResult;
    while(stack->_stacktop != NULL)
    {
        popResult  = LDA_StackPop(stack,&aux,NULL);
        if(popResult != LDA_StackSuccess)
        {
            return popResult;
        }
        if(OnNodeCleared)
        {
            if(!OnNodeCleaned(aux))
            {
                return LDA_OnStackNodeClearedFailed;
            }
        }
        free(aux);
    }
    if(OnStackCleared)
    {
        if(!OnStackCleaned(stack))
        {
            return LDA_OnStackClearedFailed;
        }
    }
    return LDA_StackSuccess;
}
LDA_StackCode LDA_StackDelete(LDA_Stack **stack, bool (*OnNodeCleared)(LDA_StackNode *node), bool (OnStackCleared)(LDA_Stack *stack))
{
    LDA_StackCode clearResult = LDA_StackClear(*stack, OnNodeCleared,OnStackCleared);
    if(clearResult != LDA_StackSuccess)
    {
        return clearResult;
    }
    free(*stack);
    return LDA_StackSuccess;
}