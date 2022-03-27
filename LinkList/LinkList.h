#pragma once
#include"ListNode.h"

template<typename T>
class LinkList
{
private:
	int _size;
	ListNodePosi<T> header; // ͷ�ڱ�
	ListNodePosi<T> trailer; // β�ڱ�

protected:
	void init(); // �����б�ʱ�õĳ�ʼ��
	int clear(); // ������еĽڵ�
	void copyNodes(ListNodePosi<T>p, int n); // �����б�����pλ�����n��
	ListNodePosi<T> merge(ListNodePosi<T>, int, LinkList<T>&, ListNodePosi<T>, int); // �鲢
	void mergeSort(ListNodePosi<T>& p, int n); // �Դ�p��ʼ��n���ڵ�鲢����
	/*
	* void selectionSort(ListNodePosi<T> p,int n); ѡ������
	* void insertSort(ListNodePosi<T> p,int n);    ��������
	* void radixSort(ListNodePosi<T> p, int n);    ��������
	*/

public:
	LinkList() { init(); }
	LinkList(LinkList<T> const& L); // ���帴���б�L
	LinkList(LinkList<T> const& L, int r, int n); // �����б�L��r���n��
	LinkList(ListNodePosi<T> p, int n); // �����б�����λ��p���n��

	~LinkList();

	// ֻ�����ʽӿ�
	int size() const { return _size; }
	bool empty() const { return _size <= 0; }

	T& operator[] (int r) const; // ֧��ѭ�ȷ���

	ListNodePosi<T> first() const { return header->succ; } // �����׽ڵ��λ��
	ListNodePosi<T> last() const { return  trailer->pred; } // ����β�ڵ��λ��

	bool vaild(LinkList<T> p) { return p && header != p && trailer != p; } // �ж�p�Ƿ���һ���Ϸ�λ�ã�����һ����������

	ListNodePosi<T> find(T const& e, int n, ListNodePosi<T>p) const; // �����������
	ListNodePosi<T> find(T const& e) const { return find(e, _size, trailer); } // �������e
	ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const; // �������e
	ListNodePosi<T> search(T const& e)const { return search(e, _size, trailer); } // �������e

	ListNodePosi<T> insertAsFirst(T const& e); // ��e����p�׽ڵ����
	ListNodePosi<T> insertAsLast(T const& e); // ��e����ĩ�ڵ����
	ListNodePosi<T> insertAfter(ListNodePosi<T>p, T const& e); // ��p֮�����e
	ListNodePosi<T> insertBefore(T const& e��ListNodePosi<T>p); // ��p֮ǰ����e

	T remove(ListNodePosi<T> p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�

	void merge(LinkList<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); } // ȫ�б�鲢

	void sort(ListNodePosi<T> p, int n); // �б���������
	void sort() { sort(first(), _size); } //�б���������

	int deduplicate(); // ����ȥ��
	int uniquify(); // ����ȥ��

	void reverse(); // ǰ����

	void traverse(void(*)(T&)); // ����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
	template<VST>
	void traverse(VST&);// ����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�

};