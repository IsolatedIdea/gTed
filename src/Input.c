/**
 * Description:
 * Input control functions for gTed
 *
 * Author:
 * Graeme Tinsdale
 * Version:
 * v1.0.0
 **/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "Definitions.h"
#include "NativeTerminal.h"

//-----------------------------------------------------------ProcessKeypress(..)
void ProcessKeypress()
{
	char c = ReadKey();
	switch(c)
	{
		case CTRL_KEY('q'):
		{
			write(STDOUT_FILENO, ESC_2J, 4);
			write(STDOUT_FILENO, ESC_H, 3);
			exit(0);
		}
		break;
	}
}//ProcessKeypress(...) ends
