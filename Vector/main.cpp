#include "Vector.cpp" // 写模板类，必须要包含的是cpp
#include<iostream>
using namespace std;
int main()
{
	// 构造函数测试
	Vector<int>a; // 默认：容量为DEFAULT_CAPACITY，规模为s=0，所有元素初始化为v=0
	cout << a.size() << endl;
	a.insert(12);
	cout << a.size() << endl;
	cout << a[0] << endl;
	a.remove(0);
	cout << a.size() << endl;
	return 0;
}