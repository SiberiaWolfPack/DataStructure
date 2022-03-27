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


