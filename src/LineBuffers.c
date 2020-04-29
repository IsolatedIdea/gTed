/**
 * Description:
 * Contains the structs, data, and functions for the line buffer system.
 * 
 * Author:
 * Graeme Tinsdale
 *
 * Version:
 * v1.0.0
 **/

#include <string.h>
#include <stdlib.h>


struct line_buffer
{
	char *b;
	int len;
};


//-------------------------------------------------------------------Append(...)
void Append(struct line_buffer *buffer, const char *s, int len)
{
	char *new  = realloc(buffer->b, buffer->len + len);

	if(new == NULL)
	{
		return;
	}

	memcpy(&new[buffer->len], s, len);
	buffer->b = new;
	buffer->len += len;
}//Append(...) ends

//------------------------------------------------------------------FreeBuffer()
void FreeBuffer(struct line_buffer *buffer)
{
	free(buffer->b);
}// FreeBuffer(...) ends
