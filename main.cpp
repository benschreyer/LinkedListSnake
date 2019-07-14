#pragma once
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <time.h>
#include <stdlib.h>
typedef struct LinkedListElement
{
	int x = -10;
	int y = -10;
	LinkedListElement* next = NULL;
};
LinkedListElement* getLast(LinkedListElement* s)
{
	LinkedListElement* ret = s;
	while (ret->next != NULL)
		ret = ret->next;
	return ret;
}
class LinkedListSnake : public olc::PixelGameEngine
{
public:
	int foodX;
	int foodY;
	int xV = 0;
	int yV = 0;
	int length = 1;
	double time = 0;
	LinkedListElement* snakeHead = new LinkedListElement;
	
	LinkedListSnake()
	{
		
	}
	bool OnUserCreate()
	{
		sAppName = "LinkedListSnake";
		// Called once at the start, so create things here
		//srand(time(NULL));
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(0, 0, 0));
		length = 1;
		snakeHead->next = NULL;
		snakeHead->x = 25;
		snakeHead->y = 25;
		foodX = (double)rand() / RAND_MAX * 20 + 3;
		foodY = (double)rand() / RAND_MAX * 20 + 7;
		std::cout << foodX << "__" << foodY << "\n";
		FillRect(snakeHead->x, snakeHead->y, 1, 1, olc::Pixel(0, 240, 100));
		FillRect(foodX, foodY, 1, 1, olc::Pixel(255, 80, 0));
		return true;
	}
	bool OnUserUpdate(float fElapsedTime)
	{
		time += fElapsedTime;
	if (time > .1)
		{
			time = 0;
			LinkedListElement* temp = snakeHead;

			snakeHead = getLast(snakeHead);
			FillRect(snakeHead->x, snakeHead->y, 1, 1, olc::Pixel(0, 0, 0));
			snakeHead->x = temp->x + xV;

			snakeHead->y = temp->y + yV;

	
			
			if (snakeHead->next != snakeHead)
			{
				snakeHead->next = temp;
				LinkedListElement* iter = snakeHead;
				while (iter->next != snakeHead)
					iter = iter->next;
				iter->next = NULL;
			}
			
			if (foodX == snakeHead->x && foodY == snakeHead->y)
			{
				FillRect(foodX, foodY, 1, 1, olc::Pixel(0, 240, 100));
				foodX = (double)rand() / RAND_MAX * 40 + 8;
				foodY = (double)rand() / RAND_MAX * 40 + 7;
				std::cout << foodX << "__" << foodY << "\n";
				FillRect(foodX, foodY, 1, 1, olc::Pixel(255, 80, 0));
				getLast(snakeHead)->next = new LinkedListElement;
				length++;
			}

			LinkedListElement* iter = snakeHead;

			while (iter  != NULL)
			{
				if (snakeHead != iter && snakeHead->x == iter->x && snakeHead->y == iter->y)
				{
					
					//clear memory used by body on snake death
					iter = snakeHead->next;
					while (iter != NULL)
					{
						temp = iter->next;
						delete iter;
						iter = temp;
					}
					OnUserCreate();
					break;
				}
				FillRect(iter->x, iter->y,1,1, olc::Pixel(0, 240, 100));
				iter = iter->next;
			}
		}
		// Called once at the start, so create things here
		if (GetKey(olc::W).bPressed)
		{
			xV = 0;
			yV = -1;
		}
		if (GetKey(olc::S).bPressed)
		{
			xV = 0;
			yV = 1;
		}
		if (GetKey(olc::A).bPressed)
		{
			xV = -1;
			yV = 0;
		}
		if (GetKey(olc::D).bPressed)
		{
			xV = 1;
			yV = 0;
		}
		if (GetKey(olc::B).bPressed)
		{
			for (int i = 0; i < 10; i++)
			{
				getLast(snakeHead)->next = new LinkedListElement;
				length++;
			}
		}
		return true;
	}
};
int main()
{
	LinkedListSnake demo;
	if (demo.Construct(50, 50, 20, 20))
	{
		demo.Start();
	}
	return 0;
}
