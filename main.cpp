#include <iostream>

#include "Hysc/Interface.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

/* At this point: I am unsure weither I want this to be a framework or a more
 * IDE resemblant engine, due to such; I do not plan to store much
 *  important data relating to the engine in the main. Instead i'd rather 
 *  for function def's to be in headers to allow for easy inclusion */

bool Running = false;

int main(){

SDL_Interface Interface(400, 400, Running);

TwoD_GL_Renderer GLR;

ResMan& RM = ResMan::GetInstance();

RM.AddNewShader("Core/Shaders/Vert1.shader",
                        "Core/Shaders/Frag1.shader","First");

RM.AddNewImg("Core/Assets/RetardTheClown.png", "Retard", true);
RM.AddNewImg("Core/Assets/weeping.png", "weep", true);

GLR.Textures[0] = RM.GetImg("Retard").GL_ID;
GLR.Textures[1] = RM.GetImg("weep").GL_ID;

RM.Use("First");


RM.AddUniform("First", "uniTexture");
GLR.MakeTextureUniform("First", "uniTexture", 2);

glm::mat4 Proj = glm::ortho(0.0f, 250.0f, 0.0f, 250.0f, 0.0f, 2.0f);


RM.AddUniform("First", "Proj");
RM.AddUniform("First", "View");
RM.AddUniform("First", "Model");

float CamY = 0;


        glViewport(0, 0, Interface.L_W, Interface.L_H);

char Input = ' ';

//Quad Test[25];
	
TileMap Testmap;

while(Running){

glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0, CamY, 0));
glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


GLR.UseMatUniform("First", "Proj", Proj);
GLR.UseMatUniform("First", "View", View);
GLR.UseMatUniform("First", "Model", Model);

glClearColor(0.2f, 1.0f, 0.3f, 1.0f);

glClear(GL_COLOR_BUFFER_BIT);

Testmap.MakeTiles(GLR);

Interface.WindowLoop(GLR);
Input = Interface.InputCheck(Running);


if(Input == 'a'){
		}
if(Input == 'd'){
	       }
if(Input == 'w'){
CamY += 1.0f;
		}
if(Input == 's'){
CamY -= 1.0f;
		}
Input = ' ';
	      }

	  } 
