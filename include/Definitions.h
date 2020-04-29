#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Macros
#define CTRL_KEY(K) ((K) & 0x1f)
#define LINE_BUFFER_INIT {NULL, 0}

// V100 Escape Sequences
#define ESC_2J "\x1b[2J" // Clear the screen
#define ESC_H "\x1b[H" // Position cursor at top left

// Shortcuts
#define SC_CR_NL "\r\n"

#endif // DEFINITIONS_H
