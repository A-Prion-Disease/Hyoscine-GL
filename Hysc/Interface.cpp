#include "Interface.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

//temp var
//float x = 0;
//float z = 0;

SDL_Interface::SDL_Interface(int W, int H, bool& Running) : W_W(W), W_H(H), L_W(W), L_H(H){

CreateWindow(Running);
									   }


void SDL_Interface::CreateWindow(bool& Running){

if(!SDL_Init(SDL_INIT_VIDEO)){
std::cout << "Failure to init SDL_Video" << std::endl;
			    }
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

SDL_CreateWindowAndRenderer("Hyoscine-GL", W_W, W_H,
       			    Window_Flags, &Window, &Renderer
			   );
	
SDL_GLContext GL_Context = SDL_GL_CreateContext(Window);

int GL_Version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);

SDL_SetRenderLogicalPresentation(Renderer, L_W, L_H, 
			SDL_LOGICAL_PRESENTATION_OVERSCAN);

//Window Opening:

SDL_ShowWindow(Window);

Running = true;

SDL_SetRenderVSync(Renderer, 1);

keyboard_handle = SDL_GetKeyboardState(nullptr);

glViewport(0, 0, L_W, L_H);

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

glEnable(GL_CULL_FACE);
}//func

void SDL_Interface::WindowLoop(TwoD_GL_Renderer& GLR){

glClear(GL_COLOR_BUFFER_BIT);

GLR.Render();
SDL_GL_SwapWindow(Window);


			}//func

char SDL_Interface::InputCheck(bool& Running){

SDL_Event event{0};
char Input = ' ';

while(SDL_PollEvent(&event)){

	switch(event.type){

	case SDL_EVENT_QUIT:{
	Running = false;
	break;			    
			    }

	case SDL_EVENT_WINDOW_RESIZED:{

	L_W = event.window.data1;
	L_H = event.window.data2;
	
	glViewport(0, 0, L_W, L_H);
	break;
				      }
	case SDL_EVENT_KEY_DOWN:{

	if(keyboard_handle[SDL_SCANCODE_A]){
//	x -= 0.033f;
	Input = 'a';
					   }

	if(keyboard_handle[SDL_SCANCODE_D]){
//	x += 0.033f;
	Input = 'd';
					   }
	if(keyboard_handle[SDL_SCANCODE_S]){
//	z -= 0.033f;
	Input = 's';		
					   }
	if(keyboard_handle[SDL_SCANCODE_W]){
//	z += 0.033f;
	Input = 'w';
					   }
	break;
			        }

			   }//switch event.type
			     } //While_Poll
	return Input;
				}//Func

