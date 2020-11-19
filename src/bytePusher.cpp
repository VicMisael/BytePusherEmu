#include "CPU.h"


#ifdef _MSC_VER
#include <SDL.h>
#include <SDL_opengl.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif
#include <GL/gl.h>

#include <assert.h>
#include <fstream>
#include <iostream>
#include <bitset>
CPU c = CPU();
SDL_GLContext Context;
SDL_Window* Window;
SDL_AudioSpec wanted;
uint32_t palette[256];

void loadPalette() {
	//24 bits are needed for a rgb representation of each color, a 32 bit value can be used, and the other 8 bits will remain 0
	uint8_t blue, green, red;
	for (int32_t color = 0; color < 216; color++) {



		blue = color % 6;
		green = ((color) / 6) % 6;
		red = ((color) / 36) % 6;
		uint32_t _color32val = 0;//32 bit unsigned integer
		((uint8_t*)&_color32val)[0] = red; //Access 8 bits as an array
		((uint8_t*)&_color32val)[1] = green;
		((uint8_t*)&_color32val)[2] = blue;
		//0 for red, 1 for green, 2 for blue
		palette[color] = _color32val;
	}

}


void init() {
	uint32_t WindowFlags = SDL_WINDOW_OPENGL;
	Window = SDL_CreateWindow("BytePusher", 100, 100, 600, 600, WindowFlags);
	assert(Window);
	Context = SDL_GL_CreateContext(Window);
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS);
	loadPalette();
}


void loop(SDL_Window* Window) {

	SDL_Event _Event;
	SDL_AudioDeviceID _dev;
	SDL_zero(wanted);
	wanted.freq = 15360;
	wanted.samples = 256;
	wanted.format = AUDIO_S8;
	wanted.channels = 1;
	_dev = SDL_OpenAudio(&wanted, NULL);
	std::cout << SDL_GetError() << std::endl;
	std::cout << _dev << std::endl;
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glLoadIdentity();
	glOrtho(0, 256, 256, 0, -1, 1);
	SDL_PauseAudio(0);
	int run = 1;
	while (run) {
		SDL_QueueAudio(1, (int8_t*)(c.getAudioMemSection()), 256);
		c.run();
		//std::cout<<"0x"<<std::hex<< (c.getBytes(6, 2) << 8) << std::endl;
		//uint8_t blue = 0, green = 0, red = 0;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		uint8_t* _videoSegment = c.getVideoMemSection();
		for (int y = 0; y < 256; y++) {
			for (int x = 0; x < 256; x++) {
				uint8_t color = _videoSegment[x + y * 256];
				uint8_t* colorvec = (uint8_t*)&palette[color];
				glColor3f((float)colorvec[0] / 5, (float)colorvec[1] / 5, (float)colorvec[2] / 5);
				glRectf(x, y, x + 1, y + 1);
			}
		}
		SDL_GL_SwapWindow(Window);
		uint16_t _key16bit = 0;
		while (SDL_PollEvent(&_Event)) {
			switch (_Event.type) {
			case SDL_QUIT:
				run = 0;
				break;
			case SDL_KEYDOWN:
				//std::cout << "Pressed" << std::endl;

				switch (_Event.key.keysym.sym) {
				case SDLK_0:
				case SDLK_KP_0:
					_key16bit |= 1;
					break;
				case SDLK_1:
				case SDLK_KP_1:
					_key16bit |= (1 << 1);
					break;
				case SDLK_2:
				case SDLK_KP_2:
					_key16bit |= (1 << 2);
					break;
				case SDLK_3:
				case SDLK_KP_3:
					_key16bit |= (1 << 3);
					break;
				case SDLK_4:
				case SDLK_KP_4:
					_key16bit |= (1 << 4);
					break;
				case SDLK_5:
				case SDLK_KP_5:
					_key16bit |= (1 << 5);
					break;
				case SDLK_6:
				case SDLK_KP_6:
					_key16bit |= (1 << 6);
					break;
				case SDLK_7:
				case SDLK_KP_7:
					_key16bit |= (1 << 7);
					break;
				case SDLK_8:
				case SDLK_KP_8:
					_key16bit |= (1 << 8);
					break;
				case SDLK_9:
				case SDLK_KP_9:
					_key16bit |= (1 << 9);
					break;
				case SDLK_a:
					_key16bit |= (1 << 10);
					break;
				case SDLK_b:
					_key16bit |= (1 << 11);
					break;
				case SDLK_c:
					_key16bit |= (1 << 12);

					break;
				case SDLK_d:
					_key16bit |= (1 << 13);

					break;
				case SDLK_e:
					_key16bit |= (1 << 14);

					break;
				case SDLK_f:
					_key16bit |= (1 << 15);

					break;
				default:
					std::cout << _Event.key.keysym.sym << std::endl;
					break;

				}
			case SDL_KEYUP:
				//std::cout << "Pressed" << std::endl;

				switch (_Event.key.keysym.sym) {
				case SDLK_0:
				case SDLK_KP_0:
					_key16bit ^= 0;
					break;
				case SDLK_1:
				case SDLK_KP_1:
					_key16bit ^= (0 << 1);
					break;
				case SDLK_2:
				case SDLK_KP_2:
					_key16bit ^= (0 << 2);
					break;
				case SDLK_3:
				case SDLK_KP_3:
					_key16bit ^= (0 << 3);
					break;
				case SDLK_4:
				case SDLK_KP_4:
					_key16bit ^= (0 << 4);
					break;
				case SDLK_5:
				case SDLK_KP_5:
					_key16bit ^= (0 << 5);
					break;
				case SDLK_6:
				case SDLK_KP_6:
					_key16bit ^= (0 << 6);
					break;
				case SDLK_7:
				case SDLK_KP_7:
					_key16bit ^= (0 << 7);
					break;
				case SDLK_8:
				case SDLK_KP_8:
					_key16bit ^= (0 << 8);
					break;
				case SDLK_9:
				case SDLK_KP_9:
					_key16bit ^= (0 << 9);
					break;
				case SDLK_a:
					_key16bit ^= (0 << 10);
					break;
				case SDLK_b:
					_key16bit ^= (0 << 11);
					break;
				case SDLK_c:
					_key16bit ^= (0 << 12);

					break;
				case SDLK_d:
					_key16bit ^= (0 << 13);

					break;
				case SDLK_e:
					_key16bit ^= (0 << 14);

					break;
				case SDLK_f:
					_key16bit ^= (0 << 15);

					break;
				default:
					//std::cout << _Event.key.keysym.sym << std::endl;
					break;

				}
				uint8_t* pad = (uint8_t*)(&_key16bit);
				//x86 is little-endian, bytepusher is big endian, revert the function input
				//Reading the MSB first
				c.setControllers(pad[1], pad[0]);
				break;
			}
		}
		//SDL_ClearQueuedAudio(_dev);


	//SDL_PauseAudio(1);
	}
}
int main(int argc, char** argv) {
	//std::cout << "Teste" << std::endl;

	if (argc == 2) {
		std::ifstream ifs(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
		long size = ifs.tellg();
		ifs.seekg(0, std::ios::beg);
		if (ifs.is_open()) {
			char* rom = new char[size];
			ifs.read(rom, size);
			c.loadROM((uint8_t*)rom, size);
			init();
			loop(Window);
			SDL_Quit();
		}
		else {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
				"Missing file",
				"The specified file was not found",
				NULL);
			return -1;
		}
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"No file specified ",
			"Please,specify a ROM file",
			NULL);
		return -1;

		return -1;
	}
	return 0;
}
