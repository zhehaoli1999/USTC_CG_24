// implementation of class DArray
#include "DArray.h"
#include <iostream>
#include <cassert> 

// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) 
	: m_nMax(nSize+1), m_pData(new double[m_nMax]), m_nSize(nSize)
{
	for(int i = 0; i < nSize; i++) {
		m_pData[i] = dValue;
	}
}

DArray::DArray(const DArray& arr) 
{
	m_nMax = arr.GetSize()+1;
	m_pData = new double[m_nMax]; 
	m_nSize = arr.GetSize(); 

	for(int i = 0; i < m_nSize; i++) {
		// this is wrong: m_pData[i] = arr[i];
		m_pData[i] = arr.m_pData[i];
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
	m_nMax = 1; 
	m_pData = new double[m_nMax];
}

// free the array
void DArray::Free() {
	delete[] m_pData;
	m_pData = nullptr; 
	// Do I need to clear m_nMax?
	// Go and check the official std::vector implementation 
	// Link: 
	m_nSize = 0;
	m_nMax = 1;  
}

// get the size of the array
int DArray::GetSize() const {
	return m_nSize; 
}

// set the size of the array
void DArray::SetSize(int nSize) {

	if(nSize < m_nSize)
	{
		m_nSize = nSize;
	}
	else if(nSize > m_nSize)
	{
		// no need to allocate new memory 
		if(nSize <= m_nMax)
		{
			m_nSize = nSize;
			for(int i = m_nSize; i < nSize; i++)
			{
				m_pData[i] = 0;
			}
		}
		// need to allocate new memory 
		else{
			assert(m_nMax > 0);
			m_nMax *= 2; 
			auto new_array = new double[m_nMax];
			for(int i = 0; i < m_nSize; i++)
			{
				new_array[i] = m_pData[i]; // You can directly use memcpy
			}
			for(int i = m_nSize; i < nSize; i++)
			{
				new_array[i] = 0;
			}
			delete[] m_pData;
			m_pData = new_array; 

			m_nSize = nSize;
		}
	}
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	return (*this)[nIndex];
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
	return; 
}

// overload operator '[]'
double& DArray::operator[](int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; 
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	// return GetAt(nIndex); a very bad idea
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; 
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	if(m_nSize < m_nMax)
	{
		m_pData[m_nSize] = dValue;
	}
	else{
		assert(m_nMax > 0);
		m_nMax *= 2;
		auto new_array = new double[m_nMax]; 
		for(int i = 0; i < m_nSize; i++)
		{
			new_array[i] = m_pData[i];
		} // IMPROVE: abstract this operation into a common reserve function 
		new_array[m_nSize] = dValue; 

		delete[] m_pData;
		m_pData = new_array; 
	}
	m_nSize ++; 
	return; 
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_nSize -= 1;
	for(int i = nIndex; i < m_nSize; i++) {
		m_pData[i] = m_pData[i+1];
	} // IMPROVE: use new array and copy data
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex <= m_nSize); // nIndex == m_nSize is legal
	if(m_nSize < m_nMax)
	{
		for(int i = m_nSize; i > nIndex; i--)
		{
			m_pData[i] = m_pData[i-1];
		}
		m_pData[nIndex] = dValue;
		m_nSize += 1;
	}
	else{
		m_nMax *= 2;
		auto new_array = new double[m_nMax];
		for(int i = 0; i < nIndex; i++)
		{
			new_array[i] = m_pData[i];
		}
		new_array[nIndex] = dValue;
		for(int i = nIndex+1; i < m_nSize; i++)
		{
			new_array[i] = m_pData[i-1];
		}
		delete[] m_pData;
		m_pData = new_array; 
	}
	return; 
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	m_nMax = arr.GetSize()+1; 

	delete[] m_pData;
	m_pData = new double[m_nMax]; 

	m_nSize = arr.GetSize(); 

	for(int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr[i];
	}

	return *this; 
}
