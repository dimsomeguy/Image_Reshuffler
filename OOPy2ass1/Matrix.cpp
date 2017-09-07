#include "stdafx.h"
#include "Matrix.h"
#include <iostream>

Matrix::Matrix() 
{

}
Matrix::Matrix(int sizeR, int sizeC, double* input_data)
{
	_M = sizeR;
	_N = sizeC;
	_Data = input_data;
}
Matrix::Matrix(int sizeR, int sizeC) 
{
	_M = sizeR;
	_N = sizeC;
	_Data = new double[_M*_N];
}
Matrix::Matrix(const Matrix& S)
{
	_M = S._M;
	_N = S._N;
	_Data = new double[_M*_N];

	for (int i = 0; i < _M * _N; i++)
	{
		_Data[i] = S._Data[i];
	}
}
Matrix Matrix::operator=(const Matrix& other)
{
	//std::cout << "Operator '=' overload" << std::endl;
	//delete existing _data information - as we are going to replace it with 'other._data'
	delete[] _Data;
	_M = other._M;
	_N = other._N;

	//reserve memory for new array
	_Data = new double[_M*_N];

	//'this' pointer refers to the current object
	for (int x = 0; x < (_M*_N); x++)
	{
		this->_Data[x] = other._Data[x];
	}

	return *this;
}

Matrix::~Matrix()
{
	delete[] _Data;
}
double Matrix::Get(int i, int j)
{
	return _Data[i * _M + j];
}

void Matrix::Set(int i, int j, double val) 
{
	 _Data[i * _M + j] = val;
}
Matrix Matrix::GetBlock(int iS, int iE, int jS, int jE)
{
	Matrix mat;
	mat._M = iE - iS + 1;
	mat._N = jE - jS + 1;
	mat._Data = new double[mat._M * mat._N];

	for (int i = 0; i < mat._M; i++)
		for (int j = 0; j < mat._N; j++)
			mat.Set(i, j, Get(i + iS, j + jS));

	return mat;
}
double Matrix::SSD(Matrix& noise) 
{
	Matrix temp(32, 32);
	double output = 0;
	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 32; j++) 
		{
			temp.Set(i, j, (Get(i, j) - noise.Get(i, j)));
			output += temp.Get(i, j)*temp.Get(i, j);
		}
	
	return output;
}
void Matrix::SetBlock(int SR, int ER, int SC, int EC, Matrix Block)
{
	int x = (ER - SR) + 1;
	int y = (EC - SC) + 1;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++) 
		{
			int val = Block.Get(i,j);
			Set(SR + i, SC + j, val);
		}
	}	
}
double* Matrix::DataGrab() 
{
	return _Data;
}
//Matrix Matrix::operator+(const Matrix& other)
//{
//	std::cout << "Operator '+' overload" << std::endl;
//	Matrix temp;
//	temp._M = other._M;
//	temp._N = other._N;
//
//	temp._Data = new double[temp._M*temp._N];
//
//	for (int x = 0; x < (temp._M*temp._N); x++)
//	{
//		temp._Data[x] = this->_Data[x] + other._Data[x];
//	}
//
//	return temp;
//}
//Matrix Matrix::operator=(const Matrix& other)
//{
//	std::cout << "Operator '=' overload" << std::endl;
//	//delete existing _data information - as we are going to replace it with 'other._data'
//	delete[] _Data;
//	_M = other._M;
//	_N = other._N;
//
//	//reserve memory for new array
//	_Data = new double[_M*_N];
//
//	//'this' pointer refers to the current object
//	for (int x = 0; x < (_M*_N); x++)
//	{
//		this->_Data[x] = other._Data[x];
//	}
//
//	return *this;
//}
//Matrix Matrix::operator-(const Matrix& other)
//{
//	std::cout << "Operator '-' overload" << std::endl;
//	Matrix temp;
//	temp._M = other._M;
//	temp._N = other._N;
//
//	temp._Data = new double[temp._M*temp._N];
//
//	for (int x = 0; x < (temp._M*temp._N); x++)
//	{
//		temp._Data[x] = this->_Data[x] - other._Data[x];
//	}
//
//	return temp;
//}
//Matrix Matrix::operator/(const Matrix& other)
//{
//	std::cout << "Operator '/' overload" << std::endl;
//	Matrix temp;
//	temp._M = other._M;
//	temp._N = other._N;
//
//	temp._Data = new double[temp._M*temp._N];
//
//	for (int x = 0; x < (temp._M*temp._N); x++)
//	{
//		temp._Data[x] = this->_Data[x] / other._Data[x];
//	}
//
//	return temp;
//}
//
//Matrix Matrix::operator*(const Matrix& other)
//{
//	std::cout << "Operator '*' overload" << std::endl;
//	Matrix temp;
//	temp._M = other._M;
//	temp._N = other._N;
//
//	temp._Data = new double[temp._M*temp._N];
//
//	for (int x = 0; x < (temp._M*temp._N); x++)
//	{
//		temp._Data[x] = this->_Data[x] * other._Data[x];
//	}
//
//	return temp;
//}
//
//Matrix Matrix::add(const Matrix& other)
//{
//	//create temporary array of row*colum size
//	double* _Data = new double[other._M*other._N];
//
//	//fill the array with other._data
//	for (int x = 0; x < (other._M*other._N); x++)
//	{
//		_Data[x] = this->_Data[x] + other._Data[x];
//	}
//
//	//create a temporary Matrix object with the row/column/data info
//	Matrix temp(other._M, other._N, _Data);
//	//delete the data array (which we can do as the array is 'deep copied' when 'temp' is created
//	delete[] _Data;
//
//	return temp;
//}
//
//Matrix Matrix::operator++(int)
//{
//	std::cout << "Operator++ overload" << std::endl;
//
//	for (int x = 0; x < (_M * _N); x++)
//	{
//		this->_Data[x] = _Data[x] + 1;
//	}
//	return *this;
//}
//
//double Matrix::operator()(int i, int j)
//{
//	std::cout << "operator '()' overload" << std::endl;
//	std::cout << "the value you have pointed to in your array is equal to: " << _Data[(i*_M + j)] << std::endl;
//	return _Data[(i*_M + j)];
//}
