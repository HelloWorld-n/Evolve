#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 600;
const int segmentSize = 1;

const int gradientStart = 0.05 * screenHeight;
const int gradientEnd = 0.75 * screenHeight;
const int brightest = 200;

void handleEvents(SDL_Window *window, bool mainWindow = false){
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0){
		if (event.type == SDL_QUIT){
			SDL_DestroyWindow(window);
			SDL_Quit();
			if (mainWindow){
				std::exit(0);
			}
		}
	}
}


int enlimit(int num, int limit){
	if (num % (limit * 2) < limit){
		return num % limit;
	} else {
		return limit - (num % limit);
	}
}


int main(int argc, char* args[]) {
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error: \e48;2;0;0;0m\e[38;2;255;0;0m" << SDL_GetError() << "\e[0m;\n";
		return -418;
	}
	window = SDL_CreateWindow(
		"EvolvingSample",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		std::cerr << "Error: \e48;2;0;0;0m\e[38;2;255;0;0m" << SDL_GetError() << "\e[0m;\n";
		return -404;
	}
	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
	
	SDL_UpdateWindowSurface(window);
	for (int i = 0; i < screenHeight / segmentSize; i++){
		for (int j = 0; j < screenWidth / segmentSize; j++){
			SDL_Rect segment {
				j * segmentSize, 
				i * segmentSize, 
				segmentSize,
				segmentSize,
			};
			SDL_FillRect(
				screenSurface, 
				&segment,
				SDL_MapRGB(
					SDL_CreateRGBSurface(
						0, 
						segmentSize, 
						segmentSize, 
						32, 0, 
						0, 0, 0
					)->format, 
					/* red */ ((i < gradientEnd)?(
						(
							((i < gradientStart)?(0):(i - gradientStart))
						) * (
							brightest / std::fmax(gradientEnd - gradientStart, 1)
						)
					):(
						85 + (3 * enlimit(j, 15))
					)), 
					/* green */ ((i < gradientEnd)?(
						(
							((i < gradientStart)?(0):(i - gradientStart))
						) * (
							brightest / std::fmax(gradientEnd - gradientStart, 1)
						)
					):(
						0
					)), 
					/* blue */ ((i < gradientEnd)?(
						(
							((i < gradientStart)?(0):(i - gradientStart))
						) * (
							brightest / std::fmax(gradientEnd - gradientStart, 1)
						)
					):(
						255
					))
				)
			);
		}
	}
	while (true){
		SDL_UpdateWindowSurface(window);
		handleEvents(window, true);
	}
	return 0;
}
