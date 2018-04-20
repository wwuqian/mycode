#pragma once
#include<vector>

//��ϣ��ֱ�Ӷ�ַ��
//���һ�����ʹ��ڻ��߲����ڡ�
//�൱��key ---ֻ���������ͣ���ʡ�ռ� 
class BitMap
{
public:
	BitMap(size_t range)
	{
		//��rangeΪ8���µ�ʱ�򣬻Ὺ��0���ռ䣬�����
		_bitMap.resize(range/8+1,0);
	}

	void Set(size_t value)
	{
		size_t index = value / 8; //value>>3
		size_t pos = value % 8;

		_bitMap[index] |= (1<<pos);//��1����1
	}

	void ReSet(size_t value)
	{
		size_t index = value / 8;
		size_t pos = value % 8;

		_bitMap[index] &= ~(1<<pos);//��0:��0
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
	BitMap b(-1); //-1תΪ�޷������������ֵ
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