#include "stdafx.h"
#include "image.h"
#include <iostream>
#include <fstream>

const unsigned char * Image::LoadBMP(const std::string & filename, int & width, int & height, int & bpp)
{
	std::ifstream file;
	file.open(filename, std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "Failed to load file." << std::endl;
		return nullptr;
	}

	char header[54];
	file.read(header, 54);

	width = *(int*)&(header[18]);
	height = *(int*)&(header[22]);
	bpp = *(int*)&(header[28]);
	int size = *(int*)&(header[34]);

	unsigned char* data = new unsigned char[size];

	file.read((char*) data, size);

	file.close();
	
	return data;
}
