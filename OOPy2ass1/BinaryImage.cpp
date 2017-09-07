#include "stdafx.h"
#include "BinaryImage.h"
#include <iostream>



BinaryImage::BinaryImage() 
{

}
		BinaryImage::BinaryImage(int M, int N, double* input_data, double threshold)
		{
			_Data = input_data;
			_M = M;
			_N = N;
			for (int i = 0; i < _M; i++)
			{
				for (int j = 0; j < _N; j++)
				{
					if (i < _M - 2) {
						if (_Data[i* _M + j] >= 210)
						{
							if (_Data[i* _M + j + 1] == 0 && _Data[i* _M + j - 1] == 0)
								_Data[i* _M + j] = 0;
							else if (_Data[i* _M + j + 2] == 0 && _Data[i* _M + j - 1] == 0)
								_Data[i* _M + j] = 0;
							else if (_Data[(i* _M + j) + _M] == 0 && _Data[(i* _M + j) + _M * 2] == 0)
								_Data[i* _M + j] = 0;
							else if (0 < _Data[i * _M + j + 1] < 255 && 0 < _Data[i * _M + j - 1] < 255)
								_Data[i* _M + j] = _Data[(i* _M + j) + _M];
						}
						else if (_Data[i* _M + j] == 0)
						{
							if (_Data[i* _M + j + 1] == 255 && _Data[i* _M + j - 1] == 255)
								_Data[i* _M + j] = 255;
							else if (_Data[i* _M + j + 2] == 255 && _Data[i* _M + j - 1] == 255)
								_Data[i* _M + j] = 255;
							else if (0 < _Data[i* _M + j + 1] < 255 && 0 < _Data[i* _M + j - 1] < 255)
								_Data[i* _M + j] = _Data[i* _M + j + 1];
						}
					}
					else if (i >= _M - 2) 
					{
						_Data[i*_M + j] = 0;
					}
					if (_Data[i* _M + j] > threshold)
					{
						_Data[i* _M + j] = 1;
					}
					else 
					{
						_Data[i* _M + j] = 0;
					} 
				}
			}
		}
		BinaryImage::BinaryImage(int M, int N, double* input_data) 
		{
			_M = M;
			_N = N;
			_Data = input_data;
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++) 
				{
					if (_Data[i* _M + j] > 110)
					{
						_Data[i* _M + j] = 1;
					}
					else
					{
						_Data[i* _M + j] = 0;
					}
				}
		}
		BinaryImage::~BinaryImage()
		{

		}	
		//BinaryImage BinaryImage::operator*(const BinaryImage& H) // AND operator
		//{
		//	BinaryImage temp;
		//	temp._M = H._M;
		//	temp._N = H._N;
		//	temp._Data = new double[temp._M*temp._N];
		//	for (int x = 0; x < (temp._M*temp._N); x++)
		//	{
		//		if (this->_Data[x] == 0 && H._Data[x] == 0 || this->_Data[x] == 1 && H._Data[x] == 1)
		//			temp._Data[x] = 1;
		//		else
		//			temp._Data[x] = 0;
		//	}
		//	return temp;
		//}
		//BinaryImage BinaryImage::operator+(const BinaryImage& H) // OR operator
		//{
		//	BinaryImage temp;
		//	temp._M = H._M;
		//	temp._N = H._N;
		//	temp._Data = new double[temp._M*temp._N];
		//	for (int x = 0; x < (temp._M*temp._N); x++)
		//	{
		//		if (this->_Data[x] == 1 || H._Data[x] == 1)
		//			temp._Data[x] = 1;
		//		else
		//			temp._Data[x] = 0;
		//	}
		//	return temp;
		//}
		//BinaryImage BinaryImage::operator-(const BinaryImage& H) //XOR oparator 
		//{
		//	BinaryImage temp;
		//	temp._M = H._M;
		//	temp._N = H._N;
		//	temp._Data = new double[temp._M*temp._N];
		//	for (int x = 0; x < (temp._M*temp._N); x++)
		//	{
		//		if (this->_Data[x] == 0 && H._Data[x] == 1 || this->_Data[x] == 1 && H._Data[x] == 0)
		//			temp._Data[x] = 1;
		//		else
		//			temp._Data[x] = 0;
		//	}
		//	return temp;
		//}
		//double BinaryImage::operator()(int i, int j) 
		//{
		//	return _Data[(i*_M + j)];
		//}
