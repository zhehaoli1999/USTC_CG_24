#include "DArray.h"
#include <string>

using S = std::string; 

int main(int argc, char** argv) {
	DArray<double> a;
	a.InsertAt(0, 2.1);
	a.Print();

	a.PushBack(3.0);
	a.PushBack(3.1);
	a.PushBack(3.2);
	a.Print();

	a.DeleteAt(0);
	a.Print();
	a.InsertAt(0, 4.1);
	a.Print();
	// a.GetAt(0);

	DArray<double> acopy = a; // 此处用到了拷贝构造函数
	acopy.Print();

	DArray<double> acopy2(a); // 该语句等同于上面的语句，都是初始化
	acopy2.Print();

	DArray<double> acopy3, acopy4;
	acopy4 = acopy3 = a; // 此处用到了赋值操作符号"="的重载
	acopy3.Print();
	acopy4.Print();

	DArray<int> b;
	b.PushBack(21);
	b.Print();
	b.DeleteAt(0);
	b.Print();
	b.PushBack(22);
	// b.SetSize(5);
	b.Print();

	DArray<char> c;
	c.PushBack('a');
	c.PushBack('b');
	c.PushBack('c');
	c.InsertAt(0, 'd');
	c.Print();

	// DArray<std::string> d; // Can be problems cause the size of a std::string can change
	// d.PushBack(S("Dog"));
	// d.PushBack(S("Cat"));
	// d.Print();
	// // d.DeleteAt(1);
	// d.Print();

	DArray<std::string*> d; // Can be problems cause the size of a std::string can change
	S s1 = "Dog"; 
	S s2 = "Kangaroo"; 
	d.PushBack(&s1);
	d.PushBack(&s2);
	d.Print();
	d.DeleteAt(1);
	d.Print();

	return 0;
}