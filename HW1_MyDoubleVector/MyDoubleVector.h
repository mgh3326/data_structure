#pragma once

#include <cstdlib>
class MyDoubleVector
{
public:

	enum { DEFAULT_CAPACITY = 30 };
	MyDoubleVector();//Default constructor
	MyDoubleVector(const MyDoubleVector& v);//Copy constructor for deep copy
	~MyDoubleVector();//Destructor
	MyDoubleVector& operator =(const MyDoubleVector& source);//Assignment operator (=) for deep copy
	void operator +=(const MyDoubleVector& addend);//Appends RHS object to LHS one.
	double& operator [](const int& index);//Returns a reference to the element at the requested position in the vector container.
	MyDoubleVector operator +(const MyDoubleVector& source);//Returns a object that is a vector-sum of the two operand objects.
	MyDoubleVector operator -(const MyDoubleVector& source);//Returns a object that is a vector-difference of the two operand objects.
	double operator *(const MyDoubleVector& source);//Returns the scalar product (or dot product) value of the two operand objects.
	MyDoubleVector operator -();//Returns a object of which each element is the unary negation of the corresponding element in the operand object.
	bool operator ==(const MyDoubleVector& source);// Returns whether or not the two operand vectors are the same. (You should check if their sizes are the same. Do not check their capacities.)
	void operator ()(const double& element);//Makes every element of this object be the value of the real-valued (double-typed) operand.
	void pop_back();//Removes the last element in the vector, effectively reducing the vector size by one and invalidating all references to it.
	void push_back(double element);//Adds a new element at the end of the vector, after its current last element. The content of this new element is initialized to a copy of x.
	size_t capacity() const;//Returns the size of the allocated storage space for the elements of the vector container.
	size_t size() const;//Returns the number of elements in the vector container.
	void reserve(size_t  new_cap);//Requests that the capacity of the allocated storage space for the elements of the vector container be at least enough to hold n elements.
	bool empty() const;//Returns whether the vector container is empty, i.e., whether its size is 0.
	void clear();//All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container, leaving the container with a size of 0.

private:
	double *data;     // 값이 담겨질 동적할당된 배열
	size_t used;       // size
	size_t cap;   // capacity
};