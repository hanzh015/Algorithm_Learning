#pragma once



#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

template <class T>
class FibNode {
public:
	T key;                // 关键字(键值)
	int degree;            // 度数
	FibNode<T> *left;    // 左兄弟
	FibNode<T> *right;    // 右兄弟
	FibNode<T> *child;    // 第一个孩子节点
	FibNode<T> *parent;    // 父节点
	bool marked;        // 是否被删除第一个孩子

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
	int keyNum;         // 堆中节点的总数
	int maxDegree;      // 最大度
	FibNode<T> *min;    // 最小节点(某个最小堆的根节点)
	FibNode<T> **cons;    // 最大度的内存区域

public:
	FibHeap();
	~FibHeap();

	// 新建key对应的节点，并将其插入到斐波那契堆中
	void insert(T key);
	// 移除斐波那契堆中的最小节点
	void removeMin();
	// 将other合并到当前堆中
	void combine(FibHeap<T> *other);
	// 获取斐波那契堆中最小键值，并保存到pkey中；成功返回true，否则返回false。
	bool minimum(T *pkey);
	// 将斐波那契堆中键值oldkey更新为newkey
	void update(T oldkey, T newkey);
	// 删除键值为key的节点
	void remove(T key);
	// 斐波那契堆中是否包含键值key
	bool contains(T key);
	// 打印斐波那契堆
	void print();
	// 销毁
	void destroy();

private:
	// 将node从双链表移除
	void removeNode(FibNode<T> *node);
	// 将node堆结点加入root结点之前(循环链表中)
	void addNode(FibNode<T> *node, FibNode<T> *root);
	// 将双向链表b链接到双向链表a的后面
	void catList(FibNode<T> *a, FibNode<T> *b);
	// 将节点node插入到斐波那契堆中
	void insert(FibNode<T> *node);
	// 将"堆的最小结点"从根链表中移除，
	FibNode<T>* extractMin();
	// 将node链接到root根结点
	void link(FibNode<T>* node, FibNode<T>* root);
	// 创建consolidate所需空间
	void makeCons();
	// 合并斐波那契堆的根链表中左右相同度数的树
	void consolidate();
	// 修改度数
	void renewDegree(FibNode<T> *parent, int degree);
	// 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
	void cut(FibNode<T> *node, FibNode<T> *parent);
	// 对节点node进行"级联剪切"
	void cascadingCut(FibNode<T> *node) ;
	// 将斐波那契堆中节点node的值减少为key
	void decrease(FibNode<T> *node, T key);
	// 将斐波那契堆中节点node的值增加为key
	void increase(FibNode<T> *node, T key);
	// 更新斐波那契堆的节点node的键值为key
	void update(FibNode<T> *node, T key);
	// 在最小堆root中查找键值为key的节点
	FibNode<T>* search(FibNode<T> *root, T key);
	// 在斐波那契堆中查找键值为key的节点
	FibNode<T>* search(T key);
	// 删除结点node
	void remove(FibNode<T> *node);
	// 销毁斐波那契堆
	void destroyNode(FibNode<T> *node);
	// 打印"斐波那契堆"
	void print(FibNode<T> *node, FibNode<T> *prev, int direction);
};






