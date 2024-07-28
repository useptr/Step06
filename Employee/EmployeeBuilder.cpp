#include "stdafx.h"
#include "EmployeeBuilder.h"
#include "ADSKEmployee.h"
#include "Tchar.h"

EmployeeBuilder::EmployeeBuilder(const TCHAR* firstName)
{
	m_employee = new ADSKEmployee;
	m_employee->assertWriteEnabled();
	if (m_employee->m_firstName)
		free(m_employee->m_firstName);
	m_employee->m_firstName = _tcsdup(firstName);
}

EmployeeBuilder& EmployeeBuilder::withID(int id)
{
	m_employee->assertWriteEnabled();
	m_employee->m_ID = id;
	return *this;
}

EmployeeBuilder& EmployeeBuilder::withCube(int cube)
{
	m_employee->assertWriteEnabled();
	m_employee->m_cube = cube;
	return *this;
}

EmployeeBuilder& EmployeeBuilder::withLastName(const TCHAR* lastName)
{
	m_employee->assertWriteEnabled();
	if (m_employee->m_lastName)
		free(m_employee->m_lastName);
	m_employee->m_lastName = _tcsdup(lastName);
	return *this;
}

EmployeeBuilder ADSKEmployee::create(const TCHAR* firstName)
{
	return EmployeeBuilder(firstName);
}
