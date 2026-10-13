#ifndef GL_TOOLS_HPP
#define GL_TOOLS_HPP

#include <glm/glm.hpp>
#include <glad/gl.h>

#include <unordered_map>
#include <map>

#include "FileTool.hpp"


struct SpriteSheet{

ImageFile Texture;

short SpriteWidth, SpriteHeight;
short SheetWidth, SheetHeight;

unsigned int Tex_ID = 2; //temp hardcode

float TW, TH; //Width/Height In Tiles

SpriteSheet(ImageFile Texture, short SpriteW, short SpriteH = 0 ); //if equal propotions

		  };

struct Sprite{

float TexX[2];
float TexY[2];

SpriteSheet* SrcSheet = nullptr;

Sprite(void){};
Sprite(SpriteSheet& SS, short STX, short STY);

	    };

struct Vertex{

glm::vec3 Position;
glm::vec4 Color;
glm::vec2 TextureCords;
GLfloat TextureID;
GLfloat MixRatio;
	     };

struct Quad{

std::array<Vertex, 4> Verts;	


Sprite* SpriteAdd = nullptr;

//Quad(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat TexID);
Quad(GLfloat X, GLfloat y, GLfloat z, GLfloat size, Sprite sprite);
};


struct Shader{

GLuint GL_ID;

Shader(void){};

Shader(const char* VertShader, const char* FragShader);

	      };//Shader_Struct


struct ModelView{

	glm::mat4 Model;
	glm::mat4 View;

ModelView(glm::mat4 Model, glm::mat4 View){} //temp till im more decided

};

#ifdef _2D_GL //Change name to GL-Renderer eventually 
class GL_Renderer{

std::vector<GLfloat> DrawGroup[5];

GLuint VAO;
GLuint IBO;
GLuint VBO;

static const size_t MaxQuads = 3000;
static const size_t MaxVerts = MaxQuads * 4;
static const size_t MaxIndices = MaxQuads * 6;

GLuint IndiceCount[5] = {0, 0, 0, 0, 0};
GLuint offset = 0;


	public:

GLuint Textures[20];

GL_Renderer(void){this->Start();}

void Start(void);
void Push_Quad(Quad& Q, short GroupIndice );
void Render(short GroupIndice);

void MakeTextureUniform(std::string ShaderName, std::string UniformName, int NumbOfTex);

void UseMatUniform(std::string ShaderName, std::string UniformName,  glm::mat4 Matr);

};
#endif //_2D_GL


class ResMan{ //Resource Manager

ResMan(void){};

std::map<std::string, Shader> Shaders;
std::map<std::string, ImageFile> Textures;
std::map<std::string, int> UniformLocations; //std::string = ShaderName + UniformName


std::unordered_map<unsigned short, Sprite> Sprites; // Number assigned to a sprite

short TexSlotIndex[20];

	public:

static ResMan& GetInstance(void){
static ResMan Instance;
return Instance;
				}

Shader AddNewShader(std::string VertPath, std::string FragPath,
	       		std::string ShaderName); 

ImageFile AddNewImg(std::string ImagePath, std::string ImageName, 
		    bool alpha = true);

void AddSprite(unsigned short Loc, Sprite InputSprite); 
Sprite GetSprite(unsigned short Loc);

Shader GetShader(std::string ShaderName);

void Use(std::string ShaderName);

ImageFile GetImg(std::string ImageName);

//uniform vvvvv

void AddUniform(std::string ShaderName, std::string UniformName);
int GetUniform(std::string ShaderName, std::string UniformName);


void SlotTexture(GL_Renderer& GLR, int TexSlot, std::string Texture);

};//ResMan struct


#ifdef _3D_GL
#endif//_3DGL
      //
#endif//Header
