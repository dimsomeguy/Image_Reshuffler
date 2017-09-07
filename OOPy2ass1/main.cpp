#include "stdafx.h"
#include <sstream> 
#include <fstream> 
#include <istream>
#include <iostream>
#include "Matrix.h"
#include "BinaryImage.h"

using namespace std;

// Input data are provided in .txt format and can be converted to .pgm files for visualization
// Download (free) ImageJ for plotting images in .pgm format
// http://rsb.info.nih.gov/ij/download.html

// Reads .txt file representing an image of R rows and C Columns stored in filename 
// and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
double* readTXT(char *fileName, int sizeR, int sizeC);

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and Q=1 for binary images.
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);


int main()
{
	// This part will show you how to use the two functions.

	//M and N represent the number of rows and columns in the image,
	//e.g. for task 1: logo_with_noise and logo_shuffled, M = 512, N = 512


	// Outputs
	char* Image = "final_logo.pgm";

	/* Binary Image Objects */
	BinaryImage shufBI;
	BinaryImage unshufBI;

	/* Matrix Image Objects */
	Matrix unshuffledMatrix;
	Matrix shufMatrix;

	int N = 512, M = 512;

	cout << "converting txt to binay array" << endl;

	// .pgm image is stored in inputFileName, change the path in your program appropriately
	char* ShuffledTXT = "shuffled_logo.txt";


	shufBI = BinaryImage(N, M, readTXT("shuffled_logo.txt", N, M));
	unshufBI = BinaryImage(N, M, readTXT("unshuffled_logo_noisy.txt", N, M), 110);


	Matrix unshuffledBlock;
	shufMatrix = Matrix(N, M, readTXT("shuffled_logo.txt", N, M));

	Matrix finaloutput = Matrix(N, M);
	Matrix vals;
	Matrix shuffledBlock;
	int tempVal;
	int minVal;

	int perfectMatches = 0;
	int highestVal = 0;
	int operations = (N * M) / 32;
	cout << "convertion to binary complete!" << endl;
	cout << "starting block search and assinment this may take a minuet..." << endl;
	for (int Y = 0; Y < M; Y += 32) 
	{
		for (int X = 0; X < N; X += 32) 
		{
			unshuffledBlock = unshufBI.GetBlock(Y, Y + 31, X, X + 31);
			minVal = 100000000;
			for (int i = 0; i < M; i += 32) 
			{
				for (int j = 0; j < N; j += 32) 
				{
					shuffledBlock = shufBI.GetBlock(i, i + 31, j, j + 31);
					tempVal = (int)(shuffledBlock.SSD(unshuffledBlock));
					if (tempVal < minVal) {
						minVal = tempVal;
						vals = shufMatrix.GetBlock(i, i + 31, j, j + 31);
					}
				}
			}
			finaloutput.SetBlock(Y, Y + 31, X, X + 31, vals);
			//cout << "your min value for this brick was: " << minVal << endl;
		}
	}



	// Use Q = 255 for greyscale images and 1 for binary images.
	//WritePGM("DenoiseyImage.pgm", , N, M, Q);
	WritePGM(Image, finaloutput.DataGrab(), N, M, 255);
	cout << "your reshuffled image should be waiting for you under the name final_logo.pgm" << endl;
	cout << "Thanks for waiting, have a fun day of marking the rest of these!" << endl;
	cin.get();

	return 0;
}


// Read .txt file with image of size RxC, and convert to an array of doubles
double* readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;

	delete[] data;
}

// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (int i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

}