#pragma once
#include<vector>
#include<map>

class UnionFindSet
{
public:
	UnionFindSet(size_t N)
	{
		_sets.resize(N,-1);
	}
	
	bool IsInOneSet(int x1,int x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	}

	int FindRoot(int x)
	{
		while(_sets[x] >= 0)
		{
			x = _sets[x];
		}
		return x;
	}

	void Union(int x,int y)
	{
		int root1 = FindRoot(x);
		int root2 = FindRoot(y);
		if(root1 != root2)
		{
			_sets[root1] += _sets[root2];
			_sets[root2] = root1; 
		}
	}

	size_t SetSize()
	{
		size_t count = 0;
		for(int i = 0; i < _sets.size(); ++i)
		{
			if(_sets[i] < 0)
				++count;
		}
		return count;
	}

protected:
	vector<int> _sets;
};

//朋友圈问题：n个人和m对关系，两个人是直接或间接的关系，则同属于一个朋友圈，求n个人共有几个朋友圈。
//例：n=5 ,m=3 r={(1,2),(2,3),(4,5)}; 共有2个朋友圈。
int Friends(int n,int m,int r[][2])
{
	UnionFindSet s(n+1);
	for(size_t i = 0; i < m; ++i)
	{
		s.Union(r[i][0],r[i][1]);
	}
	return s.SetSize()-1;
}

void TestFriend()
{
	const int n = 5;
	const int m = 3;
	int r[m][2] = {{1,2},{2,3},{4,5}};
	printf("朋友圈有 %d 个\n",Friends(n,m,r));
}

//void TestFriend1()
//{
//	const int m = 3;
//	char* a[] = {"图图","小美","小雅","小擎","小吴"};
//	int n = sizeof(a);
//	map<string,int> numNameMap;
//	numNameMap["图图"] = 1;
//	numNameMap["小美"] = 2;
//	numNameMap["小雅"] = 3;
//	numNameMap["小擎"] = 4;
//	numNameMap["小吴"] = 5;
//
//	int r[m][2] = {{1,2},{2,3},{4,5}};
//	printf("朋友圈有 %d 个\n",Friends(n,m,r));
//}
