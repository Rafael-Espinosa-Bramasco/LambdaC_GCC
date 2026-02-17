#ifndef LDA_C_ANSIESCAPECODES_INCLUDED
#define LDA_C_ANSIESCAPECODES_INCLUDED

typedef enum
{
    LDA_AnsiClearFromCursorToEnd,
    LDA_AnsiClearFromCursorToBeginning,
    LDA_AnsiClearEntire,
    LDA_AnsiClearEntireAndRestart,
}LDA_AnsiClearOptions;
typedef enum
{
    LDA_AnsiColorBlack = 30,
    LDA_AnsiColorRed,
    LDA_AnsiColorGreen,
    LDA_AnsiColorYellow,
    LDA_AnsiColorBlue,
    LDA_AnsiColorMagenta,
    LDA_AnsiColorCyan,
    LDA_AnsiColorWhite,
}LDA_AnsiColorOptions;

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
void LDA_AnsiHideCursor(void);
void LDA_AnsiShowCursor(void);
void LDA_AnsiResetVisualStyle(void);
void LDA_AnsiSetFontBolt(void);
void LDA_AnsiSetFontFaint(void);
void LDA_AnsiSetFontItalic(void);
void LDA_AnsiSetFontUnderline(void);
void LDA_AnsiSetFontNormalIntensity(void);
void LDA_AnsiSetFontNotItalic(void);
void LDA_AnsiSetFontNotUnderline(void);
void LDA_AnsiSetFontColor(LDA_AnsiColorOptions colorOption);
void LDA_AnsiSetFontColorRGB(unsigned char r, unsigned char g, unsigned char b);
void LDA_AnsiResetFontColor(void);
void LDA_AnsiSetBackgroundColor(LDA_AnsiColorOptions colorOption);
void LDA_AnsiSetBackgroundColorRGB(unsigned char r, unsigned char g, unsigned char b);
void LDA_AnsiResetBackgroundColor(void);
void LDA_AnsiInvertVideoStyle(void);

#endif /* LDA_C_ANSIESCAPECODES_INCLUDED */