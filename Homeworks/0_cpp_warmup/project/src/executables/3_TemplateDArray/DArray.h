#pragma once
#include <iostream>
#include <cassert>

// interfaces of Dynamic Array class DArray
template <class T>
class DArray {
public:
	DArray(); // default constructor
	DArray(int nSize, T dValue = 0); // set an array with default values
	DArray(const DArray& arr); // copy constructor
	~DArray(); // deconstructor

	void Print() const; // print the elements of the array

	int GetSize() const; // get the size of the array
	void SetSize(int nSize); // set the size of the array

	const T& GetAt(int nIndex) const; // get an element at an index
	void SetAt(int nIndex, T dValue); // set the value of an element

	T& operator[](int nIndex); // overload operator '[]'
	const T& operator[](int nIndex) const; // overload operator '[]'

	void PushBack(T dValue); // add a new element at the end of the array
	void DeleteAt(int nIndex); // delete an element at some index
	void InsertAt(int nIndex, T dValue); // insert a new element at some index

	T& end(); 

DArray& operator = (const DArray& arr); //overload operator '='

private:
	T* m_pData; // the pointer to the array memory
	int m_nSize; // the size of the array
	int m_nMax;

private:
	void Init(); // initilize the array
	void Free(); // free the array
	void Reserve(int nSize); // allocate enough memory
};


// default constructor
template <class T>
DArray<T>::DArray() {
	Init();
}

// set an array with default values
template <class T>
DArray<T>::DArray(int nSize, T dValue) 
	: m_nMax(nSize+1), m_pData(new T[m_nMax]), m_nSize(nSize)
{
	for(int i = 0; i < nSize; i++) {
		m_pData[i] = dValue;
	}
}

template <class T>
DArray<T>::DArray(const DArray<T>& arr) 
{
	m_nMax = arr.GetSize()+1;
	m_pData = new T[m_nMax]; 
	m_nSize = arr.GetSize(); 

	for(int i = 0; i < m_nSize; i++) {
		// this is wrong: m_pData[i] = arr[i];
		m_pData[i] = arr.m_pData[i];
	}
}

// deconstructor
template <class T>
DArray<T>::~DArray() {
	Free();
}

// display the elements of the array
template <class T>
void DArray<T>::Print() const {
	std::cout << "size = " << m_nSize << ": ["; 
	for(int i = 0; i < m_nSize; i++) {
		std::cout << m_pData[i] << ", ";
	}
	std::cout << "] " <<std::endl; 
}

template <class T>
T& DArray<T>::end() {
	return m_pData[m_nSize-1];
}

// initilize the array
template <class T>
void DArray<T>::Init() {
	m_nSize = 0;
	m_nMax = 0; 
	m_pData = nullptr;
}

// free the array
template <class T>
void DArray<T>::Free() {
	delete[] m_pData;
	m_pData = nullptr; 
	// Do I need to clear m_nMax?
	// Go and check the official std::vector implementation 
	// Link: 
	m_nSize = 0;
	m_nMax = 0;  
}

// get the size of the array
template <class T>
int DArray<T>::GetSize() const {
	return m_nSize; 
}

template <class T>
void DArray<T>::Reserve(int nSize) {
	if(nSize > m_nMax)
	{
		m_nMax = (m_nMax <= 0 )? 1 : m_nMax* 2 ; 
		auto new_array = new T[m_nMax];
		memcpy(new_array, m_pData, m_nSize*sizeof(T));
		// memset(new_array+m_nSize, 0, (nSize -m_nSize)*sizeof(T)); 
		
		delete[] m_pData;
		m_pData = new_array; 
	}
	m_nSize = nSize; 
	return;
}

// set the size of the array
template <class T>
void DArray<T>::SetSize(int nSize) {
	Reserve(nSize);
}

// get an element at an index
template <class T>
const T& DArray<T>::GetAt(int nIndex) const {
	return (*this)[nIndex];
}

// set the value of an element 
template <class T>
void DArray<T>::SetAt(int nIndex, T dValue) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
	return; 
}

// overload operator '[]'
template <class T>
T& DArray<T>::operator[](int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; 
}

// overload operator '[]'
template <class T>
const T& DArray<T>::operator[](int nIndex) const {
	// return GetAt(nIndex); a very bad idea
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; 
}

// add a new element at the end of the array
template <class T>
void DArray<T>::PushBack(T dValue) {
	Reserve(m_nSize + 1);
	this->end() = dValue;
}

// delete an element at some index
template <class T>
void DArray<T>::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_nSize -= 1;
	for(int i = nIndex; i < m_nSize; i++) {
		m_pData[i] = m_pData[i+1];
	} // IMPROVE: use new array and copy data
}

// insert a new element at some index
template <class T>
void DArray<T>::InsertAt(int nIndex, T dValue) {
	assert(nIndex >= 0 && nIndex <= m_nSize); // nIndex == m_nSize is legal
	Reserve(m_nSize + 1);
	for(int i = m_nSize - 1; i > nIndex; i--){
		m_pData[i] = m_pData[i-1];
	}
	m_pData[nIndex] = dValue;
}

// overload operator '='
template <class T>
DArray<T>& DArray<T>::operator = (const DArray<T>& arr) {
	m_nMax = arr.GetSize()+1; 

	delete[] m_pData;
	m_pData = new T[m_nMax]; 

	m_nSize = arr.GetSize(); 

	for(int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr[i];
	}

	return *this; 
}
