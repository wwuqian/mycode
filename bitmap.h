#pragma once
#include<vector>

//哈希的直接定址法
//标记一个整型存在或者不存在。
//相当于key ---只能用于整型，节省空间 
class BitMap
{
public:
	BitMap(size_t range)
	{
		//当range为8以下的时候，会开辟0个空间，会出错
		_bitMap.resize(range/8+1,0);
	}

	void Set(size_t value)
	{
		size_t index = value / 8; //value>>3
		size_t pos = value % 8;

		_bitMap[index] |= (1<<pos);//置1：或1
	}

	void ReSet(size_t value)
	{
		size_t index = value / 8;
		size_t pos = value % 8;

		_bitMap[index] &= ~(1<<pos);//置0:与0
	}

	bool Test(size_t value)
	{
		size_t index = value / 8;
		size_t pos = value % 8;
		
		return _bitMap[index] & (1<<pos);

	}

protected:
	vector<char> _bitMap;
};

void TestBitMap()
{
	BitMap b(-1); //-1转为无符号数就是最大值
	b.Set(5);
	b.Set(999);
	b.Set(1022);
	b.Set(111110000);

	cout<<b.Test(5)<<endl;
	cout<<b.Test(100)<<endl;
	cout<<b.Test(999)<<endl;
	cout<<b.Test(1022)<<endl;
	cout<<b.Test(111110000)<<endl;
}