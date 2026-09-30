#ifndef GL_TOOLS_HPP
#define GL_TOOLS_HPP

#include <glm/glm.hpp>
#include <glad/gl.h>

#include <unordered_map>
#include <map>

#include "FileTool.hpp"

struct Vertex{

glm::vec3 Position;
glm::vec4 Color;
glm::vec2 TextureCords;
GLfloat TextureID;
GLfloat MixRatio;
	     };

struct Quad{

std::array<Vertex, 4> Verts;	

Quad(void){}

Quad(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat TexID);

	   };

struct Shader{

GLuint GL_ID;

Shader(void){};

Shader(const char* VertShader, const char* FragShader);

	      };//Shader_Struct

struct SpriteSheet{

ImageFile Texture;

short SpriteWidth, SpriteHeight;
short SheetWidth, SheetHeight;

SpriteSheet(short SpriteSize, short SheetSize); //if equal propotions
SpriteSheet(short SpriteSize, short SheetWidth, short SheetHeight);

SpriteSheet(short SpriteWidth, short SpriteHeight, short SheetWidth, short SheetHeight);

SpriteSheet(ImageFile Texture, short SpriteWidth, short SpriteHeight);

		  };
struct Sprite{
short TX, TY;
//SpriteSheet Sheet;

//Sprite(SpriteSheet Sheet, short TX, short TY) : Sheet(Sheet), TX(TX), TY(TY){}
};

class ResMan{ //Resource Manager

ResMan(void){};

std::map<std::string, Shader> Shaders;
std::map<std::string, ImageFile> Textures;

std::map<std::string, int> UniformLocations; //std::string = ShaderName + UniformName

std::unordered_map<unsigned short, Sprite> Sprites; // Number assigned to a sprite

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
	    };//ResMan struct


#ifdef _2D_GL 
class TwoD_GL_Renderer{

std::vector<GLfloat> Vertices;

GLuint VAO;
GLuint IBO;
GLuint VBO;

static const size_t MaxQuads = 1000;
static const size_t MaxVerts = MaxQuads * 4;
static const size_t MaxIndices = MaxQuads * 6;

GLuint IndiceCount = 0;
GLuint offset = 0;

	public:

GLuint Textures[20] = {0, 1};

TwoD_GL_Renderer(void){this->Start();}

void Start(void);
void Push_Quad(Quad& Q);
void Render(void);

void MakeTextureUniform(std::string ShaderName, std::string UniformName, int NumbOfTex);

void UseMatUniform(std::string ShaderName, std::string UniformName,  glm::mat4 Matr);

};
#endif //_2D_GL

#ifdef _3D_GL
#endif//_3DGL
      //
#endif//Header
