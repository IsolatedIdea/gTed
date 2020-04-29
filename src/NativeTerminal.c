/**
 * Description: Bindings and interaction based of of v100 terminal codes.
 *
 * Author: Graeme Tinsdale
 *
 * Version: v1.0.0
 *
 * Change Log:
  v1.0.0
 **/

#include <ctype.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>

#include "Definitions.h"

struct native_editor_state
{
	int screenrows;
	int screencols;
	
	struct termios orig_termios;
};

struct native_editor_state E;

//----------------------------------------------------------------------Die(...)
void Die(const char *s)
{
	perror(s);
	exit(1);
}//Die(...) ends


//-----------------------------------------------------------DisableRawMode(...)
void DisableRawMode()
{
	write(STDOUT_FILENO, ESC_2J, 4);
	write(STDOUT_FILENO, ESC_H, 3);
	
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
	{
		Die("tcsetattr");
	}
}//DisableRawMode(...) ends


//------------------------------------------------------------EnableRawMode(...)
void EnableRawMode()
{
	if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)
	{
		Die("tcgetattr");
	}

	atexit(DisableRawMode);
	
	struct termios raw = E.orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag &= ~(CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		Die("tcsetattr");
	}
}//EnableRawMode(...) end


//------------------------------------------------------------------ReadKey(...)
char ReadKey()
{
	int nread;
	char c;
	while((nread = read(STDIN_FILENO, &c, 1)) != 1)
	{
		if(nread == -1 && errno != EAGAIN)
		{
			Die("read");
		}
	}
	return c;
}//ReadKey(...) ends


//--------------------------------------------------------GetCursorPosition(...)
void GetCursorPosition()
{
	if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
	{
		Die("GetCursorPosition");
	}

	char buf[32];
	unsigned int i = 0;

	while(i < sizeof(buf) - 1)
	{
		if(read(STDIN_FILENO, &buf[i], 1) != 1)
		{
			break;
		}
		if(buf[i] == 'R')
		{
			break;
		}
		i++;
	}
	buf[i] = '\0';

	if(buf[0] != '\x1b' || buf[1] != '[')
	{
		Die("GetCursorPosition");
	}
	if(sscanf(&buf[2], "%d;%d", &E.screenrows, &E.screencols) != 2)
	{
		Die("GetCursorPosition");
	}		
}//GetCursorPosition(...) ends


//------------------------------------------------------------GetWindowSize(...)
void GetWindowSize()
{
	struct winsize ws;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
		{
			Die("GetWindowSize");
		}
		GetCursorPosition();
	}
	else
	{
		E.screencols = ws.ws_col;
		E.screenrows = ws.ws_row;
	}
}// GetWindowSize(...) Ends


//---------------------------------------------------------------NativeInit(...)
void NativeInit()
{
	EnableRawMode();
	GetWindowSize();
}//NativeInit(...) ends


//-----------------------------------------------------------------DrawRows(...)
void DrawRows(struct line_buffer buffer)
{
	for(int i = 0; i < E.screenrows; ++i)
	{
		Append(buffer, "~", 1);

		// Handle last line
		if(i < E.screenrows - 1)
		{
			Append(buffer, SC_CR_NL, 2);
		}
	}
}//DrawRows(...) Ends


//------------------------------------------------------------RefreshScreen(...)
void RefreshScreen()
{
	write(STDOUT_FILENO, ESC_2J, 4);
	write(STDOUT_FILENO, ESC_H, 3);

	DrawRows(E);

	write(STDIN_FILENO, ESC_H, 3);
}//RefreshScreen(...) Ends
