#include "Vector.h"
#include<cmath>

template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) // 以数组区间A[lo, hi)为蓝本复制向量
{
	_elem = new T[_capacity = 2 * (hi - lo)]; // 分配二倍空间
	for (_size = 0; lo < hi; _size++, lo++) _elem[_size] = A[lo];
} // 用const修饰，保证A中的元素不致被篡改；运行时间 = O(hi-lo)

template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity) return; // 不溢出不需要扩容
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; // 不要小于最低容量

	T* oldelem = _elem;
	_elem = new T[_capacity << 1]; // 扩容规则：加倍
	for (Rank i = 0; i < _size; i++) _elem[i] = oldelem[i];

	delete[] oldelem;
}

template <typename T>
void Vector<T>::shrink() // 装填因子过小时压缩向量所占空间
{
	if (_capacity < DEFAULT_CAPACITY << 1) return; // 不致收缩到DEFAULT_CAPACITY以下
	if (_size << 2 > _capacity) return; // 以25%为界

	T* oldelem = _elem;
	_elem = new T[_capacity >>= 1]; // 容量减半
	for (Rank i = 0; i < _size; i++) _elem[i] = oldelem[i];

	delete[] oldelem;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	int len = lo - hi;
	for (int i = lo; i < len; i++)
		for (int j = lo; j < len - i - 1; j++)
			if (_elem[j] > _elem[j + 1])
			{
				int t = _elem[j];
				_elem[j] = _elem[j + 1];
				_elem[j + 1] = t;
			}
}

template <typename T>
Rank Vector<T>::maxItem(Rank lo, Rank hi) //选取最大元素
{
	Rank mx = hi;
	while (lo < hi--) //逆向扫描 使用while不需要开辟int i
		if (_elem[hi] > _elem[mx]) //且严格比较
			mx = hi; //故能在max有多个时保证后者优先，进而保证selectionSort稳定
	return mx;
}

template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi)
{
	while (lo < --hi)
		swap(_elem[maxItem(lo, hi)], _elem[hi]);
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	int temp[hi - lo + 1], k = 0;
	int i = lo, j = mi + 1;

	while (i <= mi && j <= hi)
	{
		if (_elem[i] < _elem[j]) temp[k++] = _elem[i++];
		else temp[k++] = _elem[j++];
	}

	while (i <= mi) temp[k++] = _elem[i++];
	while (j <= hi) temp[k++] = _elem[j++];

	for (int i = lo, j = 0; i <= hi; i++, j++) _elem[i] = temp[j];
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (lo == hi) return;

	int mid = lo + hi >> 1;
	mergeSort(lo, mid);
	mergeSort(mid + 1, hi);
	merge(lo, mid, hi);
}

template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
	//无序向量的顺序查找：返回最后一个元素e的位置；失败时，返回 -1
	while ((lo < hi--) && (e != _elem[hi]));
	if (hi < lo) return -1;
	else return hi;
}

template<typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const //在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩
{
	// 按各50%的概率随机使用二分查找或Fibonacci查找
	return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template<typename T>
T& Vector<T>::operator[] (Rank r)
{
	return _elem[r];
}

template<typename T>
const T& Vector<T>::operator[] (Rank r) const
{
	return _elem[r];
}

template<typename T>
Vector<T>& Vector<T>::operator= (Vector<T> const& V)
{
	if (_elem) delete[] _elem; // //释放原有内容
	copyFrpm(V._elem, 0, V.size());
	return *this; // 返回当前对象的引用，可以链式赋值
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) // 删除一个区间[lo,hi)，并且返回被删元素的数目
{
	if (lo == hi) return 0;
	if (_size == 1 && hi == lo + 1) _size--;
	else
	{
		while (hi < _size)
		{
			_elem[lo++] = _elem[hi++]; // 后缀整体前移
		}
		_size = lo; //更新规模，直接丢弃尾部[lo, _size = hi)区间
		shrink(); //若有必要，则缩容
	}
	return hi - lo; // 移动多少就是删除了多少元素
}

template <typename T>
T Vector<T>::remove(Rank r) // 删除某个指定的元素并且返回该元素的值
{
	T e = _elem[r];
	remove(r,r+1);
	return e; 
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) // 将e作为秩为r的元素来插入
{
	expand(); // 若有必要，扩容 f12跳转到函数实现处 ctrl+g/-跳转回来
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;
	return r; // 返回秩
}


template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand()%2)
	{
		case 1: bubbleSort(lo, hi); break;
		case 2: mergeSort(lo, hi); break;
	}
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) // 等概率随机置乱区间[lo,hi)
{
	T* V = _elem + lo; // 将子区间[lo,hi)视为另一个向量[0,hi-lo)
	for (Rank i = hi - lo; i > 0; i--)
		swap(V[i - 1], V[rand() % i]); // 将V[v-1]与V[0,i)中某一个元素随机交换
}

template <typename T>
Rank Vector<T>::deduplicate() // 无序去重
{
	int oldSize = _size; // 记录原始规模
	Rank i = 1;
	while (i < _size)
	{
		if (find(_elem[i],0,i) < 0 ) i++; //在前缀[0,i)中寻找与之雷同者（至多一个）
		else remove(i);
	}
	return oldSize - _size;
}

template <typename T>
Rank Vector<T>::uniquify()// 有序去重
{
	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j]) _elem[++i] = _elem[j]; // 发现不同元素时，向前移至紧邻于前者右侧
	
	_size = ++i;
	shrink();  // 直接截除尾部多余元素
	return j - i; // 向量规模变化量，即被删除元素总数
}

template <typename T>
void Vector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; i++) 
			visit(_elem[i]);
}

template <typename T> // 元素类型
template<typename VST> // 操作器
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}