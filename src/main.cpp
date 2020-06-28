#include<SDL2/SDL.h>
#include<cstdio>
#include<cstring>
#include<cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned LEVEL_WIDTH = 40;
constexpr unsigned LEVEL_HEIGHT = 30;

constexpr unsigned TILE_WIDTH = WINDOW_WIDTH / LEVEL_WIDTH;
constexpr unsigned TILE_HEIGHT = WINDOW_HEIGHT / LEVEL_HEIGHT;

float cameraX = 100, cameraY = 100;
float cameraAngle = 300.0;
float cameraFOV = 60.0;
float dod = 800.0;

uint8_t level[LEVEL_WIDTH * LEVEL_HEIGHT] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

SDL_Renderer* renderer;
SDL_Renderer* renderer2;

void DrawLevel()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

	for(unsigned y = 0; y < LEVEL_HEIGHT; y++)
	{
		for(unsigned x = 0; x < LEVEL_WIDTH; x++)
		{
			if(level[y * LEVEL_WIDTH + x] == 0)
				continue;

			//SDL_RenderDrawLine(renderer, 0, 0, 800, 600);

			SDL_Rect rect;
			rect.x = x * TILE_WIDTH;
			rect.y = y * TILE_HEIGHT;
			rect.w = TILE_WIDTH;
			rect.h = TILE_HEIGHT;

			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

bool IsWall(float x, float y)
{
	int cx = x / TILE_WIDTH;
	int cy = y / TILE_HEIGHT;

	return level[cy * LEVEL_WIDTH + cx] != 0;
}

float CalculateDistance(int sx, int sy, float angle, float* normalAngle = nullptr)
{
	float raydx = cos(angle);
	float raydy = -sin(angle);

	float x = sx;
	float y = sy;

	float oldX = x;
	float oldY = y;
	for(unsigned a = 0; a < 1000; a++)
	{
		int cx = x / TILE_WIDTH;
		int cy = y / TILE_HEIGHT;

		if(cx < 0 || cy < 0 || (unsigned)cx >= LEVEL_WIDTH || (unsigned)cy >= LEVEL_HEIGHT)
			break;

		if(level[cy * LEVEL_WIDTH + cx] != 0)
		{
			if(normalAngle != nullptr)
			{
				if(IsWall(oldX + raydx, oldY))
				{
					if(raydx >= 0.0)
						*normalAngle = 180;
					else
						*normalAngle = 0;
				}
				else
				{
					if(raydy >= 0.0)
						*normalAngle = 270;
					else
						*normalAngle = 90;
				}
			}

			break;
		}

		oldX = x;
		oldY = y;
		x += raydx;
		y += raydy;
	}

	float dy = y - sy;
	float dx = x - sx;

	float dist = sqrt(dx * dx + dy * dy);

	float cameraRadian = cameraAngle / 180.0 * 3.14;
	float diffRadian = cameraRadian - angle;
	dist *= cos(diffRadian);

	return dist;
}

float DotProduct(float angleA, float angleB)
{
	float a_dx = cos(angleA);
	float a_dy = -sin(angleA);
	float b_dx = cos(angleB);
	float b_dy = -sin(angleB);

	return (a_dx * b_dx) + (a_dy * b_dy);
}

void DrawRays()
{
	float cameraCRadian = cameraAngle / 180.0 * 3.14;

	float cameraARadian = (cameraAngle - cameraFOV / 2) / 180.0 * 3.14;
	float cameraBRadian = (cameraAngle + cameraFOV / 2) / 180.0 * 3.14;

	float length = 800;

	float cameraCdx = cos(cameraCRadian);
	float cameraCdy = -sin(cameraCRadian);

	float cameraAdx = cos(cameraARadian);
	float cameraAdy = -sin(cameraARadian);

	float cameraBdx = cos(cameraBRadian);
	float cameraBdy = -sin(cameraBRadian);

	// Camera bounds
	//SDL_SetRenderDrawColor(renderer, 32, 255, 32, 255);
	//SDL_RenderDrawLine(renderer, cameraX, cameraY, cameraX + cameraCdx * length, cameraY + cameraCdy * length);

	SDL_SetRenderDrawColor(renderer, 32, 128, 32, 255);
	SDL_RenderDrawLine(renderer, cameraX, cameraY, cameraX + cameraAdx * length, cameraY + cameraAdy * length);
	SDL_RenderDrawLine(renderer, cameraX, cameraY, cameraX + cameraBdx * length, cameraY + cameraBdy * length);

	{
		int cx = cameraX / TILE_WIDTH;
		int cy = cameraY / TILE_HEIGHT;

		if(cx < 0 || cy < 0 || cx >= LEVEL_WIDTH || cy >= LEVEL_HEIGHT || level[cy * LEVEL_WIDTH + cx] != 0)
			return;
	}

	SDL_SetRenderDrawColor(renderer2, 0, 0, 0, 255);

	unsigned steps = WINDOW_WIDTH;
	float stepsDeltaAngle = (cameraBRadian - cameraARadian) / steps;
	for(unsigned a = 0; a < steps; a+=1)//20)
	{
		float angleRadian = cameraARadian + stepsDeltaAngle * a;

		float raydx = cos(angleRadian);
		float raydy = -sin(angleRadian);
		float normal;
		float length = CalculateDistance(cameraX, cameraY, angleRadian, &normal);
		float normalRadian = normal / 180.0 * 3.14;
		//printf("Normal: %f\n", normalRadian);

		float dot = fabs(DotProduct(angleRadian, normalRadian));
		//printf("Dot: %f\n", dot);

		if(length > dod)
			continue;
		//	length = dod;

		unsigned gray = 64.0 * dot;// / (3.14*2);
		SDL_SetRenderDrawColor(renderer2, gray, gray, gray, 255);
		SDL_RenderDrawLine(renderer, cameraX, cameraY, cameraX + raydx * length, cameraY + raydy * length);

		//float height = 1.0 / length * WINDOW_HEIGHT;
		//float height = WINDOW_HEIGHT - (length / dod * WINDOW_HEIGHT);
		float height = WINDOW_HEIGHT / 3 / length * (WINDOW_WIDTH / 2 / tan(cameraFOV / 2.0 * 3.14 / 180.0));
		if(height > WINDOW_HEIGHT)
			height = WINDOW_HEIGHT;
		//printf("Height: %f\n", height);
		float halfHeight = height / 2.0;

		//printf("Len: %f\n", length);
		unsigned x = WINDOW_WIDTH - a - 1;
		unsigned y = WINDOW_HEIGHT / 2  - halfHeight;
		SDL_RenderDrawLine(renderer2, x, y, x, y +  height);
	}
}

#undef main
int main(int argc, char *argv[])
{
	setbuf(stdout, nullptr);

	SDL_Window* wnd = SDL_CreateWindow("VoxRay", SDL_WINDOWPOS_CENTERED, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	SDL_Surface* srf = SDL_GetWindowSurface(wnd);
	renderer = SDL_CreateSoftwareRenderer(srf);
	SDL_ShowWindow(wnd);

	SDL_Window* wnd2 = SDL_CreateWindow("VoxRay - 3D view", SDL_WINDOWPOS_CENTERED, 150 + WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	SDL_Surface* srf2 = SDL_GetWindowSurface(wnd2);
	renderer2 = SDL_CreateSoftwareRenderer(srf2);
	SDL_ShowWindow(wnd2);

	SDL_Event event;
	bool quit = false;
	while(!quit)
	{
		while(SDL_PollEvent(&event))
		//if(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEMOTION:
					if(event.motion.windowID != SDL_GetWindowID(wnd))
						break;

					//cameraX = event.motion.x;
					//cameraY = event.motion.y;
					break;
				case SDL_MOUSEWHEEL:
					//printf("%d %d %d\n", event.wheel.x, event.wheel.y, event.wheel.direction);
					cameraAngle += event.wheel.y * 5;
					break;
				case SDL_WINDOWEVENT:
					if(event.window.event == SDL_WINDOWEVENT_CLOSE)
						quit = true;

					break;
				default:
					printf("Event type: %d\n", event.type);
					break;
			}
		}

		float speed = 1.0;
		int keysCount;
		const Uint8* keys = SDL_GetKeyboardState(&keysCount);

		if(!keys)
			return 1;

		if(keys[SDL_SCANCODE_UP])
		{
			cameraX +=  cos(cameraAngle / 180.0 * 3.14) * speed;
			cameraY += -sin(cameraAngle / 180.0 * 3.14) * speed;
		}
		if(keys[SDL_SCANCODE_DOWN])
		{
			cameraX -=  cos(cameraAngle / 180.0 * 3.14) * speed;
			cameraY -= -sin(cameraAngle / 180.0 * 3.14) * speed;
		}
		if(keys[SDL_SCANCODE_LEFT])
		{
			cameraAngle += speed / 1;
		}
		if(keys[SDL_SCANCODE_RIGHT])
		{
			cameraAngle -= speed / 1;
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(renderer2, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_RenderClear(renderer2);

		DrawLevel();
		DrawRays();

		/*Uint32* pixels = (Uint32*)srf->pixels;
		for(unsigned a = 0; a < 800; ++a)
		{
			pixels[300 * 800 + a] = 0x00ff00ff;
		}*/

		//SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		//SDL_RenderDrawLine(renderer, 0, 0, 800, 600);
		SDL_RenderPresent(renderer);
		SDL_RenderPresent(renderer2);

		SDL_UpdateWindowSurface(wnd);
		SDL_UpdateWindowSurface(wnd2);

		auto error = SDL_GetError();
		if(error != nullptr && strlen(error) > 0)
			printf("Error: %s\n", error);
	}

	SDL_DestroyWindow(wnd);
	return 0;
}
