#pragma once
#include <afx.h>
class CBaseObj : public CObject
{
public:
	CBaseObj();               // construction 
	~CBaseObj();              // destruction
	DECLARE_SERIAL(CBaseObj);

	virtual void Serialize(CArchive& ar);
};

