/**
 * Description: A general text editor based on the tutorial from snaptoken
 *
 * Author: Graeme Tinsdale
 *
 * Version: 0.0.1
 *
 * Change Log:
 * v0.0.1
 */

#include "Definitions.h"
#include "NativeTerminal.h"
#include "Input.h"


//---------------------------------------------------------------------main(...)
int main(int argc, char **argv)
{
	NativeInit();

	while(1)
	{
		RefreshScreen();
		ProcessKeypress();
	}
	return 0;
}//main(..._ ends
