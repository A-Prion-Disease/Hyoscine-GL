#define _2D_GL
#include "GL_Tools.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
Quad::Quad(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat TexID){

Verts[0].Position = {x, y, z};
Verts[0].Color = {0.0f, 0.0f, 0.0f, 0.0f};
Verts[0].TextureCords = {0.0f, 0.0f };
Verts[0].TextureID = TexID;
Verts[0].MixRatio = 0.0f;

Verts[1].Position = {x + size, y, z};
Verts[1].Color = {0.0f, 0.0f, 0.0f , 0.0f };
Verts[1].TextureCords = {1.0f, 0.0f };
Verts[1].TextureID = TexID;
Verts[1].MixRatio = 0.0f;

Verts[2].Position = {x + size, y + size, z};
Verts[2].Color = {0.0f, 0.0f, 0.0f , 0.0f };
Verts[2].TextureCords = { 1.0f, 1.0f};
Verts[2].TextureID = TexID;
Verts[2].MixRatio = 0.0f;

Verts[3].Position = {x, y + size, z};
Verts[3].Color = {0.0f, 0.0f, 0.0f, 0.0f};
Verts[3].TextureCords = { 0.0f, 1.0f};
Verts[3].TextureID = TexID;
Verts[3].MixRatio = 0.0f;

							  }
*/
Quad::Quad(GLfloat x, GLfloat y, GLfloat z, GLfloat size, Sprite sprite) {

SpriteAdd = &sprite;

unsigned int T_ID = sprite.SrcSheet->Tex_ID;

Verts[0].Position = {x, y, z};
Verts[0].Color = {0.0f, 0.0f, 0.0f, 0.0f};
Verts[0].TextureCords = {SpriteAdd->TexX[0], SpriteAdd->TexY[0]}; //BL
Verts[0].TextureID = T_ID;
Verts[0].MixRatio = 0.0f;

Verts[1].Position = {x + size, y, z};
Verts[1].Color = {0.0f, 0.0f, 0.0f , 0.0f };
Verts[1].TextureCords = {SpriteAdd->TexX[1], SpriteAdd->TexY[0]}; //BR 
Verts[1].TextureID = T_ID;
Verts[1].MixRatio = 0.0f;

Verts[2].Position = {x + size, y + size, z};
Verts[2].Color = {0.0f, 0.0f, 0.0f , 0.0f };
Verts[2].TextureCords = {SpriteAdd->TexX[1], SpriteAdd->TexY[1]}; //TR
Verts[2].TextureID = T_ID;
Verts[2].MixRatio = 0.0f;

Verts[3].Position = {x, y + size, z};
Verts[3].Color = {0.0f, 0.0f, 0.0f, 0.0f};
Verts[3].TextureCords = {SpriteAdd->TexX[0], SpriteAdd->TexY[1]}; //TL
Verts[3].TextureID = T_ID;
Verts[3].MixRatio = 0.0f;

							  }
//quad ^^^
//shader vvv

Shader::Shader(const char* VertShader, const char* FragShader){

GLuint Vert, Frag;

Vert = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(Vert, 1, &VertShader, NULL);
glCompileShader(Vert);

Frag = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(Frag, 1, &FragShader, NULL);
glCompileShader(Frag);

GL_ID = glCreateProgram();

glAttachShader(GL_ID, Vert);
glAttachShader(GL_ID, Frag);

glLinkProgram(GL_ID);

glDeleteShader(Vert);
glDeleteShader(Frag);
         		                                       }
//Shaders ^^^


//ResManager vvvv

Shader ResMan::AddNewShader(std::string VertPath, std::string FragPath,
			    std::string ShaderName){

	std::string Vert = ReadFile(VertPath);
	std::string Frag = ReadFile(FragPath);

	Shader S(Vert.c_str(), Frag.c_str());

	Shaders[ShaderName] = S;


	return S;

						   }

void ResMan::Use(std::string ShaderName){

glUseProgram(Shaders.at(ShaderName).GL_ID);
					}

ImageFile ResMan::AddNewImg(std::string ImgPath, std::string ImageName,
	       					 	    bool alpha){

ImageFile Img(ImgPath, alpha);

Textures[ImageName] = Img;

return Img;
								       }


void ResMan::AddSprite(unsigned short Loc, Sprite InputSprite){

Sprites[Loc] = InputSprite;
						       }

Sprite ResMan::GetSprite(unsigned short Loc){

return Sprites.at(Loc);
					  }

Shader ResMan::GetShader(std::string ShaderName){

return Shaders.at(ShaderName);	
						}

ImageFile ResMan::GetImg(std::string ImageName){

return Textures.at(ImageName);

					       }


void ResMan::AddUniform(std::string ShaderName, std::string UniformName){
	
//Map key vvv	
std::string ShaderAndUni = UniformName + " in " + ShaderName;

UniformLocations[ShaderAndUni] = glGetUniformLocation(this->GetShader(ShaderName.c_str()).GL_ID, UniformName.c_str());
								}

int ResMan::GetUniform(std::string ShaderName, std::string UniformName){

return UniformLocations.at(UniformName + " in " + ShaderName);
								       }


//SpriteSheet & Sprite


SpriteSheet::SpriteSheet(ImageFile Texture, short SpriteW, short SpriteH) :
       	SpriteWidth(SpriteW), Texture(Texture){							 

if(SpriteH == 0){ SpriteHeight = SpriteW;}
else{ SpriteHeight = SpriteH;}

SheetWidth = Texture.W;
SheetHeight = Texture.H; 

TW = (float)SheetWidth / (float) SpriteW; // 144 / 48 = 3
TH = (float)SheetHeight / (float) SpriteHeight; //144 / 48 = 3
}

Sprite::Sprite(SpriteSheet& SS, short STX, short STY){

SrcSheet = &SS;	

float TileDistX = 1.0f / (float) SS.TH;
float TileDistY = 1.0f / (float) SS.TW;	

if(STX != 0){
TexX[0] = (float)STX  / SS.TW;
}
else{ TexX[0] = 0.0f;}

TexY[0] = 1.0f - TileDistY * ((float)STY + 1.0f);

TexX[1] = TexX[0] + TileDistX;

TexY[1] = TexY[0] + TileDistY;


						    }


void ResMan::SlotTexture(GL_Renderer& GLR, int TexSlot, std::string Texture){

unsigned int ID =  this->GetImg(Texture.c_str()).GL_ID;

this->TexSlotIndex[TexSlot] = ID; 

GLR.Textures[TexSlot] = ID; 
}

#ifdef _2D_GL
void GL_Renderer::Start(void){

glGenVertexArrays(1, &VAO);

glGenBuffers(1, &VBO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);

glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVerts,
	     nullptr, GL_DYNAMIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)0);
glEnableVertexAttribArray(0);

glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat),
	       		(void*)(4 * sizeof(GLfloat)));
glEnableVertexAttribArray(1);
			
glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), 
			(void*)(7 * sizeof(GLfloat)));

glEnableVertexAttribArray(2);
// I do not think what is below this is in the right function but im leaving it for now because my old engine did it this way :/
 GLuint Indices[MaxIndices];

for(size_t i = 0; i < MaxIndices; i += 6){

        Indices[i + 0] = 0 + offset;
        Indices[i + 1] = 1 + offset;
        Indices[i + 2] = 2 + offset;

        Indices[i + 3] = 2 + offset;
        Indices[i + 4] = 3 + offset;
        Indices[i + 5] = 0 + offset;

        offset += 4;
                                         }
glCreateBuffers(1, &IBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_DYNAMIC_DRAW);
			       
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, 1000 * 11 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);

}

void GL_Renderer::MakeTextureUniform(std::string ShaderName, std::string UniformName, int NumbOfTex){

ResMan& RM = ResMan::GetInstance();

int UniLoc = RM.GetUniform(ShaderName, UniformName);

int sampler[3] = {0, 1, 2}; // Temp. may have user pass in a int array for the textures used. 

glUniform1iv(UniLoc, NumbOfTex, sampler);

					 }

void GL_Renderer::UseMatUniform(std::string ShaderName, std::string UniformName,  glm::mat4 Matr){

ResMan& RM = ResMan::GetInstance();

int UniLoc = RM.GetUniform(ShaderName, UniformName);

glUniformMatrix4fv(UniLoc, 1, GL_FALSE, &Matr[0][0]);

												      }
void GL_Renderer::Push_Quad(Quad& Q, short GroupIndice){

   for(int i = 0; i < Q.Verts.size(); i++){

        DrawGroup [GroupIndice] .push_back(Q.Verts[i].Position.x);
        DrawGroup [GroupIndice] .push_back(Q.Verts[i].Position.y);
        DrawGroup [GroupIndice] .push_back(Q.Verts[i].Position.z);

       DrawGroup [GroupIndice] .push_back(Q.Verts[i].Color.x);
       DrawGroup [GroupIndice] .push_back(Q.Verts[i].Color.y);
       DrawGroup [GroupIndice] .push_back(Q.Verts[i].Color.z);
       DrawGroup [GroupIndice] .push_back(Q.Verts[i].Color.w);

        DrawGroup [GroupIndice] .push_back(Q.Verts[i].TextureCords.x);
        DrawGroup [GroupIndice] .push_back(Q.Verts[i].TextureCords.y);

        DrawGroup [GroupIndice] .push_back(Q.Verts[i].TextureID);

       DrawGroup [GroupIndice] .push_back(Q.Verts[i].MixRatio);

                                              }
    IndiceCount[GroupIndice] += 6;
}

void GL_Renderer::Render(short GroupIndice){

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferSubData(GL_ARRAY_BUFFER, 0, DrawGroup[GroupIndice].size() * sizeof(GLfloat), DrawGroup[GroupIndice].data());

glBindTextureUnit(0, Textures[0]);
glBindTextureUnit(1, Textures[1]);
glBindTextureUnit(2, Textures[2]);
//glBindTextureUnit(3, Textures[3]);
glBindVertexArray(VAO);

glDrawElements(GL_TRIANGLES, IndiceCount[GroupIndice], GL_UNSIGNED_INT, (void*)0);

IndiceCount[GroupIndice] = 0;
DrawGroup[GroupIndice].clear();
                              }

#endif


