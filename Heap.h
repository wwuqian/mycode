#pragma once
#include <vector>

template<class T>
struct Less //С��
{
	bool operator()(const T& left,const T& right)
	{
		return left < right;
	}
};

template<class T>
struct Greater  //���
{
	bool operator()(const T& left,const T& right)
	{
		return left > right;
	}
};
template<class T,class Compare = Less<T>>
class Heap
{
public:
	Heap()
	{}

	Heap(T* a,size_t n)
	{
		//_a.resize(n);
		//for(size_t i = 0; i<n; ++i)
		//	_a[i] = a[i];
		
		_a.reserve(n);
		for(size_t i = 0; i < n; ++i)
		{
			_a.push_back(a[i]);
		}
		//����
		for (int i = (_a.size()-2)/2; i>=0; --i)//O(N*lgN)
		{
			_AdjustDown(i); 
		}
	}

	void Push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size()-1);
	}

	void Pop()
	{
		assert(!_a.empty());
		swap(_a[0],_a[_a.size()-1]);
		_a.pop_back();
		_AdjustDown(0);
	}
      
	const T& Top()
	{
		assert(!_a.empty());
		return _a[0];
	}

	size_t Size() 
	{
		return _a.size();
	}

	bool empty()
	{
		return _a.empty();
	}

	bool IsHeap()
	{
		for(size_t i=0; i<=(_a.size()-2)/2; ++i)
		{
			if(_a[i]<_a[i*2+1] || ((i*2+2)<_a.size() && _a[i]<_a[i*2+2]))
				return false;
		}
		return true;
	}
protected:
	void _AdjustDown(int root)
	{
		Compare com;
		int parent = root;
		int child = parent*2+1;

		while(child < _a.size())
		{
			if(child+1 < _a.size() &&com(_a[child+1],_a[child]))
			{
				++child;
			}

			if(com(_a[child], _a[parent]))
			{
				swap(_a[child],_a[parent]);
				parent = child;
				child = parent*2+1;
			}
			else
			{
				break;
			}
		}
	}

	void _AdjustUp(int child)
	{
		Compare com;
		int parent = (child-1)/2;
		while(parent >= 0)
		{
			if(com(_a[child],_a[parent]))
			{
				swap(_a[parent],_a[child]);
				child = parent;
				parent = (child-1)/2;
			}
			else
			{
				break;
			}
		}
	}
protected:
	vector<T> _a;
};

void TestHeap()
{
	int a[] = {12,1,5,8,27,18,10,20,25,16,13};
	Heap<int,Less<int>> hp1(a,sizeof(a)/sizeof(a[0]));

}


//���ȼ�����
template<class T,class Compare = Less<int>>
class PriorityQueue
{
public:
	PriorityQueue(Heap<T,Compare> heap)
		:_hp(heap)
	{}

	void Push(const T& x)
	{
		_hp.Push(x);
	}

	void Pop()
	{
		_hp.Pop();
	}

	const T& Top()
	{
		return _hp.Top();
	}

protected:
	Heap<T,Compare> _hp;
};

void TestPriorityQueue()
{
	int a[] = {12,1,5,8,27,18,10,20,25,16,13};
	Heap<int,Less<int>> hp2(a,sizeof(a)/sizeof(a[0]));
 	PriorityQueue<int,Less<int>> p(hp2);
	p.Pop();
	p.Push(3);
	p.Top();

}

//TopK���⣺С��
const size_t N = 10000;
const size_t K = 10;

void AdjustDown(int* heap,int n,int root)
{
	assert(heap);

	int parent = root;
	int child = parent*2+1;

}

void TopK()
{
	int a[N] = {0};
	for (size_t i = 0; i < N; ++i)
	{
		a[i] = rand()%N;
	}
	a[0] = N+100;
	a[100] = N+101;
	a[150] = N+102;
	a[2] = N+103;
	a[50] = N+104;
	a[500] = N+105;
	a[1200] = N+106;
	a[8888] = N+107;
	a[200] = N+108;
	a[700] = N+109;
	a[5000] = N+110;

	int Heap[K] = {0};
	for (size_t i = 0;i < K;++i)
	{
		Heap[i] = a[i];
	}
	//����
	for (int i = (K-2)/2;i >= 0;--i)
	{
		AdjustDown(Heap,K,i);
	}

	for (size_t i = K;i < N;++i)
	{
		if (a[i] > Heap[0])
		{
			Heap[0] = a[i];
			AdjustDown(Heap,K,0);
		}
	}

	for (size_t i = 0;i < K;++i)
	{
		cout<<Heap[i]<<" ";
	}
}

void HeapSort() //������
{

}