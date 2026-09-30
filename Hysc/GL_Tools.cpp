#define _2D_GL
#include "GL_Tools.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>


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

SpriteSheet::SpriteSheet(short SpriteSize, short SheetSize) : SpriteWidth(SpriteSize), SpriteHeight(SpriteSize), 
							      SheetWidth(SheetSize), SheetHeight(SheetSize)
							       {

	
							       }

SpriteSheet::SpriteSheet(short SpriteSize, short SheetWidth, short SheetHeight) : SpriteWidth(SpriteSize), SpriteHeight(SpriteSize),
									          SheetWidth(SheetWidth), SheetHeight(SheetHeight)
									       {

									       }

SpriteSheet::SpriteSheet(short SpriteWidth, short SpriteHeight, short SheetWidth, short SheetHeight) : SpriteWidth(SpriteWidth),
								SpriteHeight(SpriteHeight), SheetWidth(SheetWidth), SheetHeight(SheetHeight)
												    {

												    }
SpriteSheet::SpriteSheet(ImageFile Texture, short SpriteWidth, short SpriteHeight) : Texture(Texture), SpriteWidth(SpriteWidth),
       										      SpriteHeight(SpriteHeight){
Texture.W = SheetWidth; Texture.H = SheetHeight;

											      			}
#ifdef _2D_GL
void TwoD_GL_Renderer::Start(void){

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

void TwoD_GL_Renderer::MakeTextureUniform(std::string ShaderName, std::string UniformName, int NumbOfTex){

ResMan& RM = ResMan::GetInstance();

int UniLoc = RM.GetUniform(ShaderName, UniformName);

int sampler[2] = {0, 1}; // Temp. may have user pass in a int array for the textures used. 

glUniform1iv(UniLoc, NumbOfTex, sampler);

					 }

void TwoD_GL_Renderer::UseMatUniform(std::string ShaderName, std::string UniformName,  glm::mat4 Matr){

ResMan& RM = ResMan::GetInstance();

int UniLoc = RM.GetUniform(ShaderName, UniformName);

glUniformMatrix4fv(UniLoc, 1, GL_FALSE, glm::value_ptr(Matr));

												      }
void TwoD_GL_Renderer::Push_Quad(Quad& Q){

   for(int i = 0; i < Q.Verts.size(); i++){
        Vertices.push_back(Q.Verts[i].Position.x);
        Vertices.push_back(Q.Verts[i].Position.y);
        Vertices.push_back(Q.Verts[i].Position.z);

       Vertices.push_back(Q.Verts[i].Color.x);
       Vertices.push_back(Q.Verts[i].Color.y);
       Vertices.push_back(Q.Verts[i].Color.z);
       Vertices.push_back(Q.Verts[i].Color.w);

        Vertices.push_back(Q.Verts[i].TextureCords.x);
        Vertices.push_back(Q.Verts[i].TextureCords.y);

        Vertices.push_back(Q.Verts[i].TextureID);

       Vertices.push_back(Q.Verts[i].MixRatio);

                                              }
    IndiceCount += 6;
}

void TwoD_GL_Renderer::Render(void){

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferSubData(GL_ARRAY_BUFFER, 0, Vertices.size() * sizeof(GLfloat), Vertices.data());

glBindTextureUnit(0, Textures[0]);
glBindTextureUnit(1, Textures[1]);
glBindVertexArray(VAO);

glDrawElements(GL_TRIANGLES, IndiceCount, GL_UNSIGNED_INT, (void*)0);

IndiceCount = 0;
Vertices.clear();
                              }

#endif


