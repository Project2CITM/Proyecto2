#ifndef __REDEROBJECT_H__
#define __REDEROBJECT_H__

#include <string>
#include "External/SDL/include/SDL.h"
#include "Point.h"

enum RenderType
{
	RENDER_TEXTURE,
	RENDER_RECT,
	RENDER_LINE,
	RENDER_CIRCLE
};

class RenderObject
{
public:

	RenderObject() {};
	~RenderObject() {};

	bool Draw(SDL_Renderer* renderer) 
	{
		switch (type)
		{
		case RenderType::RENDER_TEXTURE:

			// Temporal change texture color
			SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
			SDL_SetTextureAlphaMod(texture, color.a);

			if (section.w == 0 || section.h == 0)
			{
				if (SDL_RenderCopyEx(renderer, texture, nullptr, &destRect, rotation, NULL, flip) != 0)
				{
					printf_s("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
				}
			}
			else
			{
				if (SDL_RenderCopyEx(renderer, texture, &section, &destRect, rotation, NULL, flip) != 0)
				{
					printf_s("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
				}
			}
			return true;
			break;
		case RenderType::RENDER_RECT:

			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

			if (filled)
			{
				SDL_RenderFillRect(renderer, &destRect);
			}
			else
			{
				SDL_RenderDrawRect(renderer, &destRect);
			}
			return true;
			break;
		case RenderType::RENDER_CIRCLE:
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderDrawPoints(renderer, points, 360);
			return true;
			break;
		case RenderType::RENDER_LINE:
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
			break;
		}
	}

	void InitAsTexture(SDL_Texture* texture, iPoint pos, SDL_Rect section, float scale = 1, int layer = 1, float orderInLayer = 1,
		float rotation = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, float speedRegardCamera = 1.0f)
	{
		this->name = "texture";
		this->texture = texture;
		this->section = section;
		this->flip = flip;
		this->rotation = rotation;
		this->destRect.x = pos.x;
		this->destRect.y = pos.y;
		this->type = RENDER_TEXTURE;
		this->layer = layer;
		this->orderInLayer = orderInLayer;
		this->scale = scale;
		this->speedRegardCamera = speedRegardCamera;
	}

	void InitAsRect(SDL_Rect destRect, SDL_Color color = { 0,0,0,255 }, bool filled = true, int layer = 0, float orderInLayer = 0.0f,
		float speedRegardCamera = 1.0f)
	{
		this->name = "rect";
		this->color = color;
		this->filled = filled;
		this->destRect = destRect;
		this->type = RENDER_RECT;
		this->layer = layer;
		this->orderInLayer = orderInLayer;
		this->speedRegardCamera = speedRegardCamera;		
	}

	void InitAsCircle(iPoint pos, int radius, SDL_Color color = { 0,0,0,255 }, int layer = 0, float orderInLayer = 0.0f, 
		float speedRegardCamera = 1.0f)
	{
		this->name = "circle";
		this->radius = radius;
		this->color = color;
		this->destRect.x = pos.x;
		this->destRect.y = pos.y;
		this->type = RENDER_CIRCLE;
		this->layer = layer;
		this->orderInLayer = orderInLayer;
		this->speedRegardCamera = speedRegardCamera;
	}

	void InitAsLine(iPoint pos1, iPoint pos2, bool adjust = true, SDL_Color color = { 0,0,0,255 }, int layer = 0, float orderInLayer = 0.0f,
		float speedRegardCamera = 1.0f)
	{
		this->name = "line";
		this->color = color;
		this->pos1 = pos1;
		this->pos2 = pos2;
		this->type = RENDER_LINE;
		this->adjust = adjust;
		this->layer = layer;
		this->orderInLayer = orderInLayer;
		this->speedRegardCamera = speedRegardCamera;
	}

	void SetColor(SDL_Color color)
	{
		this->color = color;
	}

	#pragma region Global parameter
	SDL_Rect destRect = { 0,0,0,0 };
	RenderType type;
	int layer = 0;
	float orderInLayer = 0.0f;
	float scale = 1.0f;
	float speedRegardCamera = 1.0f;
	bool draw = true;
	std::string name = "null";
	SDL_Color color = { 255,255,255,255 };
	bool orderOnHeight = true;
	#pragma endregion

	#pragma region Texture parameter
	SDL_Texture* texture = nullptr;
	SDL_Rect section = { 0,0,0,0 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	float rotation = 0.0f;
	int textureCenterX = 0;
	int textureCenterY = 0;
	#pragma endregion

	#pragma region Rect parameter
	bool filled = false;
	#pragma endregion

	#pragma region Circle parameter
	int radius;
	SDL_Point points[360];
	#pragma endregion

	#pragma region Line parameter
	bool adjust = true;
	iPoint pos1 = { 0, 0};
	iPoint pos2 = { 0, 0};
	#pragma endregion
};

#endif //__REDEROBJECT_H__