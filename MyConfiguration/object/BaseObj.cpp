#include "BaseObj.h"

IMPLEMENT_SERIAL(CBaseObj, CObject, 1)
CBaseObj::CBaseObj()
{
	 
}

CBaseObj::~CBaseObj()
{
	 
}
void CBaseObj::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) 
	{
		
	}
	else 
	{
		
	}
}