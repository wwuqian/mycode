#pragma once
#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;

void PrintArray(int* a,size_t n)
{
	for(size_t i = 0; i < n; ++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

//1.插入排序O(N*N)
void InsertSort(int* a,size_t n)
{
	//将[end+1]插入到[0,end]的有序区间
	for(size_t i = 0; i < n-1;++i) //注意边界条件end为下标n-2
	{
		int end = i;
		int tmp = a[end+1];
		while(end >= 0)
		{
			if(a[end] > tmp)
			{
				a[end+1] = a[end];
				--end;
			}
			else
			{
				break;
			}
		}
		a[end+1] = tmp;
	}
}

void TestInsertSort()
{
	int a[] = {4,8,1,3,9,0,2,5,7,6};
	cout<<"插入排序前："<<endl;
	PrintArray(a,sizeof(a)/sizeof(a[0]));
	InsertSort(a,sizeof(a)/sizeof(a[0]));
	cout<<"插入排序后："<<endl;
	PrintArray(a,sizeof(a)/sizeof(a[0]));
}

//希尔排序O(pow(N,1.3)) 
//最好（逆序）O(N) , 最坏（有序）O(N*N)
void ShellSort(int* a,size_t n)
{
	assert(a);
	int gap = n;
	while(gap > 1)
	{
		gap = gap/3+1; //当n<3时,即gap=1,就成了插入排序。

		for(size_t i = 0; i < n-gap; ++i)
		{
			int end = i;
			int tmp = a[end+gap];
			while(end >= 0)
			{
				if(a[end] > tmp)
				{
					a[end+gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end+gap] = tmp;
		}
	}
}

void TestShellSort()
{
	int a[] = {4,8,1,3,9,0,2,5,7,6};
	cout<<"希尔排序前："<<endl;
	PrintArray(a,sizeof(a)/sizeof(a[0]));
	InsertSort(a,sizeof(a)/sizeof(a[0]));
	cout<<"希尔排序后："<<endl;
	PrintArray(a,sizeof(a)/sizeof(a[0]));
}

//2.选择排序:最大和最小的不断交换
void SelectSort(int* a,size_t n)
{
	assert(a);
	int begin = 0;
	int end = n-1;
	while(begin < end)
	{
		int max = begin,min = begin;
		for(int i = begin;i <= end;++i)
		{
			if(a[i] > a[max])
			{
				max = i;
			}
			if(a[i] < a[min])
			{
				min = i;
			}
		}
		swap(a[begin],a[min]);
		if(begin == max)
		{
			max = min;
		}
		swap(a[max],a[end]);
		++begin;//次小...
		--end;  //次大...
	}
}

void TestSelectSort()
{
	int a[] = {7,9,0,1,4,6,5,2,3,8,5};
	cout<<"选择排序前："<<endl;
	PrintArray(a,sizeof(a)/sizeof(a[0]));

	SelectSort(a,sizeof(a)/sizeof(a[0]));
	cout<<"选择排序后："<<endl;
	PrintArray(a,sizeof(a)/sizeof(a[0]));

	int a2[] = {7,9,9,1,5,6,5,5,3,8,9};
	cout<<"选择排序前："<<endl;
	PrintArray(a2,sizeof(a2)/sizeof(a2[0]));

	SelectSort(a2,sizeof(a2)/sizeof(a2[0]));
	cout<<"选择排序后："<<endl;
	PrintArray(a2,sizeof(a2)/sizeof(a2[0]));
}

//3.堆排序:建大堆
void AdjustDown(int* a,int root,size_t n)
{
	size_t parent = root;
	size_t child = parent*2+1;

	while(child < n)
	{
		if(child+1 < n && a[child+1] > a[child])
			++child;
		if(a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = parent*2+1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* a,size_t n)
{
	//建大堆
	for(int i = (n-2)/2; i >= 0; --i)
	{
		AdjustDown(a,i,n);
	}
	int end = n-1;
	while(end > 0)
	{
		swap(a[0],a[end]);
		AdjustDown(a,0,end);
		--end;
	}
}

void TestHeapSort()
{
	int a[] = {2,9,12,15,20,8,3,29,30};
	HeapSort(a,sizeof(a)/sizeof(a[0]));
	PrintArray(a,sizeof(a)/sizeof(a[0]));
}

//4.冒泡排序
void BubbleSort(int a[],size_t n)
{
	int i,j,temp;
	for(i = 0;i < n-1;++i) //进行n-1次外层循环
	{
		for(j = 0;j < n-1-i;++j)
		{
			if(a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}	
}

void TestBubbleSort()
{
	int a[] = {12,23,6,9,18,22,35,120,89,67};
	BubbleSort(a,sizeof(a)/sizeof(a[0]));
	PrintArray(a,sizeof(a)/sizeof(a[0]));
}

//5.快速排序

//5.1 左右指针法[begin,end]
int Partition1(int* a,int begin,int end)
{
	int& key = a[end];
	while(begin < end)
	{
		while(begin < end && a[begin] <= key)
			++begin; //begin找大

		while(begin < end && a[end] >= key)
			--end; //end找小

		if(begin < end)
			swap(a[begin],a[end]);
	}
	swap(a[begin],key);
	return begin;
}

//改进
int GetMidIndex(int* a,int left,int right)
{
	//三数取中法
	int mid = left + (right-left)/2;
	if(a[left] < a[mid])
	{
		if(a[left] > a[right])
			return left;
		else if(a[left] < a[right])
			return right;
		else
			return mid;
	}
	else
	{
		if(a[mid] > a[right])
			return mid;
		else if(a[mid] < a[right])
			return right;
		else
			return left;
	}
}
int Partition2(int* a,int begin,int end)
{
	int mid = GetMidIndex(a,begin,end);
	swap(a[mid],a[end]);

	int& key = a[end];
	while(begin < end)
	{
		//begin找大
		while(begin < end && a[begin] <= key)
			++begin;

		while(begin < end && a[end] >= key)
			--end;
		//end找小

		if(begin < end)
			swap(a[begin],a[end]);
	}
	swap(a[begin],key);
	return begin;
}


//5.2  挖坑法[left,right]
int Partition3(int* a,int begin,int end)
{
	int mid = GetMidIndex(a,begin,end);
	swap(a[mid],a[end]);

	int key = a[end];//不能用引用，因为a[end]改变了，key也就改变了，而key是不改变的。
	while(begin < end)
	{
		while(begin < end && a[begin] <= key)
			++begin;

		if(begin < end)
			a[end] = a[begin];
	
		while(begin < end && a[end] >= key)
			--end;
		
		if(begin < end)
			a[begin] = a[end];
		
	}
	a[begin] = key;
	return begin;
}

//5.3  前后指针法
int Partition4(int* a,int left,int right)
{
	int prev = left-1;
	int cur = left;
	while(cur < right)
	{
		if(a[cur] < a[right] && ++prev !=cur)
		{
			swap(a[cur],a[prev]);
		}
		++cur;
	}
	swap(a[right],a[++prev]);
	return prev;
}

//[left,right]
void QuickSort(int* a,int left,int right)
{
	if(left >= right)
		return;
	if(right-left < 5)
		InsertSort(a+left,right-left+1);
	else
	{
		//int div = Partition1(a,left,right);
		//int div = Partition2(a,left,right);
		int div = Partition4(a,left,right);
		QuickSort(a,left,div-1);
		QuickSort(a,div+1,right);
	}
}

void TestQuickSort()
{
	int a[] = {12,17,18,3,9,7,4,29,53,6};
	//int a[] = {7,4,21,8,16,19,20,9,10};
	QuickSort(a,0,sizeof(a)/sizeof(a[0])-1);
	PrintArray(a,sizeof(a)/sizeof(a[0]));
}

//5.4  快速排序非递归
void QuickSortNonR(int* a,int left,int right)
{
	stack<int> s;
	s.push(right);
	s.push(left);

	while(!s.empty())
	{
		int begin = s.top();
		s.pop();
		int end = s.top();
		s.pop();

		int div = Partition2(a,begin,end);

		//[begin,div-1]
		if(begin < div-1)
		{
			s.push(div-1);
			s.push(begin);
		}

		//[div+1,end]
		if(div+1 < end)
		{
			s.push(end);
			s.push(div+1);
		}
	}
}

void TestQuickNonR()
{
	int a[] = {12,3,7,9,5,20,32,36,10};
	QuickSortNonR(a,0,sizeof(a)/sizeof(a[0])-1);
	PrintArray(a,sizeof(a)/sizeof(a[0]));
}

//6.归并排序
void _MergeSort(int* a,int left,int right,int* tmp)
{
	if(left >= right)
		return;

	//不断二分区间
	int mid = left + ((right-left)>>2);//移位操作比除法更高效
	_MergeSort(a,left,mid-1,tmp);
	_MergeSort(a,mid+1,right,tmp);

	//合并区间：每次递归返回都进行合并两个区间
	int begin1 = left, end1 = mid;
	int begin2 = mid+1, end2 = right;
	size_t index = left;

	while(begin1 <= end1 && begin2 <= end2)
	{
		if(a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];
	}
	while(begin1 <= end1)
		tmp[index++] = a[begin1++];
	while(begin2 <= end2)
		tmp[index++] = a[begin2++];

	//将tmp中的数据拷贝到a中
	memcpy(a+left,tmp+left,sizeof(int)*(right-left+1));
}

void MergeSort(int* a,size_t n)
{
	int* tmp = new int[n];
	_MergeSort(a,0,n-1,tmp);
	delete[] tmp;
}

void TestMergeSort()
{
	int a[] = {12,34,78,56,9,3,7,21};
	MergeSort(a,sizeof(a)/sizeof(a[0]));
	PrintArray(a,sizeof(a)/sizeof(a[0]));
}

//7.基数排序（radix sort）
int GetDigits(int* a,size_t n)
{
	int base = 10;
	int digits = 1;  //位数
	for(size_t i = 0; i < n; ++i)
	{
		while(a[i] >= base)
		{
			++digits;
			base *= 10;
		}
	}
	return digits;
}

void LSDSort(int* a,size_t n)
{
	int digits = GetDigits(a,n);
	int* buckets = new int[n];

	int base = 1;
	for(size_t i = 0; i < digits; ++i)
	{
		//统计0-9号桶中数据的个数
		int counts[10] = {0};
		for(size_t i = 0; i < n; ++i)
		{
			int num = (a[i]/base)%10; //num为该数字的个位数字
			counts[num]++;
		}

		//计算定位数组
		int starts[10] = {0};
		starts[0] = 0;
		for(size_t i = 1; i < 10; ++i)
		{
			starts[i] = starts[i-1] + counts[i-1];
		}
		
		for(size_t i = 0; i < n; ++i)
		{
			int num = a[i]%10;
			int& pos = starts[num];
			buckets[pos] = a[i];
			++pos;
		}
		memcpy(a,buckets,sizeof(int)*n);
		base *= 10;
	}

	delete[] buckets;

}

void TestRadixSort()
{
	int a[] = {10,6,8,34,54,18,19,40,26,76};
	cout<<"基数排序前："<<endl;
	PrintArray(a,sizeof(a)/sizeof(a[0]));
	cout<<"基数排序后："<<endl;
	LSDSort(a,sizeof(a)/sizeof(a[0]));
	PrintArray(a,sizeof(a)/sizeof(a[0]));
}
