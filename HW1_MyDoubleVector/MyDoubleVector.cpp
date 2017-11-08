#pragma once

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "MyDoubleVector.h"

using namespace std;

MyDoubleVector::MyDoubleVector()//Default constructor
{
	//Precondition :
	//Postcondition :Default constructor �μ� private meber ������ �ʱ�ȭ �����ָ鼭 MyDoubleVector ��ü�� �����մϴ�.
	data = new double[DEFAULT_CAPACITY];
	cap = DEFAULT_CAPACITY;
	used = 0;
}
MyDoubleVector::MyDoubleVector(const MyDoubleVector& source)//Copy constructor for deep copy
{
	//Precondition : source�� parameter �ϴ� MyDoubleVector ��ü
	//Postcondition : Copy constructor �μ� source��� ��ü�� deepcopy�� ���� ������ ������ MyDoubleVector ��ü�� �����մϴ�.
	data = new double[source.cap];
	cap = source.cap;
	used = source.used;
	copy(source.data, source.data + used, data);
}
MyDoubleVector::~MyDoubleVector()
{
	//Precondition : 
	//Postcondition : Destructor�μ� MyDoubleVector ��ü�� �Ҹ��ŵ�ϴ�.
	delete[] data;
}
MyDoubleVector& MyDoubleVector::operator =(const MyDoubleVector& source)//Assignment operator (=) for deep copy
{
	//Precondition : source�� parameter �ϴ� MyDoubleVector ��ü
	//Postcondition : Assignment operator �μ� source��� ��ü�� deepcopy�� ���� ������ ������ MyDoubleVector ��ü�� �����մϴ�.
	//Chaining assignment should be possible �� �����ϱ� ���� MyDoubleVector& ��ȯ������ �Ͽ����ϴ�.
	double *new_data;

	if (this == &source)//���� �̹� source ��ü�� ���� ��ü�� ������ Ȯ���մϴ�.
		return *this;

	if (cap != source.cap)//���� ��ü�� capcity���� source ��ü capacity�� �ٸ��ٸ� ���� ������ݴϴ�.
	{
		new_data = new double[source.cap];
		delete[] data;
		data = new_data;
		cap = source.cap;
	}

	used = source.used;//algorithm ��� �ȿ� �ִ� copy�Լ��� ���� data ������ ���� ���ݴϴ�.
	copy(source.data, source.data + used, data);
	return *this;
}
void MyDoubleVector::operator +=(const MyDoubleVector& addend)//Appends RHS object to LHS one.
{
	//Precondition : append�� parameter �ϴ� MyDoubleVector ��ü
	//Postcondition : append ��ü(RHS)�� �����͸� ���� ��ü(LHS) �ڿ� �߰��մϴ�.
	if (used + addend.used > cap)
		reserve(used + addend.used);

	copy(addend.data, addend.data + addend.used, data + used);
	used += addend.used;
}
double& MyDoubleVector::operator [](const int& index)
{
	//Precondition : size_t���� index, index�� ���� : 0 <=index < used
	//Postcondition : index���� ���� ��ü �迭�� ���� double& ������ return���ݴϴ�.
	//�ٸ� Precondition�� �������� ���ϴ� ���(index���� ������ �迭�� ������ �ƴ� ���)���� ���� �ʰ� �ߴٴ� ���� ��°� ���α׷��� �����մϴ�.
	if (index<0 || index>used)//index���� ������ �迭�� ������ �ƴ� ���
	{
		cout << "the requested position is out of range" << endl;
		exit(0);//terminate the program
	}
	return data[index];
}
MyDoubleVector MyDoubleVector::operator +(const MyDoubleVector &source)
{
	//Precondition : source�� parameter �ϴ� MyDoubleVector ��ü�� size�� ���� ��ü�� size�� �����ؾ��մϴ�.
	//Postcondition : source ��ü�� ���� ��ü�� data�� ���� data�� ���� ��ü�� �����մϴ�.
	MyDoubleVector result(*this);
	for (size_t i = 0; i < used; i++)
		result.data[i] = this->data[i] + source.data[i];
	return result;
}
MyDoubleVector MyDoubleVector::operator -(const MyDoubleVector &source)
{
	//Precondition : source�� parameter �ϴ� MyDoubleVector ��ü�� size�� ���� ��ü�� size�� �����ؾ��մϴ�.
	//Postcondition : ���� ��üdata ���� source ��ü�� data ���� �� data�� ���� ��ü�� �����մϴ�.
	MyDoubleVector result(*this);
	for (size_t i = 0; i < used; i++)
		result.data[i] = this->data[i] - source.data[i];
	return result;
}
double MyDoubleVector::operator *(const MyDoubleVector &source)
{
	//Precondition : source�� parameter �ϴ� MyDoubleVector ��ü�� size�� ���� ��ü�� size�� �����ؾ��մϴ�.
	//Postcondition : source ��ü�� ���� ��ü�� data�� ����(�� �迭 ������ ���ؼ� ����) �� �ϰ� return �մϴ�.
	double result=0;
	for (size_t i = 0; i < used; i++)
		result += this->data[i] * source.data[i];
	return result;
}
MyDoubleVector MyDoubleVector::operator -()
{
	//Precondition :
	//Postcondition : ���� ��ü���� data ���鿡 -1 �� ���Ͽ� ����� ����, ������ ����� �ǵ��� �� data�� ���� ��ü�� �����մϴ�.
	MyDoubleVector result(*this);
	for (size_t i = 0; i < used; i++)
		result.data[i] = -data[i];
	return result;
}
bool MyDoubleVector:: operator ==(const MyDoubleVector& source)
{
	//Precondition : source�� parameter �ϴ� MyDoubleVector ��ü
	//Postcondition : source�� parameter�� �ϴ� ��ü�� ���� ��ü�� size(used)�� ������ Ȯ���� ���� �մϴ�. ���� �ʴٸ� false�� return�մϴ�.
	//size(used)�� ���ٸ� �񱳸� �ؼ� ������ ture�� �ٸ��� false�� return�˴ϴ�.
	if (used != source.used)
		return false;
	for (size_t i = 0; i < used; i++)
		if (data[i] != source.data[i])
			return false;
	return true;
}
void MyDoubleVector::operator ()(const double& element)
{
	//Precondition : double(dobule)���� element
	//Postcondition : ���� ��ü�� data���� ��� element������ �����մϴ�.
	for (size_t i = 0; i < used; i++)
		data[i] = element;
}
void MyDoubleVector::pop_back()
{
	//Precondition :
	//Postcondition : ���� ��ü�� data���� ������ element(�׸�)�� ���ְ�, ���� ��ü�� size(used)�� 1 ���� ��ŵ�ϴ�.
	double *larger_array;
	larger_array = new double[cap];

	copy(data, data + --used, larger_array);
	delete[] data;
	data = larger_array;
}
void MyDoubleVector::push_back(double x)
{
	//Precondition : double���� x
	//Postcondition : ���� ��ü�� data�� size(used)�� capacity�� ���ٸ� size(used)�� �ϳ� �ø��� �� ������ �ڸ����� x�� ���� ���ϴ�.
	if (used == cap)
		reserve(used + 1);//ũ�⸦ 1 �÷����� �� reserve �Լ��� ����մϴ�.
	data[used++] = x;//data�� �߰��� �Ŀ� used�� 1 ������ŵ�ϴ�.
}
size_t MyDoubleVector::capacity() const { return cap; }
//Precondition :
//Postcondition : return cap
size_t MyDoubleVector::size() const { return used; }
//Precondition :
//Postcondition : return used
void MyDoubleVector::reserve(size_t new_cap)
{
	//Precondition : size_t���� new_cap
	//Postcondition : ���� ��ä�� capacity(cap)�� new_cap �� ���ٸ� �ٷ� �Լ��� ����������
	//���� ��ä�� capacity(cap)�� used���� �۴ٸ� new_cap�� used��
	//�� �� ������ ��� ���� ���� �ʴ´ٸ� ���� ��ü�� data�� ������ �������ָ鼭 capacity�� new_cap���� ������� �ݴϴ�.
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
	//Postcondition : ���� ��ü�� size(used)�� 0���� �����ϰ�, �׷��ٸ� true �׷��� ������ false�� bool ������ return 
	if (used == 0)
		return true;
	else
		return false;
}
void MyDoubleVector::clear()
{
	//Precondition :
	//Postcondition : ���� ��ü�� data�� �Ҹ��Ű�� ���� data�� ����� �ָ鼭 size(used)�� 0���� �մϴ�.
	delete[] data;
	data = new double[cap];
	used = 0;
}
