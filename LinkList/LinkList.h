#pragma once
#include"ListNode.h"

template<typename T>
class LinkList
{
private:
	int _size;
	ListNodePosi<T> header; // 头哨兵
	ListNodePosi<T> trailer; // 尾哨兵

protected:
	void init(); // 创建列表时用的初始化
	int clear(); // 清除所有的节点
	void copyNodes(ListNodePosi<T>p, int n); // 复制列表中自p位置起的n项
	ListNodePosi<T> merge(ListNodePosi<T>, int, LinkList<T>&, ListNodePosi<T>, int); // 归并
	void mergeSort(ListNodePosi<T>& p, int n); // 对从p开始的n个节点归并排序
	/*
	* void selectionSort(ListNodePosi<T> p,int n); 选择排序
	* void insertSort(ListNodePosi<T> p,int n);    插入排序
	* void radixSort(ListNodePosi<T> p, int n);    基数排序
	*/

public:
	LinkList() { init(); }
	LinkList(LinkList<T> const& L); // 整体复制列表L
	LinkList(LinkList<T> const& L, int r, int n); // 复制列表L从r起的n项
	LinkList(ListNodePosi<T> p, int n); // 复制列表中自位置p起的n项

	~LinkList();

	// 只读访问接口
	int size() const { return _size; }
	bool empty() const { return _size <= 0; }

	T& operator[] (int r) const; // 支持循秩访问

	ListNodePosi<T> first() const { return header->succ; } // 返回首节点的位置
	ListNodePosi<T> last() const { return  trailer->pred; } // 返回尾节点的位置

	bool vaild(LinkList<T> p) { return p && header != p && trailer != p; } // 判断p是否是一个合法位置，他是一个辅助函数

	ListNodePosi<T> find(T const& e, int n, ListNodePosi<T>p) const; // 无序区间查找
	ListNodePosi<T> find(T const& e) const { return find(e, _size, trailer); } // 无序查找e
	ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const; // 有序查找e
	ListNodePosi<T> search(T const& e)const { return search(e, _size, trailer); } // 有序查找e

	ListNodePosi<T> insertAsFirst(T const& e); // 将e当作p首节点插入
	ListNodePosi<T> insertAsLast(T const& e); // 将e当作末节点插入
	ListNodePosi<T> insertAfter(ListNodePosi<T>p, T const& e); // 在p之后插入e
	ListNodePosi<T> insertBefore(T const& e，ListNodePosi<T>p); // 在p之前插入e

	T remove(ListNodePosi<T> p); //删除合法位置p处的节点,返回被删除节点

	void merge(LinkList<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); } // 全列表归并

	void sort(ListNodePosi<T> p, int n); // 列表区间排序
	void sort() { sort(first(), _size); } //列表整体排序

	int deduplicate(); // 无序去重
	int uniquify(); // 有序去重

	void reverse(); // 前后倒置

	void traverse(void(*)(T&)); // 遍历，依次实施visit操作（函数指针，只读或局部性修改）
	template<VST>
	void traverse(VST&);// 遍历，依次实施visit操作（函数对象，可全局性修改）

};