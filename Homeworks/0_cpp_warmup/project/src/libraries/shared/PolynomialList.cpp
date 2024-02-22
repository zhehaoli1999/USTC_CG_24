#include "PolynomialList.h"
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

PolynomialList::PolynomialList(const PolynomialList& other) {
    m_Polynomial = other.m_Polynomial; 
}

PolynomialList::PolynomialList(const string& file) {
    ReadFromFile(file);
}
PolynomialList::PolynomialList(const double* cof, const int* deg, int n) {
    for(int i = 0; i < n; i++){
        AddOneTerm(Term(deg[i], cof[i]));
    }
}

PolynomialList::PolynomialList(const vector<int>& deg, const vector<double>& cof) {
    assert(deg.size() == cof.size());
    
    for(int i = 0; i < deg.size(); i++){
        AddOneTerm(Term(deg[i], cof[i]));
    }
}

double PolynomialList::coff(int i) const {
    // We cannot random access a std::list, cause it is implemented as a doubly linked list
    for(auto t : m_Polynomial){
        if(t.deg == i){
            return t.cof;
        }
        if(t.deg > i){ // cannot find, early return
            return 0;
        }
    }
}

double& PolynomialList::coff(int i) {
    // if not found, we need to add a term with degree i since it returns double& 
    return AddOneTerm(Term(i, 0)).cof; 
}

void PolynomialList::compress() {
    for(auto it = m_Polynomial.begin(); it != m_Polynomial.end();){
        if(fabs(it->cof) < numeric_limits<double>::epsilon()){
            it = m_Polynomial.erase(it); // no need to it++ here. 
        }
        else{
            it++;
        }
    }
}

PolynomialList PolynomialList::operator+(const PolynomialList& right) const {
    auto new_poly = *this;
    for(auto t : right.m_Polynomial){
        new_poly.AddOneTerm(t);
    } // A more efficient way is to merge two sorted list
    new_poly.compress();
    return new_poly; // you should return a correct value
}

PolynomialList PolynomialList::operator-(const PolynomialList& right) const {
    auto new_poly = *this; 
    for(auto t : right.m_Polynomial){
        new_poly.AddOneTerm(Term(t.deg, -t.cof));
    }
    new_poly.compress();
    return new_poly; // you should return a correct value
}

PolynomialList PolynomialList::operator*(const PolynomialList& right) const {
    // TODO
    auto new_poly = PolynomialList(); 
    for(auto t : right.m_Polynomial){
        for(auto t2 : m_Polynomial){
            new_poly.AddOneTerm(Term(t.deg + t2.deg, t.cof * t2.cof));
        }
    }
    new_poly.compress();
    return new_poly; 
}

PolynomialList& PolynomialList::operator=(const PolynomialList& right) {
    this->m_Polynomial = right.m_Polynomial;
    return *this;
}

void PolynomialList::Print() const {
    for(auto t = m_Polynomial.begin(); t != m_Polynomial.end();){
        if(t->deg == 0)
            cout << t->cof; 
        else 
            cout << t->cof << "x^" << t->deg; 

        if( (++t) != m_Polynomial.end() )
            cout << " + ";  
    }
    cout << std::endl; 
}

bool PolynomialList::ReadFromFile(const string& file) {
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
            AddOneTerm(Term(deg, cof));
        }
    }
    ifs.close();
    return true;
}

PolynomialList::Term& PolynomialList::AddOneTerm(const Term& term) {
    //----------------------- One wrong sample --------------------------------
    // for(auto t : m_Polynomial){
    //     if(t.deg == term.deg){
    //         t.cof += term.cof;
    //         return t; // This is wrong, since we need to return the reference. 
    //     }
    //     if(t.deg < term.deg) // high degree -> low degree  
    //         break;
    // }
    // -------------------------------------------------------------------------
    auto t = m_Polynomial.begin();
    for(;t!= m_Polynomial.end(); t++)
    {
        if(t->deg == term.deg){
            t->cof += term.cof;
            return *t; 
        }
        if(t->deg > term.deg) // sort: low degree -> high degree  
            break;
    }
    // not found terms with the same degree

    //----------------------- another bad sample: cannot guarantee the sort ----------------
    // m_Polynomial.push_back(term); 
    // return m_Polynomial.back();
    // -------------------------------------------------------------------------

    return *(m_Polynomial.insert(t, term)); // insert at the beginning
}
