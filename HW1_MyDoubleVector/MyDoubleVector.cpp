#pragma once

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "MyDoubleVector.h"

using namespace std;

MyDoubleVector::MyDoubleVector()//Default constructor
{
	//Precondition :
	//Postcondition :Default constructor 로서 private meber 변수를 초기화 시켜주면서 MyDoubleVector 객체를 생성합니다.
	data = new double[DEFAULT_CAPACITY];
	cap = DEFAULT_CAPACITY;
	used = 0;
}
MyDoubleVector::MyDoubleVector(const MyDoubleVector& source)//Copy constructor for deep copy
{
	//Precondition : source를 parameter 하는 MyDoubleVector 객체
	//Postcondition : Copy constructor 로서 source라는 객체와 deepcopy를 통해 동일한 값으로 MyDoubleVector 객체를 생성합니다.
	data = new double[source.cap];
	cap = source.cap;
	used = source.used;
	copy(source.data, source.data + used, data);
}
MyDoubleVector::~MyDoubleVector()
{
	//Precondition : 
	//Postcondition : Destructor로서 MyDoubleVector 객체를 소멸시킵니다.
	delete[] data;
}
MyDoubleVector& MyDoubleVector::operator =(const MyDoubleVector& source)//Assignment operator (=) for deep copy
{
	//Precondition : source를 parameter 하는 MyDoubleVector 객체
	//Postcondition : Assignment operator 로서 source라는 객체와 deepcopy를 통해 동일한 값으로 MyDoubleVector 객체를 생성합니다.
	//Chaining assignment should be possible 을 가능하기 위해 MyDoubleVector& 반환형으로 하였습니다.
	double *new_data;

	if (this == &source)//먼저 이미 source 객체와 현재 객체가 같은지 확인합니다.
		return *this;

	if (cap != source.cap)//현재 객체의 capcity값이 source 객체 capacity와 다르다면 같게 만들어줍니다.
	{
		new_data = new double[source.cap];
		delete[] data;
		data = new_data;
		cap = source.cap;
	}

	used = source.used;//algorithm 헤더 안에 있는 copy함수를 통해 data 값들을 같게 해줍니다.
	copy(source.data, source.data + used, data);
	return *this;
}
void MyDoubleVector::operator +=(const MyDoubleVector& addend)//Appends RHS object to LHS one.
{
	//Precondition : append를 parameter 하는 MyDoubleVector 객체
	//Postcondition : append 객체(RHS)의 데이터를 현재 객체(LHS) 뒤에 추가합니다.
	if (used + addend.used > cap)
		reserve(used + addend.used);

	copy(addend.data, addend.data + addend.used, data + used);
	used += addend.used;
}
double& MyDoubleVector::operator [](const int& index)
{
	//Precondition : size_t형의 index, index의 범위 : 0 <=index < used
	//Postcondition : index값에 따른 객체 배열의 값을 double& 형으로 return해줍니다.
	//다만 Precondition이 만족하지 못하는 경우(index값의 범위가 배열의 범위가 아닌 경우)에는 범위 초과 했다는 문장 출력과 프로그램을 종료합니다.
	if (index<0 || index>used)//index값의 범위가 배열의 범위가 아닐 경우
	{
		cout << "the requested position is out of range" << endl;
		exit(0);//terminate the program
	}
	return data[index];
}
MyDoubleVector MyDoubleVector::operator +(const MyDoubleVector &source)
{
	//Precondition : source를 parameter 하는 MyDoubleVector 객체의 size와 현재 객체의 size가 동일해야합니다.
	//Postcondition : source 객체와 현재 객체의 data를 더한 data를 가진 객체를 리턴합니다.
	MyDoubleVector result(*this);
	for (size_t i = 0; i < used; i++)
		result.data[i] = this->data[i] + source.data[i];
	return result;
}
MyDoubleVector MyDoubleVector::operator -(const MyDoubleVector &source)
{
	//Precondition : source를 parameter 하는 MyDoubleVector 객체의 size와 현재 객체의 size가 동일해야합니다.
	//Postcondition : 현재 객체data 에서 source 객체의 data 값을 뺀 data를 가진 객체를 리턴합니다.
	MyDoubleVector result(*this);
	for (size_t i = 0; i < used; i++)
		result.data[i] = this->data[i] - source.data[i];
	return result;
}
double MyDoubleVector::operator *(const MyDoubleVector &source)
{
	//Precondition : source를 parameter 하는 MyDoubleVector 객체의 size와 현재 객체의 size가 동일해야합니다.
	//Postcondition : source 객체와 현재 객체의 data를 내적(각 배열 값끼리 곱해서 더함) 을 하고 return 합니다.
	double result=0;
	for (size_t i = 0; i < used; i++)
		result += this->data[i] * source.data[i];
	return result;
}
MyDoubleVector MyDoubleVector::operator -()
{
	//Precondition :
	//Postcondition : 현재 객체내의 data 값들에 -1 을 곱하여 양수는 음수, 음수는 양수가 되도록 한 data를 가진 객체를 리턴합니다.
	MyDoubleVector result(*this);
	for (size_t i = 0; i < used; i++)
		result.data[i] = -data[i];
	return result;
}
bool MyDoubleVector:: operator ==(const MyDoubleVector& source)
{
	//Precondition : source를 parameter 하는 MyDoubleVector 객체
	//Postcondition : source를 parameter로 하는 개체와 현재 객체의 size(used)가 같은지 확인을 먼저 합니다. 같지 않다면 false를 return합니다.
	//size(used)가 같다면 비교를 해서 같으면 ture가 다르면 false가 return됩니다.
	if (used != source.used)
		return false;
	for (size_t i = 0; i < used; i++)
		if (data[i] != source.data[i])
			return false;
	return true;
}
void MyDoubleVector::operator ()(const double& element)
{
	//Precondition : double(dobule)형의 element
	//Postcondition : 현재 객체의 data값을 모두 element값으로 변경합니다.
	for (size_t i = 0; i < used; i++)
		data[i] = element;
}
void MyDoubleVector::pop_back()
{
	//Precondition :
	//Postcondition : 현재 객체의 data값의 마지막 element(항목)을 없애고, 현재 객체의 size(used)를 1 감소 시킵니다.
	double *larger_array;
	larger_array = new double[cap];

	copy(data, data + --used, larger_array);
	delete[] data;
	data = larger_array;
}
void MyDoubleVector::push_back(double x)
{
	//Precondition : double형의 x
	//Postcondition : 현재 객체의 data값 size(used)가 capacity와 같다면 size(used)를 하나 늘리고 그 마지막 자리에는 x의 값이 들어갑니다.
	if (used == cap)
		reserve(used + 1);//크기를 1 늘려야할 때 reserve 함수를 사용합니다.
	data[used++] = x;//data를 추가한 후에 used를 1 증가시킵니다.
}
size_t MyDoubleVector::capacity() const { return cap; }
//Precondition :
//Postcondition : return cap
size_t MyDoubleVector::size() const { return used; }
//Precondition :
//Postcondition : return used
void MyDoubleVector::reserve(size_t new_cap)
{
	//Precondition : size_t형의 new_cap
	//Postcondition : 현재 객채의 capacity(cap)가 new_cap 과 같다면 바로 함수를 빠져나가고
	//현재 객채의 capacity(cap)가 used보다 작다면 new_cap은 used로
	//위 두 조건을 모두 만족 하지 않는다면 현재 객체의 data의 내용을 복사해주면서 capacity는 new_cap으로 변경시켜 줍니다.
	double *larger_array;

	if (new_cap == cap)
		return; 

	if (new_cap < used)
		new_cap = used;

	larger_array = new double[new_cap];
	copy(data, data + used, larger_array);
	delete[] data;
	data = larger_array;
	cap = new_cap;
}
bool MyDoubleVector::empty() const
{
	//Precondition :
	//Postcondition : 현재 객체의 size(used)가 0인지 학인하고, 그렇다면 true 그렇지 않으면 false를 bool 형으로 return 
	if (used == 0)
		return true;
	else
		return false;
}
void MyDoubleVector::clear()
{
	//Precondition :
	//Postcondition : 현재 객체의 data를 소멸시키고 새로 data를 만들어 주면서 size(used)는 0으로 합니다.
	delete[] data;
	data = new double[cap];
	used = 0;
}
