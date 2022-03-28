#include"LinkList.h"

template<typename T>
void LinkList<T>::init()
{
	header = new ListNodePosi<T>;
	trailer = new ListNodePosi<T>;
	
	header->pred = nullptr;
	header->succ = trailer;

	trailer->pred = header;
	trailer->succ = nullptr;

	_size=0；
}

template<typename T>
int LinkList<T>::clear()
{
	int oldSize = _size;
	while(_size > 0) remove(header->succ); // 不断删除header的后继
	return oldSize; // 返回没删除前的规模
}

template<typename T>
void LinkList<T>::copyNodes(ListNodePosi<T> p, int n) // 列表内部的方法，会复制这个p节点以及以后的n-1个节点
{
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
ListNodePosi<T> LinkList<T>::merge(ListNodePosi<T>p, int n, LinkList<T>&L, ListNodePosi<T>q, int m)
{
	// //有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
	ListNodePosi<T> ppred = p->pred;
	while ((m > 0) && (p != q))
	{
		if (n > 0 && (p->data <= q->data)) // 前半段不动
		{
			p = p->succ;
			n--;
		}
		else // 后面的下，提过来
		{
			q = q->succ;
			insertBefore(L.remove(q->pred), p);
			m--;
		}
	}

	return ppred->succ; // 更新的首节点
}

template<typename T>
void LinkList<T>::mergeSort(ListNodePosi<T>& p, int n)
{
	if (n < 2) return;
	int m = n >> 1; // 中间点
	ListNodePosi<T>q = p;
	for (int i = 0; i < m; i++) q = q->succ; // 找到后列表的起点
	
	mergeSort(p, m);
	mergeSort(q, n-m);

	p = merge(p,m,*this,q,n-m); // 归并

}

template<typename T>
LinkList<T>::LinkList(LinkList<T> const& L)
{
	copyNodes(L.first(), L._size);
}

template<typename T>
LinkList<T>::LinkList(LinkList<T> const& L, int r, int n)
{
	ListNodePosi<T> p = L.first();
	while (r > 0)
	{
		p = p->succ;
		r--;
	}

	copyNodes(p, n);
}

template<typename T>
LinkList<T>::LinkList(ListNodePosi<T> p, int n)// 复制列表中自位置p起的n项
{
	copyNodes(p, n);
}

template<typename T>
LinkList<T>::~LinkList()
{
	clear();
	delete header;
	delete trailer;
}

template<typename T>
T& LinkList<T>::operator[](int r) const // 可以作为左值被赋值
{
	ListNodePosi<T> p = first();
	while (r > 0)
	{
		p = p->succ;
		r--;
	}
	return p->data;
}

template<typename T>
ListNodePosi<T> LinkList<T>::find(T const& e, int n, ListNodePosi<T> p) const
{
	// 在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
	while (n > 0)
	{
		p = p->pred;
		if (e == p->data) return p;
	}
	return nullptr;
}

template<typename T>
ListNodePosi<T> LinkList<T>::search(T const& e, int n, ListNodePosi<T> p) const
{
	// 在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
	while (n >= 0) // 有可能全部都大于他，这时候就是在0位置
	{
		p = p->pred;
		if (p->data <= e)break;
	}
	return p;
}

template<typename T>
ListNodePosi<T> LinkList<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e); // 当作首节点插入就是头指针的后继
}

template<typename T>
ListNodePosi<T> LinkList<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e); // 当作尾节点的前驱
}

template<typename T>
ListNodePosi<T> LinkList<T>::insert(ListNodePosi<T> p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
ListNodePosi<T> LinkList<T>::insert(T const& e, ListNodePosi<T> p)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
T LinkList<T>::remove(ListNodePosi<T> p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	
	delete p; // 删除这个节点占用的空间
	_size--;
	
	return e;
}

template<typename T>
int LinkList<T>::deduplicate() // 无序列表去重
{
	int oldSize = _size;
	ListNodePosi<T> p = first();

	for (int r = 0; p != trailer; p = p->succ) // 从当前节点的前驱中找到第一个等于他的值，删掉他
	{
		if (ListNodePosi<T> q = find(p->data, r, p)) remove(q);
		else r++;
	}
	return oldSize - _size;
}

template<typename T>
int LinkList<T>::uniquify() // 成批剔除重复元素
{
	if (_size < 2) return 0;
	int oldSize = _size;

	ListNodePosi<T>p = first();
	ListNodePosi<T> q;
	while (q != trailer)
	{
		if (q->data != p->data) p = q; // 不一样说明转向下一个阶段
		else remove(q); // 一样的话就删掉快指针
		q = p->succ; // q指向p的下一个指针
	}
	return oldSize - _size;
}










