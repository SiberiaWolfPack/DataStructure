#pragma once
#define DEFAULT_CAPACITY 3 // Ĭ�ϵĳ�ʼ����
typedef int Rank;

template<typename T>
class Vector
{
protected:
	Rank _size; // ʵ�ʴ�С
	Rank _capacity; // ����
	T* _elem;

	// ����A[lo,hi) T const* A��ָ�볣����Aָ���T�������飬A��һ��ָ��T�γ�����ָ�롣p�ڱ���ĳ����ĵ�ַ���Ա䣬����ַָ��ĳ������ܸı䡣
	void copyFrom(T const* A, Rank lo, Rank hi);
	void expand(); //�ռ䲻��ʱ����
	void shrink(); //װ�����ӹ�Сʱѹ��
	void bubbleSort(Rank lo, Rank hi); //���������㷨
	Rank maxItem(Rank lo, Rank hi); //ѡȡ���Ԫ��
	void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
	void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
	void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
	
	/**
	void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩
	Rank partition(Rank lo, Rank hi); //��㹹���㷨
	void quickSort(Rank lo, Rank hi); //���������㷨
	void shellSort(Rank lo, Rank hi); //ϣ�������㷨
	*/

public:

	// ���캯��
	Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) // ����Ϊc����ģΪs������Ԫ�س�ʼ��Ϊv
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

	// ����������
	~Vector()
	{
		delete[] _elem;
	}

	// ֻ�����ʽӿ�
	Rank size() const { return _size; }
	/*
	* ����ǰ���const���������κ����ķ���ֵ����ʾ����ֵ�� const ���ͣ�Ҳ���ǲ��ܱ��޸�
	* ���������const������Ա���������ֺ���ֻ�ܶ�ȡ��Ա������ֵ���������޸ĳ�Ա������ֵ
	*/
	bool empty() const { return !_size; }
	Rank find(T const& e, Rank lo, Rank hi) const; //���������������
	Rank find(T const& e) const { return find(e, 0, _size); } //���������������
	Rank search(T const& e) const //���������������
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi) const; //���������������

	// ��д���ʽӿ�
	T& operator[] (Rank r); // Ϊʲôʹ�����÷������ص�[]:����������ֵ��������ֵ����
	const T& operator[] (Rank r) const; // ����������ֵ�����ذ汾

	Vector<T>& operator= (Vector<T> const& V); // Ϊʲô�����б������β�����-- ����β�����һ����Ҫ
	
	int remove(Rank lo, Rank hi);
	T remove(Rank r); //ɾ����Ϊr��Ԫ�أ�ʹ������ɾ����ɾ��һ��Ԫ�أ���������һ��Ԫ��ɾ����������

	Rank insert(Rank r, T const& e); //����Ԫ��
	Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���

	void sort(Rank lo, Rank hi); //��[lo, hi)����

	void unsort(Rank lo, Rank hi); //��[lo, hi)����
	Rank deduplicate(); //����ȥ��
	Rank uniquify(); //����ȥ��

	// ����
	void traverse(void(*visit)(T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
	/*
	����ָ�룺returnType (*pointerName)(param list);
	
	*/

	template<typename VST>  //������ʹ�ú������󣬿�ȫ�����޸ģ�
	void traverse(VST&visit);
};