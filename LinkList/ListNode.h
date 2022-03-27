/* 独立写一个listNode来封装链表中的节点 */
#pragma once
typedef int Rank;
template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*; // ListNodePosi是这个节点类型的指针

template<typename T>
struct ListNode 
{
	T data;
	ListNode<T> pred; // 前驱
	ListNode<T> succ; // 后继

	ListNode() {}; // 针对header和trailer
	ListNode(T e, ListNodePosi<T> p = nullptr, ListNodePosi<T> s = nullptr) : data(a) , pred(p) , succ(s) {}

	ListNodePosi<T> insertAsPred(T const& e); // 前插
	ListNodePosi<T> insertAsSucc(T const& e); // 后插

};

