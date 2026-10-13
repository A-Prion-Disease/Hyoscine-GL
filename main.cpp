#include <iostream>

#include "Hysc/Interface.hpp"

#include <glm/glm.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
/* At this point: I am unsure weither I want this to be a framework or a more
 * IDE resemblant engine, due to such; I do not plan to store much
 *  important data relating to the engine in the main. Instead i'd rather 
 *  for function def's to be in headers to allow for easy inclusion */

bool Running = false;

int main(){

SDL_Interface Interface(400, 400, Running);

GL_Renderer GLR;

ResMan& RM = ResMan::GetInstance();

RM.AddNewShader("Core/Shaders/Vert1.shader",
                        "Core/Shaders/Frag1.shader","First");

RM.AddNewImg("Core/Assets/RetardTheClown.png", "Retard", true);
RM.AddNewImg("Core/Assets/weeping.png", "weep", true);
RM.AddNewImg("Core/Assets/TestTileSheet.png", "Best", true);


RM.SlotTexture(GLR, 0, "Retard"); 
RM.SlotTexture(GLR, 1, "weep");
RM.SlotTexture(GLR, 2, "Best");
RM.Use("First");

float fov = glm::radians(90.0f);
float AspectRatio = Interface.W_W / Interface.W_H;
RM.AddUniform("First", "uniTexture");
GLR.MakeTextureUniform("First", "uniTexture", 3);

glm::mat4 Proj = glm::perspective(fov, AspectRatio, 0.01f, 100.0f);

RM.AddUniform("First", "Proj");
RM.AddUniform("First", "View");
RM.AddUniform("First", "Model");

float CamX = 0;
float CamY = 1.0f;

 glViewport(0, 0, Interface.L_W, Interface.L_H);


char Input = ' ';

//Quad Test[25];
	
TileMap Testmap;

SpriteSheet TestSheet(RM.GetImg("Best"), 48, 48);

Sprite TestSprite(TestSheet, 0, 0);


glEnable(GL_DEPTH_TEST);
//glDepthMask(GL_TRUE);
glDepthFunc(GL_LESS);

while(Running){


glDepthMask(GL_TRUE);

glClearColor(0.7f, 0.7f, 1.0f, 0.0f);

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

glm::mat4 View = //Vec1: CamPos Vec2: TargetPos
		 //Vec3: upVector
glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 3.5f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));


//View = glm::rotate(glm::mat4(1.0f), glm::radians(CamX), glm::vec3(0.0f, 1.0f, 0.0f)) * View;

glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, CamY, 0.0f ));

if(CamX > 360 || -360 > CamX ){

CamX = 0.0f;
}
GLR.UseMatUniform("First", "Proj", Proj);
GLR.UseMatUniform("First", "View", View);
GLR.UseMatUniform("First", "Model", Model);


Testmap.MakeTiles(GLR, 0.96f);

Quad TestQuad(0.0f, 0.0, 0.2f, 0.96, TestSprite);

GLR.Push_Quad(TestQuad, 1);


GLR.Render(0);


View = glm::lookAt(glm::vec3(0,0,CamY),glm::vec3(0,0,0.0f),glm::vec3(0,1,0));
Model= glm::translate(glm::mat4(1.0f), glm::vec3(CamX, 0.0f, 1.0f));

GLR.UseMatUniform("First", "View", View);
GLR.UseMatUniform("First", "Model", Model);


GLR.Render(1);


Interface.WindowLoop(GLR);
Input = Interface.InputCheck(Running);


if(Input == 'a'){
CamX -= 1.0f;
		}
if(Input == 'd'){
CamX += 1.0f;
	       }
if(Input == 'w'){
CamY += 1.0f;
		}
if(Input == 's'){
CamY -= 1.0f;
		}
if(Input == 'e'){
	std::cout << "CamX: " << CamX << " CamY:  " << CamY << " \n ";
		}
Input = ' ';
	      }

	  } 
