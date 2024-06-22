// Global.cpp: implementation of the Global class.
//
//////////////////////////////////////////////////////////////////////
#include "../stdafx.h"
#include "Global.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Global::Global()
{

}

Global::~Global()
{

}
COLORREF InvertColor(COLORREF color) 
{
	return RGB(~GetRValue(color), ~GetGValue(color), ~GetBValue(color));
}

BOOL copy_File_To_ProFlies(char *sourcePath, char *taggetPath, int fileType)
{
	switch (fileType)
	{
		case BACK_PIC:
			CopyFile(sourcePath, taggetPath, FALSE);
			break;
		default:
			break;
	}
	return TRUE;
}