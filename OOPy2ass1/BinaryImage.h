#pragma once
#include "Matrix.h"

typedef double element;
class BinaryImage : public Matrix
{
public:
	BinaryImage::BinaryImage();
	BinaryImage(int M, int N, double* input_data, double threshold);
	BinaryImage(int M, int N, double* input_data);
	~BinaryImage();

};

