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
#include "ADSKEmployee.h"
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
			if (!acrxDynamicLinker->loadModule(_T("AsdkEmployee.dbx"), 0))
			{
				acutPrintf(_T("Unable to load AsdkEmployeeDetails.dbx. Unloading this application...\n"));
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
		int id, cube;
		TCHAR firstName[128];
		TCHAR lastName[128];
		AcGePoint3d pt;
		if (acedGetInt(_T("Enter employee ID: "), &id) != RTNORM
			|| acedGetInt(_T("Enter cube: "), &cube) != RTNORM
			|| acedGetString(0, _T("Enter first name: "), firstName) != RTNORM
			|| acedGetString(0, _T("Enter last name: "), lastName) != RTNORM
			|| acedGetPoint(NULL, _T("Employee position: "), asDblArray(pt)) != RTNORM
			) {
			return;
		}
		AcDbBlockTable* pBlockTable;
		if (acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable) != Acad::eOk) {
			acutPrintf(_T("ERROR: Cannot open AcDbBlockTable"));
			return;
		}
		AcDbBlockTableRecord* pSpaceBlockTableRecord;
		if (pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceBlockTableRecord, AcDb::kForWrite) != Acad::eOk) {
			pBlockTable->close();
			acutPrintf(_T("ERROR: Cannot open AcDbBlockTable for write"));
			return;
		}
		pBlockTable->close();
		//ADSKEmployee* pEmployee = ADSKEmployee::create(firstName).withLastName(lastName).withID(id).withCube(cube).build();
		ADSKEmployee* pEmployee = new ADSKEmployee;
		pEmployee->setID(id);
		pEmployee->setCube(cube);
		pEmployee->setFirstName(firstName);
		pEmployee->setLastName(lastName);

		AcDbObjectId idObj;
		if (pSpaceBlockTableRecord->appendAcDbEntity(idObj, pEmployee) != Acad::eOk) {
			delete pEmployee;
			pSpaceBlockTableRecord->close();
			acutPrintf(_T("ERROR: Cannot appendAcDbEntity to AcDbBlockTableRecord"));
			return;
		}
		pEmployee->close();
		pSpaceBlockTableRecord->close();

	}
	
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CS6App)

ACED_ARXCOMMAND_ENTRY_AUTO(CS6App, AdskS6, _CREATEEMPLOYEE, CREATEEMPLOYEE, ACRX_CMD_TRANSPARENT, NULL)

