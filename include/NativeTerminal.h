#ifndef NATIVE_TERMINAL_H
#define NATIVE_TERMINAL_H

void EnableRawMode();
void DisableRawMode();
char ReadKey();
void NativeInit();
void DrawRows();
void RefreshScreen();

#endif
