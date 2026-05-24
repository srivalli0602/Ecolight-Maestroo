//LCD.h
#include "types.h"
void write_lcd(u8 data);
void CmdLCD(u8 cmd);
void CharLCD(u8 ascii);
void Init_LCD(void);
void StrLCD(char *str);
void U32LCD(u32 n);
void S32LCD(u32 n);
void BuildCGRAM(u8 *p,u32 nbytes);
void F32LCD(f32 f,u8 ndp);
