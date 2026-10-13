#include "Graphic_Funcs.hpp"

void TileMap::MakeTiles(GL_Renderer& GLR, float TileSize){
float x = TileSize; float y = TileSize;

ResMan& RM = ResMan::GetInstance();

SpriteSheet Testy(RM.GetImg("Best"), 48, 48);
Sprite TS(Testy, 2, 0);

for(int i= -9; i < 13; i++){
float NewX = (x * i);
for(int j= 0; j < 10; j++){
float NewY = (y * j);
Quad Temp = Quad(NewX, NewY, 0.1f, TileSize, TS);
GLR.Push_Quad(Temp, 0);
        		 }
			 }
}


