#include <LDA/LDA_AnsiEscapeCodes.h>

#include <stdio.h>

void LDA_AnsiCursorUp(unsigned int times)
{
    printf("\033[%iA",times);
}
void LDA_AnsiCursorDown(unsigned int times)
{
    printf("\033[%iB",times);
}
void LDA_AnsiCursorForward(unsigned int times)
{
    printf("\033[%iC",times);
}
void LDA_AnsiCursorBack(unsigned int times)
{
    printf("\033[%iD",times);
}
void LDA_AnsiCursorNextLine(unsigned int lines)
{
    printf("\033[%iE",lines);
}
void LDA_AnsiCursorPreviousLine(unsigned int lines)
{
    printf("\033[%iF", lines);
}
void LDA_AnsiCursorToColumn(unsigned int column)
{
    printf("\033[%iG",column);
}
void LDA_AnsiCursorGoToXY(unsigned int x, unsigned int y)
{
    printf("\033[%i;%iH",y,x);
}
void LDA_AnsiClearScreen(LDA_AnsiClearOptions option)
{
    printf("\033[%iJ", option);
}
void LDA_AnsiClearLine(LDA_AnsiClearOptions option)
{
    printf("\033[%iK",option);
    if(option == LDA_AnsiClearEntireAndRestart)
    {
        LDA_CursorToColumn(1);
    }
}
void LDA_AnsiScrollUp(unsigned int lines)
{
    printf("\033[%iS",lines);
}
void LDA_AnsiScrollDown(unsigned int lines)
{
    printf("\033[%iT",lines);
}
void LDA_AnsiHideCursor()
{
    printf("\033[?25l");
}
void LDA_AnsiShowCursor()
{
    printf("\033[?25h");
}
void LDA_AnsiResetVisualStyle()
{
    printf("\033[0m");
}