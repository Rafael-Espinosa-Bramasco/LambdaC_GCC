#ifndef LDA_C_STATUSCODES_INCLUDED
#define LDA_C_STATUSCODES_INCLUDED

typedef enum __lda_returncodes__
{
    LDA_Success,
    LDA_MainStructureParameterResultIsNULL,
    LDA_MainStructureParameterIsNULL,
    LDA_NodeStructureParameterIsNULL,
    LDA_NodeStructureParameterResultIsNULL,
    LDA_ItemNotCreated,
    LDA_PreActionCallbackFunctionFailed,
    LDA_PostActionCallbackFunctionFailed,
}LDA_ReturnCodes;

#endif /* LDA_C_STATUSCODES_INCLUDED */