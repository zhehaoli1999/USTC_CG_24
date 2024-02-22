#include "PolynomialMap.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

PolynomialMap::PolynomialMap(const PolynomialMap& other) {
	m_Polynomial = other.m_Polynomial;
}

PolynomialMap::PolynomialMap(const string& file) {
    ReadFromFile(file);
}

PolynomialMap::PolynomialMap(const double* cof, const int* deg, int n) {
	for(int i = 0; i < n; i++){
		m_Polynomial.emplace(deg[i], cof[i]);
	}
}

PolynomialMap::PolynomialMap(const vector<int>& deg, const vector<double>& cof) {
	assert(deg.size() == cof.size());
	for(int i = 0; i < deg.size(); i++){
		m_Polynomial.emplace(deg[i], cof[i]);
	}
}

double PolynomialMap::coff(int i) const {
	return m_Polynomial.count(i) ? m_Polynomial.at(i) : 0;
}

double& PolynomialMap::coff(int i) {
	unsigned c = m_Polynomial.count(i);
	if(c){
		return m_Polynomial.at(i);
	}
	else{
		return m_Polynomial.emplace(i, 0).first->second;
	}
	// IMPROVE: no need to check count, directly use [] will create new item if not exist
}

void PolynomialMap::compress() {
	for(auto it = m_Polynomial.begin(); it != m_Polynomial.end();){
		if(fabs(it->second) < numeric_limits<double>::epsilon()){
			it = m_Polynomial.erase(it);
		}
		else{
			it++;
		}
	}
}

PolynomialMap PolynomialMap::operator+(const PolynomialMap& right) const {
	auto new_poly = *this; 
	for(auto t : right.m_Polynomial){
		new_poly.m_Polynomial[t.first] += t.second;
	}
	new_poly.compress();
	return new_poly; // you should return a correct value
}

PolynomialMap PolynomialMap::operator-(const PolynomialMap& right) const {
	auto new_poly = *this; 
	for(auto t : right.m_Polynomial){
		new_poly.m_Polynomial[t.first] -= t.second;
	}
	new_poly.compress();
	return new_poly; // you should return a correct value
}

PolynomialMap PolynomialMap::operator*(const PolynomialMap& right) const {
	auto new_poly = PolynomialMap();
	for(auto t1 : m_Polynomial){
		for(auto t2: right.m_Polynomial)
		{
			// ----------- a wrong sample ---------------
			// will cause new value overwrite the old value
			// new_poly.m_Polynomial[t1.first + t2.first] = t1.second * t2.second;
			//--------------------------------------------

			if (new_poly.m_Polynomial.count(t1.first + t2.first))
				new_poly.m_Polynomial[t1.first + t2.first] += t1.second * t2.second;
			else
				new_poly.m_Polynomial[t1.first + t2.first] = t1.second * t2.second;
		}
	}
	new_poly.compress();
	return new_poly; // you should return a correct value
}

PolynomialMap& PolynomialMap::operator=(const PolynomialMap& right) {
	m_Polynomial = right.m_Polynomial;
	return *this;
}

void PolynomialMap::Print() const {
    for(auto t = m_Polynomial.begin(); t != m_Polynomial.end();){
        if(t->first == 0)
            cout << t->second; 
        else 
            cout << t->second << "x^" << t->first; 

        if( (++t) != m_Polynomial.end() )
            cout << " + ";  
    }
    cout << std::endl; 
}

bool PolynomialMap::ReadFromFile(const string& file) {
    ifstream ifs; 
    ifs.open(file, ifstream::in);
    if (!ifs.is_open()) {
        cerr << "Error: cannot open file " << file << endl;
        return false;
    }
    else{
        std::string first_line; 
        std::getline(ifs, first_line);
        // std::cout << "first line: " << first_line << std::endl;
        m_Polynomial.clear();
        while(ifs.good()){
            int deg; 
            double cof; 
            ifs >> deg >> cof;  // Ignore the white space 
            // std::cout << "deg: " << deg << " cof: " << cof << std::endl;
			m_Polynomial.emplace(deg, cof);
        }
    }
    ifs.close();
    return true;
}
