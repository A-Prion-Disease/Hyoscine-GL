#include "Graphic_Funcs.hpp"

void TileMap::MakeTiles(TwoD_GL_Renderer& GLR){
float x = 25; float y = 25;

for(int i=0; i < 10; i++){
float NewX = x * i;
for(int j=0; j < 10; j++){
float NewY = y * j;
Quad Temp = Quad(NewX, NewY, 0.0f, 25.0f, 1.0f);
GLR.Push_Quad(Temp);
        		 }
			 }
}


