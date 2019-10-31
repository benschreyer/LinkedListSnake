
#include <windows.h>//get keyboard input
#include <iostream>
#include <time.h>// seed random
#include <stdio.h>
#include <chrono>
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
	{
		ret = ret->next;
	}
	return ret;
}

int main()
{


	

	//1d array with enough space for 25x25 grid
	char screen[25*25];
	//seed random with current time
	srand(time(NULL));
	//play the game over and over
	while (true)
	{
		// variable to store the last time
		std::chrono::milliseconds lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		int xV = 0;
		int yV = 0;
		int foodX = (double)rand() / RAND_MAX * 10 + 3;
		int foodY = (double)rand() / RAND_MAX * 10 + 7;
		LinkedListElement* snakeHead = new LinkedListElement;
		snakeHead->x = 12;
		snakeHead->y = 14;
		bool aliveState = true;
		while(aliveState)
		{
			if (GetAsyncKeyState(VK_UP))
			{
				xV = 0;
				yV = -1;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				xV = 0;
				yV = 1;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				xV = 1;
				yV = 0;
			}
			if (GetAsyncKeyState(VK_LEFT))
			{
				xV = -1;
				yV = 0;
			}
			if (std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()
				).count() - lastTime.count() > 10)
			{
				for (int i = 0; i < 25 * 25; i++)
				{
					screen[i] = ' ';
				}
				LinkedListElement* temp = snakeHead;
				snakeHead = getLast(snakeHead);
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
					foodX = (double)rand() / RAND_MAX * 10 + 8;
					foodY = (double)rand() / RAND_MAX * 10 + 7;
					getLast(snakeHead)->next = new LinkedListElement;
				}

				LinkedListElement* iter = snakeHead->next;
				bool finnish = true;
				while (iter != NULL)
				{
					if (snakeHead->x == iter->x && snakeHead->y == iter->y)
					{
						aliveState = false;
						LinkedListElement* temp;
						while (iter != NULL)
						{
							temp = iter->next;
							delete iter;
							iter = temp;
						}
						finnish = false;
						break;
						
					}
					iter = iter->next;
				}
				if (true||finnish)
				{
					iter = snakeHead;
					while (iter != NULL)
					{
						screen[iter->x + 25 * iter->y] = '@';
						iter = iter->next;
					}
					screen[foodX + foodY * 25] = '%';
					//draw game
					system("cls");
				
				
					
					for (int i = 0; i < 25; i++)
					{
						for (int j = 0; j < 25; j++)
						{
							if (GetAsyncKeyState(VK_UP))
							{
								xV = 0;
								yV = -1;
							}
							if (GetAsyncKeyState(VK_DOWN))
							{
								xV = 0;
								yV = 1;
							}
							if (GetAsyncKeyState(VK_RIGHT))
							{
								xV = 1;
								yV = 0;
							}
							if (GetAsyncKeyState(VK_LEFT))
							{
								xV = -1;
								yV = 0;
							}
							if (j == 0 || j == 24 || i == 0 || i == 24)
							{
								std::cout << '#';
							}
							else
							{
								std::cout << screen[25 * i + j];
							}
						}
						std::cout << "\n";
					}
				}
			}
			
		}
	}
}
