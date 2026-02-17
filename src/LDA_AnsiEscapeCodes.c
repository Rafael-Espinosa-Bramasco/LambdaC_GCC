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
void LDA_AnsiHideCursor(void)
{
    printf("\033[?25l");
}
void LDA_AnsiShowCursor(void)
{
    printf("\033[?25h");
}
void LDA_AnsiResetVisualStyle(void)
{
    printf("\033[0m");
}
void LDA_AnsiSetFontBolt(void)
{
    printf("\033[1m");
}
void LDA_AnsiSetFontFaint(void)
{
    printf("\033[2m");
}
void LDA_AnsiSetFontItalic(void)
{
    printf("\033[3m");
}
void LDA_AnsiSetFontUnderline(void)
{
    printf("\033[4m");
}
void LDA_AnsiSetFontNormalIntensity(void)
{
    printf("\033[22m");
}
void LDA_AnsiSetFontNotItalic(void)
{
    printf("\033[23m");
}
void LDA_AnsiSetFontNotUnderline(void)
{
    printf("\033[24m");
}
void LDA_AnsiSetFontColor(LDA_AnsiColorOptions colorOption)
{
    printf("\033[%im",colorOption);
}
void LDA_AnsiSetFontColorRGB(unsigned char r, unsigned char g, unsigned char b)
{
    printf("\033[38;2;%i;%i;%im",r,g,b);
}
void LDA_AnsiResetFontColor(void)
{
    printf("\033[39m");
}
void LDA_AnsiSetBackgroundColor(LDA_AnsiColorOptions colorOption)
{
    printf("\033[%im",colorOption+10);
}
void LDA_AnsiSetBackgroundColorRGB(unsigned char r, unsigned char g, unsigned char b)
{
    printf("\033[48;2;%i;%i;%im",r,g,b);
}
void LDA_AnsiResetBackgroundColor(void)
{
    printf("\033[49m");
}
void LDA_AnsiInvertVideoStyle(void)
{
    printf("\033[7m");
}