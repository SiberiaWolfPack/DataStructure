#include "Vector.cpp" // дģ���࣬����Ҫ��������cpp
#include<iostream>
using namespace std;
int main()
{
	// ���캯������
	Vector<int>a; // Ĭ�ϣ�����ΪDEFAULT_CAPACITY����ģΪs=0������Ԫ�س�ʼ��Ϊv=0
	cout << a.size() << endl;
	a.insert(12);
	cout << a.size() << endl;
	cout << a[0] << endl;
	a.remove(0);
	cout << a.size() << endl;
	return 0;
}