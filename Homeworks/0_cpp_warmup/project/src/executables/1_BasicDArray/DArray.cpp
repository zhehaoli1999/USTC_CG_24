// implementation of class DArray
#include "DArray.h"
#include <iostream>

// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) {
	m_pData = new double[nSize];
	m_nSize = nSize;
	for(int i = 0; i < nSize; i++) {
		m_pData[i] = dValue;
	}
	return; 
}

DArray::DArray(const DArray& arr) {
	if(arr.GetSize() == 0) {
		Init();
		return;
	}
	else{
		m_nSize = arr.GetSize();
		m_pData = new double[m_nSize]; 
		for(int i = 0; i < m_nSize; i++) {
			m_pData[i] = arr.GetAt(i);
		}
	}
}

// deconstructor
DArray::~DArray() {
	Free();
}

// display the elements of the array
void DArray::Print() const {
	for(int i = 0; i < m_nSize; i++) {
		std::cout << m_pData[i] << " ";
	}
	std::cout << std::endl; 
}

// initilize the array
void DArray::Init() {
	m_nSize = 0;
	m_pData = nullptr; // todo: use smart pointer 
}

// free the array
void DArray::Free() {
	if(m_pData){
		delete[] m_pData;
		m_pData = nullptr;
	}
	m_nSize = 0; 
	return; 
}

// get the size of the array
int DArray::GetSize() const {
	return m_nSize; // you should return a correct value
}

// set the size of the array
void DArray::SetSize(int nSize) {
	m_nSize = nSize;
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	if(nIndex < 0 || nIndex >= m_nSize)
	{
		std::cout << "Error at SetAt: invalid index\n" << std::endl;
		exit(1);
	}
	return m_pData[nIndex]; 
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	if(nIndex < 0 || nIndex >= m_nSize) {
		std::cout << "Error at SetAt: invalid index\n" << std::endl;
		exit(1);
	}
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	return GetAt(nIndex);
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	m_nSize += 1; 

	// First create a new array and move data 
	double* new_array = new double[m_nSize];
	for(int i = 0; i < m_nSize - 1; i++) {
		new_array[i] = m_pData[i];
	}
	delete[] m_pData; 
	m_pData = new_array; 
	// Then add the new value to the end 
	m_pData[m_nSize-1] = dValue;  // CAREFUL: not [m_nSize] but [m_nSize - 1]
	return; 
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	if(nIndex < 0 || nIndex > m_nSize)
	{
		std::cout << "Error at DeleteAt: invalid index\n" << std::endl;
		exit(1);
	}
	m_nSize -= 1;
	for(int i = nIndex; i < m_nSize; i++) {
		m_pData[i] = m_pData[i+1];
	}
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	if(nIndex < 0 || nIndex > m_nSize)
	{
		std::cout << "Error at InsertAt: invalid index\n" << std::endl;
		exit(1);
	}
	m_nSize += 1;

	double* new_array = new double[m_nSize];
	for(int i = 0; i < nIndex; i++) {
		new_array[i] = m_pData[i];
	}
	new_array[nIndex] = dValue;
	for(int i = nIndex + 1; i < m_nSize; i++) {
		new_array[i] = m_pData[i-1];
	}
	delete[] m_pData; 
	
	m_pData = new_array;
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	Free();

	if(arr.GetSize() == 0) {
		Init();
	}
	else{
		m_nSize = arr.GetSize();
		m_pData = new double[m_nSize]; 
		for(int i = 0; i < m_nSize; i++) {
			m_pData[i] = arr.GetAt(i);
		}
	}
	return *this;
}
