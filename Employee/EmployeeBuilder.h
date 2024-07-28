#pragma once
#include "ADSKEmployee.h"
#include "Tchar.h"
class EmployeeBuilder
{
public:
	EmployeeBuilder(const TCHAR* firstName);
	EmployeeBuilder& withID(int id);
	EmployeeBuilder& withCube(int cube);
	EmployeeBuilder& withLastName(const TCHAR* lastName);
	//operator ADSKEmployee* () const { return m_employee; }
	ADSKEmployee* build() const { return m_employee; }
private:
	ADSKEmployee* m_employee;
};