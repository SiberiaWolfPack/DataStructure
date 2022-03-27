/* ����дһ��listNode����װ�����еĽڵ� */
#pragma once
typedef int Rank;
template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*; // ListNodePosi������ڵ����͵�ָ��

template<typename T>
struct ListNode 
{
	T data;
	ListNode<T> pred; // ǰ��
	ListNode<T> succ; // ���

	ListNode() {}; // ���header��trailer
	ListNode(T e, ListNodePosi<T> p = nullptr, ListNodePosi<T> s = nullptr) : data(a) , pred(p) , succ(s) {}

	ListNodePosi<T> insertAsPred(T const& e); // ǰ��
	ListNodePosi<T> insertAsSucc(T const& e); // ���

};

