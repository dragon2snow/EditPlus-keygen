/*
 * File name : copy_to_clipboard.c
 * API description : Copy a string to clipboard.
 * Author : wxx9248
 */

#include <windows.h>
#include <string.h>

BOOL copy_to_clipboard(char *content)
{
	HGLOBAL hMemory;
	LPTSTR lpMemory;
	int contentSize = strlen(content) + 1;

	if (!OpenClipboard(NULL))
		return FALSE;

	if (!EmptyClipboard())
	{
		CloseClipboard();
		return FALSE;
	}

	if ((hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize)) == NULL)	// Allocating memory
	{
		CloseClipboard();
		return FALSE;
	}

	if ((lpMemory = (LPTSTR)GlobalLock(hMemory)) == NULL)	// Locking down the clipboard mem
	{
		CloseClipboard();
		return FALSE;
	}

	memcpy_s(lpMemory, contentSize, content, contentSize);	// Copying data to clipboard

	GlobalUnlock(hMemory);	// Unlock the clipboard mem

	if (SetClipboardData(CF_TEXT, hMemory) == NULL)
	{
		CloseClipboard();
		return FALSE;
	}

	return TRUE;
}