#include <LDA/DataStructures/LDA_Stack.h>

LDA_ReturnCodes LDA_CreateStack(void *stackstate, LDA_Stack **stackResult, bool (*OnStackCreated)(LDA_Stack *stack))
{
    if(!stackResult)
    {
        return LDA_MainStructureParameterResultIsNULL;
    }
    LDA_Stack *newstack = malloc(sizeof(LDA_Stack));
    if(!newstack)
    {
        return LDA_ItemNotCreated;
    }
    newstack->_stackstate = stackstate;
    newstack->_stacktop = NULL;
    if(OnStackCreated)
    {
        if(!OnStackCreated(newstack))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    *stackResult = newstack;
    return LDA_Success;
}
LDA_ReturnCodes LDA_CreateStackNode(void *nodestate, void *nodedata, LDA_StackNode **nodeResult, bool (*OnStackNodeCreated)(LDA_StackNode *node))
{
    if(!nodeResult)
    {
        return LDA_NodeStructureParameterResultIsNULL;
    }
    LDA_StackNode *newnode = malloc(sizeof(LDA_StackNode));
    if(!newnode)
    {
        return LDA_ItemNotCreated;
    }
    newnode->_nodestate = nodestate;
    newnode->_nodedata = nodedata;
    newnode->_nextnode = NULL;
    if(OnStackNodeCreated)
    {
        if(!OnStackNodeCreated(newnode))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    *nodeResult = newnode;
    return LDA_Success;
}
LDA_ReturnCodes LDA_StackPush(LDA_StackNode *node, LDA_Stack *stack, bool (*ToStackPush)(LDA_StackNode *node, LDA_Stack *stack), bool (*OnStackPush)(LDA_StackNode *node, LDA_Stack *stack))
{
    if(!stack)
    {
        return LDA_MainStructureParameterIsNULL;
    }
    if(!node)
    {
        return LDA_NodeStructureParameterIsNULL;
    }
    if(ToStackPush)
    {
        if(!ToStackPush(node,stack))
        {
            return LDA_PreActionCallbackFunctionFailed;
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
    if(OnStackPush)
    {
        if(!OnStackPush(node,stack))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    return LDA_Success;
}
LDA_ReturnCodes LDA_StackPop(LDA_Stack *stack, LDA_StackNode **stackNodePopped, bool (*ToStackPop)(LDA_StackNode *node, LDA_Stack *stack), bool (*OnStackPop)(LDA_StackNode *node, LDA_Stack *stack))
{
    if(!stack)
    {
        return LDA_MainStructureParameterIsNULL;
    }
    if(!stackNodePopped)
    {
        return LDA_NodeStructureParameterResultIsNULL;
    }
    LDA_StackNode *auxnode = stack->_stacktop;
    if(ToStackPop)
    {
        if(!ToStackPop(auxnode,stack))
        {
            return LDA_PreActionCallbackFunctionFailed;
        }
    }
    if(!stack->_stacktop)
    {
        stack->_stacktop = auxnode->_nextnode;
        auxnode->_nextnode = NULL;
    }
    if(OnStackPop)
    {
        if(!OnStackPop(auxnode,stack))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    *stackNodePopped = auxnode;
    return LDA_Success;
}
LDA_ReturnCodes LDA_StackPeek(LDA_Stack *stack, LDA_StackNode **nodeResult)
{
    if(!stack)
    {
        return LDA_MainStructureParameterIsNULL;
    }
    if(!nodeResult)
    {
        return LDA_NodeStructureParameterResultIsNULL;
    }
    *nodeResult = stack->_stacktop;
    return LDA_Success;
}
bool LDA_StackIsEmpty(LDA_Stack *stack)
{
    if(!stack)
    {
        return false;
    }
    return stack->_stacktop == NULL;
}
LDA_ReturnCodes LDA_StackClear(LDA_Stack *stack, bool (*OnNodeCleared)(LDA_StackNode *node), bool (OnStackCleared)(LDA_Stack *stack))
{
    if(!stack)
    {
        return LDA_MainStructureParameterIsNULL;
    }
    LDA_StackNode *aux;
    LDA_ReturnCodes popResult;
    while(stack->_stacktop != NULL)
    {
        popResult  = LDA_StackPop(stack,&aux,NULL,NULL);
        if(popResult != LDA_Success)
        {
            return popResult;
        }
        if(OnNodeCleared)
        {
            if(!OnNodeCleared(aux))
            {
                return LDA_PreActionCallbackFunctionFailed;
            }
        }
        free(aux);
    }
    if(OnStackCleared)
    {
        if(!OnStackCleared(stack))
        {
            return LDA_PostActionCallbackFunctionFailed;
        }
    }
    return LDA_Success;
}
LDA_ReturnCodes LDA_StackDelete(LDA_Stack **stack, bool (*OnNodeCleared)(LDA_StackNode *node), bool (OnStackCleared)(LDA_Stack *stack))
{
    LDA_ReturnCodes clearResult = LDA_StackClear(*stack, OnNodeCleared,OnStackCleared);
    if(clearResult != LDA_Success)
    {
        return clearResult;
    }
    free(*stack);
    return LDA_Success;
}