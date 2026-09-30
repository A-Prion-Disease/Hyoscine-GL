#include "FileTool.hpp"

std::string ReadFile(const std::string& FilePath){

	std::ifstream CurrentFile(FilePath);

	if(CurrentFile.is_open()){

	std::stringstream CharBuffer;

	CharBuffer << CurrentFile.rdbuf();

	const std::string FileData = CharBuffer.str();

	CurrentFile.close();

	return FileData;
			       }
	std::string FailString = "Failure to ReadFile";	
	return FailString;
						  }

//FileReading ^^^
//ImageTranslation vvv

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/gl.h>
#include <iostream>

ImageFile::ImageFile(const std::string& ImgPath, bool alpha){

	int nr_channels;
	unsigned char* data;

	stbi_set_flip_vertically_on_load(1);

	data = stbi_load(ImgPath.c_str(), &W, &H, &nr_channels, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &GL_ID);

	glBindTexture(GL_TEXTURE_2D, GL_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if(alpha){
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, W, H, 0, GL_RGBA,
	     GL_UNSIGNED_BYTE, data);
	         }
   	if(!alpha){
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, W, H, 0, GL_RGB,
	     GL_UNSIGNED_BYTE, data);
	   	  }

   if(data == nullptr){std::cerr << "Img failed to load\n";}

   stbi_image_free(data);
						    };

