// (C) Copyright 2002-2007 by Autodesk, Inc. 
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
//----- ADSKEmployee.cpp : Implementation of ADSKEmployee
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "ADSKEmployee.h"
#include "Tchar.h"
//-----------------------------------------------------------------------------
Adesk::UInt32 ADSKEmployee::kCurrentVersionNumber = 1;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS(
	ADSKEmployee, AcDbEllipse,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
	AcDbProxyEntity::kNoOperation, ADSKEMPLOYEE,
	ADSKEMPLOYEEAPP
	| Product Desc : A description for your object
	| Company : Your company name
	| WEB Address : Your company WEB site address
)

//-----------------------------------------------------------------------------
ADSKEmployee::ADSKEmployee() : AcDbEllipse(AcGePoint3d::kOrigin, AcGeVector3d::kZAxis, AcGeVector3d(1, 0, 0), 2), m_szFirstName(nullptr), m_szLastName(nullptr) {
}

ADSKEmployee::~ADSKEmployee() {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus ADSKEmployee::dwgOutFields(AcDbDwgFiler * pFiler) const {
	assertReadEnabled();
	//----- Save parent class information first.
	Acad::ErrorStatus es = AcDbEllipse::dwgOutFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be saved first
	if ((es = pFiler->writeUInt32(ADSKEmployee::kCurrentVersionNumber)) != Acad::eOk)
		return (es);
	//----- Output params
	pFiler->writeItem(m_nID);
	pFiler->writeItem(m_nCube);
	pFiler->writeItem(m_szFirstName);
	pFiler->writeItem(m_szLastName);

	return (pFiler->filerStatus());
}

Acad::ErrorStatus ADSKEmployee::dwgInFields(AcDbDwgFiler * pFiler) {
	assertWriteEnabled();
	//----- Read parent class information first.
	Acad::ErrorStatus es = AcDbEllipse::dwgInFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be read first
	Adesk::UInt32 version = 0;
	if ((es = pFiler->readUInt32(&version)) != Acad::eOk)
		return (es);
	if (version > ADSKEmployee::kCurrentVersionNumber)
		return (Acad::eMakeMeProxy);
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < ADSKEmployee::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	switch (version)
	{
	case (1):
		pFiler->readItem(&m_nID);
		pFiler->readItem(&m_nCube);
		pFiler->readItem(&m_szFirstName);
		pFiler->readItem(&m_szLastName);
		break;
	}

	return (pFiler->filerStatus());
}

//- Dxf Filing protocol
Acad::ErrorStatus ADSKEmployee::dxfOutFields(AcDbDxfFiler * pFiler) const {
	assertReadEnabled();
	//----- Save parent class information first.
	Acad::ErrorStatus es = AcDbEllipse::dxfOutFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	es = pFiler->writeItem(AcDb::kDxfSubclass, _RXST("ADSKEmployee"));
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be saved first
	if ((es = pFiler->writeUInt32(kDxfInt32, ADSKEmployee::kCurrentVersionNumber)) != Acad::eOk)
		return (es);
	//----- Output params
	pFiler->writeItem(AcDb::kDxfInt32 + 1, m_nID); // DXF Code 91
	pFiler->writeItem(AcDb::kDxfInt32, m_nCube); // DXF Code 90
	pFiler->writeItem(AcDb::kDxfXTextString + 1, m_szFirstName); // DXF Code 300
	pFiler->writeItem(AcDb::kDxfXTextString, m_szLastName); // DXF Code 301

	return (pFiler->filerStatus());
}

Acad::ErrorStatus ADSKEmployee::dxfInFields(AcDbDxfFiler * pFiler) {
	assertWriteEnabled();
	//----- Read parent class information first.
	Acad::ErrorStatus es = AcDbEllipse::dxfInFields(pFiler);
	if (es != Acad::eOk || !pFiler->atSubclassData(_RXST("ADSKEmployee")))
		return (pFiler->filerStatus());
	//----- Object version number needs to be read first
	struct resbuf rb;
	pFiler->readItem(&rb);
	if (rb.restype != AcDb::kDxfInt32) {
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode, _RXST("\nError: expected group code %d (version #)"), AcDb::kDxfInt32);
		return (pFiler->filerStatus());
	}
	Adesk::UInt32 version = (Adesk::UInt32)rb.resval.rlong;
	if (version > ADSKEmployee::kCurrentVersionNumber)
		return (Acad::eMakeMeProxy);
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < ADSKEmployee::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params in non order dependant manner
	while (es == Acad::eOk && (es = pFiler->readResBuf(&rb)) == Acad::eOk) {
		switch (rb.restype) {
			//----- Read params by looking at their DXF code (example below)
		case  AcDb::kDxfInt32:
			m_nCube = rb.resval.rlong;
			break;
		case AcDb::kDxfInt32 + 1:
			m_nID = rb.resval.rlong;
			break;
		case AcDb::kDxfXTextString:
			if (m_szLastName != NULL)
				free(m_szLastName);
			m_szLastName = _tcsdup(rb.resval.rstring);
			break;
		case  AcDb::kDxfXTextString + 1:
			if (m_szFirstName != NULL)
				free(m_szFirstName);
			m_szFirstName = _tcsdup(rb.resval.rstring);
			break;
		default:
			//----- An unrecognized group. Push it back so that the subclass can read it again.
			pFiler->pushBackItem();
			es = Acad::eEndOfFile;
			break;
		}
	}
	//----- At this point the es variable must contain eEndOfFile
	//----- - either from readResBuf() or from pushback. If not,
	//----- it indicates that an error happened and we should
	//----- return immediately.
	if (es != Acad::eEndOfFile)
		return (Acad::eInvalidResBuf);

	return (pFiler->filerStatus());
}

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean ADSKEmployee::subWorldDraw(AcGiWorldDraw * pMode) {
	assertReadEnabled();
	// write the Employee full name
	TCHAR buffer[255];
	_stprintf(buffer, _T("%s %s"), m_szFirstName, m_szLastName);
	pMode->geometry().text(center() - minorAxis() / 2, normal(), majorAxis(), minorAxis().length() / 2, 1.0, 0.0, buffer);
	return (AcDbEllipse::subWorldDraw(pMode));
}


Adesk::UInt32 ADSKEmployee::subSetAttributes(AcGiDrawableTraits * pTraits) {
	assertReadEnabled();
	return (AcDbEllipse::subSetAttributes(pTraits));
}

Acad::ErrorStatus ADSKEmployee::lastName(TCHAR * &aszLastName)
{
	assertReadEnabled();
	aszLastName = _tcsdup(m_szLastName);
	return Acad::eOk;
}

Acad::ErrorStatus ADSKEmployee::setLastName(const TCHAR * aszLastName)
{
	assertWriteEnabled();
	if (m_szLastName)
		free(m_szLastName);
	m_szLastName = _tcsdup(aszLastName);
	return Acad::eOk;
}

Acad::ErrorStatus ADSKEmployee::firstName(TCHAR * &aszFirstName)
{
	assertReadEnabled();
	aszFirstName = _tcsdup(m_szFirstName);
	return Acad::eOk;
}

Acad::ErrorStatus ADSKEmployee::setFirstName(const TCHAR * aszFirstName)
{
	assertWriteEnabled();
	if (m_szFirstName)
		free(m_szFirstName);
	m_szFirstName = _tcsdup(aszFirstName);
	return Acad::eOk;
}

Acad::ErrorStatus ADSKEmployee::cube(Adesk::Int32 & anCube)
{
	assertReadEnabled();
	anCube = m_nCube;
	return Acad::eOk;
}

Acad::ErrorStatus ADSKEmployee::setCube(const Adesk::Int32 anCube)
{
	assertWriteEnabled();
	m_nCube = anCube;
	return Acad::eOk;
}

Acad::ErrorStatus ADSKEmployee::ID(Adesk::Int32 & anID)
{
	assertReadEnabled();
	anID = m_nID;
	return Acad::eOk;
}

Acad::ErrorStatus ADSKEmployee::setID(const Adesk::Int32 anID)
{
	assertWriteEnabled();
	m_nID = anID;
	return Acad::eOk;
}

