//Created for Graphics I and II
//Author: Minsi Chen

#ifndef __IMAGEIO_H__
#define __IMAGEIO_H__

#include <stdio.h>

enum EImageReaderStatus
{
	E_IMAGEREADER_ERROR = 0,
	E_IMAGEREADER_FILENOTFOUND,
	E_IMAGEREADER_SUCCESS,
	E_UNRECOGNISED_HEADER
};

class ImageReader
{
private:
	static EImageReaderStatus LoadUncompressedTGA(unsigned char** buffer, int* sizeX, int* sizeY, int* bpp, int* nChannels, FILE* pf);
public:
	//Usage:
	//filename: path to the TGA file
	//buffer: the address of an unallocated unsigned char pointer for storage; note the image storage will be allocated inside the function
	//sizeX: pointer to an int, this returns the width of the image
	//sizeY: pointer to an int, this returns the height of the image
	//bpp: pointer to an int, this returns bits per pixel, e.g. 24 or 32
	//nChannels: pointer to an int, this returns the number of channel per pixel, it loads both RGB and RGBA images
	//
	//The function returns an enum indicating the status of loading
	static EImageReaderStatus LoadTGA(const char* filename, unsigned char** buffer, int* sizeX, int* sizeY, int* bpp, int* nChannels);
};

#endif