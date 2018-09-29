/*
This software is following MIT License written below:

MIT License

Copyright (c) [year] [fullname]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Author:L-Stefano
*/
#include "lodepng.h"
#include <iostream>
#include <string>
#include <ShlObj.h>
using namespace std;
void getGray(const vector<unsigned char> &image, vector<unsigned char> &gray);//Get the gray level of image, then save in vector gray
void mapping(vector<unsigned char> &gray);//Mapping gray value [0,255] to printable char [33-126]
void toTXT(unsigned Width, vector<unsigned char> &gray);//Write a TXT file

//Mapping Threshold, whose minimum is limited to 3.
//the higher threshold value is, the more details lose; the less threshold value is, the more disordered characters generated are.
int mappingThreshold;

int main(int argc, char *argv[])
{
	vector<unsigned char> image; //Date of pixels, every four elements is a pixel, following the order as RGBARGBA
	unsigned width, height;

	cout << "Tips:	1. Don't apply images of little difference in color (eg. a picture of the whole scene too dark)" << endl;
	cout << "	2. Don't apply images with high resolution (max of height and width within 200px is recommended.)" << endl;
	cout << "	3. The higher threshold value is, the more details lose,\n	  the less threshold value is, the more disordered characters generated are" << endl;
	cout << "	4. (IMPORTANT) Please use monospaced fonts" << endl;
	cout << "	5. If the final result txt is too big to display, there are two ways to improve:" << endl;
	cout << "	  1>. Adjust font size smaller." << endl;
	cout << "	  1>. Retry a image with smaller resolution." << endl << endl;
	cout << "Noiced that the aspect ratio of the original image to the result is not 1:1" << endl;
	cout << "	The result will be higher in height. The solution is that reducing height to 0.5-0.75 \n	ahead of time (with Photoshop), or expand the width to 0.5-0.75 " << endl;

	cout << "----------------------------------------------------------------" << endl;
	cout << "Enter the path of image (only PNG): (such as\"C:\\Users\\Administrator\\Pictures\\test.png\")" << endl;
	string path;
	cin >> path;
	cout << "Enter the mapping threshold (3-150): " << endl;
	extern int mappingThreshold;
	cin >> mappingThreshold;

	//Decode PNG
	unsigned error = lodepng::decode(image, width, height, path);

	//Find error
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	//Decoding is complete, pixels are stored in image

	vector<unsigned char> gray;//vector of gray level
	getGray(image, gray);

	mapping(gray);
	toTXT(width, gray);

	cout << "SUCCESS! Result is saved in your desktop, named \"Resule.txt\"" << endl;

	system("pause");
	return EXIT_SUCCESS;
}
void getGray(const vector<unsigned char> &image, vector<unsigned char> &gray)
{
	unsigned char Gray;//for saving gray value
	unsigned char R, G, B;


	auto beg = image.cbegin();//beginning iterator
	while (beg != image.cend())
	{
		R = *beg++;
		G = *beg++;
		B = *beg++;
		++beg;
		Gray = static_cast<unsigned char>(R * 0.3 + G * 0.59 + B * 0.11);//Weighted algorithm of gray value
		gray.push_back(Gray);
	}
}
void mapping(vector<unsigned char> &gray)
{

	for (int a = 0, b = mappingThreshold, ascii = 32; b<=256+mappingThreshold; a += mappingThreshold, b += mappingThreshold, ascii++)
		for (auto&i : gray)
		{
			if (i >= a && i <= b)
				i = ascii;
		}
}
void toTXT(unsigned Width, vector<unsigned char> &gray)
{
	char path[400];
	SHGetSpecialFolderPath(0, path, CSIDL_DESKTOPDIRECTORY, 0);//Get the path of user's desktop
	strcat(path, "\\Result.txt");

	FILE *fp;
	fp = fopen(path , "w");//New statements _CRT_SECURE_NO_DEPRECATE in preprocessor

	int loop = 0; 
	for (auto chara : gray)
	{
		fputc(chara, fp);
		if (loop++ == Width-1)//Print a new line character for every width character printed
		{
			putc('\n', fp);
			loop = 0;
		}
	}
}
