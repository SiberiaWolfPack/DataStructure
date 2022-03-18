#pragma once
#define DEFAULT_CAPACITY 3 // 默认的初始容量
typedef int Rank;

template<typename T>
class Vector
{
protected:
	Rank _size; // 实际大小
	Rank _capacity; // 容量
	T* _elem;

	// 复制A[lo,hi) T const* A，指针常量，A指向的T类型数组，A是一个指向T形常量的指针。p内保存的常量的地址可以变，而地址指向的常量不能改变。
	void copyFrom(T const* A, Rank lo, Rank hi);
	void expand(); //空间不足时扩容
	void shrink(); //装填因子过小时压缩
	void bubbleSort(Rank lo, Rank hi); //起泡排序算法
	Rank maxItem(Rank lo, Rank hi); //选取最大元素
	void selectionSort(Rank lo, Rank hi); //选择排序算法
	void merge(Rank lo, Rank mi, Rank hi); //归并算法
	void mergeSort(Rank lo, Rank hi); //归并排序算法
	
	/**
	void heapSort(Rank lo, Rank hi); //堆排序（稍后结合完全堆讲解）
	Rank partition(Rank lo, Rank hi); //轴点构造算法
	void quickSort(Rank lo, Rank hi); //快速排序算法
	void shellSort(Rank lo, Rank hi); //希尔排序算法
	*/

public:

	// 构造函数
	Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) // 容量为c，规模为s，所有元素初始化为v
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}

	Vector(T const* A, Rank n)
	{
		copyFrom(A, 0, n);
	}

	Vector(T const* A, Rank lo, Rank hi)
	{
		copyFrom(A, lo, hi);
	}

	Vector(Vector<T> const& V)
	{
		copyFrom(V._elem, 0, V._size);
	}

	Vector(Vector<T> const& V, Rank lo, Rank hi)
	{
		copyFrom(V._elem, lo, hi);
	}

	// 析构函数：
	~Vector()
	{
		delete[] _elem;
	}

	// 只读访问接口
	Rank size() const { return _size; }
	/*
	* 函数前面加const：用来修饰函数的返回值，表示返回值是 const 类型，也就是不能被修改
	* 函数后面加const：常成员函数，这种函数只能读取成员变量的值，而不能修改成员变量的值
	*/
	bool empty() const { return !_size; }
	Rank find(T const& e, Rank lo, Rank hi) const; //无序向量区间查找
	Rank find(T const& e) const { return find(e, 0, _size); } //无序向量整体查找
	Rank search(T const& e) const //有序向量整体查找
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找

	// 可写访问接口
	T& operator[] (Rank r); // 为什么使用引用返回重载的[]:可以用于左值，用来赋值操作
	const T& operator[] (Rank r) const; // 仅限于做右值的重载版本

	Vector<T>& operator= (Vector<T> const& V); // 为什么参数列表不加上形参名？-- 这个形参名不一定需要
	
	int remove(Rank lo, Rank hi);
	T remove(Rank r); //删除秩为r的元素，使用区间删除来删除一个元素，而不是用一个元素删除整个区间

	Rank insert(Rank r, T const& e); //插入元素
	Rank insert(T const& e) { return insert(_size, e); } //默认作为末元素插入

	void sort(Rank lo, Rank hi); //对[lo, hi)排序

	void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
	Rank deduplicate(); //无序去重
	Rank uniquify(); //有序去重

	// 遍历
	void traverse(void(*visit)(T&)); //遍历（使用函数指针，只读或局部性修改）
	/*
	函数指针：returnType (*pointerName)(param list);
	
	*/

	template<typename VST>  //遍历（使用函数对象，可全局性修改）
	void traverse(VST&visit);
};