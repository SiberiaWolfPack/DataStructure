#include "ListNode.h"

template<typename T>
ListNodePosi<T> ListNode<T>:: insertAsPred(T const& e)
{
	ListNodePosi<T> x = new ListNode(e , pred , this); // ����һ���½ڵ㣬����ǰ���������ǵ�ǰ�ڵ��ǰ������̾��ǵ�ǰ�ڵ�
	pred->succ = x; // ��ǰ�ڵ�֮ǰ��ǰ������µĽڵ�
	pred = x; // ��ǰ�ڵ��ǰ������µĽڵ�

	return x; // �����½ڵ��λ��
}

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi<T> x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;

	return x;
}

