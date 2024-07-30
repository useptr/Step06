// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include <functional>
#include "ADSKEmployee.h"
#include "EmployeeBuilder.h"
#include "Tchar.h"
//-----------------------------------------------------------------------------
#define szRDS _RXST("ADSK")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CS6App : public AcRxArxApp {

public:
	CS6App () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here
		AcRxObject* pSvc;
		if (!(pSvc = acrxServiceDictionary->at(ASDKEMPLOYEE_DBXSERVICE)))
		{
			// Try to load the module, if it is not yet present 
			if (!acrxDynamicLinker->loadModule(_T("ADSKEmployee.dbx"), 0))
			{
				acutPrintf(_T("Unable to load ADSKEmployee.dbx. Unloading this application...\n"));
				return (AcRx::kRetError);
			}
		}

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
	static void AdskS6_CREATEEMPLOYEE(void)
	{
		int nId, nCube;
		TCHAR szFirstName[128];
		TCHAR szLastName[128];
		AcGePoint3d pt;
		if (acedGetInt(_T("Enter employee ID: "), &nId) != RTNORM
			|| acedGetInt(_T("Enter cube: "), &nCube) != RTNORM
			|| acedGetString(0, _T("Enter first name: "), szFirstName) != RTNORM
			|| acedGetString(0, _T("Enter last name: "), szLastName) != RTNORM
			|| acedGetPoint(NULL, _T("Employee position: "), asDblArray(pt)) != RTNORM
			) {
			return;
		}
		AcDbBlockTableRecordPointer pSpaceBlockTableRecord(acdbHostApplicationServices()->workingDatabase()->currentSpaceId(), AcDb::kForWrite);
		if (pSpaceBlockTableRecord.openStatus() != Acad::eOk) {
			acutPrintf(_T("\nERROR: Cannot open BlockTableRecord for write"));
			return;
		}
		AcDbObjectPointer<ADSKEmployee> pEmployee = std::move(ADSKEmployee::create(szFirstName).withLastName(szLastName).withID(nId).withCube(nCube)); // TODO improve
		AcDbObjectId idObj;
		if (pSpaceBlockTableRecord->appendAcDbEntity(idObj, pEmployee) != Acad::eOk) {
			acutPrintf(_T("ERROR: Cannot append ADSKEmployee to BlockTable"));
			return;
		}
	}
	
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CS6App)

ACED_ARXCOMMAND_ENTRY_AUTO(CS6App, AdskS6, _CREATEEMPLOYEE, CREATEEMPLOYEE, ACRX_CMD_TRANSPARENT, NULL)

