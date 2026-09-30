#ifndef FILE_TOOLS_HPP
#define FILE_TOOLS_HPP

#include <sstream>
#include <fstream>

std::string ReadFile(const std::string& FilePath);

struct ImageFile{

unsigned int GL_ID;
int W, H;

ImageFile(){};	
ImageFile(const std::string& ImgPath, bool alpha);

		};

#endif
