#ifndef RDCV_H
#define RDCV_H

#include <cstdio>
#include "log.h"

class Colour 
{
public:
	int R;
	int G;
	int B;
	Colour(int _r, int _g, int _b)
	{
		R = _r;
		G = _g;
		B = _b;
	}
	Colour()
	{
		R = 0;
		G = 0;
		B = 0;
	}
};

class Image 
{	
public:
	int sizeX;
	int sizeY;
	Colour** colourMap;
	Image()
	{
		colourMap = (Colour**)malloc(sizeof(Colour*) * 2048);
		if(colourMap != NULL)
		for (int i = 0; i < 2048; i++)
		{
			colourMap[i] = (Colour*) malloc(sizeof(Colour) * 2048);
		}
		if (colourMap != NULL)
		for (int i = 0; i < 2048; i++)
		{
			if(colourMap[i]!=NULL)
			for (int j = 0; j < 2048; j++)
			{
				colourMap[i][j] = Colour(0, 0, 0);
			}
		}
		sizeX = 0;
		sizeY = 0;
	}
};

struct rdBMfileHeader
{
	unsigned long int bfSize;
	unsigned short int bfReserved1;
	unsigned short int bfReserved2;
	unsigned long int bfOffBits;
};

struct rdBMdetailHeader
{
	unsigned long int bdSize;
	long int bdWidth;
	long int bdHeight;
	unsigned short int bdPlanes;
	unsigned short int bdBitCount;
	unsigned long int bdCompression;
	unsigned long int bdSizeImage;
	long int bdXPelsPerMeter;
	long int bdYPelsPerMeter;
	unsigned long int bdClrUsed;
	unsigned long int bdClrImportant;
};

struct rdBMcolour
{
	unsigned char bmBlue;
	unsigned char bmGreen;
	unsigned char bmRed;
	unsigned char bmReserved;
};

struct rdBMimage
{
	int width;
	int height;
	int channels;
	unsigned char* imageData;
};

Image rdBMReadImage(char* path)
{
	rdBMimage* bmpImage;
	FILE* fileP;
	unsigned short int fileType;
	rdBMfileHeader fileHeader;
	rdBMdetailHeader detailHeader;
	int channels = 1;
	int width=0;
	int height=0;
	int step=0;
	int offset=0;
	unsigned char pixVal;
	rdBMcolour colour4;
	Image out = Image();

	bmpImage = (rdBMimage*)malloc(sizeof(sizeof(rdBMimage)));
	fopen_s(&fileP,path, "r");
	if (!fileP)
	{
		free(bmpImage);
		_log(0, "open failed");
		return out;
	}
	fread(&fileType, sizeof(unsigned short int),1,fileP);
	if (fileType != 0x4D42)
	{
		_log(0, "Not a BitMap");
		return out;
	}
	fread(&fileHeader, sizeof(rdBMfileHeader), 1, fileP);
	fread(&detailHeader, sizeof(rdBMdetailHeader), 1, fileP);
	if (detailHeader.bdBitCount == 24)
	{
		width = detailHeader.bdWidth;
		height = detailHeader.bdHeight;
		out.sizeX = width;
		out.sizeY = height;
		channels = 3;
		offset = (channels * width) % 4;
		if (offset != 0)offset = 4 - offset;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//printf("i=%d,j=%d\n", i, j);
				int p[3];
				for (int k = 0; k < 3; k++)
				{
					fread(&pixVal, sizeof(unsigned char), 1, fileP);
					p[2 - k] = (int)pixVal;
				}
				out.colourMap[i][j] = Colour(p[0], p[1], p[2]);
				//printf("%d,%d,%d\n", out.colourMap[i][j].R, out.colourMap[i][j].G, out.colourMap[i][j].B);
				//printf("\n");
			}
			if (offset != 0)
			{
				for (int j = 0; j < offset; j++)
				{
					fread(&pixVal, sizeof(unsigned char), 1, fileP);
				}
			}
		}
	}
	return out;
}



#endif RDCV_H
