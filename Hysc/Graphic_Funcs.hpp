#ifndef GRAPHICS_FUNCS
#define GRAPHICS_FUNCS

#define _2D_GL
#include "GL_Tools.hpp"


class TileMap{

std::vector<glm::vec4> CordsAndTex; //x, y, z; then SpriteNumber

std::vector<int> Tiles; 

//std::vector<Quad> CachedTiles; //idk how to implement this yet

	public:
TileMap(void){};

void MakeTiles(TwoD_GL_Renderer& GLR); //placeholder func

	     };

      

#endif//GRAPHIC_FUNCS

