#pragma once



#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

template <class T>
class FibNode {
public:
	T key;                // �ؼ���(��ֵ)
	int degree;            // ����
	FibNode<T> *left;    // ���ֵ�
	FibNode<T> *right;    // ���ֵ�
	FibNode<T> *child;    // ��һ�����ӽڵ�
	FibNode<T> *parent;    // ���ڵ�
	bool marked;        // �Ƿ�ɾ����һ������

	FibNode(T value):key(value), degree(0), marked(false), 
		left(NULL),right(NULL),child(NULL),parent(NULL) {
			key    = value;
			degree = 0;
			marked = false;
			left   = this;
			right  = this;
			parent = NULL;
			child  = NULL;
	}
};

template <class T>
class FibHeap {
private:
	int keyNum;         // ���нڵ������
	int maxDegree;      // ����
	FibNode<T> *min;    // ��С�ڵ�(ĳ����С�ѵĸ��ڵ�)
	FibNode<T> **cons;    // ���ȵ��ڴ�����

public:
	FibHeap();
	~FibHeap();

	// �½�key��Ӧ�Ľڵ㣬��������뵽쳲���������
	void insert(T key);
	// �Ƴ�쳲��������е���С�ڵ�
	void removeMin();
	// ��other�ϲ�����ǰ����
	void combine(FibHeap<T> *other);
	// ��ȡ쳲�����������С��ֵ�������浽pkey�У��ɹ�����true�����򷵻�false��
	bool minimum(T *pkey);
	// ��쳲��������м�ֵoldkey����Ϊnewkey
	void update(T oldkey, T newkey);
	// ɾ����ֵΪkey�Ľڵ�
	void remove(T key);
	// 쳲����������Ƿ������ֵkey
	bool contains(T key);
	// ��ӡ쳲�������
	void print();
	// ����
	void destroy();

private:
	// ��node��˫�����Ƴ�
	void removeNode(FibNode<T> *node);
	// ��node�ѽ�����root���֮ǰ(ѭ��������)
	void addNode(FibNode<T> *node, FibNode<T> *root);
	// ��˫������b���ӵ�˫������a�ĺ���
	void catList(FibNode<T> *a, FibNode<T> *b);
	// ���ڵ�node���뵽쳲���������
	void insert(FibNode<T> *node);
	// ��"�ѵ���С���"�Ӹ��������Ƴ���
	FibNode<T>* extractMin();
	// ��node���ӵ�root�����
	void link(FibNode<T>* node, FibNode<T>* root);
	// ����consolidate����ռ�
	void makeCons();
	// �ϲ�쳲������ѵĸ�������������ͬ��������
	void consolidate();
	// �޸Ķ���
	void renewDegree(FibNode<T> *parent, int degree);
	// ��node�Ӹ��ڵ�parent���������а����������ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
	void cut(FibNode<T> *node, FibNode<T> *parent);
	// �Խڵ�node����"��������"
	void cascadingCut(FibNode<T> *node) ;
	// ��쳲��������нڵ�node��ֵ����Ϊkey
	void decrease(FibNode<T> *node, T key);
	// ��쳲��������нڵ�node��ֵ����Ϊkey
	void increase(FibNode<T> *node, T key);
	// ����쳲������ѵĽڵ�node�ļ�ֵΪkey
	void update(FibNode<T> *node, T key);
	// ����С��root�в��Ҽ�ֵΪkey�Ľڵ�
	FibNode<T>* search(FibNode<T> *root, T key);
	// ��쳲��������в��Ҽ�ֵΪkey�Ľڵ�
	FibNode<T>* search(T key);
	// ɾ�����node
	void remove(FibNode<T> *node);
	// ����쳲�������
	void destroyNode(FibNode<T> *node);
	// ��ӡ"쳲�������"
	void print(FibNode<T> *node, FibNode<T> *prev, int direction);
};






