#ifndef LDA_C_ANSIESCAPECODES_INCLUDED
#define LDA_C_ANSIESCAPECODES_INCLUDED

typedef enum
{
    LDA_AnsiClearFromCursorToEnd,
    LDA_AnsiClearFromCursorToBeginning,
    LDA_AnsiClearEntire,
    LDA_AnsiClearEntireAndRestart,
}LDA_AnsiClearOptions;

void LDA_AnsiCursorUp(unsigned int times);
void LDA_AnsiCursorDown(unsigned int times);
void LDA_AnsiCursorForward(unsigned int times);
void LDA_AnsiCursorBack(unsigned int times);
void LDA_AnsiCursorNextLine(unsigned int lines);
void LDA_AnsiCursorPreviousLine(unsigned int lines);
void LDA_AnsiCursorToColumn(unsigned int column);
void LDA_AnsiCursorGoToXY(unsigned int x, unsigned int y);
void LDA_AnsiClearScreen(LDA_AnsiClearOptions option);
void LDA_AnsiClearLine(LDA_AnsiClearOptions option);
void LDA_AnsiScrollUp(unsigned int lines);
void LDA_AnsiScrollDown(unsigned int lines);
void LDA_AnsiHideCursor();
void LDA_AnsiShowCursor();
void LDA_AnsiResetVisualStyle();

#endif /* LDA_C_ANSIESCAPECODES_INCLUDED */