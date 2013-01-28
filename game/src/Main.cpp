#define GLEW_STATIC // Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "GameAsset.h"
#include "Md2Asset.h"
#include "TriangularPyramidAsset.h"
#include "BallisticInterpolator.h"
#include "Camera.h"
#include "CubeAsset.h"
#include "EnvironmentAsset.h"
#include "FloorAsset.h"
#include "EnemyAsset.h"
#include "CollectAsset.h"


using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;

int health = 15; //player health
bool cameramode = false;
int playerX = 0;
int playerY = 0;
int playerZ = 1;

string filename = "data/ogre.md2";
vector<shared_ptr<GameAsset> > assets;
vector<shared_ptr<CubeAsset> > player;
vector<shared_ptr<EnemyAsset> > enemy;
vector<shared_ptr<CollectAsset> > collect;

/*
* SDL timers run in separate threads. In the timer thread
* push an event onto the event queue. This event signifies
* to call display() from the thread in which the OpenGL
* context was created.
*/
Uint32 display(Uint32 interval, void *param) {
SDL_Event event;
event.type = SDL_USEREVENT;
event.user.code = RUN_GRAPHICS_DISPLAY;
event.user.data1 = 0;
event.user.data2 = 0;
SDL_PushEvent(&event);
return interval;
}

void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // This O(n + n^2 + n) sequence of loops is written for clarity,
  // not efficiency
  for(auto it : assets) {
    it->update();
  }

  for(auto it : player) {	//player update
      it->update();
    }

  for(auto it : enemy) {	//enemy update
       it->update();
      }

  for(auto it : collect) {	//collect update
        it->update();
      }

  for(auto i : assets) {
    for(auto j : player) {
      if((i != j) && i->collidesWith(*j)) {
cout << "We have a collision" << endl;
	health--;
	cout << "Player health is: " << endl;
	cout << health << endl;

	if (health == 0)
		exit(1);
      }
    }
  }

  for(auto it : assets) {
    it->draw();
  }
  
  for(auto it : player) {	//player draw
      it->draw();
    }

  for(auto it : enemy) {	//enemy draw
        it->draw();
     }

 for(auto it : collect) {	//collect draw
        it->draw();
      }

  // Don't forget to swap the buffers
  SDL_GL_SwapBuffers();
}

int main(int argc, char ** argv) {
SDL_Surface * surf;
Uint32 width = 640;
Uint32 height = 480;
Uint32 colour_depth = 16; // in bits
Uint32 delay = 1000/60; // in milliseconds

// Initialise SDL - when using C/C++ it's common to have to
// initialise libraries by calling a function within them.
if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
SDL_Quit();
}

// When we close a window quit the SDL application
atexit(SDL_Quit);

// Create a new window with an OpenGL surface
if (!(surf = SDL_SetVideoMode(width, height, colour_depth, SDL_OPENGL))) {
cout << "Failed to initialise video mode: " << SDL_GetError() << endl;
SDL_Quit();
}

// Initialise GLEW - an easy way to ensure OpenGl 2.0+
// The *must* be done after we have set the video mode - otherwise we have no OpenGL context.
glewInit();
if (!glewIsSupported("GL_VERSION_2_0")) {
cerr<< "OpenGL 2.0 not available" << endl;
return 1;
}
glEnable(GL_DEPTH_TEST);


shared_ptr<CubeAsset> p = shared_ptr<CubeAsset> (new CubeAsset(0, -1, 0));
shared_ptr<GameAsset> j = shared_ptr<GameAsset> (new EnvironmentAsset(0, -4, 10));
shared_ptr<GameAsset> f = shared_ptr<GameAsset> (new FloorAsset(0, -4, 13));
shared_ptr<EnemyAsset> e = shared_ptr<EnemyAsset>(new EnemyAsset(2,1,2));
shared_ptr<CollectAsset> c = shared_ptr<CollectAsset>(new CollectAsset(1,1,9));

player.push_back(p);
assets.push_back(j);
assets.push_back(f);
enemy.push_back(e);
collect.push_back(c);

// Call the function "display" every delay milliseconds
SDL_AddTimer(delay, display, NULL);

// Add the main event loop



	SDL_Event event;
	while (SDL_WaitEvent(&event)) {

			switch (event.type) {
			case SDL_QUIT:
			  SDL_Quit();
			  break;
			case SDL_USEREVENT:
				display();
				break;

			case SDL_KEYUP:
			  Camera::getInstance().setCamera(Matrix4::identity());
			  break;
			case SDL_KEYDOWN:
			  Matrix4 camera = Camera::getInstance().getCameraM();
			  switch(event.key.keysym.sym){

			case SDLK_c:
				if(cameramode == false){
					cameramode = true;
					cout << "Camera on"<< endl;
				} else {
					cameramode = false;
					cout << "Camera off"<< endl;
					}
				break;

			  case SDLK_LEFT:
				if(cameramode == true){
					Camera::getInstance().setCamera((camera * Matrix4::rotationY(5.0/180.0)));
			  	} else if (cameramode == false) {
			  		playerX = playerX - 1;
			  		player[0]=shared_ptr<CubeAsset> (new CubeAsset(playerX,playerY,playerZ));

				}
				break;

			  case SDLK_RIGHT:
				  if(cameramode == true){
			    Camera::getInstance().setCamera(camera * Matrix4::rotationY(-5.0/180.0) );
			    }else {
				  playerX = playerX + 1;
				  player[0]=shared_ptr<CubeAsset> (new CubeAsset(playerX,playerY,playerZ));
			     }
				  break;

			  case SDLK_UP:
				  if(cameramode == true){
			    Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.0, -1.0)) );
			  } else {
				  playerY = playerY + 1;
				  player[0]=shared_ptr<CubeAsset> (new CubeAsset(playerX,playerY,playerZ));
			  }
				  break;

			  case SDLK_DOWN:
				  if(cameramode == true){
			    Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.0, 1.0)) );
				  } else {
				  playerY = playerY - 1;
				  player[0]=shared_ptr<CubeAsset> (new CubeAsset(playerX,playerY,playerZ));
				  }
			    break;

			  case SDLK_LCTRL:
				  if(cameramode == true){
			   Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.2, 0.0)) );
			  } else {
			  	playerZ = playerZ - 1;
			  	player[0]=shared_ptr<CubeAsset> (new CubeAsset(playerX,playerY,playerZ));
			  }
				  break;

			  case SDLK_LSHIFT:
				  if(cameramode == true){
			  	Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, -0.2, 0.0)) );
			} else {
			    playerZ = playerZ + 1;
				player[0]=shared_ptr<CubeAsset> (new CubeAsset(playerX,playerY,playerZ));
			}
				  break;

			  case SDLK_RCTRL:
				  if(cameramode == true){
			   Camera::getInstance().setCamera(camera * Matrix4::rotationX(5.0/180.0) );}
			   break;

			  case SDLK_RSHIFT:
				  if(cameramode == true){
			  	Camera::getInstance().setCamera(camera * Matrix4::rotationX(-5.0/180.0) );}
			  	break;

			  default:
			    break;
			  }
			  break;
			}
	}
}
