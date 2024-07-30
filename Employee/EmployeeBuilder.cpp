#include "stdafx.h"
#include "EmployeeBuilder.h"
#include "ADSKEmployee.h"
#include "Tchar.h"

EmployeeBuilder::EmployeeBuilder(const TCHAR* aszFirstName) : m_pEmployee()
{
	m_pEmployee.create();
	m_pEmployee->assertWriteEnabled();
	if (m_pEmployee->m_szFirstName)
		free(m_pEmployee->m_szFirstName);
	m_pEmployee->m_szFirstName = _tcsdup(aszFirstName);
}

EmployeeBuilder& EmployeeBuilder::withID(int anId)
{
	m_pEmployee->assertWriteEnabled();
	m_pEmployee->m_nID = anId;
	return *this;
}

EmployeeBuilder& EmployeeBuilder::withCube(int anCube)
{
	m_pEmployee->assertWriteEnabled();
	m_pEmployee->m_nCube = anCube;
	return *this;
}

EmployeeBuilder& EmployeeBuilder::withLastName(const TCHAR* aszLastName)
{
	m_pEmployee->assertWriteEnabled();
	if (m_pEmployee->m_szLastName)
		free(m_pEmployee->m_szLastName);
	m_pEmployee->m_szLastName = _tcsdup(aszLastName);
	return *this;
}

EmployeeBuilder ADSKEmployee::create(const TCHAR* aszFirstName)
{
	return EmployeeBuilder(aszFirstName);
}
