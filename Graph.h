#pragma once
#include<vector>
#include<string>
#include<assert.h>
#include<map>
#include<queue>
#include"UnionFindSet.h"

//临接矩阵法：顶点集合，边的集合，无向图
template<class V,class W,bool digraph = false>
class GraphMartix
{
public:
	GraphMartix(V* vertexs,size_t n)
	{
		_vertexs.reserve(n);
		for(size_t i = 0; i < n; ++i)
		{
			_vertexs.push_back(vertexs[i]);
			_indexMap[vertexs[i]] = i;
		}

		_martix.resize(n);
		for(size_t i = 0; i < _martix.size(); ++i)
		{
			_martix[i].resize(n,W());
		}
	}

	size_t GetVertexIndex(const V& v)
	{
		/*for(size_t i = 0; i < _vertexs.size(); ++i)
		{
			if(_vertexs[i] == v)
				return i;
		}
		assert(false);*/

		//有了map，每个顶点的索引已建立，不用每次再查找一遍
		assert(_indexMap.count(v));
		return _indexMap[v];
	}

	void AddEdge(const V& src, const V& dst, const W& w)
	{
		size_t srcIndex = GetVertexIndex(src);
		size_t dstIndex = GetVertexIndex(dst);

		_martix[srcIndex][dstIndex] = w;
		if(digraph == false)
		{
			_martix[dstIndex][srcIndex] = w;
		}

	}

	W& GetEdge(const V& src, const V& dst)
	{
		size_t srcIndex = GetVertexIndex(src);
		size_t dstIndex = GetVertexIndex(dst);

		return _martix[srcIndex][dstIndex];
	}

protected:
	map<V,size_t> _indexMap;      //给顶点建立索引下标
	vector<V> _vertexs;           //顶点集合
	vector<vector<W>> _martix;    //临接矩阵(存的是边)
};

void TestGraphMartix()
{
	string city[] = {"西安","渭南","宝鸡","汉中","商洛"};
	GraphMartix<string,int> gm(city,sizeof(city)/sizeof(city[0]));
	gm.AddEdge("西安","宝鸡",60); //西安到宝鸡60分钟
	gm.AddEdge("西安","渭南",19);
	gm.AddEdge("商洛", "西安",50);
	gm.AddEdge("宝鸡", "商洛", 40);

	cout<<"商洛->西安"<<gm.GetEdge("商洛", "西安")<<endl;
	cout<<"西安->宝鸡"<<gm.GetEdge("西安", "宝鸡")<<endl;
}

//临接表法：顶点集合，边的集合，无向图
template<class W>
struct EdgeNode
{
	W _w;
	EdgeNode<W>* _next;
	int _src;
	int _dst;

	EdgeNode(int src, int dst,const W& w)
		:_src(src)
		,_dst(dst)
		,_w(w)
		,_next(NULL)
	{}
};

template<class V, class W, bool IsDirected = false>
class GraphLinkTable
{
	typedef EdgeNode<W> Edge;
public:
	GraphLinkTable()
	{}

	GraphLinkTable(V* vertexs, size_t n)
	{
		_vertexs.reserve(n);
		for(size_t i = 0; i < n; ++i)
		{
			_vertexs.push_back(vertexs[i]);
			_indexMap[vertexs[i]] = i;
		}

		_linkTable.resize(n,NULL);
	}

	size_t GetVertexIndex(const V& v)
	{
		assert(_indexMap.count(v));
		return _indexMap[v];
	}

	void _AddEdge(size_t srcIndex, size_t dstIndex,const W& w)
	{
		//头插
		Edge* edge = new Edge(srcIndex,dstIndex,w);
		edge->_next = _linkTable[srcIndex];
		_linkTable[srcIndex] = edge;
	}

	void AddEdge(const V& src, const V& dst, const W& w)
	{
		size_t srcIndex = GetVertexIndex(src);
		size_t dstIndex = GetVertexIndex(dst);
		
		_AddEdge(srcIndex, dstIndex, w);
		if(IsDirected == false) //无向图
		{
			//无向图每条边在临接表中出现两次
			_AddEdge(dstIndex, srcIndex, w);
		}
	}

	Edge* GetEdge(const V& src, const V& dst)
	{
		size_t srcIndex = GetVertexIndex(src);
		size_t dstIndex = GetVertexIndex(dst);

		Edge* edge = _linkTable[srcIndex];
		while(edge)
		{
			if(edge->_dst == dstIndex)
				return edge;

			edge = edge->_next;
		}

		return NULL;
	}

	//图的深度优先遍历：一路走到头，再往回退，看还有没有其他的路，有继续往深走。
	//遍历的是顶点
	void DFS(const V& src)
	{
		vector<bool> visited;  //是否访问过
		size_t srcIndex = GetVertexIndex(src);
		visited.resize(_vertexs.size(), false);
		_DFS(srcIndex, visited);
		cout<<endl;
	}

	void _DFS(size_t srcIndex, vector<bool>& visited)
	{
		cout<<srcIndex<<":"<<_vertexs[srcIndex]<<"->";
		visited[srcIndex] = true;

		Edge* cur = _linkTable[srcIndex];
		while(cur)
		{
			if(visited[cur->_dst] == false)
				_DFS(cur->_dst, visited);

			cur = cur->_next;
		}
	}

	//图的广度优先遍历：一层一层遍历,队列
	void GFS(const V& src)
	{
		size_t srcIndex = GetVertexIndex(src);
		queue<size_t> q;
		q.push(srcIndex);
		
		vector<bool> visited;
		visited.resize(_vertexs.size(),false);
		while(!q.empty())
		{
			size_t front = q.front();
			q.pop();
			if(visited[front] == true)
			{
				continue;
			}
			cout<<front<<":"<<_vertexs[front]<<"->";
			visited[front] = true;

			Edge* cur = _linkTable[front];
			while(cur)
			{
				if(visited[cur->_dst] == false)
					q.push(cur->_dst);
			}
			cur = cur->_next;
		}
		cout<<endl;
	}

	//最小生成树
	bool Kruskal(GraphLinkTable<V,W,IsDirected>& minTree)
	{
		assert(IsDirected == false);

		minTree._vertexs = _vertexs;
		minTree._indexMap = _indexMap;
		minTree._linkTable.resize(_vertexs.size(),NULL);

		vector<Edge*> edges;
		for(size_t i = 0; i < _linkTable.size();++i)
		{
			Edge* cur = _linkTable[i];
			while(cur)
			{
				if(cur->_src < cur->_dst)
					edges.push_back(cur);

				cur = cur->_next;
			}
		}

		struct Less
		{
			bool operator()(const Edge* left,const Edge* right)
			{
				return left->_w < right->_w;
			}
		};

		sort(edges.begin(),edges.end(),Less());
		size_t N = _vertexs.size()-1;
		UnionFindSet ufs(_vertexs.size());
		for(size_t i = 0; i < edges.size();++i)
		{
			Edge* edge = edges[i];
			if(ufs.IsInOneSet(edge->_src,edge->_dst) == false)
			{
				minTree._AddEdge(edge->_src,edge->_dst,edge->_w);
				minTree._AddEdge(edge->_dst,edge->_src,edge->_w);
				ufs.Union(edge->_src,edge->_dst);

				if(--N == 0)
					return true;
			}
		}

		return false;
	}

protected:
	map<V,size_t> _indexMap;    //顶点的索引表
	vector<V> _vertexs;         //顶点集合
	vector<Edge*> _linkTable;   //临接表：顺序表存放每个链表的头结点
};

void TestGraphLinkTable()
{
	string city[] = {"西安","渭南","宝鸡","蓝田","商洛","吴起"};
	GraphLinkTable<string,int> gl(city,sizeof(city)/sizeof(city[0]));
	gl.AddEdge("西安","宝鸡",300); //西安到宝鸡300千米
	gl.AddEdge("西安","渭南",600);
	gl.AddEdge("西安","蓝田",200);
	gl.AddEdge("西安","商洛",400);
	gl.AddEdge("蓝田","渭南",300);
	gl.AddEdge("渭南","商洛",200);
	gl.AddEdge("商洛","吴起",500);
	gl.AddEdge("宝鸡", "商洛", 100);

	cout<<"商洛->西安"<<gl.GetEdge("商洛", "西安")->_w<<endl;
	cout<<"西安->宝鸡"<<gl.GetEdge("西安", "宝鸡")->_w<<endl;

	//gl.GFS("西安");  //广度遍历
	//gl.GFS("商洛");
	//gl.DFS("西安"); //深度遍历
	//gl.DFS("商洛");

	GraphLinkTable<string, int> minTree;
	gl.Kruskal(minTree);
}
