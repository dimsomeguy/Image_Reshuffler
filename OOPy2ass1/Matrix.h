#include <iostream>
#pragma once
class Matrix
{
public:
	Matrix();
	Matrix(int i, int j, double* input_data);
	Matrix(int sizeR, int sizeC);
	Matrix(const Matrix& S);
	~Matrix();
	Matrix operator=(const Matrix& other);

	double Get(int i, int j);
	void Set(int i, int j, double val);
	Matrix GetBlock(int start_row, int end_row, int start_column, int end_column);
	double SSD(Matrix& noise);
	void SetBlock(int SR, int ER, int SC, int EC, Matrix Block);
	double* DataGrab();


protected:
	double* _Data;
	int _M, _N;
};

