#include<iostream>
#include<string>
#include "MyDoubleVector.h"
using namespace std;
void outputData(MyDoubleVector vector_num, string s)
{
	cout << s<<" outputData "<<s<<".size() : " << vector_num.size() << endl;
	for (size_t i = 0; i < vector_num.size(); i++)
		cout << s<<"[" << i << "]" << ":" << vector_num[i] << ", ";
	cout << endl;
	cout << endl;
}

int main() {

	MyDoubleVector vector1;//Default constructor
	//vector1[1];//주석을 제거 하면 잘못된 배열이 참조된 경우가 됩니다.
	cout << "MyDoubleVector vector1;" << endl<<endl;
	for(size_t i=0;i<3;i++)//값 입력
	{
		vector1.push_back(i*1.1);
	}
	cout << "for(size_t i=0;i<3;i++)\nvector1.push_back(i*1.1);"<<endl<<endl;
	outputData(vector1, "vector1");

	MyDoubleVector vector2(vector1);//Copy constructor for deep copy
	cout << "MyDoubleVector vector2(vector1);" << endl<<endl;
	outputData(vector2, "vector2");
	vector2[1]++;//deep copy를 확인하기 위해
	cout << "vector2[1]++;"<<endl;
	outputData(vector1, "vector1");
	outputData(vector2, "vector2");
	MyDoubleVector vector5;
	MyDoubleVector vector3 = vector5 = vector1;//Assignment operator (=) for deep copy //Chaining assignment should be possible.
	cout << "MyDoubleVector vector5;\nMyDoubleVector vector3 = vector5 = vector1;" << endl << endl;
	outputData(vector3, "vector3");
	vector3[1]++;//deep copy를 확인하기 위해
	cout << "vector3[1]++;" << endl;
	outputData(vector1, "vector1");
	outputData(vector3, "vector3");
	outputData(vector5, "vector5");
	vector3 += vector1;//Operator: +=
	cout << "vector3 += vector1;" << endl;
	outputData(vector3, "vector3");

	vector2 = vector1 + vector2;//(Binary) operator: +
	cout << "vector2 = vector1 + vector2;" << endl;
	outputData(vector1, "vector1");
	outputData(vector2, "vector2");
	
	vector1 = vector1 - vector1;//(Binary) operator: -
	cout << "vector1 = vector1 - vector1;" << endl;
	outputData(vector1, "vector1");
	cout<<"vector2*vector2 : "<<vector2*vector2<<endl<<endl;//(Binary) operator: *
	
	MyDoubleVector vector4=-vector3;//(Unary) operator: -
	outputData(vector3, "vector3");
	outputData(vector4, "vector4");

	cout << "vector3==vector4 : " << (vector3 == vector4) << endl<<endl;//(Binary) operator: ==
	vector4=-vector4;
	cout << "vector4=-vector4;" << endl<<endl;
	cout << "vector3==vector4 : " << (vector3 == vector4) << endl << endl;
	outputData(vector3, "vector3");
	outputData(vector4, "vector4");
	
	vector2(0);//(Unary) operator:  ()
	cout << "vector2(0);" << endl << endl;
	outputData(vector2, "vector2");
	
	vector2.pop_back();//void pop_back( );
	cout << "vector2.pop_back();" << endl << endl;
	outputData(vector2, "vector2");
	
	vector2.push_back(9.4);//void push_back(double x);
	cout << "vector2.push_back(9.4);" << endl << endl;
	outputData(vector2, "vector2");
	cout << "vector1.capacity() : " << vector1.capacity() << endl<<endl;
	
	vector1.reserve(100);//void reserve(size_t n);
	cout << "vector1.reserve(100);" << endl << endl;
	cout << "vector1.capacity() : " << vector1.capacity() << endl<<endl;

	cout << "vector1.empty() : " << vector1.empty() << endl<<endl;//bool empty( ) const;
	for (size_t i = 0; i < 3; i++)
		vector1.pop_back();
	cout << "for (size_t i = 0; i < 3; i++)\n\tvector1.pop_back(); " << endl<<endl;
	cout <<"vector1.empty() : "<< vector1.empty() << endl<<endl;
	outputData(vector1, "vector1");

	cout << "vector2.empty() : " << vector2.empty() << endl << endl;
	vector2.clear();//void clear( );
	cout << "vector2.clear(); " << endl << endl;
	cout << "vector2.empty() : " << vector2.empty() << endl << endl;
	outputData(vector2, "vector2");
	

	return 0;
}
