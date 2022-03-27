#include "ListNode.h"

template<typename T>
ListNodePosi<T> ListNode<T>:: insertAsPred(T const& e)
{
	ListNodePosi<T> x = new ListNode(e , pred , this); // 创建一个新节点，他的前驱就是我们当前节点的前驱，后继就是当前节点
	pred->succ = x; // 当前节点之前的前驱变成新的节点
	pred = x; // 当前节点的前驱变成新的节点

	return x; // 返回新节点的位置
}

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi<T> x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;

	return x;
}

