#pragma once
#include "ADSKEmployee.h"
#include "Tchar.h"
#include <utility>
class EmployeeBuilder // TODO rule of 5
{
public:
	using pointer = AcDbObjectPointer<ADSKEmployee>;
	EmployeeBuilder(const TCHAR* aszfirstName);
	EmployeeBuilder& withID(int anId);
	EmployeeBuilder& withCube(int anCube);
	EmployeeBuilder& withLastName(const TCHAR* aszLastName);
	operator AcDbObjectPointer<ADSKEmployee>()  { return std::move(m_pEmployee); }
	//auto build() -> pointer {
	//	return std::move(m_pEmployee);
	//}
private:
	pointer m_pEmployee; // TODO maybe store ADSKEmployee and return copy, 
};